/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackhole <blackhole@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:54:39 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/19 17:09:54 by blackhole        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	if (quote == 0)
		quote = str[i];
	else if (quote == str[i])
		quote = 0;*/
int count_tokens(const char* str)
{
	int count;
	int in_quotes;
	const char* p;

	in_quotes = 0;
	p = str;
	count = 0;
	while (*p != '\0')
	{
		if (*p == '\"' || *p == '\'')
		{
			if (in_quotes == 0)
				in_quotes = *p;
			else if (in_quotes == *p)
				in_quotes = 0;
		}
		else if (*p == ' ' && !in_quotes)
			count++;
		p++;
	}
	return (count + 1);
}

char*	extract_token(const char* start, const char *str)
{
	char* 	token;
	int		len;

	len = str - start;
	token = malloc((len + 1) * sizeof(char));
	ft_strncpy(token, start, len);
	token[len] = '\0';
	return token;
}

char**	split_string(const char* str)
{
	int			num_tokens;
	int			in_quotes;
	const char*	start;
	char**		tokens;

	in_quotes = 0;
	num_tokens = 0;
	tokens = malloc(count_tokens(str) * sizeof(char*));
	start = &str[0];
	while (*str != '\0')
	{
		if (*str == '\'' || *str == '\"')
		{
			if (in_quotes == 0)
				in_quotes = *str;
			else if (in_quotes == *str)
				in_quotes = 0;
		}
		else if (*str == ' ' && !in_quotes)
		{
			tokens[num_tokens] = extract_token(start, str);
			start = str + 1;
			num_tokens++;
		}
		str++;							
	}
	// tokens[num_tokens] = extract_token(start, str);
	return (tokens[num_tokens] = NULL, tokens);
}
