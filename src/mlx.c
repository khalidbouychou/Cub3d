/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:38:38 by khbouych          #+#    #+#             */
/*   Updated: 2023/11/02 17:27:56 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub.h"

void    draw_square(mlx_image_t *img, t_mlx **smlx , int color)
{
    t_mlx *tmp;

    tmp = *smlx;
    tmp->x = -1;

    while (++tmp->x < P_SIZE)
    {
        tmp->y = -1;
        while (++tmp->y < P_SIZE)
            mlx_put_pixel(img,(tmp->j * P_SIZE) + tmp->x ,(tmp->i * P_SIZE) + tmp->y, color);
    }
}

void    draw2d(t_map *m, t_mlx *smlx)
{
    smlx->i = 0;
    smlx->color = 0;
    smlx->img = mlx_new_image(smlx->mlx,(smlx->m->w_map * P_SIZE),(smlx->m->h_map * P_SIZE));
    if (!smlx->img)
    {
        printf("error\n");
        exit(0);
    }
    while (m->sq_map[smlx->i])
    {
        smlx->j = 0;
        while (m->sq_map[smlx->i][smlx->j])
        {
            if (m->sq_map[smlx->i][smlx->j] == '1')
                draw_square(smlx->img,&smlx,0x00FFFFFF);
            else
                draw_square(smlx->img,&smlx, 0x00000000);
            smlx->j++;
        }
        smlx->i++;
    }
    mlx_image_to_window(smlx->mlx,smlx->img,0,0);
}

void    draw_player(t_mlx *smlx)
{
    smlx->i = -1;
    while (++smlx->i < 5)
    {
        smlx->j = -1;
        while (++smlx->j < 5)
            mlx_put_pixel(smlx->img,(smlx->xplayer * P_SIZE) + smlx->i ,(smlx->yplayer * P_SIZE) + smlx->j, 0xFF0000FF);
    }
}
void draw(t_mlx *smlx, t_map *m , t_txtr *l_ture)
{
    (void)l_ture;
    smlx->mlx = mlx_init((m->w_map * P_SIZE),(m->h_map * P_SIZE),"cub3d",false);
    if (!smlx->mlx)
    {
        printf("%s",mlx_strerror(mlx_errno));
        exit(EXIT_FAILURE);
    }
    draw2d(m,smlx);
    draw_player(smlx);
}

void key(mlx_key_data_t keydata , void *param)
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
