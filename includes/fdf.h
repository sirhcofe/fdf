/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:11:51 by chenlee           #+#    #+#             */
/*   Updated: 2023/01/04 22:41:27 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include "libft.h"

# define BUFFER_SIZE 10
# define MAX_INT 2147483647
# define MIN_INT -2147483648

typedef struct	s_coor
{
	double	x;
	double	y;
	double	z;
	double	w;
}				t_coor;

typedef struct	s_screen
{
	double	x0;
	double	y0;
	double	x1;
	double	y1;
	double	max_x;
	double	max_y;
	double	gradient;
	double	c_start;
	double	c_range;
}				t_screen;

typedef struct	s_xlwu
{
	double	xend;
	double	yend;
	double	xgap;
	double	ygap;
	double	interx;
	double	intery;
	int		xpxl1;
	int		ypxl1;
	int		xpxl2;
	int		ypxl2;
}				t_xlwu;

typedef struct	s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}				t_color;

typedef struct	s_map
{
	t_coor	**map;
	int		row;
	int		col;
	double	peak;
	double	trough;
	double	relative;
	double	ratio;
}				t_map;

typedef struct	s_wframe
{
	double	total_h;
	double	total_w;
	int		dot_dist;
	double	dot_x;
	double	dot_y;
}				t_wframe;


typedef struct	s_fdf
{
	void		*mlx;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_len;
	int			endian;
	int			width;
	int			height;
	t_wframe	wf;
}				t_fdf;

void	error(int condition, t_map *map);
void    ft_free(t_map *map);

// read map function
char	*get_next_line(int fd);
char	*join_str(char *s1, char *s2);
void	read_map(t_map *map, int fd);
void	free_line(char **line);
int		compare_columns(int column_count, int j);
void	relative_to_zero(t_map *map);
void	relative_to_mean(t_map *map);

// line drawing function
void	draw(t_fdf *fdf, t_map *map);

// line drawing algo inspired by xiaolin wu's line algo
void	draw_aa_line(t_fdf *fdf, t_screen *screen);
void	draw_along_x(t_fdf *fdf, t_screen *screen, t_xlwu *algo);
void	draw_along_y(t_fdf *fdf, t_screen *screen, t_xlwu *algo);
void	swap(double *a, double *b);
int		i_part(double value);
double	f_part(double value);
double	rf_part(double value);
int		set_color(double color_start, double tr);
void	put_pxl(t_fdf *fdf, int x, int y, int color);

// isometric
void	isometric_view(t_fdf *fdf, t_map *map);

void	print_coor(t_map *map);

#endif