/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 12:18:23 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/21 15:46:37 by ahmaymou         ###   ########.fr       */
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
	word,
	trunc,
	here_doc,
	in_redir,
	delimiter,
	in_file,
	append,
	out_file,
	Pipe,
	_delimiter
}			t_type;

extern int	g_exit_status;

void	prompt(void);
t_list	*pars_error(char *str);
void	print_error(char c);
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
void	expand_variables(t_list *head, int pos);
void	expand_multi_vars(t_list **head);
void	check_and_expand(t_list *tmp);
int		count_tokens(const char *str);
char	**split_string(const char *str, int in_quotes, int num_tokens);
char	*extract_token(const char *start, const char *str);
void	remove_quotes(char *str);
void	remove_quotes_node(t_list **temp);
t_list	*create_final_list(t_list **head);
void	free_node(t_list **node, int to_free);
void	print_list(t_list *list, bool flag);
int		open_fill(t_list **head, t_list **temp, int i);
int		open_out_file(t_list **head, t_list **temp, char *file_name);
int		open_files(t_list **head, t_list **temp);
int		count_delimiter(t_list *temp);
t_type	which_delimiter(char *str);
void	finish_node(t_list **final, t_list *temp, int i);
int		count_commands(t_list *temp);
int		fill_check_final(char *inpstr, t_list **final, t_list **command);

#endif