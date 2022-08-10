/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarles <rcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 20:17:04 by rcarles           #+#    #+#             */
/*   Updated: 2022/07/06 15:28:07 by rcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	absolute(int nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}

static void	octant1_8(t_img *frame, t_point p1, t_point p2, int color)
{
	int	e;
	int	d;
	int	dx;
	int	dy;

	e = p2.x - p1.x;
	dx = e * 2;
	dy = absolute((p2.y - p1.y) * 2);
	d = 1;
	if ((p2.y - p1.y) * 2 < 0)
		d = -1;
	while (p1.x < p2.x)
	{
		pixel_put(frame, p1, color);
		p1.x++;
		e -= dy;
		if (e < 0)
		{
			p1.y += d;
			e += dx;
		}
	}
	pixel_put(frame, p2, color);
}

static void	octant6_7(t_img *frame, t_point p1, t_point p2, int color)
{
	int	e;
	int	d;
	int	dx;
	int	dy;

	e = p2.y - p1.y;
	dy = e * 2;
	dx = absolute((p2.x - p1.x) * 2);
	d = 1;
	if ((p2.x - p1.x) * 2 < 0)
		d = -1;
	while (p1.y < p2.y)
	{
		pixel_put(frame, p1, color);
		p1.y++;
		e -= dx;
		if (e < 0)
		{
			p1.x += d;
			e += dy;
		}
	}
	pixel_put(frame, p2, color);
}

void	draw_line(t_img *frame, t_point p1, t_point p2, int color)
{
	int	dx;
	int	dy;

	dx = absolute(p2.x - p1.x);
	dy = absolute(p2.y - p1.y);
	if ((p1.x > W_WIDTH && p2.x > W_WIDTH)
		|| (p1.x < 0 && p2.x < 0)
		|| (p1.y > W_HEIGHT / 2 && p2.y > W_HEIGHT)
		|| (p1.y < 0 && p2.y < 0))
		return ;
	if (dx > dy)
	{
		if (p2.x < p1.x)
			swap_coordinates(&p1, &p2);
		octant1_8(frame, p1, p2, color);
	}
	else
	{
		if (p2.y < p1.y)
			swap_coordinates(&p1, &p2);
		octant6_7(frame, p1, p2, color);
	}
}

void	draw_lines(t_game *game, t_ray *ray, int start, int end)
{
	t_point	p1;
	t_point	p2;

	p1.x = ray->x_camera;
	p2.x = ray->x_camera;
	p1.y = start;
	p2.y = end;
	if (end != W_HEIGHT - 1)
	{
		p1.y = end;
		p2.y = W_HEIGHT;
		draw_line(game->mlx->frame, p1, p2, game->map_info->floor_color);
	}
	if (start != 0)
	{
		p1.y = 0;
		p2.y = start;
		draw_line(game->mlx->frame, p1, p2, game->map_info->ceiling_color);
	}
}
