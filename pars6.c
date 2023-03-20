/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:23:00 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/20 21:42:36 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_node(t_list **node, int to_free)
{
	t_list	*temp;
	int		i;

	i = -1;
	temp = (*node)->next;
	if ((*node)->content && to_free)
		free((*node)->content);
	// while ((*node)->delims[++i].delimiter)
	// 	free((*node)->delims[i].delimiter);
	free((*node));
	(*node) = temp;
}

int	count_commands(t_list *temp)
{
	int	count;

	count = 0;
	while (temp)
	{
		if (temp->type == Pipe)
			count++;
		temp = temp->next;
	}
	return (count + 1);
}

t_type	which_delimiter(char *str)
{
	if (ft_strchr(str, '\"') || ft_strchr(str, '\''))
		return (_delimiter);
	else
		return (delimiter);
}

int	open_out_file(t_list **head, t_list **temp, char *file_name)
{
	if ((*temp)->out_fd != -2 && !(*temp)->_errno)
		close((*temp)->out_fd);
	if ((*head)->prev->type == trunc && !(*temp)->_errno)
		(*temp)->out_fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if ((*head)->prev->type == append && !(*temp)->_errno)
		(*temp)->out_fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if ((*temp)->out_fd == -1 && !(*temp)->_errno)
		return (free((*temp)->out_file)
			, (*temp)->out_file = file_name, (*temp)->_errno = errno, 1);
	if (!(*temp)->_errno)
	{
		if ((*temp)->out_file)
			free((*temp)->out_file);
		(*temp)->out_file = file_name;
	}
	else
		free(file_name);
	return (0);
}

int	open_files(t_list **head, t_list **temp)
{
	char	*file_name;

	file_name = (*head)->content;
	remove_quotes(file_name);
	if ((*head)->prev->type == in_redir)
	{
		if ((*temp)->in_fd != -2 && !(*temp)->_errno)
			close((*temp)->in_fd);
		if (!(*temp)->_errno)
			(*temp)->in_fd = open(file_name, O_RDONLY);
		if ((*temp)->in_fd == -1 && !(*temp)->_errno)
			return (free((*temp)->in_file)
				, (*temp)->in_file = file_name, (*temp)->_errno = errno, 1);
		if (!(*temp)->_errno)
		{
			if ((*temp)->in_file)
				free((*temp)->in_file);
			(*temp)->in_file = file_name;
		}
		else
			free(file_name);
	}
	else
		return (open_out_file(head, temp, file_name));
	return (0);
}

int	count_delimiter(t_list *temp)
{
	int	count;

	count = 0;
	while (temp && temp->type != Pipe)
	{
		if (temp->type == delimiter)
			count++;
		temp = temp->next;
	}
	return (count + 1);
}

int	open_fill(t_list **head, t_list **temp, int i)
{
	if ((*head)->type == in_file || (*head)->type == out_file)
		open_files(head, temp);
	else if ((*head)->type == delimiter)
	{
		(*temp)->delims[++i].type = which_delimiter((*head)->content);
		(*temp)->delims[i].delimiter = (*head)->content;
	}
	if (*head)
		free_node(head, ((*head)->type != delimiter
				&& (*head)->type != in_file && (*head)->type != out_file));
	(*temp)->type = word;
	return (i);
}

void	remove_quotes(char *str)
{
	int	i;
	int	j;
	int	quote;

	i = -1;
	j = 0;
	quote = 0;
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			if (quote == 0)
				quote = str[i];
			else if (quote == str[i])
				quote = 0;
			else
				str[j++] = str[i];
		}
		else
			str[j++] = str[i];
	}
	str[j] = '\0';
}

void	finish_node(t_list **final, t_list *temp, int i)
{
	if (i == -1)
	{
		free(temp->delims);
		temp->delims = NULL;
	}
	else
		temp->delims[++i].delimiter = NULL;
	remove_quotes_node(&temp);
	ft_lstadd_back(final, temp);
}

void	get_node(t_list **head, t_list **final)
{
	t_list	*temp;
	int		i;

	temp = ft_lstnew(ft_strdup("", 0));
	i = -1;
	if (*head && (*head)->type == Pipe)
		free_node(head, 1);
	temp->delims = malloc(count_delimiter(*head) * sizeof(t_delim));
	while ((*head) && (*head)->type != Pipe)
	{
		if ((*head)->type == word)
		{
			temp->content = ft_strjoin(temp->content, (*head)->content, 1);
			temp->content = ft_strjoin(temp->content, " ", 1);
		}
		i = open_fill(head, &temp, i);
		if (i == -2)
		{
			i = -1;
			break ;
		}
	}
	finish_node(final, temp, i);
}

void	remove_quotes_node(t_list **temp)
{
	int	i;
	int	in_quotes;
	int	num_tokens;

	i = -1;
	in_quotes = 0;
	num_tokens = 0;
	printf("content :%s\n", (*temp)->content);
	(*temp)->commands = split_string((*temp)->content, in_quotes, num_tokens);
	if ((*temp)->commands && (*temp)->commands[0]
		&& ft_strcmp((*temp)->commands[0], "export"))
	{
		while ((*temp)->commands[++i])
			remove_quotes((*temp)->commands[i]);
	}
	i = -1;
	if ((*temp)->delims)
	{
		while ((*temp)->delims[++i].delimiter)
			remove_quotes((*temp)->delims[i].delimiter);
	}
}

t_list	*create_final_list(t_list **head)
{
	t_list	*final;
	int		count;

	final = NULL;
	count = count_commands(*head);
	printf("count :%d\n", count);
	while (count--)
		get_node(head, &final);
	return (final);
}
