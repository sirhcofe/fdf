/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:19:49 by chenlee           #+#    #+#             */
/*   Updated: 2023/01/07 18:57:32 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * Function gets value of peak (highest) and trough (lowest) of the parameters.
 * These values can be useful to determine the color coordinate when drawing the
 * map
 * 
 * @param map struct containing information of homogeneous coordinate vectors
 * along with the peak and trough of the map
 */
void	get_peak_trough(t_map *map)
{
	int	i;
	int	j;

	map->peak = map->map[0][0].z;
	map->trough = map->map[0][0].z;
	i = -1;
	while (++i < map->row)
	{
		j = -1;
		while (++j < map->col)
		{
			if (map->map[i][j].z > map->peak)
				map->peak = map->map[i][j].z;
			if (map->map[i][j].z < map->trough)
				map->trough = map->map[i][j].z;
		}
	}
	if (fabs(map->trough) > 0.001)
		relative_to_zero(map);
	relative_to_mean(map);
}

/**
 * Function parse information in map config file into struct
 * 
 * @param map struct containing information of homogeneous coordinate vectors
 * along with the peak and trough of the map
 * @param array double char array storing information from map config file used
 * for int-conversion into map struct
 * @param column the column length of the map from config
 * @param row the row length of the map from config
 */
void	parse_file_to_struct(t_map *map, char **array, int column, int row)
{
	int		i;
	int		j;
	char	**line;

	if (row == 1 && column == 1)
		error(4, map, NULL);
	map->map = (t_coor **) malloc(sizeof(t_coor *) * row);
	i = -1;
	while (++i < row)
	{
		line = ft_split(array[i], ' ');
		map->map[i] = (t_coor *) malloc(sizeof(t_coor) * column);
		j = -1;
		while (++j < column)
		{
			map->map[i][j].x = 0.0;
			map->map[i][j].y = 0.0;
			map->map[i][j].z = (double)ft_atoi(line[j]);
			map->map[i][j].w = 1.0;
		}
		free_line(line, NULL);
	}
	map->row = row;
	map->col = column;
}
