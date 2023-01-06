/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:53:45 by chenlee           #+#    #+#             */
/*   Updated: 2023/01/06 14:05:21 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_free(t_map *map, t_fdf *fdf, int situation)
{
	int	i;

	if (situation == 1 || situation == 2 || situation == 4)
	{
		i = -1;
		if (situation != 1)
		{
			while (++i < map->row)
				free(map->map[i]);
		}
		free(map);
	}
	if (situation == 3 || situation == 4)
	{
		fdf->img = NULL;
		fdf->addr = NULL;
		free(fdf);
	}
}
