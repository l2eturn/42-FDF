/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 02:53:18 by slimvutt          #+#    #+#             */
/*   Updated: 2025/10/24 02:53:18 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include "fdf.h"

void	free_map(t_map *map)
{
	int	y;

	if (!map)
		return ;
	y = 0;
	while (y < map->height)
	{
		free(map->matrix[y]);
		y++;
	}
	free(map->matrix);
	free(map);
}

void	free_points(t_point **points, int height)
{
	int	y;

	if (!points)
		return ;
	y = 0;
	while (y < height)
	{
		free(points[y]);
		y++;
	}
	free(points);
}
