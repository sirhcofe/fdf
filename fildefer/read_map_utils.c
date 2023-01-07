/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 17:30:37 by chenlee           #+#    #+#             */
/*   Updated: 2023/01/07 18:32:17 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	relative_to_mean(t_map *map)
{
	double	total_z;
	int		coord[2];

	total_z = 0.0;
	coord[0] = -1;
	while (++coord[0] < map->row)
	{
		coord[1] = -1;
		while (++coord[1] < map->col)
			total_z += fabs(map->map[coord[0]][coord[1]].z);
	}
	total_z /= ((map->row * map->col) / 10);
	if (total_z - map->peak < -0.001)
	{
		map->ratio = total_z / map->peak;
		map->peak = total_z;
	}
	if (map->peak > 100)
	{
		map->ratio = 0.42;
		map->peak *= 0.42;
	}
	else
		map->ratio = 1.0;
}

void	relative_to_zero(t_map *map)
{
	map->peak -= map->trough;
	map->relative = map->trough;
	map->trough = 0.0;
}

void	free_line(char **lineone, char *linetwo)
{
	int	i;

	i = -1;
	while (lineone[++i] != NULL)
		free(lineone[i]);
	free(lineone);
	if (linetwo != NULL)
		free(linetwo);
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
		return (s1);
	else if (!s1 && s2)
		return (s2);
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
