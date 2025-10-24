/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_trans.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 02:01:11 by slimvutt          #+#    #+#             */
/*   Updated: 2025/10/24 02:01:11 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	get_auto_scale(t_map *map, int width, int height)
{
	float	scale_x;
	float	scale_y;

	scale_x = (float)width / (float)map->width / 1.5f;
	scale_y = (float)height / (float)map->height / 1.5f;
	if (scale_x < scale_y)
		return (scale_x);
	return (scale_y);
}

t_point project_iso(t_point p, t_fdf *fdf)
{
	t_point new;
	double 	angle;

	angle = 0.523599;
	new.x = (p.x - p.y) * cos(angle);
	new.y = (p.x + p.y) * sin(angle) - (p.z * fdf->z_scale);
	new.x += fdf->x_offset;
	new.y += fdf->y_offset;
	new.color = p.color;
	return (new);
}


t_point	**z_map_to_point(t_map *map, float scale)
{
	t_point	**point;
	int		x;
	int		y;

	point = malloc(sizeof(t_point *) * map->height);
	if (!point)
		return (NULL);
	y = 0;
	while (y < map->height)
	{
		point[y] = malloc(sizeof(t_point) * map->width);
		x = 0;
		while (x < map->width)
		{
			point[y][x].x = x * scale;
			point[y][x].y = y * scale;
			point[y][x].z = map->matrix[y][x].z;
			point[y][x].color = map->matrix[y][x].color;
			x++;
		}
		y++;
	}
	return (point);
}
