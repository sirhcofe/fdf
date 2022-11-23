/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:11:51 by chenlee           #+#    #+#             */
/*   Updated: 2022/11/23 19:33:43 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include "libft.h"

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}				t_data;

typedef struct	s_coor
{
	int		x0;
	int		x1;
	int		y0;
	int		y1;
}				t_coor;

typedef struct	s_color
{
	int		r;
	int		g;
	int		b;
}				t_color;

#endif