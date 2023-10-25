/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:57:29 by khbouych          #+#    #+#             */
/*   Updated: 2023/10/25 20:04:42 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub.h"

int if_surrounded(char *line)
{
    while (*line == 32 || (*line >= 9 && *line <= 13))
        line++;
    if (*line != '1' || line[ft_strlen(line) - 2] != '1')
        return 0;
    return 1;
}

int check_color_textures(char *line)
{
    while (*line == ' ' || (*line >= 9 && *line <= 13))
        line++;
    if ((!ft_strncmp(line, "EA", 2) || !ft_strncmp(line, "NO", 2) ||
        !ft_strncmp(line, "SO", 2) || !ft_strncmp(line, "WE", 2) ||
        !ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1)))
    {
        return 1;
    }
    return (0);
}

int if_validmap(char *line)
{
    int i;

    i = 0;
    if (*line == '\n')
        return (0);
    while (line[i])
    {
        if (line[i] != '1' && line[i] != 32 && line[i] != '0' &&
            line[i] != 'W' && line[i] != 'E' && line[i] != 'N' &&
                line[i] != 'S' && line[i] != '\n')
            return (0);
        i++;
    }
    return (1);
}

void    read_map_(t_map *m)
{
    m->map = ft_strdup("");
    while (m->line)
    {
        if (!if_validmap(m->line) || !if_surrounded(m->line)  )
        {
            write(1, "Error\ninvalid map\n", 19);
            free(m->map);
            exit(1);
        }
        m->map = ft_strjoin(m->map, m->line);
        free(m->line);
        m->line = get_next_line(m->fd);
    }
    m->map2d = ft_split(m->map, '\n');
    free(m->map);
    free(m->line);
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
    if (*count < 6 || *count > 6)
    {
        write(1, "Error\ninvalid map element [texture/color]\n", 41);
        free(m->ture);
        free(m->line);
        exit(1);
    }
    m->ture2d = ft_split(m->ture, '\n');
    read_map_(m);
    free(m->ture);
    free(m->line);
    close(m->fd);
}
char    *removeSpaces(char* str)
{
    char* src;
    char* dst;

    src = str;
    dst = str;

    while (*src)
    {
        if (*src != '\t' && *src != '\r')
        {
            *dst = *src;
            dst++;
        }
        src++;
    }
    *dst = '\0';
    return str;
}
