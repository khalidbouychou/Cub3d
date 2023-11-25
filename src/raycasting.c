/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:07:17 by khbouych          #+#    #+#             */
/*   Updated: 2023/11/24 17:50:21 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub.h"

float normalizeAngle(float rayAngle)
{
    rayAngle = remainder(rayAngle, (M_PI * 2));
    if (rayAngle < 0)
        rayAngle = (2 * M_PI) + rayAngle;
    return (rayAngle);
}

float distanceBetweenPoints(float xp, float yp, float x, float y)
{
    return (sqrt((x - xp) * (x - xp) + (y - yp) * (y - yp)));
}
// void castRay(float rayAngle, int IdCast, t_mlx *smlx)
// {
//     rayAngle = normalizeAngle(rayAngle);
//     int isRayFacingDown = rayAngle > 0 && rayAngle < M_PI;
//     int isRayFacingUp = !isRayFacingDown;

//     int isRayFacingRight = rayAngle < (0.5 * M_PI )|| rayAngle > (1.5 * M_PI);
//     int isRayFacingLeft = !isRayFacingRight;

//     float xintercept, yintercept, xstep, ystep;
//     ///////////////Horizontal///////////////
//     int foundHorzWallHit = 0;
//     float horzWallHitX = 0;
//     float horzWallHitY = 0;
//     // Find the y-coordinate of the closest horizontal grid intersection
//     yintercept = floor(smlx->m->p_y / P_SIZE) * P_SIZE;
//     yintercept += isRayFacingDown ? P_SIZE : 0;
//     // Find the x-coordinate of the closest horizontal grid intersection
//     xintercept = smlx->m->p_x + (yintercept - smlx->m->p_y) / tan(rayAngle);
//     // Calculate the increment xstep and ystep (deltax and deltay)
//     ystep = P_SIZE;
//     ystep *= isRayFacingUp ? -1 : 1;

//     xstep = P_SIZE / tan(rayAngle);
//     xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
//     xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;

//     float nextHorzTouchX = xintercept;
//     float nextHorzTouchY = yintercept;

//     while (nextHorzTouchX < smlx->w_window && nextHorzTouchX > 0 && nextHorzTouchY < smlx->h_window && nextHorzTouchY > 0)
//     {
//         float xToCheck = nextHorzTouchX;
//         float yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);

//         if (check_next_step_2(smlx, xToCheck, yToCheck))
//         {
//             foundHorzWallHit = 1;
//             horzWallHitX = nextHorzTouchX;
//             horzWallHitY = nextHorzTouchY;
//             break;
//         }
//         else
//         {
//             nextHorzTouchX += xstep;
//             nextHorzTouchY += ystep;
//         }
//     }
//     ///////////////Vertical///////////////

//     int foundVertWallHit = 0;
//     float vertWallHitX = 0;
//     float vertWallHitY = 0;
//     // Find the x-coordinate of the closest vertical grid intersection
//     xintercept = floor(smlx->m->p_x / P_SIZE) * P_SIZE;
//     xintercept += isRayFacingRight ? P_SIZE : 0;

//     // Find the y-coordinate of the closest vertical grid intersection

//     yintercept = smlx->m->p_y + (xintercept - smlx->m->p_x) * tan(rayAngle);

//     xstep = P_SIZE;
//     xstep *= isRayFacingLeft ? -1 : 1;

//     ystep = P_SIZE * tan(rayAngle);
//     ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
//     ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;

//     float nextVertTouchX = xintercept;
//     float nextVertTouchY = yintercept;

//     while (nextVertTouchX < smlx->w_window && nextVertTouchX > 0 && nextVertTouchY < smlx->h_window && nextVertTouchY > 0)
//     {
//         float xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
//         float yToCheck = nextVertTouchY;

//         if (check_next_step_2(smlx, xToCheck, yToCheck))
//         {
//             foundVertWallHit = 1;
//             vertWallHitX = nextVertTouchX;
//             vertWallHitY = nextVertTouchY;
//             break;
//         }
//         else
//         {
//             nextVertTouchX += xstep;
//             nextVertTouchY += ystep;
//         }
//     }
//     // Calculate both horizontal and vertical distances and choose the smallest value
//     float horzHitDistance = foundHorzWallHit ? distanceBetweenPoints(smlx->m->p_x, smlx->m->p_y, horzWallHitX, horzWallHitY) : INT_MAX;
//     float vertHitDistance = foundVertWallHit ? distanceBetweenPoints(smlx->m->p_x, smlx->m->p_y, vertWallHitX, vertWallHitY) : INT_MAX;
//     if (vertHitDistance < horzHitDistance)
//     {
//         smlx->m->rays[IdCast].distance = vertHitDistance;
//         smlx->m->rays[IdCast].wallHitX = vertWallHitX;
//         smlx->m->rays[IdCast].wallHitY = vertWallHitY;
//         smlx->m->rays[IdCast].wasHitVertical = 1;
//     }
//     else
//     {
//         smlx->m->rays[IdCast].distance = horzHitDistance;
//         smlx->m->rays[IdCast].wallHitX = horzWallHitX;
//         smlx->m->rays[IdCast].wallHitY = horzWallHitY;
//         smlx->m->rays[IdCast].wasHitVertical = 0;
//     }
//     smlx->m->rays[IdCast].rayAngle = rayAngle;
//     smlx->m->rays[IdCast].isRayFacingDown = isRayFacingDown;
//     smlx->m->rays[IdCast].isRayFacingUp = isRayFacingUp;
//     smlx->m->rays[IdCast].isRayFacingLeft = isRayFacingLeft;
//     smlx->m->rays[IdCast].isRayFacingRight = isRayFacingRight;
// }
// void castAllRay(t_mlx *smlx)
// {
//     float rayAngle = smlx->m->rotationangle - (FOV_ANGLE / 2);
//     for (int IdCast = 0; IdCast < smlx->nbr_rays; IdCast++)
//     {
//         castRay(rayAngle, IdCast, smlx);
//         rayAngle += FOV_ANGLE / (float)smlx->nbr_rays;
//     }
// }

void init_vars(t_mlx *smlx)
{

    smlx->m->turndirection = 0;
    smlx->m->walkdirection = 0;
    smlx->m->rotationangle = M_PI / 2;
    smlx->m->rotatespeed = 3 * (M_PI / 180);
    smlx->m->movespeed = 2.0;
    smlx->w_window = smlx->m->w_map * P_SIZE;
    smlx->h_window = smlx->m->h_map * P_SIZE;
    smlx->nbr_rays = WINDOW_W;
    // smlx->m->rays = malloc(sizeof(t_ray) * smlx->nbr_rays);
    smlx->texture = mlx_load_png(smlx->l_ture->value);
    smlx->m->rgb = get_f_c_color(smlx->l_ture);
    smlx->floor_color = rgbcolor(ft_atoi(smlx->m->rgb[0]), ft_atoi(smlx->m->rgb[1]), ft_atoi(smlx->m->rgb[2]), 255);
    smlx->ceiling_color = rgbcolor(ft_atoi(smlx->m->rgb[3]), ft_atoi(smlx->m->rgb[4]), ft_atoi(smlx->m->rgb[5]), 255);
}

void fabs_(int *step, float dx, float dy)
{
    if (f_abs(dx) > f_abs(dy))
        *step = f_abs(dx);
    else
        *step = f_abs(dy);
}
void draw_line(t_mlx *smlx, float X1, float Y1)
{
    int steps = 0;
    float Xincrement;
    float Yincrement;
    int i;

    i = 0;
    smlx->delta_x = X1 - smlx->m->p_x;
    smlx->delta_y = Y1 - smlx->m->p_y;
    fabs_(&steps, smlx->delta_x, smlx->delta_y);
    Xincrement = smlx->delta_x / (float)steps;
    Yincrement = smlx->delta_y / (float)steps;
    smlx->newXplayer = smlx->m->p_x;
    smlx->newYplayer = smlx->m->p_y;

    while (i < steps)
    {
        if (smlx->newXplayer > 0 && smlx->newXplayer < smlx->w_window
            && smlx->newYplayer > 0 && smlx->newYplayer < smlx->h_window)
            mlx_put_pixel(smlx->img, smlx->newXplayer, smlx->newYplayer, 0x960058FF); // put pixel at (X,Y)
        smlx->newXplayer += Xincrement;
        smlx->newYplayer += Yincrement;
        i++;
    }
}

uint32_t rgbcolor(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 |a);
}
