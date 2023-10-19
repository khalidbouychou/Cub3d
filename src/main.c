/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:10:03 by khbouych          #+#    #+#             */
/*   Updated: 2023/10/19 23:49:08 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub.h"

int check_color_textures(char *line)
{
    while (*line == ' ' || (*line >= 9 && *line <= 13))
        line++;
    if ((!ft_strncmp(line, "EA" , 2) || !ft_strncmp(line, "NO", 2) ||
        !ft_strncmp(line, "SO", 2) || !ft_strncmp(line, "WE", 2) ||
            !ft_strncmp(line, "S", 1) || !ft_strncmp(line, "F", 1) ||
                !ft_strncmp(line, "C", 1)))
    {
        return (1);
    }
    return (0);
}

int if_validmap(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] != '1' && line[i] != ' ' && line[i] != '0' &&
            line[i] != 'W' && line[i] != 'E' && line[i] != 'N' &&
                line[i] != 'S' && line[i] != '\n')
            return (0);
        i++;
    }
    return (1);
}

void    read_map(char *av ,t_map *m)
{
    m->fd = open(av, O_RDONLY);
    m->line = get_next_line(m->fd);
    m->ture = ft_strdup("");

    while (m->line != NULL)
    {
        if (if_validmap(m->line))
            m->map = ft_strjoin(m->map, m->line);
        free(m->line);
        m->line = get_next_line(m->fd);
    }
    close(m->fd);
    m->map2d = ft_split(m->map, '\n');
    free(m->map);
    free(m->line);
}
void read_textures(char *av ,t_map *m , int *count)
{
    m->fd = open(av, O_RDONLY);
    m->line = get_next_line(m->fd);
    m->ture = ft_strdup("");

    while (m->line[0] != '1' && m->line != NULL)
    {
        if (check_color_textures(m->line))
        {
            m->ture = ft_strjoin(m->ture, m->line);
            (*count)++;
        }
        free(m->line);
        m->line = get_next_line(m->fd);
    }
    close(m->fd);
    m->ture2d = ft_split(m->ture, '\n');
    free(m->ture);
    free(m->line);
}

int check_ifvalid(char *line)
{
   while (*line == ' ' || (*line >= 9 && *line <= 13))
        line++;
    if ((!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2) ||
        !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2) ) &&
            (line[2] == 32 || (line[2] >= 9 && line[2] <= 13)))
        return (1);
    else if ((!ft_strncmp(line, "S", 1) || !ft_strncmp(line, "F", 1) ||
                !ft_strncmp(line, "C", 1) )&&
                (line[1] == 32 || (line[1] >= 9 && line[1] <= 13)))
        return (1);
    return (0);
}

int checktures_space_tab(char **ture2d , int count)
{
    int i;

    i = 0;
    if (count != 6)
        return (0);
    while (i < count)
        if (!check_ifvalid(ture2d[i++]))
            return (0);
    return (1);
}

int count_vergules(char *rgb)
{
    int i;
    int count;

    i = 0;
    while (rgb[i])
        if (rgb[i++] == ',')
            count++;
    return (count);
}
// int parse_rgb(char **ture2d)
// {
//     int i;

//     i = 0;
//     while (ture2d[i])
//     {
        
//     }
// }
int main(int ac, char **av)
{
    (void) av;
    (void) ac;
    t_map m;
    int count;
    count = 0;
    // if (ac != 2)
    //     return (write(1, "To many Args\n", 13));
    read_textures("map.cub", &m, &count);
    read_map("map.cub", &m);
    if (checktures_space_tab(m.ture2d , count) == 0)
        return (write(1, "Error\n", 6));
    else
        return (write(1, "OK\n", 3));
    return (0);
}