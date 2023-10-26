/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:57:29 by khbouych          #+#    #+#             */
/*   Updated: 2023/10/26 22:30:44 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub.h"

int if_surrounded(char *line)
{
    while (*line == 32 || (*line >= 9 && *line <= 13))
        line++;
   if (*line != '1' || line[ft_strlen(line) - 1] != '1')
        return 0;
    return 1;
}
int if_validmap(char *line ,int  *flag)
{
    int i;

    (void)flag;
    i = 0;
    while (line[i])
    {
        if ((line[i] != '1' && line[i] != 32 && line[i] != '0' &&
        line[i] != '\n') && !(line[i] == 'W' || line[i] == 'E' || line[i] == 'N' ||
                line[i] == 'S'))
            return (0);
        else if (line[i] == 'W' || line[i] == 'E' || line[i] == 'N' ||
                line[i] == 'S')
        {
            (*flag)++;
        }
        i++;
    }
    return (1);
}

int suroundedbyone(char **map)
{
    int i;
    int flag;

    flag = 0;
    i = 0;
    while (map[i])
    {
        if (!if_surrounded(map[i]) || !if_validmap(map[i], &flag) || flag > 1)
        {
            write(1, "Error\ninvalid map\n", 19);
            return (0);
        }
        i++;
    }
    if (flag == 0)
    {
        write(1, "Error\nMissing charachters of the map\n", 37);
        return (0);
    }
    return (1);
}
int check_color_textures(char *line)
{
    while (*line == ' ' || (*line >= 9 && *line <= 13))
        line++;
    if ((!ft_strncmp(line, "EA", 2) || !ft_strncmp(line, "NO", 2) ||
        !ft_strncmp(line, "SO", 2) || !ft_strncmp(line, "WE", 2) ) ||
            (!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1)) )
        return 1;
    return (0);
}

int check_l_surroundedbyone(char *line)
{
    int i;

    i = -1;
    while (line[++i])
        if (line[i] != '1' && line[i] != 32)
            return (0);
    return (1);
}
char  *getlastline(char **map)
{
    int i;

    i = 0;
    while (map[i])
        i++;
    return (map[i - 1]);
}

int check_first_last_line(char **map)
{
    if (!check_l_surroundedbyone(map[0]) ||
        !check_l_surroundedbyone(getlastline(map)))
        {
            write(1, "Error\n(first/last) line not surrounded by 1 \n", 46);
            return (0);
        }
    return (1);
}
void    read_map_(t_map *m , int count)
{
    m->map = ft_strdup("");
    while (m->line)
    {
        if (m->line[0] == '\n')
        {
            write(1, "Error\nempty ligne in the map\n", 29);
            free(m->map);
            return ;
        }
        m->map = ft_strjoin(m->map, m->line);
        free(m->line);
        m->line = get_next_line(m->fd);
    }
    m->map2d = ft_split(m->map, '\n');
    free(m->map);
    free(m->line);
    if (!checktures_space_tab(m->ture2d , count) ||
        !parse_rgb(m->ture2d) || !check_duplicat(m) ||
        !check_first_last_line(m->map2d) || !suroundedbyone(m->map2d))
        return ;
}

void check_countture(t_map *m , int count)
{
    if (count < 6 || count > 6)
    {
        write(1, "Error\ninvalid map element [texture/color]\n", 41);
        free(m->ture);
        free(m->line);
        return ;
    }
}

void  read_map(char *av ,t_map *m , int *count)
{
    m->fd = open(av, O_RDONLY);
    m->line = get_next_line(m->fd);
    m->ture = ft_strdup("");
    while (m->line && m->line[0] != '1' && m->line[0] != 32)
    {
        if (check_color_textures(m->line))
        {
            m->ture = ft_strjoin(m->ture, m->line);
            (*count)++;
        }
        free(m->line);
        m->line = get_next_line(m->fd);
    }
    check_countture(m ,*count);
    m->ture2d = ft_split(m->ture, '\n');
    read_map_(m, *count);
    free(m->ture);
    free(m->line);
    close(m->fd);
}
