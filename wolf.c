/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 13:30:35 by fkao              #+#    #+#             */
/*   Updated: 2017/08/29 18:26:07 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	wolf_error(int i)
{
	if (i == 1)
		ft_putendl("usage: ./wolf3d [map]");
	if (i == 2)
		ft_putendl("map error: invalid map");
	exit(1);
}

void	wolf_move(t_wolf *e)
{
	double	walk;

	walk = 0.09;
	if (e->key.up)
	{
		if (e->map[(int)(e->pos.x + e->dir.x * walk)][(int)e->pos.y] == 0)
			e->pos.x += e->dir.x * walk;
		if (e->map[(int)e->pos.x][(int)(e->pos.y + e->dir.y * walk)] == 0)
			e->pos.y += e->dir.y * walk;
	}
	if (e->key.down)
	{
		if (e->map[(int)(e->pos.x - e->dir.x * walk)][(int)e->pos.y] == 0)
			e->pos.x -= e->dir.x * walk;
		if (e->map[(int)e->pos.x][(int)(e->pos.y - e->dir.y * walk)] == 0)
			e->pos.y -= e->dir.y * walk;
	}
}

void	wolf_turn(t_wolf *e)
{
	double	turn;
	double	olddir_x;
	double	oldplane_x;

	turn = 0.06;
	if (e->key.right || e->key.left)
	{
		turn *= (e->key.right) ? -1 : 1;
		olddir_x = e->dir.x;
		e->dir.x = e->dir.x * cos(turn) - e->dir.y * sin(turn);
		e->dir.y = olddir_x * sin(turn) + e->dir.y * cos(turn);
		oldplane_x = e->plane.x;
		e->plane.x = e->plane.x * cos(turn) - e->plane.y * sin(turn);
		e->plane.y = oldplane_x * sin(turn) + e->plane.y * cos(turn);
	}
}

void	wolf3d(char *file)
{
	t_wolf	*e;

	e = (t_wolf*)ft_memalloc(sizeof(t_wolf));
	get_map(e, file);
	e->w = 900;
	e->h = 600;
	e->pos.x = 2;
	e->pos.y = 2;
	e->dir.x = 1;
	e->dir.y = 0;
	e->plane.x = 0;
	e->plane.y = -0.66;
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, e->w, e->h, "Wolf3D");
	mlx_hook(e->win, 2, 0, press_hook, e);
	mlx_hook(e->win, 3, 0, release_hook, e);
	mlx_hook(e->win, 17, 0, exit_hook, e);
	mlx_loop_hook(e->mlx, loop_hook, e);
	mlx_loop(e->mlx);
}

int		main(int ac, char **av)
{
	if (ac != 2)
		wolf_error(1);
	else
		wolf3d(av[1]);
	return (0);
}
