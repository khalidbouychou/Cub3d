/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:17:28 by khbouych          #+#    #+#             */
/*   Updated: 2023/10/15 15:09:28 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

// # include "../headers/cub.h"
#include "headers/get_next_line.h"
typedef struct	s_map
{
    int			width;
    int			height;
    char		**map;
}				t_map;

#endif