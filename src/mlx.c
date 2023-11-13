/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:38:38 by khbouych          #+#    #+#             */
/*   Updated: 2023/11/12 23:32:00 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub.h"

void draw_square(mlx_image_t *img, t_mlx **smlx, int color)
{
    t_mlx *tmp;

    tmp = *smlx;
    tmp->x = -1;

    while (++tmp->x < P_SIZE)
    {
        tmp->y = -1;
        while (++tmp->y < P_SIZE)
            mlx_put_pixel(img, ((tmp->j * P_SIZE) + tmp->x) * 0.2, ((tmp->i * P_SIZE)  + tmp->y) * 0.2, color);
    }
}

void draw2d(t_mlx *smlx)
{
    smlx->i = 0;
    smlx->color = 0;
    smlx->img = mlx_new_image(smlx->mlx, WINDOW_W, WINDOW_H);
    if (!smlx->img)
    {
        printf("error\n");
        exit(0);
    }
    mlx_image_to_window(smlx->mlx, smlx->img, 0, 0);
}

void draw_player(t_mlx *smlx)
{
    smlx->i = -1;
    while (++smlx->i < W_PLAYER)
    {
        smlx->j = -1;
        while (++smlx->j < H_PLAYER)
            mlx_put_pixel(smlx->img, (smlx->xplayer  + smlx->i) * 0.2, (smlx->yplayer  + smlx->j) * 0.2, 0xFFFFFFFF);
    }
}
void draw(t_mlx *smlx, t_map *m, t_txtr *l_ture)
{
    (void)l_ture;
    (void)m;
    smlx->mlx = mlx_init(WINDOW_W,WINDOW_H, "CUB3D", false);
    if (!smlx->mlx)
    {
        printf("%s", mlx_strerror(mlx_errno));
        exit(EXIT_FAILURE);
    }
    draw2d(smlx);
    draw_player(smlx);
}

void key(mlx_key_data_t keydata, void *param)
{

    t_map *m;
    m = param;
    if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        exit(0);
    else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS))
        m->turndirection = -1;
    else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS))
        m->turndirection = 1;
    else if (keydata.key == MLX_KEY_DOWN && (keydata.action == MLX_PRESS))
        m->walkdirection = -1;
    else if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
        m->walkdirection = 1;

    if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_RELEASE))
        m->turndirection = 0;
    else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_RELEASE))
        m->turndirection = 0;
    else if (keydata.key == MLX_KEY_DOWN && (keydata.action == MLX_RELEASE))
        m->walkdirection = 0;
    else if (keydata.key == MLX_KEY_UP && (keydata.action == MLX_RELEASE))
        m->walkdirection = 0;
}
