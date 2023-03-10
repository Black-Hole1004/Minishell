/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 12:08:20 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/10 20:31:22 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*temp function */

void	print_list(char *str, t_list *list)
{
	t_list	*current;

	current = list;
	printf("After tokenisation: of str %s\n", str);
	while (current)
	{
		printf("{%s:%d}", (char *)current->content, current->type);
		if (current->next)
			printf("->");
		current = current->next;
	}
}

void	assign_type(t_list *command)
{
	t_list	*temp;
	char	*cmd;

	temp = command;
	while (temp)
	{
		cmd = (char *)temp->content;
		if (!ft_strcmp(cmd, "|"))
			temp->type = Pipe;
		else if (!ft_strcmp(cmd, "<"))
			temp->type = in_redir;
		else if (!ft_strcmp(cmd, "<<"))
			temp->type = here_doc;
		else if (!ft_strcmp(cmd, ">"))
			temp->type = trunc;
		else if (!ft_strcmp(cmd, ">>"))
			temp->type = append;
		else
			temp->type = word;
		temp = temp->next;
	}
}

void	fill_list(char *inputString, t_list **head)
{
	int		end_word;
	char	*word;

	if (!(*inputString))
		return ;
	if (*inputString == ' ')
	{
		while (*inputString == ' ')
			inputString++;
		fill_list(inputString, head);
	}
	else
	{
		end_word = end_word_index(inputString);
		if (end_word == -1)
		{
			word = ft_strtrim(ft_strdup(inputString), " ");
			ft_lstadd_back(head, ft_lstnew(word));
			return ;
		}
		word = ft_strtrim(ft_substr(inputString, 0, end_word), " ");
		ft_lstadd_back(head, ft_lstnew(word));
		fill_list(inputString + end_word, head);
	}
}

int	pars_error(char *str)
{
	t_list	*command;

	command = NULL;
	str = ft_strtrim(str, " ");
	if (*str == '|' || *str == ';' || *str == '>'  || *str == '<')
	{
		printf("minishell: syntax error near unexpected token `%c'\n", *(str));
		return (1);
	}
	else if (*(str + ft_strlen(str) - 1) == '|' || *(str + ft_strlen(str) - 1) == ';'
		|| *(str + ft_strlen(str) - 1) == '>' || *(str + ft_strlen(str) - 1) == '<')
	{
		printf("minishell: syntax error near unexpected token `\\n'\n");
		return (1);
	}
	if (!count_quotes(str))
	{
		printf("minishell: syntax error, unclosed quotes\n");
		return (1);
	}
	fill_list(str, &command);
	assign_type(command);
	command = check_join(command);
	print_list(str, command);
	printf("\n");
	return (0);
}

void	prompt(void)
{
	char	*str;

	signal(SIGINT, handle_kill);
	signal(SIGQUIT, handle_kill);
	while (1)
	{
		str = readline("\033[1;32mminishell> \033[0m");
		if (!str || !ft_strncmp(str, "exit", 4))
		{
			clear_history();
			exit(1);
		}
		if (!ft_strncmp(str, "cd", 2))
			chdir(str + 3);
		else if (!ft_strncmp(str, "pwd", 3))
			printf("%s\n", getcwd(NULL, 0));
		if (!pars_error(str))
			add_history(str);
	}
}
