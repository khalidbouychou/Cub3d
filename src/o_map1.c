/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_map1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:03:58 by khbouych          #+#    #+#             */
/*   Updated: 2023/11/08 11:11:27 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub.h"

void    valid_map(t_map *m)
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
void get_x_y_player(t_mlx *smlx , t_map *m)
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
                smlx->xplayer = j;
                smlx->yplayer = i;
                return ;
            }
            j++;
        }
        i++;
    }
}

int check_next_step(t_mlx *smlx, int x, int y)
{
    if (smlx->m->sq_map[y][x] != '1')
        return (1);
    return (0);
}

void update_pos_player(t_mlx *smlx)
{
  float speed_sin;
  float smove;
  float sb;
  float speed_cos;
  float ca;
  smlx->m->rotationangle += smlx->m->rotatespeed * smlx->m->turndirection; //rotation
  smove = smlx->m->walkdirection  * smlx->m->movespeed  ; //walk
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
void move_player(void *param)
{
    t_mlx *smlx;

    smlx = (t_mlx *)param;
    mlx_delete_image(smlx->mlx, smlx->img);
    // smlx->img = mlx_new_image(smlx->mlx,(smlx->m->w_map * P_SIZE),(smlx->m->h_map * P_SIZE));
    draw2d(smlx->m, smlx);
    update_pos_player(smlx);
    draw_player(smlx);
    // darw_line(smlx,((smlx->xplayer * P_SIZE) + (cos(smlx->m->rotationangle) * 20)), ((smlx->yplayer * P_SIZE)  + (sin(smlx->m->rotationangle) * 20)));
    castAllRay(smlx);
}

