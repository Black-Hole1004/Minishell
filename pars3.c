/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:09:49 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/10 20:43:32 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_words(t_list **command, t_list **to_return)
{
	// char *temp;

	// temp = (*command)->content;
	if ((*command)->next && (*command)->next->type == word)
	{
		(*command)->content = ft_strjoin((*command)->content, " ");
		(*command)->content = ft_strjoin((*command)->content, (*command)->next->content);
		(*command)->next = (*command)->next->next;
	}
	else
	{
		ft_lstadd_back(to_return, ft_lstnew((*command)->content));
		(*command) = (*command)->next;
	}
}

t_list	*check_join(t_list *command)
{
	t_list	*to_return;

	to_return = NULL;
	while (command)
	{
		if (command->type == word)
			join_words(&command, &to_return);
		else
		{
			ft_lstadd_back(&to_return, ft_lstnew(command->content));
			command = command->next;
		}
	}
	// ft_lstclear(&command);
	assign_type(to_return);
	return (to_return);
}