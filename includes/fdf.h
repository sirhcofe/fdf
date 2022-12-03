/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:11:51 by chenlee           #+#    #+#             */
/*   Updated: 2022/12/02 18:11:24 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include "libft.h"

# define BUFFER_SIZE 10

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

typedef struct	s_map
{
	int				**map;
	unsigned char	peak;
	unsigned char	trough;
}				t_map;


void	error(int condition);
void	read_map(t_map *map, int fd);
char	*get_next_line(int fd);

// line drawing algo inspired by xiaolin wu's line algo
void	draw_aa_line(t_data *img, t_coor *coor, float c_start, float c_range);
void	swap(int *a, int *b);
float	calculate_gradient(t_coor *coor);
float	abs_fraction_num(float x);
int		set_color(float color_start, float tr);
int		create_trgb(int t, int r, int g, int b);


#endif