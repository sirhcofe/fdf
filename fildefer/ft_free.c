/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:53:45 by chenlee           #+#    #+#             */
/*   Updated: 2023/01/06 19:38:07 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_free(t_map *map, t_fdf *fdf, int situation)
{
	int	i;

	if (situation == 1 || situation == 2 || situation == 4)
	{
		if (situation != 1)
		{
			i = -1;
			while (++i < map->row)
				free(map->map[i]);
		}
		free(map->map);
		free(map);
	}
	if (situation == 3 || situation == 4)
	{
		mlx_destroy_window(fdf->mlx, fdf->mlx_win);
		free(fdf->img);
		free(fdf->addr);
		fdf->img = NULL;
		fdf->addr = NULL;
		free(fdf);
	}
}
