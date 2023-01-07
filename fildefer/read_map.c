/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 19:10:03 by chenlee           #+#    #+#             */
/*   Updated: 2023/01/07 19:06:12 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

	if (long_atoi(number) > MAX_INT || long_atoi(number) < MIN_INT)
		return (-1);
	i = 0;
	neg = 0;
	while (number[i] != 0)
	{
		if (i == 0 && (number[0] == '-' || number[0] == '+'))
		{
			if (neg == 1 && !ft_isdigit(number[1]))
				return (-1);
			neg++;
			i++;
		}
		if (number[i] == ',' && number[i + 1] == '0' && number[i + 2] == 'x')
			return (0);
		else if (!ft_isdigit(number[i]))
			return (-1);
		i++;
	}
	return (0);
}

int	check_column(int *column_count, int j)
{
	if (*(column_count) == 0)
		*(column_count) = j;
	else if (compare_columns(*(column_count), j) == 1)
		return (1);
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
int	check_array_size(t_map *map, char **array, int row_count)
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
			if (check_number(line[j]) == -1)
			{
				free_line(line, NULL);
				return (1);
			}
		}
		free_line(line, NULL);
		if (check_column(&column_count, j) == 1)
			return (1);
	}
	parse_file_to_struct(map, array, column_count, row_count);
	return (0);
}

char	*gnl_loop(int fd, int *line_count)
{
	char	*line;
	char	*return_line;

	return_line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		else
			return_line = join_str(return_line, line);
		(*line_count)++;
	}
	return (return_line);
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
	char	*stored_line;
	char	**array;
	int		ret;

	line_count = 0;
	stored_line = gnl_loop(fd, &line_count);
	if (stored_line == NULL)
		error(3, map, NULL);
	array = ft_split(stored_line, '\n');
	ret = check_array_size(map, array, line_count);
	free_line(array, stored_line);
	if (ret == 1)
		error(3, map, NULL);
	get_peak_trough(map);
}
