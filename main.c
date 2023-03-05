/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 12:24:53 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/05 20:39:50 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int main()
{
	// (void)av;
	// struct sigaction	sa;
	pwd();
	change_dir("/Users/ahmaymou/Desktop");
	pwd();
	change_dir("/Users/ahmaymou/Desktop/Minishell");
	pwd();
	prompt();
	prompt();
	// sa.sa_sigaction = handle_kill;
	// sigaction(SIGINT, &sa, NULL);
	// while (1);
}