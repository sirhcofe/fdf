/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:24:28 by chenlee           #+#    #+#             */
/*   Updated: 2023/01/05 15:46:48 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

	datum[0] = (fdf->width - (fdf->wf.dot_x * (map->row + map->col - 2))) / 2;
	datum[1] = ((fdf->height
				- (fdf->wf.dot_y * (map->row + map->col - 2 + map->peak))) / 2)
		+ (fdf->wf.dot_y * (map->col - 1 + map->peak));
	p[0] = -1;
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
	pixl_dist = (pixl_w > pixl_h) * pixl_h + (pixl_h > pixl_w) * pixl_w;
	fdf->wf.dot_x = pixl_dist * cos(0.523599);
	fdf->wf.dot_y = pixl_dist * sin(0.523599);
}

void	isometric_view(t_fdf *fdf, t_map *map)
{
	get_projected_size(fdf, map);
	parse_coordinate(fdf, map);
	draw(fdf, map);
}
