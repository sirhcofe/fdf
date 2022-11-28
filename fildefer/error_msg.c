/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 22:04:44 by chenlee           #+#    #+#             */
/*   Updated: 2022/11/28 22:10:17 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error(int condition)
{
	if (condition == 1 || condition == 2)
	{
		if (condition == 1)
			ft_putstr("Usage: ./fdf <MAP_FILE>", 2);
		else if (condition == 2)
			ft_putstr("Error: Invalid map file", 2);
		exit(1);
	}
}
