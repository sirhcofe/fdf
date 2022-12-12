/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:24:28 by chenlee           #+#    #+#             */
/*   Updated: 2022/12/11 20:18:55 by chenlee          ###   ########.fr       */
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
	int	p[2];
	int	datum[2];

	datum[0] = (fdf->width - (fdf->wf.dot_dist * map->col)) / 2;
	datum[1] = (fdf->height - (fdf->wf.dot_dist * map->row)) / 2;
	p[0] = -1;
	while (++(p[0]) < map->row)
	{
		p[1] = -1;
		while (++(p[1]) < map->col)
		{
			map->map[p[0]][p[1]].x = datum[0] + (fdf->wf.dot_dist * p[1]);
			map->map[p[0]][p[1]].y = datum[1] - (fdf->wf.dot_dist * (p[1]
						+ map->map[p[0]][p[1]].z));
		}
		datum[0] += (fdf->wf.dot_dist * (p[0] + 1));
		datum[1] += (fdf->wf.dot_dist * (p[0] + 1));
	}
}

void	get_projected_size(t_fdf *fdf, t_map *map)
{
	int	pixl_h;
	int	pixl_w;

	fdf->wf.wframe_h = (map->peak - map->trough)
					+ ((map->col * sin(0.524)) + (map->row * sin(0.524)));
	pixl_h = (fdf->height * 0.8) / fdf->wf.wframe_h;
	fdf->wf.wframe_w = (map->col * cos(0.524)) + (map->row * cos(0.524));
	pixl_w = (fdf->width * 0.8) / fdf->wf.wframe_w;
	if (pixl_h > pixl_w)
		fdf->wf.dot_dist = pixl_w;
	else
		fdf->wf.dot_dist = pixl_h;
}

void	isometric_view(t_fdf *fdf, t_map *map)
{
	get_projected_size(fdf, map);
	parse_coordinate(fdf, map);
	draw(fdf, map);
}
