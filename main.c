/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:26:53 by chenlee           #+#    #+#             */
/*   Updated: 2022/11/28 22:10:54 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include <stdio.h>

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

int	main(int argc, char **argv)
{
	int		fd;
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_coor	coordinate;

	if (argc != 2)
		error(1);
	if (fd = open(argv[1], O_RDONLY) < 0)
		error(2);
	map = initialize_map();
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1900, 980, "Wireframe");
	img.img = mlx_new_image(mlx, 1900, 980);
	img.line_len = 5;
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_len, &img.endian);
	set_coor_start(&coordinate, 350, 790);
	set_coor_end(&coordinate, 1550, 190);
	draw_aa_line(&img, &coordinate, 0, 1);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
