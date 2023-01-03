#include <stdio.h>
#include "fdf.h"

void	print_coor(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->row)
	{
		j = -1;
		while (++j < map->col)
			printf("coord[%d][%d] = x=%.2f, y=%.2f, z=%.2f, w=%.2f\n", i, j, map->map[i][j].x, map->map[i][j].y, map->map[i][j].z, map->map[i][j].w);
		printf("\n");
	}
}