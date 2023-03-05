/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:31:12 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/05 21:26:27 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    echo(char *str, bool option)
{
    if (option)
        printf("%s", str);
    else
        printf("%s\n", str);
}

void    pwd(void)
{
    char    str[256];

    if (!getcwd(str, sizeof(str)))
        printf("Error !\n");
    else
        printf("%s\n", str);
}

void    change_dir(char *path)
{
    if (chdir(path))
        printf("Error \n");
}