/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:56:14 by khbouych          #+#    #+#             */
/*   Updated: 2023/10/25 19:56:45 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub.h"

void free_2dmap(t_map *m)
{
    int i;

    i = 0;
    while (m->map2d[i])
        free(m->map2d[i++]);
    free(m->map2d);
}

void free_ture2d(t_map *m)
{
    int i;

    i = 0;
    while (m->ture2d[i])
        free(m->ture2d[i++]);
    free(m->ture2d);
}

void free_list(t_txtr *l_ture)
{
    t_txtr *tmp;

    while (l_ture)
    {
        tmp = l_ture;
        l_ture = l_ture->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
    }
    free(tmp);
}
