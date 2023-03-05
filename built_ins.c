/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:31:12 by ahmaymou          #+#    #+#             */
/*   Updated: 2023/03/05 20:38:54 by ahmaymou         ###   ########.fr       */
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
        printf("Error printing current working directory!\n");
    else
        printf("%s\n", str);
}

void    change_dir(char *path)
{
    if (chdir(path))
        printf("Error changing directory!\n");
}