/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:00:46 by khbouych          #+#    #+#             */
/*   Updated: 2023/10/19 17:29:34 by khbouych         ###   ########.fr       */
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
}              t_map;

typedef struct s_txtr
{
    char *key;
    char *value;
    struct s_txtr *next;
} t_txtr;

char	*ft_strdup(char *s1);
char	**ft_split(char const *s, char c);
#endif

