/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 17:30:37 by chenlee           #+#    #+#             */
/*   Updated: 2023/01/03 16:01:52 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	get_peak_trough_coor(t_map *map, int i, int j, int condition)
{
	if (condition == 1)
	{
		map->pk_coor[0] = i;
		map->pk_coor[1] = j;
	}
	else if (condition == 2)
	{
		map->tr_coor[0] = i;
		map->tr_coor[1] = j;
	}
}

void	relative_to_zero(t_map *map)
{
	map->peak -= map->trough;
	map->relative = map->trough;
	map->trough = 0.0;
}

void	free_line(char **line)
{
	int	i;

	i = -1;
	while (line[++i] != NULL)
		free(line[i]);
	free(line);
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
