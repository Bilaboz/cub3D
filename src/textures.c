/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarles <rcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 17:29:58 by alorain           #+#    #+#             */
/*   Updated: 2022/07/06 15:20:48 by rcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	copy_tex_to_frame(t_game *game, t_ray *r, t_texture tex, t_slice slice)
{
	int	y;

	y = slice.draw_start;
	while (y <= slice.draw_end)
	{
		slice.y_tex_offset = (int)slice.tex_pos & (tex.height - 1);
		slice.tex_pos += slice.step;
		ft_memcpy(game->mlx->frame->addr
			+ ((game->mlx->frame->size_l * y) + r->x_camera * 4),
			tex.frame.addr + ((tex.frame.size_l * slice.y_tex_offset)
				+ slice.x_tex_offset * 4), 4);
		y++;
	}
}

void	draw_textured_slice(t_game *game, t_ray *ray, t_texture	texture)
{
	t_slice	slice;

	slice.height = W_HEIGHT / ray->wall_dist;
	slice.draw_start = -slice.height / 2 + W_HEIGHT / 2;
	if (slice.draw_start < 0 || slice.draw_start > W_HEIGHT)
		slice.draw_start = 0;
	slice.draw_end = slice.height / 2 + W_HEIGHT / 2;
	if (slice.draw_end >= W_HEIGHT || slice.draw_end < 0)
		slice.draw_end = W_HEIGHT - 1;
	if (ray->hit_side == 0)
		slice.x_wall_offset = game->player.y + ray->wall_dist * ray->dir.y;
	else
		slice.x_wall_offset = game->player.x + ray->wall_dist * ray->dir.x;
	slice.x_wall_offset -= (int)slice.x_wall_offset;
	slice.x_tex_offset = (int)(slice.x_wall_offset * (double)texture.width);
	if ((ray->hit_side == 0 && ray->dir.x < 0)
		|| (ray->hit_side == 1 && ray->dir.y > 0))
		slice.x_tex_offset = texture.width - slice.x_tex_offset - 1;
	slice.step = 1.0 * texture.height / slice.height;
	slice.tex_pos = (slice.draw_start - W_HEIGHT / 2 + slice.height / 2)
		* slice.step;
	draw_lines(game, ray, slice.draw_start, slice.draw_end);
	copy_tex_to_frame(game, ray, texture, slice);
}

int	init_texture(t_game *game, t_texture *tex, char *path, int idx)
{
	int	i;

	i = 0;
	tex->frame.img = mlx_xpm_file_to_image(game->mlx->ptr, path,
			&(tex->width), &(tex->height));
	if (!tex->frame.img)
	{
		while (i < idx)
			mlx_destroy_image(game->mlx->ptr, game->textures[i++].frame.img);
		return (MEM_ERR);
	}
	tex->frame.addr = mlx_get_data_addr(tex->frame.img,
			&tex->frame.bpp, &tex->frame.size_l, &tex->frame.endian);
	return (0);
}

int	load_textures(t_game *game)
{
	t_texture	*texture_tab;

	texture_tab = malloc(sizeof(t_texture) * 4);
	if (!texture_tab)
		return (1);
	game->textures = texture_tab;
	if (init_texture(game, &game->textures[NORTH],
			game->map_info->north_texture_path, NORTH))
		return (1);
	if (init_texture(game, &game->textures[SOUTH],
			game->map_info->south_texture_path, SOUTH))
		return (1);
	if (init_texture(game, &game->textures[EAST],
			game->map_info->east_texture_path, EAST))
		return (1);
	if (init_texture(game, &game->textures[WEST],
			game->map_info->west_texture_path, WEST))
		return (1);
	return (0);
}
