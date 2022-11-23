/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:26:53 by chenlee           #+#    #+#             */
/*   Updated: 2022/11/23 20:17:38 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include <stdio.h>

void	swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

float	absolute(float x)
{
	if (x < 0)
		return (-x);
	else
		return (x);
}

float	fraction_num(float x)
{
	if (x > 0)
		return (x - (int)x);
	else
		return (x - (((int)x) + 1));
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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
	return (create_trgb(0, (int)(color.r * tr), (int)(color.g * tr), (int)(color.b * tr)));
}

void	drawAAline(t_data *img, t_coor *coor, float color_start, float color_range)
{
	int		steep;
	float	dx;
	float	dy;
	float	gradient;
	int		xpixel1;
	int		xpixel2;
	float	intersectY;
	int		x;
	int		color;

	steep = absolute(coor->y1 - coor->y0) > absolute(coor->x1 - coor->x0);
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
	dx = coor->x1 - coor->x0;
	dy = coor->y1 - coor->y0;
	if (dx == 0.0)
		gradient = 1;
	else
		gradient = dy / dx;
	xpixel1 = coor->x0;
	xpixel2 = coor->x1;
	intersectY = coor->y0;
	if (steep)
	{
		x = xpixel1 - 1;
		while (++x <= xpixel2)
		{
			color = set_color(color_start, fraction_num(intersectY));
			my_mlx_pixel_put(img, (int)intersectY, x, color);
			color = set_color(color_start, (1 - fraction_num(intersectY)));
			my_mlx_pixel_put(img, ((int)intersectY) - 1, x, color);
			color_start += color_range / (xpixel2 - xpixel1);
			intersectY += gradient;
		}
	}
	else
	{
		x = xpixel1 - 1;
		while (++x <= xpixel2)
		{
			color = set_color(color_start, fraction_num(intersectY));
			my_mlx_pixel_put(img, x, (int)intersectY, color);
			color = set_color(color_start, (1 - fraction_num(intersectY)));
			my_mlx_pixel_put(img, x, ((int)intersectY) - 1, color);
			color_start += (color_range / (xpixel2 - xpixel1));
			intersectY += gradient;
		}
	}
}

void	set_coor_start(t_coor *coordinate, int x0, int y0)
{
	coordinate->x0 = x0;
	coordinate->y0 = y0;
}

void	set_coor_end(t_coor *coordinate, int x1, int y1)
{
	coordinate->x1 = x1;
	coordinate->y1 = y1;
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_coor	coordinate;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1900, 980, "Wireframe");
	img.img = mlx_new_image(mlx, 1900, 980);
	img.line_len = 5;
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_len, &img.endian);
	set_coor_start(&coordinate, 350, 790);
	set_coor_end(&coordinate, 1550, 190);
	drawAAline(&img, &coordinate, 0, 1);
	// drawAAline(&img, 1, 1, 1919, 1079);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
