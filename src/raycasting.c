/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarles <rcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 20:41:13 by alorain           #+#    #+#             */
/*   Updated: 2022/07/14 17:50:26 by rcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	absolute(double nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}

static void	calculate_steps(t_game *game, t_ray *ray)
{
	ray->pos.x = (int)(game->player.x);
	ray->pos.y = (int)(game->player.y);
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->dist.x = (game->player.x - ray->pos.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->dist.x = (ray->pos.x + 1.0 - game->player.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->dist.y = (game->player.y - ray->pos.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->dist.y = (ray->pos.y + 1.0 - game->player.y) * ray->delta_dist.y;
	}
}

static void	cast_ray(t_game *game, t_ray *ray)
{
	int		hit;

	hit = 0;
	calculate_steps(game, ray);
	while (!hit)
	{
		if (ray->dist.x < ray->dist.y)
		{
			ray->dist.x += ray->delta_dist.x;
			ray->pos.x += ray->step.x;
			ray->hit_side = 0;
		}
		else
		{
			ray->dist.y += ray->delta_dist.y;
			ray->pos.y += ray->step.y;
			ray->hit_side = 1;
		}
		if (game->map[ray->pos.y][ray->pos.x] > '0')
			hit = 1;
	}
	if (ray->hit_side == 0)
		ray->wall_dist = ray->dist.x - ray->delta_dist.x;
	else
		ray->wall_dist = ray->dist.y - ray->delta_dist.y;
}

static void	draw_slice(t_game *game, t_ray *ray)
{
	if (ray->hit_side == 0 && ray->dir.x < 0)
		draw_textured_slice(game, ray, game->textures[WEST]);
	if (ray->hit_side == 0 && ray->dir.x > 0)
		draw_textured_slice(game, ray, game->textures[EAST]);
	if (ray->hit_side == 1 && ray->dir.y > 0)
		draw_textured_slice(game, ray, game->textures[SOUTH]);
	if (ray->hit_side == 1 && ray->dir.y < 0)
		draw_textured_slice(game, ray, game->textures[NORTH]);
}

void	raycasting(t_game *game)
{
	int		i;
	double	plane_coef;
	t_ray	ray;

	i = 0;
	while (i < W_WIDTH)
	{
		plane_coef = 2 * (double)i / W_WIDTH - 1;
		ray.x_camera = W_WIDTH - i - 1;
		ray.dir.x = game->dir.x + game->plane.x * plane_coef;
		ray.dir.y = game->dir.y + game->plane.y * plane_coef;
		if (ray.dir.x == 0)
			ray.delta_dist.x = INFINITY;
		else
			ray.delta_dist.x = absolute(1 / ray.dir.x);
		if (ray.dir.y == 0)
			ray.delta_dist.y = INFINITY;
		else
			ray.delta_dist.y = absolute(1 / ray.dir.y);
		cast_ray(game, &ray);
		draw_slice(game, &ray);
		i++;
	}
}
