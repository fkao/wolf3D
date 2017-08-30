/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_cast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 12:49:58 by fkao              #+#    #+#             */
/*   Updated: 2017/08/29 18:28:18 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	wall_color(t_wolf *e, t_cast *ray, int x)
{
	int	start;
	int	end;
	int	color;
	int	y;

	start = -ray->wall / 2 + e->h / 2;
	if (start < 0)
		start = 0;
	end = ray->wall / 2 + e->h / 2;
	if (end >= e->h)
		end = e->h - 1;
	if (ray->side == 1)
		color = (ray->stepy == -1) ? RED : YELLOW;
	else
		color = (ray->stepx == -1) ? PURPLE : ORANGE;
	y = -1;
	while (++y < start)
		e->pix[x + y * e->size / 4] = BLUE;
	y = start - 1;
	while (++y <= end)
		e->pix[x + y * e->size / 4] = color;
	y = end;
	while (++y < e->h)
		e->pix[x + y * e->size / 4] = GREEN;
}

void	digital_diff(t_wolf *e, t_cast *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sidedis.x < ray->sidedis.y)
		{
			ray->sidedis.x += ray->deltadis.x;
			ray->mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sidedis.y += ray->deltadis.y;
			ray->mapy += ray->stepy;
			ray->side = 1;
		}
		if (e->map[ray->mapx][ray->mapy] > 0)
			hit = 1;
	}
	if (ray->side == 0)
		ray->dis = (ray->mapx - ray->pos.x + (1 - ray->stepx) / 2) / ray->dir.x;
	else
		ray->dis = (ray->mapy - ray->pos.y + (1 - ray->stepy) / 2) / ray->dir.y;
	ray->wall = (int)(e->h / ray->dis);
}

void	init_dist(t_cast *ray)
{
	if (ray->dir.x < 0)
	{
		ray->stepx = -1;
		ray->sidedis.x = (ray->pos.x - ray->mapx) * ray->deltadis.x;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedis.x = (ray->mapx + 1.0 - ray->pos.x) * ray->deltadis.x;
	}
	if (ray->dir.y < 0)
	{
		ray->stepy = -1;
		ray->sidedis.y = (ray->pos.y - ray->mapy) * ray->deltadis.y;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedis.y = (ray->mapy + 1.0 - ray->pos.y) * ray->deltadis.y;
	}
}

void	init_cast(t_wolf *e, t_cast *ray, int x)
{
	double	cam;

	cam = 2 * x / (double)e->w - 1;
	ray->pos.x = e->pos.x;
	ray->pos.y = e->pos.y;
	ray->dir.x = e->dir.x + e->plane.x * cam;
	ray->dir.y = e->dir.y + e->plane.y * cam;
	ray->mapx = (int)ray->pos.x;
	ray->mapy = (int)ray->pos.y;
	ray->deltadis.x = sqrt(1 + (ray->dir.y * ray->dir.y) /
		(ray->dir.x * ray->dir.x));
	ray->deltadis.y = sqrt(1 + (ray->dir.x * ray->dir.x) /
		(ray->dir.y * ray->dir.y));
}

void	ray_cast(t_wolf *e)
{
	t_cast	*ray;
	int		x;

	ray = (t_cast*)ft_memalloc(sizeof(t_cast));
	x = -1;
	while (++x < e->w)
	{
		init_cast(e, ray, x);
		init_dist(ray);
		digital_diff(e, ray);
		wall_color(e, ray, x);
	}
	free(ray);
}
