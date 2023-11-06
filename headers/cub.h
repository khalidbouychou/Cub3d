/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:00:46 by khbouych          #+#    #+#             */
/*   Updated: 2023/11/05 18:14:28 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

#include <math.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "../MLX42/include/MLX42/MLX42.h"
#define P_SIZE 32
#define MINIMAP_SCALE_FACTOR 1.0
#define FOV_ANGLE (60 * (M_PI / 180))
#define NUM_RAYS 1
#define TILE_SIZE 64
//****************************************
typedef struct s_map
{
    int     fd;
    int     i;
    char    *line;
    char    *ture;
    char    *map;
    char    **map2d;
    char    **ture2d;
    char    **sq_map;
    int     h_map;
    int     w_map;
    int     turndirection;
    int     walkdirection;
    float   rotatangle;
    float   movespeed;
    float   rotatespeed;
}              t_map;

typedef struct s_mlx
{
    mlx_t       *mlx;
    mlx_image_t *img;
    t_map       *m;
    int         x;
    int         y;
    int         i;
    int         j;
    int         color;
    float       xplayer;
    float       yplayer;
    float       newXplayer;
    float       newYplayer;
    float       delta_x;
    float       delta_y;
}              t_mlx;


typedef struct s_txtr
{
    char            *key;
    char            *value;
    struct s_txtr   *next;
}               t_txtr;

char	*ft_strdup(char *s1);
char	**ft_split(char  *s, char c);
char	*ft_strtrim(char  *s1, char  *set);
char	*ft_substr(char  *s, unsigned int start, unsigned len);
int     ft_isdigit(int c);
int	    ft_atoi(const char *str);
//----------parse textures----------------
int     checktures_space_tab(char **ture2d, int count);
int     parse_rgb(char **ture2d);
void    lst_ture(t_map *m, t_txtr **l_ture);
void    parse_rgb_color(t_txtr *ture);
//----------parse map----------------
void    read_map(char *av ,t_map *m , int *count);
//----------otils list----------------
int     check_duplicat(t_map *m);
void    lst_ture(t_map *m, t_txtr **l_ture);
//-----------free----------------
void    free_2dmap(t_map *m);
void    free_ture2d(t_map *m);
void    free_list(t_txtr *l_ture);
int     check_ifvalid(char *line);
char    *removeSpaces(char* str);
//-----------mlx----------------
void    draw(t_mlx *smlx, t_map *m , t_txtr *l_ture);
void    key(mlx_key_data_t keydata , void *param);
void    draw2d(t_map *m, t_mlx *smlx);
void    draw_player(t_mlx *smlx);
//-----------map----------------
#endif

