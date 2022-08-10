/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 15:44:13 by alorain           #+#    #+#             */
/*   Updated: 2022/07/18 19:56:25 by rcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_frames_data(t_mlx *mlx)
{
	mlx->frame2->addr = mlx_get_data_addr(mlx->frame2->img,
			&mlx->frame2->bpp,
			&mlx->frame2->size_l, &mlx->frame2->endian);
	mlx->frame->addr = mlx_get_data_addr(mlx->frame->img,
			&mlx->frame->bpp,
			&mlx->frame->size_l, &mlx->frame->endian);
	return (0);
}

static int	init_frames(t_mlx *mlx)
{
	mlx->frame = malloc(sizeof(t_img));
	if (!mlx->frame)
		return (MEM_ERR);
	mlx->frame2 = malloc(sizeof(t_img));
	if (!mlx->frame2)
	{
		free(mlx->frame);
		return (MEM_ERR);
	}
	mlx->frame->img = mlx_new_image(mlx->ptr, W_WIDTH, W_HEIGHT);
	if (!mlx->frame->img)
	{
		free(mlx->frame);
		free(mlx->frame2);
		return (MEM_ERR);
	}
	mlx->frame2->img = mlx_new_image(mlx->ptr, W_WIDTH, W_HEIGHT);
	if (!mlx->frame2->img)
	{
		mlx_destroy_image(mlx->ptr, mlx->frame->img);
		free(mlx->frame);
		free(mlx->frame2);
		return (MEM_ERR);
	}
	return (get_frames_data(mlx));
}

static int	init_mlx(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		return (MEM_ERR);
	if (init_frames(mlx))
	{
		mlx_destroy_display(mlx->ptr);
		free(mlx->ptr);
		return (MEM_ERR);
	}
	mlx->win = mlx_new_window(mlx->ptr, W_WIDTH, W_HEIGHT, "cub3D");
	if (!mlx->win)
	{
		mlx_destroy_image(mlx->ptr, mlx->frame->img);
		mlx_destroy_image(mlx->ptr, mlx->frame2->img);
		free(mlx->frame);
		free(mlx->frame2);
		mlx_destroy_display(mlx->ptr);
		free(mlx->ptr);
		return (MEM_ERR);
	}
	return (0);
}

static void	fill_map_info(t_game *game, t_map *map)
{
	game->map = map->map;
	game->map_info = map;
	game->player = map->spawn_position;
	game->dir = map->spawn_direction;
	game->plane = map->spawn_plane;
}

int	init(t_mlx *mlx, t_game *game, t_map *map, char *map_path)
{
	ft_bzero(map, sizeof(t_map));
	if (parse_map_file(map, map_path))
		return (ft_printf(_RED_ "Error: Invalid map\n" _RST_));
	if (init_mlx(mlx))
	{
		free_map(*map);
		return (printf(_RED_ "Error: Failed to init MLX\n" _RST_));
	}
	ft_bzero(game, sizeof(t_game));
	game->mlx = mlx;
	fill_map_info(game, map);
	if (MINIMAP_WIDTH > MINIMAP_HEIGHT)
		game->pixel_per_block = MINIMAP_HEIGHT / game->map_info->max_y;
	else
		game->pixel_per_block = MINIMAP_WIDTH / game->map_info->max_x;
	if (load_textures(game))
	{
		ft_printf(_RED_ "Error: Invalid textures\n" _RST_);
		free(game->textures);
		free_map(*game->map_info);
		destroy_mlx(mlx);
		return (1);
	}
	return (0);
}
