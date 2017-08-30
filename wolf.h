/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 13:31:59 by fkao              #+#    #+#             */
/*   Updated: 2017/08/29 18:27:42 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# include "libft.h"
# include "mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# define UP 126
# define DOWN 125
# define RIGHT 124
# define LEFT 123
# define ESC 53
# define RED 0xFF008C
# define BLUE 0x00A1FF
# define YELLOW 0xFFFF00
# define PURPLE 0x9D00FF
# define GREEN 0x00FF7B
# define ORANGE 0xFFA100

typedef struct	s_axis
{
	double		x;
	double		y;
}				t_axis;

typedef struct	s_code
{
	int			up;
	int			down;
	int			right;
	int			left;
}				t_code;

typedef struct	s_wolf
{
	int			**map;
	void		*mlx;
	void		*win;
	void		*img;
	int			*pix;
	int			bpp;
	int			size;
	int			endian;
	int			w;
	int			h;
	t_axis		pos;
	t_axis		dir;
	t_axis		plane;
	t_code		key;
}				t_wolf;

typedef struct	s_cast
{
	t_axis		pos;
	t_axis		dir;
	t_axis		sidedis;
	t_axis		deltadis;
	double		dis;
	int			mapx;
	int			mapy;
	int			stepx;
	int			stepy;
	int			side;
	int			wall;
}				t_cast;

void			get_map(t_wolf *e, char *file);
void			ray_cast(t_wolf *e);
void			wolf_move(t_wolf *e);
void			wolf_turn(t_wolf *e);
int				loop_hook(t_wolf *e);
int				press_hook(int code, t_wolf *e);
int				release_hook(int code, t_wolf *e);
int				exit_hook(t_wolf *e);
void			wolf_error(int i);
#endif
