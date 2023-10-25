/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_list.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 20:07:15 by khbouych          #+#    #+#             */
/*   Updated: 2023/10/25 20:10:16 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub.h"

char    *removeSpaces(char* str)
{
    char* src;
    char* dst;

    src = str;
    dst = str;

    while (*src)
    {
        if (*src != '\t' && *src != '\r')
        {
            *dst = *src;
            dst++;
        }
        src++;
    }
    *dst = '\0';
    return str;
}

int check_duplicat(t_map *m)
{
    int i;
    int j;

    i = 0;
    while (m->ture2d[i])
    {
        j = i + 1;
        while (m->ture2d[j])
        {
            if (!ft_strncmp(m->ture2d[i], m->ture2d[j], 2))
            {
                write(1, "Error\nDuplicate map element [texture/color]\n", 45);
                return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}

