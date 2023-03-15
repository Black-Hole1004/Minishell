/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:23:00 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/15 21:45:49 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_commands(t_list *temp)
{
	int	count;

	count = 0;
	while (temp)
	{
		if (temp->type == Pipe)
			count++;
		temp = temp->next;
	}
	return ((2 * count) + 1);
}

void	get_node(t_list **head, t_list **final)
{
	t_list	*temp;

	temp = ft_lstnew(ft_strdup("", 0));
	if (*head && (*head)->type == Pipe)
	{
		temp->type = Pipe;
		ft_lstadd_back(final, temp);
		(*head) = (*head)->next;
		return ;
	}
	while ((*head) && (*head)->type != Pipe)
	{
		if ((*head)->type == word)
		{
			temp->content = ft_strjoin(temp->content, (*head)->content, 1);
			temp->content = ft_strjoin(temp->content, " ", 1);
		}
		else if ((*head)->type == in_file)
			temp->in_file = (*head)->content;
		else if ((*head)->type == out_file)
			temp->out_file = (*head)->content;
		else if ((*head)->type == delimiter)
			temp->delimiter = (*head)->content;
		temp->type = (*head)->type;
		(*head) = (*head)->next;
	}
	ft_lstadd_back(final, temp);
}

t_list	*create_final_list(t_list **head)
{
	t_list  *final;
	int		count;

	final = NULL;
	count = count_commands(*head);
	while (count--)
		get_node(head, &final);
	return (final);
}