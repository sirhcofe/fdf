/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:26:53 by chenlee           #+#    #+#             */
/*   Updated: 2023/01/06 19:53:22 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*map_init(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	map->map = NULL;
	map->peak = 0;
	map->trough = 0;
	map->relative = 0;
	map->ratio = 0.0;
	return (map);
}

void	get_resolution(t_fdf *fdf)
{
	char	*resolution;
	char	**width_height;
	int		fd;

	fd = open("resolution", O_RDONLY);
	resolution = get_next_line(fd);
	width_height = ft_split(resolution, 'x');
	// fdf->width = ft_atoi(width_height[0]) * 0.9;
	// fdf->height = ft_atoi(width_height[1]) * 0.9;
	fdf->width = 1920;
	fdf->height = 1080;
	free(width_height[0]);
	free(width_height[1]);
	free(width_height);
	free(resolution);
	system("rm resolution");
}

t_fdf	*fdf_init(void)
{
	t_fdf	*fdf;

	fdf = malloc(sizeof(t_fdf));
	fdf->mlx = mlx_init();
	get_resolution(fdf);
	fdf->mlx_win = mlx_new_window(fdf->mlx, fdf->width, fdf->height, "FDF");
	fdf->img = mlx_new_image(fdf->mlx, fdf->width, fdf->height);
	fdf->line_len = 5;
	fdf->addr = mlx_get_data_addr(fdf->img, &(fdf->bits_per_pixel),
			&(fdf->line_len), &(fdf->endian));
	return (fdf);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_fdf	*fdf;
	t_map	*map;

	if (argc != 2)
		error(1, NULL, NULL);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error(2, NULL, NULL);
	map = map_init();
	read_map(map, fd);
	fdf = fdf_init();
	isometric_view(fdf, map);
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, fdf->img, 0, 0);
	set_controls(fdf, map);
	mlx_loop(fdf->mlx);
}
