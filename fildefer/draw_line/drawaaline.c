/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawaaline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:39:47 by chenlee           #+#    #+#             */
/*   Updated: 2022/12/11 23:04:34 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	c_increment(double *c_start, double *c_range, t_screen *screen)
{
	if (*c_range == 0.0)
		return ;
	else
		*(c_start) = *(c_range) / (screen->x1 - screen->x0);
}

void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	dst = fdf->addr + (y * fdf->line_len + x * (fdf->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	do_if_steep(t_screen *screen, int steep)
{
	if (steep)
	{
		swap(screen->x0, screen->y0);
		swap(screen->x1, screen->y1);
	}
	if (screen->x0 > screen->x1)
	{
		swap(screen->x0, screen->x1);
		swap(screen->y0, screen->y1);
	}
}

void	draw_aa_line(t_fdf *fdf, t_screen *screen, double c_start, double c_range)
{
	double	gradient;
	double	intersect_y;
	int		x;
	int		color;
	int		steep;

	steep = abs(screen->y1 - screen->y0) > abs(screen->x1 - screen->x0);
	do_if_steep(screen, steep);
	gradient = calculate_gradient(screen);
	intersect_y = screen->y0;
	x = screen->x0 - 1;
	while (++x <= screen->x1)
	{
		color = set_color(c_start, abs_fraction_num(intersect_y));
		if (steep)
			my_mlx_pixel_put(fdf, (int)intersect_y, x, color);
		else
			my_mlx_pixel_put(fdf, x, (int)intersect_y, color);
		color = set_color(c_start, (1 - abs_fraction_num(intersect_y)));
		if (steep)
			my_mlx_pixel_put(fdf, ((int)intersect_y) - 1, x, color);
		else
			my_mlx_pixel_put(fdf, x, ((int)intersect_y) - 1, color);
		c_increment(&c_start, &c_range, screen);
		intersect_y += gradient;
	}
}
