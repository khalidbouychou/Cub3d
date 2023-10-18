/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:10:03 by khbouych          #+#    #+#             */
/*   Updated: 2023/10/18 13:40:17 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub.h"
#include "outils/outils.h"

int check_f_e_line(char *fline)
{
    int i;

    i = 0;
    while (i < ft_strlen(fline))
    {
        if (fline[i] != '1' && fline[i] != ' ')
            return (0);
        i++;
    }
    return (1);
}
int check_color_textures(char *line)
{
    while (*line == ' ' || *line == '\t')
        line++;
    if (!ft_strncmp(line, "EA " , 3) || !ft_strncmp(line, "NO ", 3) ||
        !ft_strncmp(line, "SO ", 3) || !ft_strncmp(line, "WE ", 3) ||
            !ft_strncmp(line, "S ", 2) || !ft_strncmp(line, "F ", 2) ||
                !ft_strncmp(line, "C ", 2))
        return (1);
    return (0);
}

int get_size_map(int fd)
{
    char *line;
    int size;

    size = 0;
    line = get_next_line(fd);
    while (line)
    {
        line = get_next_line(fd);
        size++;
    }
    close(fd);
    return (size);
}
int if_validmap(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] != '1' && line[i] != ' ' && line[i] != '0' ||
            line[i] != 'W' || line[i] != 'E' || line[i] != 'N' ||
                line[i] != 'S')
            return (0);
        i++;
    }
    return (1);
}
void read_map(char *av)
{
    int fd;
    char *line;
    int size;
    int i;
    char *m;
    char *map;

    i = 0;
    fd = open(av, O_RDONLY);
    line = get_next_line(fd);
    size = 1;
    m = ft_strdup("");
    while (line)
    {
        if (check_color_textures(line))
            m = ft_strjoin(m, line);
        else if ()
        line = get_next_line(fd);
        free(line);
    }
    printf("%s", m);
}
int main(int ac, char **av)
{
    (void) av;
    // if (ac != 2)
    //     return (write(1, "To many Args\n", 13));
    read_map("map.cub");
    return (0);
}