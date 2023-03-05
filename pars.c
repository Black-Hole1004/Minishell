/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 12:08:20 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/05 15:16:51 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// bool	reprompt = false;

// void	handle_kill(int sig)
// {
// 	// bool	*rep;
// 	// (void)info;
// 	// (void)reprompt;
// 	(void)sig;
// 	if (sig == SIGINT)
// 	{
// 		reprompt = true;
// 		write(1, "gdf\n", 4);
// 		// prompt();
// 	}
// }

// char	**get_envpath(char **envp)
// {
// 	int	i;

// 	i = 0;
// 	while (envp[i] != NULL && ft_strnstr(envp[i], "PATH", 4) == NULL)
// 		i++;
// 	if (envp[i] == NULL)
// 		return (NULL);
// 	return (ft_split(envp[i] + 5, ':'));
// }

// char	*get_command_path(char **paths, char **main_cmd)
// {
// 	int		i;
// 	char	*str;
// 	char	*cmd;

// 	i = 0;
// 	cmd = ft_strjoin("/", main_cmd[0]);
// 	if (access(main_cmd[0], F_OK | X_OK) == 0)
// 		return (free(cmd), main_cmd[0]);
// 	while (paths[i] != NULL)
// 	{
// 		str = ft_strjoin(paths[i], cmd);
// 		if (access(str, F_OK) == 0)
// 			break ;
// 		i++;
// 		free(str);
// 	}
// 	if (paths[i] == NULL)
// 		return (free(cmd),  NULL);
// 	else
// 		return (free(cmd), str);
// }

bool	count_quotes(char *str)
{
	bool	d_is_opened;
	bool	s_is_opened;

	d_is_opened = 0;
	s_is_opened = 0;
	while (*str)
	{
		if (*str == '"')
			d_is_opened = !d_is_opened;
		else if (!ft_strncmp(str, "'", 1) && !d_is_opened)
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
