/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:10:03 by khbouych          #+#    #+#             */
/*   Updated: 2023/10/25 20:03:04 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub.h"

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

int main(int ac, char **av)
{
    (void) av;
    (void) ac;
    t_map m;
    t_txtr *l_ture;
    int count;

    l_ture = malloc(sizeof(t_txtr));
    count = 0;
    // if (ac != 2)
    //     return (write(1, "To many Args\n", 13));
    read_map("map.cub", &m, &count);
    if (!checktures_space_tab(m.ture2d , count) ||
        !parse_rgb(m.ture2d) || !check_duplicat(&m))
        return (0);
    return (0);
}
