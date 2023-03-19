/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackhole <blackhole@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:13:54 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/19 23:17:54 by blackhole        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_variable(char *str)
{
	int		i;
	char	*var;
	char	*var2;
	char	*value;

	i = 0;
	if (ft_isdigit(str[1]))
		var = ft_substr(str, 1, 1);
	else
	{
		while (str[i + 1] && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
			i++;
		var = ft_substr(str, 1, i);
	}
	var2 = ft_substr(str, ft_strlen(var) + 1, ft_strlen(str) - ft_strlen(var));
	value = getenv(var);
	if (!value)
		value = ft_strdup("", 0);
	value = ft_strjoin(value, var2, 0);
	free(var);
	free(var2);
	return (value);
}

int	var_exist(char *str)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			if (ft_isalnum(str[i + 1]) || str[i + 1] == '_')
				count++;
		}
	}
	return (count);
}

void	expand_variables(t_list *tmp, int pos)
{
	char	*value;
	char	*tmp_str;
	int		i;

	i = pos;
	tmp_str = ft_substr((tmp->content), 0, i);
	value = get_variable((tmp->content) + i);
	free(tmp->content);
	tmp->content = ft_strjoin(tmp_str, value, 1);
	free(value);
}

void	remove_spaces(char *str)
{
	int		i;
	int		j;
	char	*tmp;
	bool	quote;

	i = 0;
	j = 0;
	tmp = ft_strdup(str, 0);
	quote = false;
	while (tmp[i])
	{
		if (tmp[i] == '\"' || tmp[i] == '\'')
			quote = !quote;
		if (tmp[i] == ' ' && tmp[i + 1] == ' ' && !quote)
			i++;
		else
			str[j++] = tmp[i++];
	}
	str[j] = '\0';
	free(tmp);
}

void	expand_multi_vars(t_list **head)
{
	t_list	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp->prev && tmp->prev->type == here_doc)
			tmp = tmp->next;
		if (tmp)
		{
			check_and_expand(tmp);
			remove_spaces(tmp->content);
			tmp = tmp->next;
		}
	}
}

void	check_and_expand(t_list *tmp)
{
	int		i;
	int		quote;
	char	*str;

	i = -1;
	quote = 0;
	str = tmp->content;
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			if (quote == 0)
				quote = str[i];
			else if (quote == str[i])
				quote = 0;
		}
		if (str[i] == '$' && (!quote || quote == '\"')
			&& str[i + 1] && (ft_isalnum(str[i + 1])
			|| str[i + 1] == '_'))
		{
			expand_variables(tmp, i);
			str = tmp->content;
			i = -1;
			quote = 0;
		}
	}
}
