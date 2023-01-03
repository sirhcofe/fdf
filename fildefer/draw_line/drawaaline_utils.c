/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawaaline_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:45:06 by chenlee           #+#    #+#             */
/*   Updated: 2022/12/28 16:37:28 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int		set_color(double color_start, double tr)
{
	int		t_col;
	t_color	color;

	t_col = round(color_start * 1020);
	color.r = 0;
	color.g = 0;
	color.b = 255;
	color.g += (t_col <= 1020)
				* ((t_col - 255 > 0) * 255 + (t_col - 255 <= 0) * t_col);
	color.b -= (t_col > 255)
				* ((t_col - 255 > 0) * 255 + (t_col - 255 <= 0) * t_col);
	color.r += (t_col <= 1020 && t_col > 510)
				* ((t_col - 765 > 0) * 255 + (t_col - 765 <= 0) * t_col);
	color.g -= (t_col > 765)
				* (t_col - 765);
	return (create_trgb(0, round(color.r * tr), round(color.g * tr),
			round(color.b * tr)));
}

double	abs_fraction_num(double x)
{
	if (x < 0)
		x *= -1;
	return (x - (int)x);
}

double	calculate_gradient(t_screen *screen, int condition)
{
	double	dy;
	double	dx;
	double	gradient;

	dy = screen->y1 - screen->y0;
	dx = screen->x1 - screen->x0;
	if (condition == 1)
	{
		if (dx == 0.0)
			gradient = 1;
		else
			gradient = dy / dx;
	}
	else if (condition == 2)
	{
		if (dy == 0.0)
			gradient = 1;
		else
			gradient = dx / dy;
	}
	return (gradient);
}

void	swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
