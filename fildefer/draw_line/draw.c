/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 19:47:21 by chenlee           #+#    #+#             */
/*   Updated: 2023/01/04 22:45:51 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	assign_start_coor(t_screen *screen, t_map *map, int x, int y)
{
	screen->x0 = map->map[y][x].x;
	screen->y0 = map->map[y][x].y;
}

void	draw_vertical(t_fdf *fdf, t_map *map)
{
	int			y;
	int			x;
	t_screen	screen;

	y = -1;
	while (++y < map->row - 1)
	{
		x = -1;
		while (++x < map->col)
		{
			assign_start_coor(&screen, map, x, y);
			screen.x1 = map->map[y + 1][x].x;
			screen.y1 = map->map[y + 1][x].y;
			if (fabs(map->peak) < 0.0001)
				screen.c_start = 0.0;
			else
				screen.c_start = (map->map[y][x].z) / (map->peak);
			if (fabs(map->map[y + 1][x].z - map->map[y][x].z) < 0.0001)
				screen.c_range = 0.0;
			else
				screen.c_range = ((map->map[y + 1][x].z - map->map[y][x].z)
						/ (map->peak));
			draw_aa_line(fdf, &(screen));
		}
	}	
}

void	draw_horizontal(t_fdf *fdf, t_map *map)
{
	int			y;
	int			x;
	t_screen	screen;

	y = -1;
	while (++y < map->row)
	{
		x = -1;
		while (++x < map->col - 1)
		{
			assign_start_coor(&screen, map, x, y);
			screen.x1 = map->map[y][x + 1].x;
			screen.y1 = map->map[y][x + 1].y;
			if (fabs(map->peak) < 0.0001)
				screen.c_start = 0.0;
			else
				screen.c_start = (map->map[y][x].z) / (map->peak);
			if (fabs(map->map[y][x + 1].z - map->map[y][x].z) < 0.0001)
				screen.c_range = 0.0;
			else
				screen.c_range = ((map->map[y][x + 1].z - map->map[y][x].z)
						/ (map->peak));
			draw_aa_line(fdf, &screen);
		}
	}
}

void	draw(t_fdf *fdf, t_map *map)
{
	draw_vertical(fdf, map);
	draw_horizontal(fdf, map);
}
