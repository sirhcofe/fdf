/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawaaline_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:45:06 by chenlee           #+#    #+#             */
/*   Updated: 2023/01/05 14:36:49 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	i_part(double value)
{
	return ((int)value);
}

double	f_part(double value)
{
	return (((double)(value)) - (double)i_part(value));
}

double	rf_part(double value)
{
	return (1.0 - f_part(value));
}
