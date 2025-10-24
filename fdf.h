/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 03:12:39 by slimvutt          #+#    #+#             */
/*   Updated: 2025/10/22 03:12:39 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "libft/libft.h"
# include "libft/get_next_line.h"
# include "MLX42/include/MLX42/MLX42.h"

typedef struct s_map_elem
{
	int	z;
	int	color;
}			t_map_elem;

typedef struct s_map
{
	t_map_elem		**matrix;
	int				width;
	int				height;
}				t_map;

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	int		color;
}	t_point;

typedef struct s_fdf
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_map		*map;
	t_point		**points;
	float		scale;
	float		z_scale;
	float		x_offset;
	float		y_offset;
}	t_fdf;

typedef struct s_drawctx
{
	mlx_image_t	*img;
	t_point		a;
	t_point		b;
	int			steps;
	int			i;
}	t_drawctx;

int				file_name_err(char	*file_name);
t_map			*read_map(char *filename);
t_point			**z_map_to_point(t_map *map, float scale);
t_point			project_iso(t_point p, t_fdf *fdf);
t_map_elem		parse_elem(char *str);
void			ft_free_split(char **split);
void			free_points(t_point **points, int height);
void			free_map(t_map *map);
void			draw_map(t_fdf *fdf);
float			get_auto_scale(t_map *map, int width, int height);
#endif
