/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:07:17 by khbouych          #+#    #+#             */
/*   Updated: 2023/11/11 21:02:41 by khbouych         ###   ########.fr       */
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
void castRay(float rayAngle, int IdCast, t_mlx *smlx)
{
    rayAngle = normalizeAngle(rayAngle);
    int isRayFacingDown = rayAngle > 0 && rayAngle < M_PI;
    int isRayFacingUp = !isRayFacingDown;

    int isRayFacingRight = rayAngle < 0.5 * M_PI || rayAngle > 1.5 * M_PI;
    int isRayFacingLeft = !isRayFacingRight;

    float xintercept, yintercept, xstep, ystep;
    ///////////////Horizontal///////////////
    int foundHorzWallHit = 0;
    float horzWallHitX = 0;
    float horzWallHitY = 0;
    // Find the y-coordinate of the closest horizontal grid intersection
    yintercept = floor(smlx->yplayer / P_SIZE) * P_SIZE;
    yintercept += isRayFacingDown ? P_SIZE : 0;
    // Find the x-coordinate of the closest horizontal grid intersection
    xintercept = smlx->xplayer + (yintercept - smlx->yplayer) / tan(rayAngle);
    // Calculate the increment xstep and ystep (deltax and deltay)
    ystep = P_SIZE;
    ystep *= isRayFacingUp ? -1 : 1;

    xstep = P_SIZE / tan(rayAngle);
    xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
    xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;

    float nextHorzTouchX = xintercept;
    float nextHorzTouchY = yintercept;

    while (nextHorzTouchX >= 0 && nextHorzTouchX <= WINDOW_W && nextHorzTouchY >= 0 && nextHorzTouchY <= WINDOW_H)
    {
        float xToCheck = nextHorzTouchX;
        float yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);

        if (check_next_step_2(smlx, xToCheck, yToCheck))
        {
            foundHorzWallHit = 1;
            horzWallHitX = nextHorzTouchX;
            horzWallHitY = nextHorzTouchY;
            break;
        }
        else
        {
            nextHorzTouchX += xstep;
            nextHorzTouchY += ystep;
        }
    }
    ///////////////Vertical///////////////

    int foundVertWallHit = 0;
    float vertWallHitX = 0;
    float vertWallHitY = 0;
    // Find the x-coordinate of the closest vertical grid intersection
    xintercept = floor(smlx->xplayer / P_SIZE) * P_SIZE;
    xintercept += isRayFacingRight ? P_SIZE : 0;

    // Find the y-coordinate of the closest vertical grid intersection

    yintercept = smlx->yplayer + (xintercept - smlx->xplayer) * tan(rayAngle);

    xstep = P_SIZE;
    xstep *= isRayFacingLeft ? -1 : 1;

    ystep = P_SIZE * tan(rayAngle);
    ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
    ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;

    float nextVertTouchX = xintercept;
    float nextVertTouchY = yintercept;

    while (nextVertTouchX >= 0 && nextVertTouchX <= smlx->w_window && nextVertTouchY >= 0 && nextVertTouchY <= smlx->h_window)
    {
        float xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
        float yToCheck = nextVertTouchY;

        if (check_next_step_2(smlx, xToCheck, yToCheck))
        {
            foundVertWallHit = 1;
            vertWallHitX = nextVertTouchX;
            vertWallHitY = nextVertTouchY;
            break;
        }
        else
        {
            nextVertTouchX += xstep;
            nextVertTouchY += ystep;
        }
    }
    // Calculate both horizontal and vertical distances and choose the smallest value
    float horzHitDistance = foundHorzWallHit ? distanceBetweenPoints(smlx->xplayer, smlx->yplayer, horzWallHitX, horzWallHitY) : INT_MAX;
    float vertHitDistance = foundVertWallHit ? distanceBetweenPoints(smlx->xplayer, smlx->yplayer, vertWallHitX, vertWallHitY) : INT_MAX;
    if (vertHitDistance < horzHitDistance)
    {
        smlx->m->rays[IdCast].distance = vertHitDistance;
        smlx->m->rays[IdCast].wallHitX = vertWallHitX;
        smlx->m->rays[IdCast].wallHitY = vertWallHitY;
        smlx->m->rays[IdCast].wasHitVertical = 1;
    }
    else
    {
        smlx->m->rays[IdCast].distance = horzHitDistance;
        smlx->m->rays[IdCast].wallHitX = horzWallHitX;
        smlx->m->rays[IdCast].wallHitY = horzWallHitY;
        smlx->m->rays[IdCast].wasHitVertical = 0;
    }
    smlx->m->rays[IdCast].rayAngle = rayAngle;
    smlx->m->rays[IdCast].isRayFacingDown = isRayFacingDown;
    smlx->m->rays[IdCast].isRayFacingUp = isRayFacingUp;
    smlx->m->rays[IdCast].isRayFacingLeft = isRayFacingLeft;
    smlx->m->rays[IdCast].isRayFacingRight = isRayFacingRight;
}
void castAllRay(t_mlx *smlx)
{
    float rayAngle = smlx->m->rotationangle - (FOV_ANGLE / 2);
    for (int IdCast = 0; IdCast < smlx->nbr_rays; IdCast++)
    {
        castRay(rayAngle, IdCast, smlx);
        rayAngle += FOV_ANGLE / (float)smlx->nbr_rays;
    }
}

void init_vars(t_mlx *smlx)
{

    smlx->m->turndirection = 0;
    smlx->m->walkdirection = 0;
    smlx->m->rotationangle = M_PI / 2;
    smlx->m->rotatespeed = 3 * (M_PI / 180);
    smlx->m->movespeed = 3;
    smlx->w_window = smlx->m->w_map * P_SIZE;
    smlx->h_window = smlx->m->h_map * P_SIZE;
    smlx->nbr_rays = WINDOW_W;
    smlx->m->rays = malloc(sizeof(t_ray) * smlx->nbr_rays);
}

void draw_line(t_mlx *smlx, float X1, float Y1)
{
    int steps = 0;
    float Xincrement;
    float Yincrement;
    int i;

    i = 0;
    smlx->delta_x = X1 - smlx->xplayer;
    smlx->delta_y = Y1 - smlx->yplayer;
    if (f_abs(smlx->delta_x) > f_abs(smlx->delta_y))
        steps = f_abs(smlx->delta_x);
    else
        steps = f_abs(smlx->delta_y);
    Xincrement = smlx->delta_x / (float)steps;
    Yincrement = smlx->delta_y / (float)steps;
    smlx->newXplayer = smlx->xplayer;
    smlx->newYplayer = smlx->yplayer;

    while (i < steps)
    {
        if (smlx->newXplayer > 0 && smlx->newXplayer < smlx->w_window && smlx->newYplayer > 0 && smlx->newYplayer < smlx->h_window)
            mlx_put_pixel(smlx->img, smlx->newXplayer, smlx->newYplayer, 0x960058FF); // put pixel at (X,Y)
        smlx->newXplayer += Xincrement;
        smlx->newYplayer += Yincrement;
        i++;
    }
}