/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:08:29 by alorain           #+#    #+#             */
/*   Updated: 2022/07/18 19:29:01 by rcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rect(t_mlx *mlx, t_vector origin, int width, int height)
{
	t_point	p1;
	t_point	p2;
	int		w;

	w = 0;
	while (w < width)
	{
		p1.x = origin.x + w;
		p2.x = origin.x + w;
		p1.y = origin.y;
		p2.y = origin.y + 1 * height ;
		draw_line(mlx->frame, p1, p2, 0xFF0000);
		w++;
	}
}

void	draw_blocks(t_game *game)
{
	t_point		p1;
	t_point		p2;
	size_t		i;
	size_t		j;
	int			w;

	i = 0;
	while (i < game->map_info->max_y)
	{
		w = 0;
		j = 0;
		while (w <= MINIMAP_WIDTH && game->map[i][j])
		{
			p1 = (t_point){.x = w, .y = i * game->pixel_per_block};
			p2 = (t_point){.x = w, .y = (i + 1) * game->pixel_per_block};
			if (game->map[i][j] > '0')
				draw_line(game->mlx->frame, p1, p2, 0xFFFFFF);
			w++;
			if ((int)(w % game->pixel_per_block) == 0)
				j++;
		}
		i++;
	}
}

void	draw_map(t_game *game)
{
	t_vector	origin;
	int			width;
	int			height;

	draw_blocks(game);
	width = game->pixel_per_block / 2;
	height = game->pixel_per_block / 2;
	origin.x = game->player.x * game->pixel_per_block - width / 2;
	origin.y = game->player.y * game->pixel_per_block - height / 2;
	draw_rect(game->mlx, origin, width, height);
}
