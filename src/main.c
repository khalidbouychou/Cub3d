/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:10:03 by khbouych          #+#    #+#             */
/*   Updated: 2023/11/01 23:41:14 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub.h"

int getsize_largline(char **map)
{
    int i;
    int max;

    i = -1;
    max = ft_strlen(map[0]);
    while (map[++i])
        if (ft_strlen(map[i]) > max)
            max = ft_strlen(map[i]);
    return (max);
}
int getsizemap(char **map)
{
    int i;

    i = 0;
    while (map[i])
        i++;
    return (i);
}

char *fixline(char *line, int maxlen)
{
    char *new;
    int i;

    i = 0;
    new = malloc(sizeof(char) * (maxlen + 1));
    while (line[i])
    {
        new[i] = line[i];
        i++;
    }
    while (i < maxlen)
    {
        new[i] = ' ';
        i++;
    }
    new[i] = '\0';
    return (new);
}



int h_map(char **map)
{
    int i;
    int j;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] != '1' && map[i][j] != ' ')
            {
                if (map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
                {
                    write(1, "Error\ninvalid map (h)\n", 23);
                    return (0);
                }
            }
            j++;
        }
        i++;
    }
    return 1;
}

int v_map(char **map)
{
    int i;
    int j;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] != '1' && map[i][j] != ' ')
            {
                if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ')
                {
                    write(1, "Error\ninvalid map (v)\n", 23);
                    return (0);
                }
            }
            j++;
        }
        i++;
    }
    return 1;
}
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
    if (smlx->m->sq_map[x][y] == '1')
        return (0);
    return (1);
}
void update_pos_player(t_mlx *smlx)
{


    // smlx->m->rotatangle += smlx->m->turndirection * smlx->m->rotatespeed;
    float smove = smlx->m->walkdirection * smlx->m->movespeed;
    smlx->xplayer += (cos(smlx->m->rotatangle) * smove);
    smlx->yplayer += (sin(smlx->m->rotatangle) * smove);
    // int tx;
    // int ty;

    // int to_move;

    // to_move = smlx->m->walkdirection  * smlx->m->movespeed * 0.05;
    // printf("to move %f\n",smove);
    printf("speed %f\n",smlx->m->movespeed);
    printf("walk %d\n",smlx->m->walkdirection);
    printf("turn %d\n",smlx->m->turndirection);
    //  smlx->xplayer += cos(smlx->m->rotatangle) * to_move;
    //  smlx->yplayer += sin(smlx->m->rotatangle) * to_move;

}
//*******player*************
void move_player(void *param)
{
    t_mlx *smlx;

    smlx = (t_mlx *)param;
    mlx_delete_image(smlx->mlx, smlx->img);
    smlx->img = mlx_new_image(smlx->mlx,(smlx->m->w_map * P_SIZE),(smlx->m->h_map * P_SIZE));
    draw2d(smlx->m, smlx);
    update_pos_player(smlx);
    draw_player(smlx);
}
//********************

void    init_vars(t_mlx *smlx, t_map *m)
{
    get_x_y_player(smlx ,m);
    m->rotatespeed = 2 * (M_PI / 180);
    // m->movespeed = 50;
    m->movespeed = 2.0;
    m->turndirection = 0;
    m->walkdirection = 0;
    m->rotatangle = (M_PI / 2);
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
    init_vars(&smlx, &m);
    draw(&smlx, &m, l_ture);
    mlx_key_hook(smlx.mlx, &key, &m);
    mlx_loop_hook(smlx.mlx, &move_player, &smlx);
    mlx_loop(smlx.mlx);
    mlx_terminate(smlx.mlx);
    // move_player(&smlx, &m);
    return (0);
}