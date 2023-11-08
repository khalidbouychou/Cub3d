/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:10:03 by khbouych          #+#    #+#             */
/*   Updated: 2023/11/08 18:08:19 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub.h"

int main(int ac, char **av)
{
    (void) av;
    (void) ac;
    t_map m;
    t_txtr *l_ture;
    t_mlx smlx;
    int count;

    l_ture = malloc(sizeof(t_txtr));
    count = 0;
    // // if (ac != 2)
    // //     return (write(1, "To many Args\n", 13));
    read_map("map.cub", &m, &count);
    valid_map(&m);
    lst_ture(&m, &l_ture);
    smlx.m = &m;
    parse_rgb_color(l_ture);
    //--------------mlx-------------
    init_vars(&smlx);;
    get_x_y_player(&smlx, &m);
    draw(&smlx, &m, l_ture);

    mlx_key_hook(smlx.mlx, &key, &m);
    mlx_loop_hook(smlx.mlx, &move_player, &smlx);
    mlx_loop(smlx.mlx);
    mlx_terminate(smlx.mlx);
    return (0);
}
