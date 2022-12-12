/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 19:10:03 by chenlee           #+#    #+#             */
/*   Updated: 2022/12/12 17:24:24 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

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

	i = -1;
	while (++i < map->row)
	{
		map->peak = map->map[0][0].z;
		map->trough = map->map[0][0].z;
		j = -1;
		while (++j < map->col)
		{
			// printf("peak=%f && trough=%f\n", map->peak, map->trough);
			// printf("z=%f\n", map->map[i][j].z);
			if (map->map[i][j].z > map->peak)
				map->peak = map->map[i][j].z;
			if (map->map[i][j].z < map->trough)
				map->trough = map->map[i][j].z;
		}
	}
}

void	print_cooorrr(t_map *map, int row, int col)
{
	int	i;

	i = -1;
	while (++i < col)
		printf("z of row[%d] = %f\n", row, map->map[row][i].z);
}

void	print_coor(t_map *map, int row, int col)
{
	int	i;
	int	j;

	i = -1;
	while (++i < row)
	{
		j = -1;
		while (++j < col)
			printf("coord[%d][%d] = %f\n", i, j, map->map[i][j].z);
		printf("\n");
	}
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

	printf("row=%d && col=%d\n", row, column);
	map->map = (t_coor **) malloc(sizeof(t_coor **) * row);
	i = -1;
	while (++i < row)
	{
		line = ft_split(array[i], ' ');
		map->map[i] = (t_coor *) malloc(sizeof(t_coor *) * column);
		
		j = -1;
		while (++j < column)
		{
			map->mapc[i][j].x = 0.0;
			map->map[i][j].y = 0.0;
			map->map[i][j].z = -1.0;
			map->map[i][j].w = 1.0;
			// printf("BEFOREE: i=%d && j=%d && z=%f\n\n", i, j, map->map[i][j].z);
			// map->map[i][j] = malloc(sizeof(t_coor));
			parse(map, i, j, 8.0);
			// parse(&(map->map[i][j]), 8.0);
			printf("AFTERRR: i=%d && j=%d && z=%f\n\n", i, j, map->map[i][j].z);
		}
		printf("\n");
		free_line(line);
	}
	// map->row = row;
	// map->col = column;
	parse(map, 0, 2, 8.0);
	print_cooorrr(map, 0, column);
	printf("\n");
	print_coor(map, row, column);
}

/**
 * Function checks for valid input from the map file, where invalid/repetitive
 * signs, non-digits will return error
 * 
 * @param number The number parsed for checking
 */
int	check_number(char *number)
{
	int	i;
	int	neg;

	i = 0;
	while (number[i] != 0)
	{
		if (i == 0 && (number[0] == '-' || number[0] == '+'))
		{
			if (neg == 1 && !ft_isdigit(number[1]))
				return (1);
			neg++;
			i++;
		}
		if (!ft_isdigit(number[i]))
			return (1);
		i++;
	}
	return (0);
}

/**
 * Function checks for potential errors in the map config file, where checking
 * includes non-digit input, repetitive signs for every number, MAX/MIN int
 * 
 * @param map struct containing information of homogeneous coordinate vectors
 * along with the peak and trough of the map
 * @param array map config data
 */
void	check_array_size(t_map *map, char **array, int row_count)
{
	int		i;
	int		j;
	int		column_count;
	char	**line;

	i = -1;
	column_count = 0;
	while (array[++i] != NULL)
	{
		line = ft_split(array[i], ' ');
		j = -1;
		while (line[++j] != NULL)
		{
			if (check_number(line[j]) == 1)
				error(3, map);
			if (long_atoi(line[j]) > MAX_INT || long_atoi(line[j]) < MIN_INT)
				error(4, map);
		}
		if (column_count == 0)
			column_count = j;
		else
			if (compare_columns(column_count, j) == 1)
				error(5, map);
		free_line(line);
	}
	parse_file_to_struct(map, array, column_count, row_count);
	// print_coor(map->map, map->row, map->col);
}

/**
 * Function reads data from map config file, check for potential error,
 * then the map config will be extracted to useful information through
 * get_next_line function
 * 
 * @param map struct containing information of homogeneous coordinate vectors
 * along with the peak and trough of the map
 * @param fd file descriptor registered for the opened map config file
 */
void	read_map(t_map *map, int fd)
{
	int		line_count;
	char	*line;
	char	*stored_line;
	char	**array;

	stored_line = NULL;
	line_count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		else
		{
			stored_line = join_str(stored_line, line);
			line_count++;
		}
	}
	array = ft_split(stored_line, '\n');
	map->map = ft_calloc(sizeof(int *), line_count);
	check_array_size(map, array, line_count);
	get_peak_trough(map);
	free(stored_line);
	free_line(array);
}
