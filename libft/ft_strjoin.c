/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 11:05:21 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/13 14:53:18 by ahmaymou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2, bool free_s1)
{
	char				*to_return;
	unsigned int		len;


	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (free_s1)
		free((void*)s1);
	to_return = (char *)malloc((len + 1)
			* sizeof(char));
	if (!to_return)
		return (NULL);
	ft_strlcpy(to_return, s1, ft_strlen(s1) + 1);
	ft_strlcat(to_return, s2, len + 1);
	return (to_return);
}
