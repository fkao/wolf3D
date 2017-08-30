/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 16:26:20 by fkao              #+#    #+#             */
/*   Updated: 2017/08/29 16:34:09 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		*get_row(char *line, int width)
{
	int	*row;
	int	i;

	row = (int*)malloc(sizeof(int) * width);
	i = 0;
	while (*line)
	{
		if (ft_isdigit(*line) || *line == '-')
		{
			row[i] = ft_atoi(line);
			while (*line != ' ' && *line)
				line++;
			i++;
		}
		else
			line++;
	}
	return (row);
}

int		init_map(t_wolf *e, char *file)
{
	int		fd;
	int		width;
	int		height;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		wolf_error(2);
	if (get_next_line(fd, &line) != 1)
		wolf_error(2);
	width = ft_countstr(line, ' ');
	height = 1;
	free(line);
	while (get_next_line(fd, &line) == 1)
	{
		if (ft_countstr(line, ' ') != (size_t)width)
			wolf_error(2);
		height++;
		free(line);
	}
	close(fd);
	e->map = (int**)malloc(sizeof(int*) * height);
	return (width);
}

void	get_map(t_wolf *e, char *file)
{
	int		i;
	int		fd;
	int		width;
	int		*row;
	char	*line;

	width = init_map(e, file);
	i = 0;
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		row = get_row(line, width);
		free(line);
		e->map[i++] = row;
	}
}
