/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:26:53 by chenlee           #+#    #+#             */
/*   Updated: 2022/11/30 20:52:57 by chenlee          ###   ########.fr       */
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

t_map	*map_init(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	map->map = NULL;
	return (map);
}

int	main(int argc, char **argv)
{
	int		fd;
	void	*mlx;
	void	*mlx_win;
	t_map	*map;
	t_data	img;
	// t_coor	coordinate;

	if (argc != 2)
		error(1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error(2);
	mlx = mlx_init();
	map = map_init();
	mlx_win = mlx_new_window(mlx, 1900, 980, "Wireframe");
	img.img = mlx_new_image(mlx, 1900, 980);
	img.line_len = 5;
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_len, &img.endian);
	read_map(map, fd);
	// set_coor_start(&coordinate, 1000, 790);
	// set_coor_end(&coordinate, 1550, 590);
	// draw_aa_line(&img, &coordinate, 0, 1);
	// mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	// mlx_loop(mlx);
}
