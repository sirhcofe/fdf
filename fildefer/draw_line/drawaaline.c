/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawaaline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:39:47 by chenlee           #+#    #+#             */
/*   Updated: 2023/01/06 10:18:54 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	put_pxl(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	dst = fdf->addr + (y * fdf->line_len + x * (fdf->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	set_color(double color_start, double tr)
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

void	draw_aa_line(t_fdf *fdf, t_screen *screen)
{
	t_xlwu	algo;

	if (abs(screen->x1 - screen->x0) > abs(screen->y1 - screen->y0))
		draw_along_x(fdf, screen, &algo);
	else
		draw_along_y(fdf, screen, &algo);
}
