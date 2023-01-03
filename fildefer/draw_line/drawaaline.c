/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawaaline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:39:47 by chenlee           #+#    #+#             */
/*   Updated: 2022/12/28 17:19:14 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	dst = fdf->addr + (y * fdf->line_len + x * (fdf->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

#define ipart_(X) ((int)(X))
#define round_(X) ((int)(((double)(X)) + 0.5))
#define fpart_(X) (((double)(X))-(double)ipart_(X))
#define rfpart_(X) (1.0-fpart_(X))

void	draw_aa_line(t_fdf *fdf, t_screen *screen, double c_strt, double c_ran)
{
	double	dy;
	double	dx;
	double	gradient;
	double	xend;
	double	yend;
	double	xgap;
	double	ygap;
	int		xpxl1;
	int		ypxl1;
	int		xpxl2;
	int		ypxl2;
	int		x;
	int		y;
	int		color;
	double	interx;
	double	intery;

	dx = (double)screen->x1 - (double)screen->x0;
	dy = (double)screen->y1 - (double)screen->y0;
	if (fabs(dx) > fabs(dy))
	{
		if (screen->x1 < screen->x0)
		{
			swap(screen->x0, screen->x1);
			swap(screen->y0, screen->y1);
			c_strt += c_ran;
			c_ran *= -1;
		}
		gradient = dy / dx;
		//first end point
		xend = round_(screen->x0);
		yend = screen->y0 + gradient * (xend - screen->x0);
		xgap = rfpart_(screen->x0 + 0.5);
		xpxl1 = xend;
		ypxl1 = ipart_(yend);
		color = set_color(c_strt, rfpart_(yend) * xgap);
		my_mlx_pixel_put(fdf, xpxl1, ypxl1, color);
		color = set_color(c_strt, fpart_(yend) * xgap);
		my_mlx_pixel_put(fdf, xpxl1, ypxl1 + 1, color);
		intery = yend + gradient;
		//second end point
		xend = round_(screen->x1);
		yend = screen->y1 + gradient * (xend - screen->x1);
		xgap = fpart_(screen->x1 + 0.5);
		xpxl2 = xend;
		ypxl2 = ipart_(yend);
		color = set_color(c_strt + c_ran, rfpart_(yend) * xgap);
		my_mlx_pixel_put(fdf, xpxl2, ypxl2, color);
		color = set_color(c_strt + c_ran, fpart_(yend) * xgap);
		my_mlx_pixel_put(fdf, xpxl2, ypxl2 + 1, color);
		//loop
		x = xpxl1 + 1;
		while (x < xpxl2)
		{
			color = set_color(c_strt, rfpart_(yend) * xgap);
			my_mlx_pixel_put(fdf, x, ipart_(intery), color);
			color = set_color(c_strt, fpart_(yend) * xgap);
			my_mlx_pixel_put(fdf, x, ipart_(intery) + 1, color);
			intery += gradient;
			c_strt += c_ran / (xpxl2 - xpxl1);
			x++;
		}
	}
	else
	{
		if (screen->y1 < screen->y0)
		{
			swap(&(screen->x0), &(screen->x1));
			swap(&(screen->y0), &(screen->y1));
			c_strt += c_ran;
			c_ran *= -1;
		}
		gradient = dx / dy;
		//first
		yend = round_(screen->y0);
		xend = screen->x0 + gradient * (yend - screen->y0);
		ygap = rfpart_(screen->y0 + 0.5);
		ypxl1 = yend;
		xpxl1 = ipart_(xend);
		color = set_color(c_strt, rfpart_(xend) * ygap);
		my_mlx_pixel_put(fdf, xpxl1, ypxl1, color);
		color = set_color(c_strt, fpart_(xend) * ygap);
		my_mlx_pixel_put(fdf, xpxl1 + 1, ypxl1, color);
		interx = xend + gradient;
		//second
		yend = round_(screen->y1);
		xend = screen->x1 + gradient * (yend - screen->y1);
		ygap = fpart_(screen->y1 + 0.5);
		ypxl2 = yend;
		xpxl2 = ipart_(xend);
		color = set_color(c_strt + c_ran, rfpart_(xend) * ygap);
		my_mlx_pixel_put(fdf, xpxl2, ypxl2, color);
		color = set_color(c_strt + c_ran, fpart_(xend) * ygap);
		my_mlx_pixel_put(fdf, xpxl2 + 1, ypxl2, color);
		y = ypxl1 + 1;
		while (y < ypxl2)
		{
			// printf("loopdeloop\n");
			color = set_color(c_strt, rfpart_(xend) * ygap);
			my_mlx_pixel_put(fdf, ipart_(interx), y, color);
			color = set_color(c_strt, fpart_(xend) * ygap);
			my_mlx_pixel_put(fdf, ipart_(interx) + 1, y, color);
			interx += gradient;
			c_strt += c_ran / (ypxl2 - ypxl1);
			y++;
		}
	}
}

/** METHOD 2

void	c_increment(double *c_strt, double *c_ran, t_screen *screen)
{
	if (*c_ran < 0.0001)
		return ;
	else
		*(c_strt) += *(c_ran) / (screen->x1 - screen->x0);
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

void	draw_along_y(t_fdf *fdf, t_screen *screen, double c_strt, double c_ran)
{
	double	gradient;
	double	intersect;
	int		color;
	int		y;
	int		steep;

	steep = screen->y1 < screen->y0;
	do_if_steep(screen, steep);
	gradient = calculate_gradient(screen, 2);
	printf("gradient=%f\n", gradient);
	intersect = screen->x0 + gradient;
	printf("intersect=%f && abs=%f\n", intersect, abs_fraction_num(intersect));
	y = screen->y0;
	while (++y < screen->y1)
	{
		color = set_color(c_strt, abs_fraction_num(intersect));
		if (steep)
			my_mlx_pixel_put(fdf, (int)intersect, y, color);
		else
			my_mlx_pixel_put(fdf, y, (int)intersect, color);
		color = set_color(c_strt, (1 - abs_fraction_num(intersect)));
		if (steep)
			my_mlx_pixel_put(fdf, ((int)intersect) - 1, y, color);
		else
			my_mlx_pixel_put(fdf, y, ((int)intersect) - 1, color);
		c_increment(&c_strt, &c_ran, screen);
		intersect += gradient;
	}
}

void	draw_along_x(t_fdf *fdf, t_screen *screen, double c_strt, double c_ran)
{
	double	gradient;
	double	intersect;
	int		color;
	int		x;
	int		steep;

	steep = screen->x1 < screen->x0;
	do_if_steep(screen, steep);
	gradient = calculate_gradient(screen, 1);
	printf("gradient=%f\n", gradient);
	intersect = screen->y0 + gradient;
	printf("intersect=%f\n", intersect);
	x = screen->x0;
	while (++x < screen->x1)
	{
		color = set_color(c_strt, abs_fraction_num(intersect));
		if (steep)
			my_mlx_pixel_put(fdf, (int)intersect, x, color);
		else
			my_mlx_pixel_put(fdf, x, (int)intersect, color);
		color = set_color(c_strt, (1 - abs_fraction_num(intersect)));
		if (steep)
			my_mlx_pixel_put(fdf, ((int)intersect) - 1, x, color);
		else
			my_mlx_pixel_put(fdf, x, ((int)intersect) - 1, color);
		c_increment(&c_strt, &c_ran, screen);
		intersect += gradient;
	}
}

void	draw_aa_line(t_fdf *fdf, t_screen *screen, double c_strt, double c_ran)
{
	if ((screen->y1 - screen->y0) < (screen->x1 - screen->x0))
	{
		printf("X\n");
		draw_along_x(fdf, screen, c_strt, c_ran);
	}
	else
	{
		printf("Y\n");
		draw_along_y(fdf, screen, c_strt, c_ran);
	}
}

**/
