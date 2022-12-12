/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 17:30:37 by chenlee           #+#    #+#             */
/*   Updated: 2022/12/12 17:08:37 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	free_line(char **line)
{
	int	i;

	i = -1;
	while (line[++i] != NULL)
		free(line[i]);
	free(line);
}

/**
 * Each and every points derived from the map config file holds a homogeneous
 * coordinate vector
 * 
 * @param coord struct to contain homogenous coordinates
 * @param x the x coordinate of the projective plane
 * @param y the y coordinate of the projective plane
 * @param z the z coordinate of the projective plane
 */
void	parse(t_map *map, int i, int j, double z)
{
	map->map[i][j].x = 0.0;
	map->map[i][j].y = 0.0;
	map->map[i][j].z = z;
	map->map[i][j].w = 1.0;
	// coord->x = 0.0;
	// coord->y = 0.0;
	// coord->z = z;
	// coord->w = 1.0;
}

/**
 * Similar to ft_atoi, except function returns long instead of int
 * 
 * @param str string parsed for conversion to long
*/
long	long_atoi(const char *str)
{
	int	i;
	int	nbr;
	int	sign;

	i = 0;
	nbr = 0;
	sign = 1;
	while (str[i] == 32 || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-')
	{
		sign = sign * -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
		nbr = (nbr * 10) + (str[i++] - '0');
	nbr = nbr * sign;
	return (nbr);
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
	if (s1 != NULL)
		free(s1);
	free(s2);
	return (ptr);
}

int	compare_columns(int column_count, int j)
{
	if (j != column_count)
		return (1);
	else
		return (0);
}
