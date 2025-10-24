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
