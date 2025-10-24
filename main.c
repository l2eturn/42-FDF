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

static int	check_file_name(char *name)
{
	int	len;

	len = ft_strlen(name);
	if (len < 5)
		return (0);
	if (ft_strncmp(name + len - 4, ".fdf", 4) != 0)
		return (0);
	return (1);
}

static void	close_fdf(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (fdf->points)
		free_points(fdf->points, fdf->map->height);
	if (fdf->map)
		free_map(fdf->map);
	if (fdf->mlx)
		mlx_terminate(fdf->mlx);
	exit(0);
}

static void	key_hook(mlx_key_data_t key, void *param)
{
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
		close_fdf(param);
}

static int	err_handle(int ac, char **av, t_fdf *fdf)
{
	if (ac != 2)
	{
		ft_putendl_fd("Usage: ./fdf <mapfile.fdf>", 2);
		return (1);
	}
	if (!check_file_name(av[1]))
	{
		ft_putendl_fd("Error: File must have .fdf extension", 2);
		return (1);
	}
	fdf->map = read_map(av[1]);
	if (!fdf->map)
	{
		ft_putendl_fd("Error: Failed to load map file", 2);
		free_map(fdf->map);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_fdf	fdf;

	if (err_handle(ac, av, &fdf))
		return (1);
	fdf.scale = get_auto_scale(fdf.map, 800, 600);
	fdf.z_scale = 1.5f;
	fdf.x_offset = 400;
	fdf.y_offset = 200;
	fdf.points = z_map_to_point(fdf.map, fdf.scale);
	fdf.mlx = mlx_init(800, 600, "FdF", true);
	if (!fdf.mlx)
		close_fdf(&fdf);
	fdf.img = mlx_new_image(fdf.mlx, 800, 600);
	if (!fdf.img)
		close_fdf(&fdf);
	draw_map(&fdf);
	mlx_image_to_window(fdf.mlx, fdf.img, 0, 0);
	mlx_key_hook(fdf.mlx, key_hook, &fdf);
	mlx_close_hook(fdf.mlx, close_fdf, &fdf);
	mlx_loop(fdf.mlx);
	close_fdf(&fdf);
	return (0);
}

//int	main(int argc, char **argv)
//{
//	t_fdf	fdf;

//	if (argc != 2)
//		return (1);
//	fdf.map = read_map(argv[1]);
//	if (!fdf.map)
//	{
//		free_map(fdf.map);
//		return (1);
//	}

//	fdf.scale = get_auto_scale(fdf.map, 800, 600);
//	fdf.z_scale = 1.5f;
//	fdf.x_offset = 400;
//	fdf.y_offset = 200;
//	fdf.points = z_map_to_point(fdf.map, fdf.scale);
//	fdf.mlx = mlx_init(800, 600, "FdF", true);
//	fdf.img = mlx_new_image(fdf.mlx, 800, 600);
//	draw_map(&fdf);
//	mlx_image_to_window(fdf.mlx, fdf.img, 0, 0);
//	mlx_loop(fdf.mlx);
//	free_points(fdf.points, fdf.map->height);
//	free_map(fdf.map);
//	mlx_terminate(fdf.mlx);
//	return (0);
//}