/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 19:10:03 by chenlee           #+#    #+#             */
/*   Updated: 2022/12/02 18:16:02 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	print_map(t_map *map)
{
	int	i;

	i = 0;
	while ()
}

// void	get_peak_trough(t_map *map, char **array)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	while (array[++i] != NULL)
// 	{
// 		j = -1;
// 		while (array[i][++j] != NULL)
// 		{
// 			if (ft_atoi(array[i][j]) )
// 		}
// 	}
// }

/**
 * Function checks for valid input from the map file, where invalid/repetitive
 * signs, non-digits will return error
 * 
 * @param number The number parsed for checking
 */
void	check_number(char *number)
{
	int	i;
	int	neg;

	i = 0;
	while (number[i] != 0)
	{
		if (i == 0 && (number[0] == '-' || number[0] == '+'))
		{
			if (neg == 1 && !ft_isdigit(number[1]))
				error(3);
			neg++;
			i++;
		}
		if (!ft_isdigit(number[i]))
			error(3);
		i++;
	}
}

/**
 * Function checks for potential errors in the map config file, where checking
 * includes non-digit input, repetitive signs for every number, MAX/MIN int
 * 
 * @param array map config data
 */
void	check_array_size(t_map *map, char **array)
{
	int		i;
	int		j;
	int		column_count;
	char	**line

	i = -1;
	while (array[++i] != NULL)
	{
		line = ft_split(array[i], ' ');
		j = -1;
		while (line[++j] != NULL)
		{
			check_is_number(line[j]);
			if (ft_long_atoi(line[j] > 2147483647
				|| ft_long_atoi(line[j]) < -2147483648)
				error(4);
			else
				map[i][j] = ft_atoi(line[j]);
		}
		column_count = j;
	}
}

/**
 * Similar to ft_strjoin, with the addition where function frees the previous
 * string parsed for joining.
 * 
 * @param s1 first string for joining
 * @param s2 second string for joining
 */
char	*join_str(char *s1, char *s2)
{
	char	*ptr;
	int		s1_len;
	int		s2_len;

	if (!s1 && !s2)
		return (0);
	else if (s1 && !s2)
		return (ft_strdup(s1));
	else if (!s1 && s2)
		return (ft_strdup(s2));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!ptr)
		return (0);
	ft_memmove (ptr, s1, s1_len);
	ft_memmove ((ptr + s1_len), s2, s2_len);
	ptr[s1_len + s2_len] = '\0';
	free(s1);
	free(s2);
	return (ptr);
}

/**
 * Function reads data from map config file, check for potential error,
 * then the map config will be extracted to useful information through
 * get_next_line function
 * 
 * @param map struct that will store information of map config, along with
 * the peak/trough value
 * @param fd file descriptor registered for the opened map config file
 */
void	read_map(t_map *map, int fd)
{
	int		line_count;
	char	*line;
	char	*stored_line;
	char	**array;

	map = NULL;
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
	check_array_size(map, array);
	print_map(map);
	// get_peak_trough(map, array);
}
