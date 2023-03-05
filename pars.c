/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 12:08:20 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/05 19:28:47 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	handle_kill(int sig)
{
	(void)sig;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_clear_history();
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		return ;
}

bool	count_quotes(char *str)
{
	bool	d_is_opened;
	bool	s_is_opened;

	d_is_opened = 0;
	s_is_opened = 0;
	while (*str)
	{
		if (*str == 34)
			d_is_opened = !d_is_opened;
		else if (*str == 39 && !d_is_opened)
			s_is_opened = !s_is_opened;
		str++;
	}
	if (!d_is_opened && !s_is_opened)
		return (1);
	else
		return (0);
}

int	pars_error(char *str)
{
	if (*str == '|' || *(str + ft_strlen(str) - 1) == '|')
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	if (!count_quotes(str))
	{
		printf("minishell: syntax error, unclosed quotes\n");
		return (1);
	}
	else
		return (0);
}

void    prompt()
{
	char	*str;

	signal(SIGINT, handle_kill);
	signal(SIGQUIT, handle_kill);
	while (1) {
		str = readline("\033[1;32mminishell> \033[0m");
		if (!str || !ft_strncmp(str, "exit", 4))
		{
			clear_history();
			exit(1);
		}
		if (!pars_error(str))
			add_history(str);
	}
}
