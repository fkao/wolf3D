/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 18:23:30 by fkao              #+#    #+#             */
/*   Updated: 2017/08/29 18:24:22 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		exit_hook(t_wolf *e)
{
	mlx_destroy_window(e->mlx, e->win);
	exit(0);
}

int		release_hook(int code, t_wolf *e)
{
	if (code == UP)
		e->key.up = 0;
	if (code == DOWN)
		e->key.down = 0;
	if (code == RIGHT)
		e->key.right = 0;
	if (code == LEFT)
		e->key.left = 0;
	return (0);
}

int		press_hook(int code, t_wolf *e)
{
	if (code == UP)
		e->key.up = 1;
	if (code == DOWN)
		e->key.down = 1;
	if (code == RIGHT)
		e->key.right = 1;
	if (code == LEFT)
		e->key.left = 1;
	if (code == ESC)
		exit_hook(e);
	return (0);
}

int		loop_hook(t_wolf *e)
{
	e->img = mlx_new_image(e->mlx, e->w, e->h);
	e->pix = (int*)mlx_get_data_addr(e->img, &e->bpp, &e->size, &e->endian);
	wolf_move(e);
	wolf_turn(e);
	ray_cast(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	mlx_destroy_image(e->mlx, e->img);
	return (0);
}
