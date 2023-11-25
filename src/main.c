/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:41:29 by khbouych          #+#    #+#             */
/*   Updated: 2023/11/25 14:27:32 by khbouych         ###   ########.fr       */
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
		j = -1;
		while (++j < WINDOW_W)
			mlx_put_pixel(smlx->img, j, i, smlx->ceiling_color);
	}
	i = HALF_HEIGHT;
	while (i < WINDOW_H)
	{
		j = -1;
		while (++j < WINDOW_W)
			mlx_put_pixel(smlx->img, j, i, smlx->floor_color);
		i++;
	}
}


void l()
{
	system("leaks cub3D");
}

int parsing(int ac, char **av, t_data *m, t_txtr *l_ture)
{
	t_mlx smlx;
	int count;
  if (ac != 2 || !checkextension(av[1]))
			return (write(1, "Error\ninvalid args\n", 20), 0);
	count = 0;
	if (!read_map(av[1], m, &count))
		return (0);
	l_ture = malloc(sizeof(t_txtr));
	if (!valid_map(m) || !l_ture)
		return (free1(m, l_ture), 0);
	if (!lst_ture(m, &l_ture))
		return (free1(m, l_ture), 0);
	// if (!parse_rgb_color(&smlx))
	// 	return (freelist(&l_ture), 0);
	smlx.m = m;
	free_2d(m->ture2d);
	return (1);
}
int main(int ac, char **av)
{
	atexit(l);
	t_txtr *l_ture = NULL;
	t_data m;
	if (!parsing(ac, av, &m, l_ture))
		return (0);
	// // finish
	// free1(&m, l_ture);
	// free_2d(m.sq_map);
	// get_f_c_color(l_ture);
	// smlx.l_ture = l_ture;
	// init_vars(&smlx);
	// //--------------mlx-------------
	// get_x_y_player(&smlx, &m);
	// draw(&smlx, &m, l_ture);
	// mlx_key_hook(smlx.mlx, &key, &m);
	// mlx_loop_hook(smlx.mlx, &move_player, &smlx);
	// mlx_loop(smlx.mlx);
	// mlx_terminate(smlx.mlx);
  return (0);
}

