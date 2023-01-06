/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawaaline_x_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:15:48 by chenlee           #+#    #+#             */
/*   Updated: 2023/01/05 14:41:48 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	x_end_points(t_fdf *fdf, t_screen *sc, t_xlwu *algo, int color)
{
	algo->xend = round(sc->x0);
	algo->yend = sc->y0 + sc->gradient * (algo->xend - sc->x0);
	algo->xgap = rf_part(sc->x0 + 0.5);
	algo->xpxl1 = algo->xend;
	algo->ypxl1 = i_part(algo->yend);
	color = set_color(sc->c_start, rf_part(algo->yend) * algo->xgap);
	put_pxl(fdf, algo->xpxl1, algo->ypxl1, color);
	color = set_color(sc->c_start, f_part(algo->yend) * algo->xgap);
	put_pxl(fdf, algo->xpxl1, algo->ypxl1 + 1, color);
	algo->intery = algo->yend + sc->gradient;
	algo->xend = round(sc->x1);
	algo->yend = sc->y1 + sc->gradient * (algo->xend - sc->x1);
	algo->xgap = f_part(sc->x1 + 0.5);
	algo->xpxl2 = algo->xend;
	algo->ypxl2 = i_part(algo->yend);
	color = set_color(sc->c_start + sc->c_range,
			rf_part(algo->yend) * algo->xgap);
	put_pxl(fdf, algo->xpxl2, algo->ypxl2, color);
	color = set_color(sc->c_start + sc->c_range,
			f_part(algo->yend) * algo->xgap);
	put_pxl(fdf, algo->xpxl2, algo->ypxl2 + 1, color);
}

void	draw_along_x(t_fdf *fdf, t_screen *screen, t_xlwu *algo)
{
	int	x;
	int	color;

	color = 0;
	if (screen->x1 < screen->x0)
	{
		swap(&(screen->x0), &(screen->x1));
		swap(&(screen->y0), &(screen->y1));
		screen->c_start += screen->c_range;
		screen->c_range *= -1;
	}
	screen->gradient = (double)(screen->y1 - screen->y0)
		/ (double)(screen->x1 - screen->x0);
	x_end_points(fdf, screen, algo, color);
	x = algo->xpxl1;
	while (++x < algo->xpxl2)
	{
		color = set_color(screen->c_start, rf_part(algo->yend) * algo->xgap);
		put_pxl(fdf, x, i_part(algo->intery), color);
		color = set_color(screen->c_start, f_part(algo->yend) * algo->xgap);
		put_pxl(fdf, x, i_part(algo->intery) + 1, color);
		algo->intery += screen->gradient;
		screen->c_start += screen->c_range / (algo->xpxl2 - algo->xpxl1);
	}
}
