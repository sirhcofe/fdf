/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:29:31 by chenlee           #+#    #+#             */
/*   Updated: 2023/01/06 15:11:17 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int	key_press(int key, void *memory)
{
	printf("key=%d\n", key);
	if (key == ESC_KEY)
	{
		ft_free(((t_mem *)memory)->map, ((t_mem *)memory)->fdf, 3);
		exit(0);
	}
	return (0);
}

int	close_program(void *memory)
{
	ft_free(((t_mem *)memory)->map, ((t_mem *)memory)->fdf, 3);
	exit(0);
}

void	set_controls(t_fdf *fdf, t_map *map)
{
	t_mem	memory;

	memory.fdf = fdf;
	memory.map = map;
	mlx_hook(fdf->mlx_win, 2, 0, key_press, &memory);
	mlx_hook(fdf->mlx_win, 17, 0, close_program, &memory);
}
