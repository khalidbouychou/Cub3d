/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:10:03 by khbouych          #+#    #+#             */
/*   Updated: 2023/10/29 18:26:14 by khbouych         ###   ########.fr       */
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
    if (!h_map(m->sq_map) || !v_map(m->sq_map))
        return ;
}

void _rgb(char *rgb)
{
    char **rgb2d;
    int i;

    i = 0;
    rgb2d = ft_split(rgb, ',');
    while (rgb2d[i])
    {
        if (ft_atoi(rgb2d[i]) < 0 || ft_atoi(rgb2d[i]) > 255)
        {
            write (1, "Error\ninvalid rgb color\n", 25);
            exit(0);
        }
        i++;
    }
}
void parse_rgb_color(t_txtr *ture)
{
    t_txtr *tmp;

    tmp = ture;
    while (tmp)
    {
        if (!ft_strncmp(tmp->key, "F", 1) || !ft_strncmp(tmp->key, "C", 1))
            _rgb(tmp->value);
        tmp = tmp->next;
    }
}
int main(int ac, char **av)
{
    (void) av;
    (void) ac;
    t_map m;
    t_txtr *l_ture;
    int count;

    l_ture = malloc(sizeof(t_txtr));
    count = 0;
    // if (ac != 2)
    //     return (write(1, "To many Args\n", 13));
    read_map("map.cub", &m, &count);
    valid_map(&m);
    lst_ture(&m, &l_ture);
    parse_rgb_color(l_ture);
    return (0);
}