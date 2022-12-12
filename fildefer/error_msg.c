/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 22:04:44 by chenlee           #+#    #+#             */
/*   Updated: 2022/12/02 17:43:22 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// 1 - 2 no free
// 3 - 5 free map*
void	error(int condition, t_map *map)
{
	if (condition >= 1 && condition <= 5)
	{
		if (condition == 1)
			ft_putstr_fd("Usage: ./fdf <MAP_FILE>", 2);
		else if (condition == 2)
			ft_putstr_fd("Error: Invalid map file!", 2);
		else if (condition == 3)
			ft_putstr_fd("Error: Invalid map input!", 2);
		else if (condition == 4)
			ft_putstr_fd("Error: Max/Min Int exceeded!", 2);
		else if (condition == 5)
			ft_putstr_fd("Error: Inconsistent map size!", 2);
		if (condition >= 3 && condition <= 5)
			ft_free(map);
		exit(1);
	}
}
