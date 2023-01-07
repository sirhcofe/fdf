/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:29:31 by chenlee           #+#    #+#             */
/*   Updated: 2023/01/07 19:09:31 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_keycode(void)
{
	int		fd;
	int		ret;
	char	*key;

	fd = open("keycode", O_RDONLY);
	key = get_next_line(fd);
	ret = ft_atoi(key);
	free(key);
	return (ret);
}

int	key_press(int key, t_mem *mem)
{
	int	esc_key;

	esc_key = get_keycode();
	if (key == esc_key)
	{
		ft_free(mem->map, mem->fdf, 4);
		exit(0);
	}
	return (0);
}

int	close_program(t_mem *mem)
{
	ft_free(mem->map, mem->fdf, 4);
	exit(0);
}

void	set_controls(t_mem *mem)
{
	mlx_key_hook(mem->fdf->mlx_win, key_press, mem);
	mlx_hook(mem->fdf->mlx_win, 17, 0, close_program, mem);
}
