/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawAAline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:39:47 by chenlee           #+#    #+#             */
/*   Updated: 2022/11/28 21:09:54 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	do_if_steep(t_coor *coor, int steep)
{
	if (steep)
	{
		swap(&coor->x0, &coor->y0);
		swap(&coor->x1, &coor->y1);
	}
	if (coor->x0 > coor->x1)
	{
		swap(&coor->x0, &coor->x1);
		swap(&coor->y0, &coor->y1);
	}
}

void	draw_aa_line(t_data *img, t_coor *coor, float c_start, float c_range)
{
	float	gradient;
	float	intersect_y;
	int		x;
	int		color;
	int		steep;

	steep = abs(coor->y1 - coor->y0) > abs(coor->x1 - coor->x0);
	do_if_steep(coor, steep);
	gradient = calculate_gradient(coor);
	intersect_y = coor->y0;
	x = coor->x0 - 1;
	while (++x <= coor->x1)
	{
		color = set_color(c_start, fraction_num(intersect_y));
		if (steep)
			my_mlx_pixel_put(img, (int)intersect_y, x, color);
		else
			my_mlx_pixel_put(img, x, (int)intersect_y, color);
		color = set_color(c_start, (1 - fraction_num(intersect_y)));
		if (steep)
			my_mlx_pixel_put(img, ((int)intersect_y) - 1, x, color);
		else
			my_mlx_pixel_put(img, x, ((int)intersect_y) - 1, color);
		c_start += c_range / (coor->x1 - coor->x0);
		intersect_y += gradient;
	}
}
