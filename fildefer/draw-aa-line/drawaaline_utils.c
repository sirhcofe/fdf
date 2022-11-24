/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawaaline_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:45:06 by chenlee           #+#    #+#             */
/*   Updated: 2022/11/24 14:57:28 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int		set_color(float color_start, float tr)
{
	int		i;
	t_color	color;

	color.r = 0;
	color.g = 0;
	color.b = 255;
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

float	fraction_num(float x)
{
	if (x > 0)
		return (x - (int)x);
	else
		return (x - (((int)x) + 1));
}

float	calculate_gradient(t_coor *coor)
{
	float	dy;
	float	dx;
	float	gradient;

	dy = coor->y1 - coor->y0;
	dx = coor->x1 - coor->x0;
	if (dx == 0.0)
		gradient = 1;
	else
		gradient = dy / dx;
	return (gradient);
}

void	swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
