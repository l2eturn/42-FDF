/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 03:52:59 by slimvutt          #+#    #+#             */
/*   Updated: 2025/10/24 03:52:59 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static uint32_t	to_rgba(int color)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

static int	get_gradient_color(int c1, int c2, float t)
{
	int	r1;
	int	g1;
	int	b1;
	int	r2;
	int	g2;
	int	b2;

	r1 = (c1 >> 16) & 0xFF;
	g1 = (c1 >> 8) & 0xFF;
	b1 = c1 & 0xFF;
	r2 = (c2 >> 16) & 0xFF;
	g2 = (c2 >> 8) & 0xFF;
	b2 = c2 & 0xFF;
	return ((r1 + (int)((r2 - r1) * t)) << 16
		| (g1 + (int)((g2 - g1) * t)) << 8
		| (b1 + (int)((b2 - b1) * t)));
}

static int	calc_steps(float dx, float dy)
{
	if (fabsf(dx) > fabsf(dy))
		return (fabsf(dx));
	return (fabsf(dy));
}

static void	draw_pixel_at(t_drawctx *ctx, float t, float x, float y)
{
	int	color;

	color = get_gradient_color(ctx->a.color, ctx->b.color, t);
	mlx_put_pixel(ctx->img, (int)x, (int)y, to_rgba(color));
}

static void	draw_step(t_drawctx *ctx, float x, float y)
{
	float	t;

	if (x < 0 || y < 0 || x >= ctx->img->width || y >= ctx->img->height)
		return ;
	if (ctx->steps == 0)
		t = 0.0f;
	else
		t = (float)ctx->i / (float)ctx->steps;
	draw_pixel_at(ctx, t, x, y);
}

static void	draw_line(t_point a, t_point b, mlx_image_t *img)
{
	t_drawctx	ctx;
	float		dx;
	float		dy;
	float		x;
	float		y;

	ctx.img = img;
	ctx.a = a;
	ctx.b = b;
	dx = b.x - a.x;
	dy = b.y - a.y;
	ctx.steps = calc_steps(dx, dy);
	x = a.x;
	y = a.y;
	ctx.i = 0;
	while (ctx.i <= ctx.steps)
	{
		draw_step(&ctx, x, y);
		x += dx / ctx.steps;
		y += dy / ctx.steps;
		ctx.i++;
	}
}

void	draw_map(t_fdf *fdf)
{
	int		y;
	int		x;
	t_point	p1;
	t_point	p2;

	y = 0;
	while (y < fdf->map->height)
	{
		x = -1;
		while (++x < fdf->map->width)
		{
			p1 = project_iso(fdf->points[y][x], fdf);
			if (x < fdf->map->width - 1)
			{
				p2 = project_iso(fdf->points[y][x + 1], fdf);
				draw_line(p1, p2, fdf->img);
			}
			if (y < fdf->map->height - 1)
			{
				p2 = project_iso(fdf->points[y + 1][x], fdf);
				draw_line(p1, p2, fdf->img);
			}
		}
		y++;
	}
}

