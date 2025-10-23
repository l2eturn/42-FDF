/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 02:30:29 by slimvutt          #+#    #+#             */
/*   Updated: 2025/10/24 02:30:29 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

t_map_elem	parse_elem(char *str)
{
	t_map_elem	elem;
	char		**split;
	char		*color_str;

	split = ft_split(str, ',');
	elem.z = ft_atoi(split[0]);

	if (split[1])
	{
		color_str = split[1];
		if (ft_strncmp(color_str, "0x", 2) == 0 || ft_strncmp(color_str, "0X", 2) == 0)
			elem.color = (int)strtol(color_str, NULL, 16);
		else
			elem.color = ft_atoi(color_str);
	}
	else
		elem.color = 0xFFFFFF;
	ft_free_split(split);
	return (elem);
}

	
	//printf("z=%d, color=0x%06X\n", elem.z, elem.color);