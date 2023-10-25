/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:10:03 by khbouych          #+#    #+#             */
/*   Updated: 2023/10/25 19:46:24 by khbouych         ###   ########.fr       */
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

int check_ifvalid(char *line)
{
   while (*line == ' ' || (*line >= 9 && *line <= 13))
        line++;
    if ((!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2) ||
        !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2) ) &&
            (line[2] == 32 || (line[2] >= 9 && line[2] <= 13)))
            return (1);
    else if ((!ft_strncmp(line, "F", 1) ||
                !ft_strncmp(line, "C", 1) )&&
                (line[1] == 32 || (line[1] >= 9 && line[1] <= 13)))
        return (1);
    return (0);
}
//--------------read map-----------------------
void    read_map_(t_map *m)
{
    m->map = ft_strdup("");
    while (m->line)
    {
        if ( !if_validmap(m->line) || !if_surrounded(m->line)  )
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
//-------------------------------------------------
int checktures_space_tab(char **ture2d, int count)
{
    int i;

    i = -1;
    if (count != 6)
        return (0);
    while (++i < count)
        if (!check_ifvalid(ture2d[i]))
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

int ft_isdigit(int c)
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
    printf("res = %s\n",str);
    return str;
}

int check_duplicat(t_map *m)
{
    int i;
    int j;

    i = 0;
    while (m->ture2d[i])
    {
        j = i + 1;
        while (m->ture2d[j])
        {
            if (!ft_strncmp(m->ture2d[i], m->ture2d[j], 2))
            {
                write(1, "Error\nDuplicate map element [texture/color]\n", 45);
                return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}
//---------------------21/10/2023-------------------------------------------
int get_index(char *line, int i)
{
    while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
        i++;
    return (i);
}
t_txtr  *new_texture(char *line)
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
    else if ((!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1) ))
    {
        list->key = ft_substr(line, 0, 1);
        list->value = ft_substr(line, get_index(line, 1), ft_strlen(line));
    }
    list->next = NULL;
    return (list);
}

t_txtr  *lst_back_ture(t_txtr *l_ture, t_txtr *new)
{
    t_txtr *tmp;

    tmp = l_ture;
    if (l_ture == NULL)
        return (new);
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    return (l_ture);
}
void    lst_ture(t_map *m, t_txtr **l_ture)
{
    int i;
    t_txtr *tmp;
    i = 0;
    (*l_ture) = NULL;
    while (m->ture2d[i])
    {
        tmp = new_texture(m->ture2d[i++]);
        (*l_ture) = lst_back_ture((*l_ture), tmp);
    }
}
void free_2dmap(t_map *m)
{
    int i;

    i = 0;
    while (m->map2d[i])
        free(m->map2d[i++]);
    free(m->map2d);
}

void free_ture2d(t_map *m)
{
    int i;

    i = 0;
    while (m->ture2d[i])
        free(m->ture2d[i++]);
    free(m->ture2d);
}

void free_list(t_txtr *l_ture)
{
    t_txtr *tmp;

    while (l_ture)
    {
        tmp = l_ture;
        l_ture = l_ture->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
    }
    free(tmp);
}
//--------------------------------------------------------------------------

void check_rgb(t_txtr *l_ture)
{
   t_txtr *tmp;

   tmp = l_ture;
    while (tmp)
    {
        if (!ft_strncmp(tmp->key, "F",1) || !ft_strncmp(tmp->key,"C",1))
            printf("%s%s\n", tmp->key, tmp->value);
        tmp = tmp->next;
    }
}

void leak(void)
{
    system("leaks cub3D");
}
int main(int ac, char **av)
{
    // atexit(leak);
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
    if (!checktures_space_tab(m.ture2d , count) || !parse_rgb(m.ture2d) || !check_duplicat(&m))
        return (0);
    // else
    // {
    // lst_ture(&m,&l_ture);
    // check_rgb(l_ture);
    //     return (write(1, "OK\n", 3));
    // }
    // free_2dmap(&m);
    // free_ture2d(&m);
    // free_list(l_ture);
    return (0);
}
