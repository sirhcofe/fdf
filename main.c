/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:26:53 by chenlee           #+#    #+#             */
/*   Updated: 2022/11/23 16:13:15 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}				t_data;

typedef struct	s_coor
{
	int		x0;
	int		x1;
	int		y0;
	int		y1;
}				t_coor;

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

float	rfraction_num(float x)
{
	return (1 - fraction_num(x));
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, float brightness)
{
	char	*dst;
	float	c;
	int		color;

	c = 255 * brightness;
	color = create_trgb(0, (int)c, (int)c, (int)c);
	dst = data->addr + (y * data->line_len + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	drawAAline(t_data *img, int x0, int y0, int x1, int y1)
{
	int		steep;
	float	dx;
	float	dy;
	float	gradient;
	int		xpixel1;
	int		xpixel2;
	float	intersectY;
	int		x;

	steep = absolute(y1 - y0) > absolute(x1 - x0);
	if (steep)
	{
		swap(&x0, &y0);
		swap(&x1, &y1);
	}
	if (x0 > x1)
	{
		swap(&x0, &x1);
		swap(&y0, &y1);
	}
	dx = x1 - x0;
	dy = y1 - y0;
	if (dx == 0.0)
		gradient = 1;
	else
		gradient = dy / dx;
	xpixel1 = x0;
	xpixel2 = x1;
	intersectY = y0;
	if (steep)
	{
		x = xpixel1 - 1;
		while (++x <= xpixel2)
		{
			my_mlx_pixel_put(img, (int)intersectY, x, fraction_num(intersectY));
			my_mlx_pixel_put(img, ((int)intersectY) - 1, x, rfraction_num(intersectY));
			intersectY += gradient;
		}
	}
	else
	{
		x = xpixel1 - 1;
		while (++x <= xpixel2)
		{
			my_mlx_pixel_put(img, x, (int)intersectY, fraction_num(intersectY));
			my_mlx_pixel_put(img, x, ((int)intersectY) - 1, rfraction_num(intersectY));
			intersectY += gradient;
		}
	}
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1024, 720, "Outfile");
	img.img = mlx_new_image(mlx, 1024, 720);
	img.line_len = 5;
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_len, &img.endian);
	drawAAline(&img, 800, 500, 500, 700);
	// drawAAline(&img, 1, 1, 1919, 1079);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
