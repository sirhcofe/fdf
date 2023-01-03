/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 19:47:21 by chenlee           #+#    #+#             */
/*   Updated: 2023/01/03 16:30:03 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	draw_vertical(t_fdf *fdf, t_map *map)
{
	int			y;
	int			x;
	double		c_start;
	double		c_range;
	t_screen	screen;

	y = -1;
	while (++y < map->row - 1)
	{
		x = -1;
		while (++x < map->col)
		{
			screen.x0 = map->map[y][x].x;
			screen.y0 = map->map[y][x].y;
			screen.x1 = map->map[y + 1][x].x;
			screen.y1 = map->map[y + 1][x].y;
			if (fabs(map->peak - map->trough) < 0.0001)
				c_start = 0.0;
			else
				c_start = (map->map[y][x].z - map->trough) / (map->peak - map->trough);
			if (fabs(map->peak - map->trough) < 0.0001
					|| fabs(map->map[y + 1][x].z - map->map[y][x].z) < 0.0001)
				c_range = 0.0;
			else
				c_range = (map->map[y + 1][x].z - map->map[y][x].z)
							/ (map->peak - map->trough);
			draw_aa_line(fdf, &screen, c_start, c_range);
		}
	}	
}

void	draw_horizontal(t_fdf *fdf, t_map *map)
{
	int			y;
	int			x;
	double		c_start;
	double		c_range;
	t_screen	screen;

	y = -1;
	while (++y < map->row)
	{
		x = -1;
		while (++x < map->col - 1)
		{
			screen.x0 = map->map[y][x].x;
			screen.y0 = map->map[y][x].y;
			screen.x1 = map->map[y][x + 1].x;
			screen.y1 = map->map[y][x + 1].y;
			if (fabs(map->peak - map->trough) < 0.0001)
				c_start = 0.0;
			else
				c_start = (map->map[y][x].z - map->trough) / (map->peak - map->trough);
			if ((fabs(map->peak - map->trough) < 0.0001)
					|| (fabs(map->map[y][x + 1].z - map->map[y][x].z) < 0.0001))
				c_range = 0.0;
			else
				c_range = ((map->map[y][x + 1].z - map->map[y][x].z)
								/ (map->peak - map->trough));
			draw_aa_line(fdf, &screen, c_start, c_range);
		}
	}
}

void	draw(t_fdf *fdf, t_map *map)
{
	draw_vertical(fdf, map);
	draw_horizontal(fdf, map);
}
