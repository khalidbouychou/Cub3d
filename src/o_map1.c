/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_map1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:03:58 by khbouych          #+#    #+#             */
/*   Updated: 2023/11/11 20:34:33 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub.h"

void valid_map(t_map *m)
{
    int i;
    int maxlen;

    maxlen = getsize_largline(m->map2d);
    i = 0;
    m->sq_map = malloc(sizeof(char *) * (getsizemap(m->map2d) + 1));
    while (m->map2d[i])
    {
        if (maxlen == ft_strlen(m->map2d[i]))
            m->sq_map[i] = ft_strdup(m->map2d[i]);
        else
            m->sq_map[i] = fixline(m->map2d[i], maxlen);
        i++;
    }
    m->sq_map[i] = NULL;
    m->h_map = getsizemap(m->sq_map);
    m->w_map = ft_strlen(m->sq_map[0]);
    if (!h_map(m->sq_map) || !v_map(m->sq_map))
        exit(0);
}
void get_x_y_player(t_mlx *smlx, t_map *m)
{
    int i;
    int j;

    i = 0;
    while (m->sq_map[i])
    {
        j = 0;
        while (m->sq_map[i][j])
        {
            if (m->sq_map[i][j] == 'N' || m->sq_map[i][j] == 'S' || m->sq_map[i][j] == 'W' || m->sq_map[i][j] == 'E')
            {
                smlx->xplayer = j * P_SIZE;
                smlx->yplayer = i * P_SIZE;
                return;
            }
            j++;
        }
        i++;
    }
}

int check_next_step_2(t_mlx *smlx, float x, float y)
{
    int newx = floor(x / P_SIZE);
    int newy = floor(y / P_SIZE);
    if (x < 0 || x > smlx->w_window || y < 0 || y > smlx->h_window)
        return (1);
    if (smlx->m->sq_map[newy][newx] == '1')
        return (1);
    return (0);
}

int check_next_step(t_mlx *smlx, float x, float y)
{
    if (smlx->m->sq_map[(int)floor(y / P_SIZE)][(int)floor(x / P_SIZE)] == '1')
        return (0);
    return (1);
}

void update_pos_player(t_mlx *smlx)
{
    float speed_sin;
    float smove;
    float sb;
    float speed_cos;
    float ca;
    
    smlx->m->rotationangle += smlx->m->rotatespeed * smlx->m->turndirection; // rotation
    smove = smlx->m->walkdirection * smlx->m->movespeed;                     // walk
    speed_sin = smove * sin(smlx->m->rotationangle);
    speed_cos = smove * cos(smlx->m->rotationangle);
    ca = smlx->xplayer + speed_cos;
    sb = smlx->yplayer + speed_sin;
    if (check_next_step(smlx, ca, sb))
    {
        smlx->xplayer = ca;
        smlx->yplayer = sb;
    }
}

void renderRays(t_mlx *smlx)
{
    int r;

    r = -1;
    while (++r < smlx->nbr_rays)
        draw_line(smlx, smlx->xplayer +( cos(smlx->m->rays[r].rayAngle) * smlx->m->rays[r].distance) ,
            smlx->yplayer + ( sin(smlx->m->rays[r].rayAngle) * smlx->m->rays[r].distance));
}

void wall_projection_3dmap(t_mlx *smlx)
{
    int i;

    i = -1;
    while (++i < smlx->nbr_rays)
    {
        float perpDistance = smlx->m->rays[i].distance * cos(smlx->m->rays[i].rayAngle - smlx->m->rotationangle);
        float distanceProjPlane = (WINDOW_W/ 2) / tan(FOV_ANGLE / 2);
        float projectedWallHeight = (P_SIZE / perpDistance) * distanceProjPlane;
        int wallStripHeight = (int)projectedWallHeight;
        int wallTopPixel = (WINDOW_H / 2) - (wallStripHeight / 2);
        wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;
        int wallBottomPixel = (WINDOW_H / 2) + (wallStripHeight / 2);
        wallBottomPixel = wallBottomPixel > WINDOW_H ? WINDOW_H : wallBottomPixel;

        //render the wall from wallTopPixel to wallBottomPixel
        int j;
        j = wallTopPixel;
        while (j < wallBottomPixel)
        {
            mlx_put_pixel(smlx->img, i, j, 0xFF2400FF);
            j++;
        }
    }
}

void drawmap(t_mlx *smlx, t_map *m)
{
    smlx->i = 0;
    while (m->sq_map[smlx->i])
    {
        smlx->j = 0;
        while (m->sq_map[smlx->i][smlx->j])
        {
            if (m->sq_map[smlx->i][smlx->j] == '1')
                draw_square(smlx->img, &smlx, 0xdbdbdbFF);
            else
                draw_square(smlx->img, &smlx, 0x00000000);
            smlx->j++;
        }
        smlx->i++;
    }
}
void move_player(void *param)
{
    t_mlx *smlx;

    smlx = (t_mlx *)param;
    mlx_delete_image(smlx->mlx, smlx->img);
    draw2d(smlx);
    update_pos_player(smlx);
    castAllRay(smlx);
    wall_projection_3dmap(smlx);
    drawmap(smlx, smlx->m);
    draw_player(smlx);
    // renderRays(smlx);
}
