/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:11:51 by chenlee           #+#    #+#             */
/*   Updated: 2022/11/28 22:09:36 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <math.h>
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
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}				t_color;

void	error(int condition);

// line drawing algo inspired by xiaolin wu's line algo
void	draw_aa_line(t_data *img, t_coor *coor, float c_start, float c_range);
void	swap(int *a, int *b);
float	calculate_gradient(t_coor *coor);
float	fraction_num(float x);
int		set_color(float color_start, float tr);
int		create_trgb(int t, int r, int g, int b);


#endif