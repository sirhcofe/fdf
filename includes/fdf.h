/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:11:51 by chenlee           #+#    #+#             */
/*   Updated: 2022/12/12 17:09:00 by chenlee          ###   ########.fr       */
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
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	max_x;
	int	max_y;
}				t_screen;


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
}				t_map;

typedef struct	s_wframe
{
	int		wframe_h;
	int		wframe_w;
	int		dot_dist;
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
void	parse(t_map *map, int i, int j, double z);
void	free_line(char **line);
long	long_atoi(const char *str);
int		compare_columns(int column_count, int j);

// line drawing function
void	draw(t_fdf *fdf, t_map *map);

// line drawing algo inspired by xiaolin wu's line algo
void	draw_aa_line(t_fdf *fdf, t_screen *screen, double c_start, double c_range);
void	swap(int a, int b);
double	calculate_gradient(t_screen *screen);
double	abs_fraction_num(double x);
int		set_color(double color_start, double tr);
int		create_trgb(int t, int r, int g, int b);

// isometric
void	isometric_view(t_fdf *fdf, t_map *map);

#endif