/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 12:08:20 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/14 19:25:47 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*temp function */

void	print_list(t_list *list)
{
	t_list	*current;
	int		i = -1;

	current = list;
	printf("After tokenisation: of str\n");
	while (current)
	{
		printf("{%s:%d}\nSplitted command:\n", current->content, current->type);
		current->commands = split_string(current->content);
		while (current->commands[++i])
			printf("tmp->commands[%d] = %s\n", i, current->commands[i]);
		if (current->next)
			printf("->");
		current = current->next;
	}
	printf("\n");
}

t_type	what_type(char *cmd)
{
	if (!ft_strncmp(cmd, "|", 1))
		return (Pipe);
	else if (!ft_strncmp(cmd, "<<", 2))
		return (here_doc);
	else if (!ft_strncmp(cmd, "<", 1))
		return (in_redir);
	else if (!ft_strncmp(cmd, ">>", 2))
		return (append);
	else if (!ft_strncmp(cmd, ">", 1))
		return (trunc);
	else
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
		else if (temp->prev && temp->type == word && (temp->prev->type == trunc || temp->prev->type == append))
			temp->type = out_file;
		else if (temp->prev && temp->type == word && temp->prev->type == here_doc)
			temp->type = delimiter;
		temp = temp->next;
	}
}

int	fill_list(char *inputString, t_list **head)
{
    char	*temp;
    int		end_word;
	int		redir_count;
	t_list	*temp2;

	temp2 = NULL;
	redir_count = 0;
    while (*inputString)
    {
		if (!(redir_count % 2))
			redir_count = 0;
        if (*inputString == ' ')
            while (*inputString == ' ')
                inputString++;
        else
        {
            end_word = end_word_index(inputString);
            temp = ft_substr(inputString, 0, end_word);
			if (what_type(temp) == in_redir || what_type(temp) == trunc
				|| what_type(temp) == append || what_type(temp) == here_doc)
				redir_count++;
			add_or_join(head, temp, &temp2, &redir_count);
            if (end_word == -1)
                return (free(temp), 0);
            free(temp);
            inputString += end_word;
        }
    }
	return (expand_multi_vars(head), 0);
}

int	pars_error(char *str)
{
	t_list	*command;
	char	*inpStr;

	command = NULL;
	inpStr = ft_strtrim(str, " ");
	if (*inpStr == '|' || *inpStr == ';')
	{
		printf("minishell: syntax error near unexpected token `%c'\n", *(str));
		return (free(inpStr), 1);
	}
	else if (*(inpStr + ft_strlen(inpStr) - 1) == '|' || *(inpStr + ft_strlen(inpStr) - 1) == ';'
		|| *(inpStr + ft_strlen(inpStr) - 1) == '>' || *(inpStr + ft_strlen(inpStr) - 1) == '<')
	{
		printf("minishell: syntax error near unexpected token `\\n'\n");
		return (free(inpStr), 1);
	}
	if (!count_quotes(str))
	{
		printf("minishell: syntax error, unclosed quotes\n");
		return (free(inpStr), 1);
	}
	fill_list(inpStr, &command);
	assign_type(command);
	print_list(command);
	if (check_pars_errors(command))
		return (free(inpStr), ft_lstclear(&command), 1);
	return (free(inpStr), ft_lstclear(&command), 0);
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
