/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_cmds_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 22:30:00 by arabiai           #+#    #+#             */
/*   Updated: 2023/03/23 22:31:24 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_process(int pipe_ends[2])
{
	close(pipe_ends[1]);
	dup2(pipe_ends[0], STDIN_FILENO);
	close(pipe_ends[0]);
}

void create_pipe(int pipe_ends[2])
{
	if (pipe(pipe_ends) == -1)
	{
		perror("minishell: pipe:");
		exit(EXIT_FAILURE);
	}
}

pid_t my_fork(t_infos *infos, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork:");
		exit(EXIT_FAILURE);
	}
	infos->pids[i] = pid;
	return (pid);
}
