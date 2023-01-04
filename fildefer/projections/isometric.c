/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:24:28 by chenlee           #+#    #+#             */
/*   Updated: 2023/01/04 14:19:38 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

/**
 * Parse in resulting coordinates of every points that will appear on the screen
 * Where point p[2] is the x & y coordinates of every point; and datum[2] will
 * serve as a reference to the starting position every time function works on 
 * the next row.
 * 
 * @param fdf struct containing mlx info and screen/wf resolution
 * @param map struct containing wireframe coordinate information
 */
void	parse_coordinate(t_fdf *fdf, t_map *map)
{
	int		p[2];
	double	datum[2];

	printf("datum1=%f\n", ((fdf->height - (fdf->wf.dot_y * (map->row + map->col - 2 + map->peak))) / 2));
	datum[0] = (fdf->width - (fdf->wf.dot_x * (map->row + map->col - 2))) / 2;
	datum[1] = ((fdf->height - (fdf->wf.dot_y * (map->row + map->col - 2 + map->peak))) / 2)
				+ (fdf->wf.dot_y * (map->col - 1 + map->peak));
	p[0] = -1;
	printf("ratio=%f\n", map->ratio);
	while (++(p[0]) < map->row)
	{
		p[1] = -1;
		while (++(p[1]) < map->col)
		{
			map->map[p[0]][p[1]].z -= map->relative;
			map->map[p[0]][p[1]].z *= map->ratio;
			map->map[p[0]][p[1]].x = datum[0] + (fdf->wf.dot_x
				* (p[1]));
			map->map[p[0]][p[1]].y = datum[1] - (fdf->wf.dot_y
				* (p[1] + map->map[p[0]][p[1]].z));
		}
		datum[0] += (fdf->wf.dot_x * 1);
		datum[1] += (fdf->wf.dot_y * 1);
	}
	print_coor(map);
}

void	get_projected_size(t_fdf *fdf, t_map *map)
{
	double	pixl_h;
	double	pixl_w;
	double	pixl_dist;

	fdf->wf.total_h = (map->peak) + (sin(0.523599) * (map->row + map->col - 2));
	pixl_h = (fdf->height * 0.9) / fdf->wf.total_h;
	fdf->wf.total_w = cos(0.523599) * (map->row + map->col - 2);
	pixl_w = (fdf->width * 0.9) / fdf->wf.total_w;
	printf("\nwframe.w=%f && wframe.h=%f\n", fdf->wf.total_w, fdf->wf.total_h);
	printf("pixl_w=%f && pixl_h=%f\n\n", pixl_w, pixl_h);
	pixl_dist = (pixl_w > pixl_h) * pixl_h + (pixl_h > pixl_w) * pixl_w;
	fdf->wf.dot_x = pixl_dist * cos(0.523599);
	fdf->wf.dot_y = pixl_dist * sin(0.523599);
	printf("wf-width=%d && wf-height=%d\n", fdf->width, fdf->height);
	printf("xdot=%f(%f) && ydot=%f(%f)\n", fdf->wf.dot_x, fdf->wf.dot_x * map->row, fdf->wf.dot_y, fdf->wf.dot_y * map->col);
}

void	isometric_view(t_fdf *fdf, t_map *map)
{
	printf("peak=%f && trough=%f\n", map->peak, map->trough);
	printf("row=%d && col=%d\n", map->row, map->col);
	get_projected_size(fdf, map);
	parse_coordinate(fdf, map);
	draw(fdf, map);
}
