/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackhole <blackhole@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 12:18:23 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/18 01:28:38 by blackhole        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <ctype.h>
# include <readline/history.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/errno.h>
# include "libft/libft.h"

typedef enum TYPE
{
	word,/*0*/
	trunc,/*1*/
	here_doc,/*2*/
	in_redir,/*3*/
	delimiter,/*4*/
	in_file,/*5*/
	append,/*6*/
	out_file,/*7*/
	Pipe,/*8*/
	_delimiter/*9*/
}			t_type;

void	prompt(void);
void	print_error(char c);
void	echo(char *str, bool option);
void	pwd(void);
void	change_dir(char *path);
void	handle_kill(int sig);
bool	count_quotes(char *str);
int		end_word_index(char *str);
bool	is_spec(char str);
int		end_word_index(char *str);
void	add_or_join(t_list **head, char *temp, t_list **temp2, int *redir_c);
void	assign_type(t_list *command);
t_type	what_type(char *cmd);
int		check_pars_errors(t_list *command);
int		check_pars_syntax(char *str);
int		check_pars_erros2(t_list *temp, char *str);
void	expand_variables(t_list *head);
void	expand_multi_vars(t_list **head);
bool	is_expandable(char *str);
int		count_tokens(const char* str);
char**	split_string(const char* str);
char*	extract_token(const char* start, const char *str);
t_list	*create_final_list(t_list **head);

#endif