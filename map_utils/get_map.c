/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 00:27:41 by slimvutt          #+#    #+#             */
/*   Updated: 2025/10/23 00:27:41 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_words(char **split)
{
	int	count;

	count = 0;
	while (split[count])
		count++;
	return (count);
}

void	ft_free_split(char **nums)
{
	int	i;

	i = 0;
	while (nums[i])
		free(nums[i++]);
	free(nums);
}

static void	get_map_size(char *filename, t_map *map)
{
	int		fd;
	char	*line;
	char	**split;

	map->width = 0;
	map->height = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		if (map->width == 0)
		{
			split = ft_split(line, ' ');
			map->width = count_words(split);
			ft_free_split(split);
		}
		map->height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

static t_map_elem	*get_map_row(char *line, int width)
{
	char		**split;
	t_map_elem	*row;
	int			i;

	i = 0;
	split = ft_split(line, ' ');
	row = malloc(sizeof(t_map_elem) * width);
	while (i < width)
	{
		row[i] = parse_elem(split[i]);
		i++;
	}
	ft_free_split(split);
	return (row);
}

t_map	*read_map(char *filename)
{
	t_map	*map;
	int		fd;
	char	*line;
	int		y;

	y = 0;
	map = malloc(sizeof(t_map));
	fd = open(filename, O_RDONLY);
	if (!map || fd < 0)
	{
		free(map);
		return (NULL);
	}
	get_map_size(filename, map);
	map->matrix = malloc(sizeof(t_map_elem *) * map->height);
	line = get_next_line(fd);
	while (line)
	{
		map->matrix[y++] = get_map_row(line, map->width);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (map);
}
