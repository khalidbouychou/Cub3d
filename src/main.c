/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:41:29 by khbouych          #+#    #+#             */
/*   Updated: 2023/11/19 22:33:30 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub.h"

float f_abs(float number)
{
    if (number < 0)
        return -number;
    return number;
}

void splitwindow(t_mlx *smlx)
{
    int i;
    int j;

    i = -1;
    while (++i < HALF_HEIGHT)
    {
        puts("ok");
        j = -1;
        while (++j < WINDOW_W)
            mlx_put_pixel(smlx->img, j, i, 0xA0E9FFFF);
    }
    i = HALF_HEIGHT;
    while (i < WINDOW_H)
    {
        puts("--");
        j = -1;
        while (++j < WINDOW_W)
            mlx_put_pixel(smlx->img, j, i, 0x28334AFF);
        i++;
    }
}
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
    smlx.l_ture = l_ture;
    init_vars(&smlx);
    get_x_y_player(&smlx, &m);
    draw(&smlx, &m, l_ture);
    mlx_key_hook(smlx.mlx, &key, &m);
    mlx_loop_hook(smlx.mlx, &move_player, &smlx);
    mlx_loop(smlx.mlx);
    mlx_terminate(smlx.mlx);
    return (0);
}
