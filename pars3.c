/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:09:49 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/11 18:07:08 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_or_join(t_list **head, char *temp, t_list **temp2)
{
	if ((*temp2) && what_type(temp) == word && what_type((*temp2)->content) == word)
	{
		(*temp2)->content = ft_strjoin((*temp2)->content, " ");
		(*temp2)->content = ft_strjoin((*temp2)->content, temp);
	}
	else
	{
		(*temp2) = ft_lstnew(ft_strtrim(temp, " "));
		(*temp2)->type = what_type(temp);
		ft_lstadd_back(head, (*temp2));
	}
}