/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:10:03 by khbouych          #+#    #+#             */
/*   Updated: 2023/10/21 19:10:30 by khbouych         ###   ########.fr       */
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
        return 1;
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
void  read_textures(char *av ,t_map *m , int *count)
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
    if (*count < 6)
    {
        write(1, "Error\ninvalid map element [texture/color]\n", 41);
        exit(1);
    }
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
        {
            write(1, "Error\ninvalid map element [texture/color]\n", 41);
            return (0);
        }
    return (1);
}

int count_vergules(char *rgb)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (rgb[i])
        if (rgb[i++] == ',')
            count++;
    return (count);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int check_pos_ofv(char*line)
{
    int i;

    i = 0;
    while (*line == ' ' || (*line >= 9 && *line <= 13) || *line == 'C' || *line == 'F')
        line++;
    if (!ft_isdigit(line[i]) || !ft_isdigit(line[(ft_strlen(line) - 1)]))
        return (0);
    while (line[i])
    {
        if ((!ft_isdigit(line[i]) && line[i] != ',' )|| (line[i] == ',' && line[i+1] && line[i+1] == ','))
            return (0);
        i++;
    }
    return (1);
}
int parse_rgb(char **ture2d)
{
    int i;
    char *ptr;
    i = 0;

    while (ture2d[i])
    {
        ptr = ture2d[i];
        while (*ptr == ' ' || (*ptr >= 9 && *ptr <= 13))
            ptr++;
        if (ptr[0] == 'F' || ptr[0] == 'C')
        {
            if (count_vergules(ptr) != 2 || !check_pos_ofv(ptr))
            {
                write(1, "Error\ninvalid map element [texture/color]\n", 41);
                return (0);
            }
        }
            i++;
    }
    return (1);
}

char* removeSpaces(char* str)
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
    printf("res = %s\n",str);
    return str;
}

int get_index(char *line, int i)
{
    while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
        i++;
    printf("c = %c\n",line[i]);
    return (i);
}
t_txtr * new_texture(char *line)
{
    t_txtr *list;
    list = (t_txtr *)malloc(sizeof(t_txtr));
   while (*line == ' ' || (*line >= 9 && *line <= 13))
        line++;
    if ((!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2) ||
        !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2) ))
    {
        list->key = ft_substr(line, 0, 2);
        list->value = ft_substr(line, get_index(line, 2), ft_strlen(line));
    }
    else if ((!ft_strncmp(line, "S", 1) || !ft_strncmp(line, "F", 1) ||
                !ft_strncmp(line, "C", 1) ))
    {
        list->key = ft_substr(line, 0, 1);
        list->value = ft_substr(line, get_index(line, 1), ft_strlen(line));
    }
    list->next = NULL;
    return (list);
}

void lst_ture(t_map *m , t_txtr *l_ture)
{
    int i;
    t_txtr *tmp;
    i = 0;
    l_ture = NULL;
    while (m->ture2d[i])
    {
        tmp = new_texture(m->ture2d[i++]);
        // l_ture = lst_back_ture(l_ture , tmp);
    }
}
int main(int ac, char **av)
{
    (void) av;
    (void) ac;
    t_map m;
    t_txtr l_ture;
    int count;
    count = 0;
    // if (ac != 2)
    //     return (write(1, "To many Args\n", 13));
    read_textures("map.cub", &m, &count);
    read_map("map.cub", &m);

    lst_ture(&m,&l_ture);
    // if (!checktures_space_tab(m.ture2d , count) || !parse_rgb(m.ture2d))
    //     return (0);
    // else
    //     return (write(1, "OK\n", 3));
    return (0);
}