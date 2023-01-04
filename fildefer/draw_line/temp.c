#define ipart_(X) ((int)(X))
// #define round_(X) ((int)(((double)(X)) + 0.5))
#define fpart_(X) (((double)(X))-(double)ipart_(X))
#define rfpart_(X) (1.0-fpart_(X))

void	draw_aa_line(t_fdf *fdf, t_screen *screen)
{
	double	dy;
	double	dx;
	double	gradient;

	double	xend;
	double	yend;
	double	xgap;
	double	ygap;
	int		xpxl1;
	int		ypxl1;
	int		xpxl2;
	int		ypxl2;
	double	interx;
	double	intery;

	int		x;
	int		y;
	int		color;

	dx = (double)screen->x1 - (double)screen->x0;
	dy = (double)screen->y1 - (double)screen->y0;
	if (fabs(dx) > fabs(dy))
	{
		if (screen->x1 < screen->x0)
		{
			swap(&(screen->x0), &(screen->x1));
			swap(&(screen->y0), &(screen->y1));
			screen->c_start += screen->c_range;
			screen->c_range *= -1;
		}
		gradient = dy / dx;
		//first end point
		xend = round_(screen->x0);
		yend = screen->y0 + gradient * (xend - screen->x0);
		xgap = rfpart_(screen->x0 + 0.5);
		xpxl1 = xend;
		ypxl1 = ipart_(yend);
		color = set_color(screen->c_start, rfpart_(yend) * xgap);
		put_pxl(fdf, xpxl1, ypxl1, color);
		color = set_color(screen->c_start, fpart_(yend) * xgap);
		put_pxl(fdf, xpxl1, ypxl1 + 1, color);
		intery = yend + gradient;
		//second end point
		xend = round_(screen->x1);
		yend = screen->y1 + gradient * (xend - screen->x1);
		xgap = fpart_(screen->x1 + 0.5);
		xpxl2 = xend;
		ypxl2 = ipart_(yend);
		color = set_color(screen->c_start + screen->c_range, rfpart_(yend) * xgap);
		put_pxl(fdf, xpxl2, ypxl2, color);
		color = set_color(screen->c_start + screen->c_range, fpart_(yend) * xgap);
		put_pxl(fdf, xpxl2, ypxl2 + 1, color);
		//loop
		x = xpxl1 + 1;
		while (x < xpxl2)
		{
			color = set_color(screen->c_start, rfpart_(yend) * xgap);
			put_pxl(fdf, x, ipart_(intery), color);
			color = set_color(screen->c_start, fpart_(yend) * xgap);
			put_pxl(fdf, x, ipart_(intery) + 1, color);
			intery += gradient;
			screen->c_start += screen->c_range / (xpxl2 - xpxl1);
			x++;
		}
	}
	else
	{
		if (screen->y1 < screen->y0)
		{
			swap(&(screen->x0), &(screen->x1));
			swap(&(screen->y0), &(screen->y1));
			screen->c_start += screen->c_range;
			screen->c_range *= -1;
		}
		gradient = dx / dy;
		//first
		yend = round_(screen->y0);
		xend = screen->x0 + gradient * (yend - screen->y0);
		ygap = rfpart_(screen->y0 + 0.5);
		ypxl1 = yend;
		xpxl1 = ipart_(xend);
		color = set_color(screen->c_start, rfpart_(xend) * ygap);
		put_pxl(fdf, xpxl1, ypxl1, color);
		color = set_color(screen->c_start, fpart_(xend) * ygap);
		put_pxl(fdf, xpxl1 + 1, ypxl1, color);
		interx = xend + gradient;
		//second
		yend = round_(screen->y1);
		xend = screen->x1 + gradient * (yend - screen->y1);
		ygap = fpart_(screen->y1 + 0.5);
		ypxl2 = yend;
		xpxl2 = ipart_(xend);
		color = set_color(screen->c_start + screen->c_range, rfpart_(xend) * ygap);
		put_pxl(fdf, xpxl2, ypxl2, color);
		color = set_color(screen->c_start + screen->c_range, fpart_(xend) * ygap);
		put_pxl(fdf, xpxl2 + 1, ypxl2, color);
		y = ypxl1 + 1;
		while (y < ypxl2)
		{
			// printf("loopdeloop\n");
			color = set_color(screen->c_start, rfpart_(xend) * ygap);
			put_pxl(fdf, ipart_(interx), y, color);
			color = set_color(screen->c_start, fpart_(xend) * ygap);
			put_pxl(fdf, ipart_(interx) + 1, y, color);
			interx += gradient;
			screen->c_start += screen->c_range / (ypxl2 - ypxl1);
			y++;
		}
	}
}