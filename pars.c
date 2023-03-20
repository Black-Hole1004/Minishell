/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 12:08:20 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/20 22:13:44 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*temp function */

void    print_list(t_list *list, bool flag)
{
    t_list    *current;

    current = list;
    int i = -1;
    printf("After tokenisation: of str\n");
    while (current)
    {
        i = 0;
        printf("*-------------------------------*\n");
        printf("{content:%s}\n", current->content);
        printf("{type:%d}\n", current->type);
        printf("{in_fd:%d}\n", current->in_fd);
        printf("{out_fd:%d}\n", current->out_fd);
        printf("{in_file:%s}\n", current->in_file);
        printf("{out_file:%s}\n", current->out_file);
        printf("{_errno:%d / %s}\n", current->_errno, strerror(current->_errno));
        printf("{delims:%p}\n", current->delims);
        if (flag)
        {
			// printf("delims[0]:%p\n", current->delims[0].delimiter);
			// printf("delims[0]:%p\n", current->delims[1].delimiter);
			// printf("delims[0]:%p\n", current->delims[2].delimiter);
            if (current->delims)
			{
                while (current->delims[i].delimiter != NULL)
				{
                    printf("(delim :%d: %s)\n", i, current->delims[i].delimiter);
					i++;
				}
				
			}
            
        }
        //print char **commands in list
        if (current->commands)
        {
            int j = -1;
            while (current->commands[++j])
                printf("commands[%d] = [%s]\n", j, current->commands[j]);
        }
        if (current->next)
            printf("->");
        current = current->next;
    }
}

t_type	what_type(char *cmd)
{
	if (!ft_strncmp(cmd, "|", 1))
		return (Pipe);
	else if (ft_strlen(cmd) > 1 && !ft_strncmp(cmd, "<<", 2))
		return (here_doc);
	else if (ft_strlen(cmd) > 1 && !ft_strncmp(cmd, ">>", 2))
		return (append);
	else if (!ft_strncmp(cmd, "<", 1))
		return (in_redir);
	else if (!ft_strncmp(cmd, ">", 1))
		return (trunc);
	return (word);
}

void	assign_type(t_list *command)
{
	char	*cmd;
	t_list	*temp;

	temp = command;
	while (temp)
	{
		cmd = temp->content;
		temp->type = what_type(cmd);
		if (temp->prev && temp->type == word && temp->prev->type == in_redir)
			temp->type = in_file;
		else if (temp->prev && temp->type == word
			&& (temp->prev->type == trunc || temp->prev->type == append))
			temp->type = out_file;
		else if (temp->prev && temp->type == word
			&& temp->prev->type == here_doc)
			temp->type = delimiter;
		temp = temp->next;
	}
}

void	init(bool *d_q, bool *s_q, int *i, int *j)
{
	*i = 0;
	*j = 0;
	*d_q = false;
	*s_q = false;
}

void	remove_instant_quotes(char *str)
{
	int		i;
	bool	s_quote;
	bool	d_quote;
	int		j;

	init(&d_quote, &s_quote, &i, &j);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if (!s_quote && str[i + 1] && str[i + 1] == str[i] && !d_quote)
				i += 2;
			else
			{
				str[j++] = str[i++];
				if (str[i] == '\'')
					s_quote = !s_quote;
				else
					d_quote = !d_quote;
			}
		}
		else
			str[j++] = str[i++];
	}
	str[j] = '\0';
}

int	fill_list(char *inputString, t_list **head)
{
	char		*temp;
	int			end_word;
	int			red_c;
	t_list		*temp2;

	temp2 = NULL;
	red_c = 0;
	while (*inputString)
	{
		while (*inputString == ' ')
			inputString++;
		end_word = end_word_index(inputString);
		temp = ft_substr(inputString, 0, end_word);
		if (what_type(temp) == in_redir || what_type(temp) == trunc
			|| what_type(temp) == append)
			red_c++;
		add_or_join(head, temp, &temp2, &red_c);
		if (end_word == -1)
			return (free(temp), 0);
		free(temp);
		inputString += end_word;
	}
	return (0);
}

void	free_final_list(t_list *final)
{
	t_list	*temp;
	int		i;

	while (final)
	{
		i = -1;
		temp = final->next;
		free(final->content);
		while (final->commands[++i])
			free(final->commands[i]);
		if (final->commands)
			free(final->commands);
		i = -1;
		if (final->delims)
		{
			while (final->delims[++i].delimiter)
				free(final->delims[i].delimiter);
			free(final->delims);
		}
		if (final->in_file)
			free(final->in_file);
		if (final->out_file)
			free(final->out_file);
		free(final);
		final = temp;
	}
}

int	fill_check_final(char *inpstr, t_list **final, t_list **command)
{
	fill_list(inpstr, command);
	assign_type(*command);
	if (check_pars_errors(*command))
		return (free(inpstr), ft_lstclear(command), 1);
	expand_multi_vars(command);
	*final = create_final_list(command);
	print_list(*final, 1);
	return (0);
}

t_list	*pars_error(char *str)
{
	t_list	*command;
	t_list	*final;
	char	*inpstr;

	command = NULL;
	inpstr = ft_strtrim(str, " ");
	printf("str : %s\n", inpstr);
	if (!inpstr || !*inpstr)
		return (free(inpstr), NULL);
	if (*inpstr == '|' || *inpstr == ';')
		return (print_error(*inpstr), free(inpstr), NULL);
	else if (*(inpstr + ft_strlen(inpstr) - 1) == '|'
		|| *(inpstr + ft_strlen(inpstr) - 1) == ';'
		|| *(inpstr + ft_strlen(inpstr) - 1) == '>'
		|| *(inpstr + ft_strlen(inpstr) - 1) == '<')
		return (print_error('\n'), free(inpstr), NULL);
	if (!count_quotes(inpstr))
	{
		printf("minishell: syntax error, unclosed quotes\n");
		return (free(inpstr), NULL);
	}
	if (fill_check_final(inpstr, &final, &command))
		return (NULL);
	return (free(inpstr), free_final_list(final), final);
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
		pars_error(str);
		add_history(str);
		free(str);
	}
}
