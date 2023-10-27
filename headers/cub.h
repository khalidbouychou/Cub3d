/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:00:46 by khbouych          #+#    #+#             */
/*   Updated: 2023/10/27 16:09:02 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

#include "get_next_line.h"

//****************************************

typedef struct s_map
{
    int fd; 
    int i;
    char *line;
    char *ture;
    char *map;
    char **map2d;
    char **ture2d;
    char **sq_map;
}              t_map;

typedef struct s_txtr
{
    char *key;
    char *value;
    struct s_txtr *next;
} t_txtr;

char	*ft_strdup(char *s1);
char	**ft_split(char  *s, char c);
char	*ft_strtrim(char  *s1, char  *set);
char	*ft_substr(char  *s, unsigned int start, unsigned len);
int     ft_isdigit(int c);
//----------parse textures----------------
int     checktures_space_tab(char **ture2d, int count);
int     parse_rgb(char **ture2d);
void    lst_ture(t_map *m, t_txtr **l_ture);
//----------parse map----------------
void    read_map(char *av ,t_map *m , int *count);
//----------otils list----------------
int     check_duplicat(t_map *m);
//-----------free----------------
void    free_2dmap(t_map *m);
void    free_ture2d(t_map *m);
void    free_list(t_txtr *l_ture);
int check_ifvalid(char *line);
char    *removeSpaces(char* str);

#endif

