/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 02:53:12 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/04/03 02:53:15 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_kill(int sig)
{
	if (sig == SIGINT && g_g.g_heredoc_cmd == 0)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGINT)
		write(1, "\n", 1);
	g_g.g_heredoc_cmd = 0;
	if (sig == SIGQUIT)
		return ;
}

void	handle_signal(int signal)
{
	if (signal == SIGINT)
		exit(EXIT_FAILURE);
}

void	handle2(int status)
{
	if (WTERMSIG(status) == SIGTERM)
		ft_printf(2, "Terminated: %d\n", SIGTERM);
	else if (WTERMSIG(status) == SIGTRAP)
		ft_printf(2, "Trace/breakpoint trap: %d\n", SIGTRAP);
	else if (WTERMSIG(status) == SIGSYS)
		ft_printf(2, "Bad system call: %d\n", SIGSYS);
	else if (WTERMSIG(status) == SIGXCPU)
		ft_printf(2, "CPU time limit exceeded: %d\n", SIGXCPU);
	else if (WTERMSIG(status) == SIGXFSZ)
		ft_printf(2, "File size limit exceeded: %d\n", SIGXFSZ);
	else if (WTERMSIG(status) == SIGPIPE)
		ft_printf(2, "Broken pipe: %d\n", SIGPIPE);
	else if (WTERMSIG(status) == SIGALRM)
		ft_printf(2, "Alarm clock: %d\n", SIGALRM);
	else if (WTERMSIG(status) == SIGVTALRM)
		ft_printf(2, "Virtual alarm clock: %d\n", SIGVTALRM);
	else if (WTERMSIG(status) == SIGPROF)
		ft_printf(2, "Profiling alarm clock: %d\n", SIGPROF);
}

void	handle_execve_signal_errors(int status)
{
	if (WIFEXITED(status))
		g_g.g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		g_g.g_exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGSEGV)
			ft_printf(2, "Segmentation fault: %d\n", SIGSEGV);
		else if (WTERMSIG(status) == SIGABRT)
			ft_printf(2, "Abort: %d\n", SIGABRT);
		else if (WTERMSIG(status) == SIGFPE)
			ft_printf(2, "Floating point exception: %d\n", SIGFPE);
		else if (WTERMSIG(status) == SIGILL)
			ft_printf(2, "Illegal instruction: %d\n", SIGILL);
		else if (WTERMSIG(status) == SIGBUS)
			ft_printf(2, "Bus error: %d\n", SIGBUS);
		else if (WTERMSIG(status) == SIGQUIT)
			ft_printf(2, "Quit: %d\n", SIGQUIT);
		else if (WTERMSIG(status) == SIGKILL)
			ft_printf(2, "Killed: %d\n", SIGKILL);
		handle2(status);
	}
}
