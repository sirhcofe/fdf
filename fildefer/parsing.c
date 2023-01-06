/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:19:49 by chenlee           #+#    #+#             */
/*   Updated: 2023/01/06 14:33:53 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		free_line(line, NULL, NULL);
	}
	map->row = row;
	map->col = column;
}
