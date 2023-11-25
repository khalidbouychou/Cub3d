/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:00:46 by khbouych          #+#    #+#             */
/*   Updated: 2023/11/25 05:49:57 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
#define CUB_H

#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include "get_next_line.h"
#include "../MLX42/include/MLX42/MLX42.h"
#define P_SIZE 32
#define FOV_ANGLE (60 * (M_PI / 180))
#define WINDOW_H 1080
#define WINDOW_W 1920
#define H_PLAYER 5
#define W_PLAYER 5
#define HALF_WIDTH (WINDOW_W / 2)
#define HALF_HEIGHT (WINDOW_H / 2)
//****************************************

typedef struct s_ray
{
	float rayAngle;
	float wallHitX;
	float wallHitY;
	float distance;
	int wasHitVertical;
	int isRayFacingUp;
	int isRayFacingDown;
	int isRayFacingLeft;
	int isRayFacingRight;
} t_ray;

//----afatir
// typedef struct s_data
// {
// 	char	**map;
// 	char	*no;
// 	char	*we;
// 	char	*so;
// 	char	*ea;
// 	char	*f;
// 	char	*c;
// 	int		p_x;
// 	int		p_y;
// 	int		map_h;
// 	int		map_w;
// 	char 	**f;
// 	char 	**c;
// }t_data;

//---afatir
typedef struct s_data
{
	// char	**map;
	char	*no;
	char	*we;
	char	*so;
	char	*ea;
	char	*f;
	char	*c;
	int		p_x;
	int		p_y;
	int		map_h;
	int		map_w;
	char 	**ff;
	char 	**cc;
	int fd;
	int i;
	char *line;
	char *ture;
	char *map;
	char **map2d;
	char **ture2d;
	char **sq_map;
	int h_map;
	int w_map;
	int turndirection;
	int walkdirection;
	float rotationangle;
	float movespeed;
	float rotatespeed;
	char **rgb;
} t_data;

typedef struct s_txtr
{
	char *key;
	char *value;
	struct s_txtr *next;
} t_txtr;

typedef struct s_mlx
{
	mlx_t *mlx;
	mlx_image_t *img;
	t_data *m;
	t_txtr *l_ture;
	int x;
	int y;
	int i;
	int j;
	int color;
	float h_player;
	float w_player;
	float newXplayer;
	float newYplayer;
	float delta_x;
	float delta_y;
	int w_window;
	int h_window;
	int nbr_rays;
	mlx_texture_t *texture;
	uint32_t floor_color;
	uint32_t ceiling_color;
} t_mlx;

char *ft_strdup(char *s1);
char **ft_split(char *s, char c);
char *ft_strtrim(char *s1, char *set);
char *ft_substr(char *s, unsigned int start, unsigned len);
int ft_isdigit(int c);
int ft_atoi(const char *str);
//----------parse textures----------------
int checktures_space_tab(char **ture2d, int count);
int parse_rgb(char **ture2d);
int lst_ture(t_data *m, t_txtr **l_ture);
int parse_rgb_color(t_mlx *smlx);
//----------parse map----------------
// void    read_map(char *av ,t_data *m , int *count);
int read_map(char *av, t_data *m, int *count);
//----------otils list----------------
int check_duplicat(t_data *m);
//-----------free----------------
// void    free_2dmap(char **m);
// void    free_ture2d(t_data *m);
// void    free_list(t_txtr *l_ture);
void freelist(t_txtr **head);
int check_ifvalid(char *line);
char *removespaces(char *str);
int ft_strncmp(const char *s1, const char *s2, size_t n);
//-----------mlx----------------
void draw(t_mlx *smlx, t_data *m, t_txtr *l_ture);
void key(mlx_key_data_t keydata, void *param);
void draw2d(t_mlx *smlx);
void drawmap(t_mlx *smlx, t_data *m);
void draw_square(mlx_image_t *img, t_mlx **smlx, int color);
void draw_player(t_mlx *smlx);
//-----------map----------------
int getsize_largline(char **map);
int getsizemap(char **map);
char *fixline(char *line, int maxlen);
int h_map(char **map);
int v_map(char **map);
void get_x_y_player(t_mlx *smlx, t_data *m);
// void    valid_map(t_data *m);
int valid_map(t_data *m);
//-----------player----------------
void castAllRay(t_mlx *smlx);
void move_player(void *param);
void init_vars(t_mlx *smlx);
void draw_line(t_mlx *smlx, float X1, float Y1);
// int     check_next_step(t_mlx *smlx, float x, float y);
int check_next_step(t_mlx *smlx, float x, float y);
int check_next_step_2(t_mlx *smlx, float x, float y);
void splitwindow(t_mlx *smlx);
float f_abs(float number);
char **get_f_c_color(t_txtr *txtr);
uint32_t rgbcolor(int r, int g, int b, int a);
char *ft_strrchr(char *str, int c);
//-----------------raycasting----------------

void free_2d(char **m);
int checkextension(char *fname);
void free1(t_data *m, t_txtr *l_ture);
int check_first_last_line(char **map);
int suroundedbyone(char **map);
int check_color_textures(char *line);
int check_countture(t_data *m, int count);
int check_l_surroundedbyone(char *line);
void freeme(char *ture, char *line, int fd);
#endif
