/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:38:38 by khbouych          #+#    #+#             */
/*   Updated: 2023/10/31 18:45:32 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub.h"

void    draw_square(mlx_image_t *img, t_mlx **smlx , char p , int color)
{
    t_mlx *tmp;
    int t;

    tmp = *smlx;
    tmp->x = -1;

    if ((p == 'N' || p == 'S' || p == 'W' || p == 'E'))
        t = 8;
    else
        t = P_SIZE;
    while (++tmp->x < t)
    {
        tmp->y = -1;
        while (++tmp->y < t)
        {
            if (p == 'N' || p == 'S' || p == 'W' || p == 'E')
                mlx_put_pixel(img,(tmp->j * P_SIZE) + tmp->x ,(tmp->i * P_SIZE) + tmp->y, color);
            else
                mlx_put_pixel(img,(tmp->j * P_SIZE) + tmp->x ,(tmp->i * P_SIZE) + tmp->y, color);
        }
    }
}

void    draw2d(t_map *m, t_mlx *smlx)
{
    smlx->i = 0;
    smlx->color = 0;
    smlx->img = mlx_new_image(smlx->mlx,(m->w_map * P_SIZE),(m->h_map * P_SIZE));
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
                draw_square(smlx->img,&smlx,'1',0x00FFFFFF);
            else if (m->sq_map[smlx->i][smlx->j] == 'W' || m->sq_map[smlx->i][smlx->j] == 'E' ||
                m->sq_map[smlx->i][smlx->j] == 'N' || m->sq_map[smlx->i][smlx->j] == 'S')
                draw_square(smlx->img,&smlx, m->sq_map[smlx->i][smlx->j], 0xFF0000FF);
            else
                draw_square(smlx->img,&smlx, m->sq_map[smlx->i][smlx->j], 0x00000000);
            smlx->j++;
        }
        smlx->i++;
    }
    mlx_image_to_window(smlx->mlx,smlx->img,0,0);
}
void draw(t_mlx *smlx, t_map *m , t_txtr *l_ture)
{
    (void)l_ture;
    smlx->mlx = mlx_init((m->w_map * P_SIZE),(m->h_map * P_SIZE),"cub3d",true);
    if (!smlx->mlx)
    {
        printf("%s",mlx_strerror(mlx_errno));
        exit(EXIT_FAILURE);
    }
    draw2d(m,smlx);
    mlx_loop(smlx->mlx);
    mlx_terminate(smlx->mlx);
}