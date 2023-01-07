/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:29:31 by chenlee           #+#    #+#             */
/*   Updated: 2023/01/07 15:03:00 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

typedef struct	s_mem
{
	t_fdf *fdf;
	t_map *map;
}				t_mem;

int	key_press(int key, t_mem *mem)
{
	printf("key=%d\n", key);
	if (key == ESC_KEY)
	{
		ft_free(mem->map, mem->fdf, 4);
		exit(0);
	}
	return (0);
}

int	close_program(t_mem *mem)
{
	exit(0);
}

void	set_controls(t_fdf *fdf, t_map *map)
{
	mlx_key_hook(fdf->mlx_win, key_press, fdf);
	mlx_hook(fdf->mlx_win, 17, 0, close_program, fdf);
}
