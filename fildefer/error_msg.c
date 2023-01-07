/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 22:04:44 by chenlee           #+#    #+#             */
/*   Updated: 2023/01/07 19:09:08 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error(int condition, t_map *map, t_fdf *fdf)
{
	if (condition >= 1 && condition <= 4)
	{
		if (condition == 1)
			ft_putstr_fd("Usage: ./fdf <MAP_FILE>\n", 2);
		else if (condition == 2)
			ft_putstr_fd("Error: Invalid map file!\n", 2);
		else if (condition == 3)
			ft_putstr_fd("Error: Invalid or inconsistent map input!\n", 2);
		else if (condition == 4)
			ft_putstr_fd("Map of only one data is considered an error!\n", 2);
		if (condition == 3 || condition == 4)
			ft_free(map, fdf, 1);
		exit(1);
	}
}
