/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 00:08:30 by slimvutt          #+#    #+#             */
/*   Updated: 2025/10/23 00:08:30 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		return (1);
	fdf.map = read_map(argv[1]);
	if (!fdf.map)
	{
		free_map(fdf.map);
		return (1);
	}

	fdf.scale = get_auto_scale(fdf.map, 800, 600);
	fdf.z_scale = 1.5f;
	fdf.x_offset = 400;
	fdf.y_offset = 200;
	fdf.points = z_map_to_point(fdf.map, fdf.scale);
	fdf.mlx = mlx_init(800, 600, "FdF", true);
	fdf.img = mlx_new_image(fdf.mlx, 800, 600);
	draw_map(&fdf);
	mlx_image_to_window(fdf.mlx, fdf.img, 0, 0);
	mlx_loop(fdf.mlx);
	free_points(fdf.points, fdf.map->height);
	free_map(fdf.map);
	mlx_terminate(fdf.mlx);
	return (0);
}

//#include "fdf.h"
//#include <stdio.h>

//static void	print_map_data(t_map *map)
//{
//	int	y;
//	int	x;

//	printf("=== MAP MATRIX (z, color) ===\n");
//	for (y = 0; y < map->height; y++)
//	{
//		for (x = 0; x < map->width; x++)
//		{
//			printf("[%2d,%2d] z=%-3d color=0x%06X  ",
//				y, x, map->matrix[y][x].z, map->matrix[y][x].color);
//		}
//		printf("\n");
//	}
//	printf("==============================\n\n");
//}

//static void	print_points_data(t_point **points, t_map *map)
//{
//	int	y;
//	int	x;

//	printf("=== POINTS AFTER TRANSFORM (x,y,z,color) ===\n");
//	for (y = 0; y < map->height; y++)
//	{
//		for (x = 0; x < map->width; x++)
//		{
//			printf("[%2d,%2d] x=%7.2f y=%7.2f z=%7.2f color=0x%06X  \n",
//				y, x,
//				points[y][x].x,
//				points[y][x].y,
//				points[y][x].z,
//				points[y][x].color);
//		}
//		printf("\n");
//	}
//	printf("=============================================\n\n");
//}

//int	main(int argc, char **argv)
//{
//	t_fdf	fdf;

//	if (argc != 2)
//	{
//		printf("Usage: ./fdf <mapfile.fdf>\n");
//		return (1);
//	}

//	fdf.map = read_map(argv[1]);
//	if (!fdf.map)
//	{
//		printf("Error: failed to load map\n");
//		return (1);
//	}

//	// basic setup
//	fdf.scale = get_auto_scale(fdf.map, 800, 600);
//	fdf.z_scale = 2.0f;
//	fdf.x_offset = 400;
//	fdf.y_offset = 300;

//	// create points
//	fdf.points = z_map_to_point(fdf.map, fdf.scale);

//	// print raw map and transformed points
//	print_map_data(fdf.map);
//	print_points_data(fdf.points, fdf.map);

//	// free
//	free_points(fdf.points, fdf.map->height);
//	free_map(fdf.map);

//	return (0);
//}
