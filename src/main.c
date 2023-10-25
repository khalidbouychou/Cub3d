/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:10:03 by khbouych          #+#    #+#             */
/*   Updated: 2023/10/25 20:15:00 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub.h"

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
   
    return (0);
}
