/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawaaline_y_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:24:51 by chenlee           #+#    #+#             */
/*   Updated: 2023/01/04 22:58:18 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	y_end_points(t_fdf *fdf, t_screen *sc, t_xlwu *algo, int color)
{
	algo->yend = round(sc->y0);
	algo->xend = sc->x0 + sc->gradient * (algo->yend - sc->y0);
	algo->ygap = rf_part(sc->y0 + 0.5);
	algo->ypxl1 = algo->yend;
	algo->xpxl1 = i_part(algo->xend);
	color = set_color(sc->c_start, rf_part(algo->xend) * algo->ygap);
	put_pxl(fdf, algo->xpxl1, algo->ypxl1, color);
	color = set_color(sc->c_start, f_part(algo->xend) * algo->ygap);
	put_pxl(fdf, algo->xpxl1 + 1, algo->ypxl1, color);
	algo->interx = algo->xend + sc->gradient;
	algo->yend = round(sc->y1);
	algo->xend = sc->x1 + sc->gradient * (algo->yend - sc->y1);
	algo->ygap = f_part(sc->y1 + 0.5);
	algo->ypxl2 = algo->yend;
	algo->xpxl2 = i_part(algo->xend);
	color = set_color(sc->c_start + sc->c_range,
		rf_part(algo->xend) * algo->ygap);
	put_pxl(fdf, algo->xpxl2, algo->ypxl2, color);
	color = set_color(sc->c_start + sc->c_range,
		f_part(algo->xend) * algo->ygap);
	put_pxl(fdf, algo->xpxl2 + 1, algo->ypxl2, color);
}

void	draw_along_y(t_fdf *fdf, t_screen *screen, t_xlwu *algo)
{
	int	y;
	int	color;

	color = 0;
	if (screen->y1 < screen->y0)
	{
		swap(&(screen->x0), &(screen->x1));
		swap(&(screen->y0), &(screen->y1));
		screen->c_start += screen->c_range;
		screen->c_range *= -1;
	}
	screen->gradient = (screen->x1 - screen->x0) / (screen->y1 - screen->y0);
	y_end_points(fdf, screen, algo, color);
	y = algo->ypxl1;
	while (++y < algo->ypxl2)
	{
		color = set_color(screen->c_start, rf_part(algo->xend) * algo->ygap);
		put_pxl(fdf, i_part(algo->interx), y, color);
		color = set_color(screen->c_start, f_part(algo->xend) * algo->ygap);
		put_pxl(fdf, i_part(algo->interx) + 1, y, color);
		algo->interx += screen->gradient;
		screen->c_start += screen->c_range / (algo->ypxl2 - algo->ypxl1);
	}
}