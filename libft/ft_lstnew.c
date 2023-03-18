/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:35:31 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/18 16:30:31 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*elem;

	elem = malloc(sizeof(t_list));
	if (!elem)
		return (NULL);
    elem->content = content;
    elem->prev = NULL;
    elem->next = NULL;
    elem->out_file = NULL;
    elem->in_file = NULL;
    elem->in_fd = -2;
    elem->out_fd = -2;
    elem->delims = NULL;
    elem->commands = NULL;
    elem->_errno = 0;
	return (elem);
}
