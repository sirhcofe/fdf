/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawaaline_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:45:06 by chenlee           #+#    #+#             */
/*   Updated: 2022/12/11 20:54:47 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int		set_color(double color_start, double tr)
{
	int		i;
	t_color	color;

	color.r = 0;
	color.g = 0;
	color.b = 255;
	// if (color_start <= 255)
	// 	color.g += color_start;
	// else if (color_start <= 510)
	// {
	// 	color.b -= 255;
	// 	color.g += colo_start - 255;
	// }
	// else if (color_start <= 765)
	// {
		
	// }
	i = -1;
	while (++i < color_start * 1020)
	{
		if (i < 255)
			color.g++;
		else if (i < 510)
			color.b--;
		else if (i < 765)
			color.r++;
		else
			color.g--;
	}
	return (create_trgb(0, round(color.r * tr), round(color.g * tr),
			round(color.b * tr)));
}

double	abs_fraction_num(double x)
{
	if (x < 0)
		x *= -1;
	return (x - (int)x);
}

double	calculate_gradient(t_screen *screen)
{
	double	dy;
	double	dx;
	double	gradient;

	dy = screen->y1 - screen->y0;
	dx = screen->x1 - screen->x0;
	if (dx == 0.0)
		gradient = 1;
	else
		gradient = dy / dx;
	return (gradient);
}

void	swap(int a, int b)
{
	int	temp;

	temp = a;
	a = b;
	b = temp;
}
