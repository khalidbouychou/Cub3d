/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:10:03 by khbouych          #+#    #+#             */
/*   Updated: 2023/11/01 01:24:24 by khbouych         ###   ########.fr       */
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

//*******player*************
void    move_player(t_mlx *smlx, t_map *m)
{
    
}
//********************
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
    parse_rgb_color(l_ture);
    //--------------mlx-------------
    draw(&smlx, &m, l_ture);
    move_player(&smlx, &m);
    return (0);
}