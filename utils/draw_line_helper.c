/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 03:09:35 by slimvutt          #+#    #+#             */
/*   Updated: 2025/10/25 03:09:35 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

uint32_t	to_rgba(int color)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

int	get_gradient_color(int c1, int c2, float t)
{
	t_rgb	c[2];

	c[0].r = (c1 >> 16) & 0xFF;
	c[0].g = (c1 >> 8) & 0xFF;
	c[0].b = c1 & 0xFF;
	c[1].r = (c2 >> 16) & 0xFF;
	c[1].g = (c2 >> 8) & 0xFF;
	c[1].b = c2 & 0xFF;
	return ((c[0].r + (int)((c[1].r - c[0].r) * t)) << 16
		| (c[0].g + (int)((c[1].g - c[0].g) * t)) << 8
		| (c[0].b + (int)((c[1].b - c[0].b) * t)));
}
