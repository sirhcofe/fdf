/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawaaline_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:45:06 by chenlee           #+#    #+#             */
/*   Updated: 2023/01/04 22:41:18 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	swap(double *a, double *b)
{
	double	temp;

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
