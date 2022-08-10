/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 17:02:58 by alorain           #+#    #+#             */
/*   Updated: 2022/07/06 16:15:10 by rcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	translate(t_game *game, double dir_step, double plane_step)
{
	if (dir_step)
	{
		if (game->map[(int)(game->player.y
				+ game->dir.y * 2 * dir_step)][(int)game->player.x] == '0')
			game->player.y += game->dir.y * dir_step;
		if (game->map[(int)game->player.y][(int)(game->player.x
			+ game->dir.x * 2 * dir_step)] == '0')
			game->player.x += game->dir.x * dir_step;
	}
	if (plane_step)
	{
		if (game->map[(int)(game->player.y
				+ game->plane.y * plane_step)][(int)game->player.x] == '0')
			game->player.y += game->plane.y * plane_step;
		if (game->map[(int)game->player.y][(int)(game->player.x
			+ game->plane.x * plane_step)] == '0')
			game->player.x += game->plane.x * plane_step;
	}
}

void	rotate(t_game *game, double rot_speed)
{
	double	old_x;

	old_x = game->dir.x;
	game->dir.x = old_x * cos(rot_speed) - game->dir.y * sin(rot_speed);
	game->dir.y = old_x * sin(rot_speed) + game->dir.y * cos(rot_speed);
	old_x = game->plane.x;
	game->plane.x = old_x * cos(rot_speed) - game->plane.y * sin(rot_speed);
	game->plane.y = old_x * sin(rot_speed) + game->plane.y * cos(rot_speed);
}
