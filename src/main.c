/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarles <rcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:18:50 by rcarles           #+#    #+#             */
/*   Updated: 2022/07/18 21:27:45 by rcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_keybindings(void)
{
	ft_printf("WASD: move\n");
	ft_printf("Directional arrows: rotate (look around)\n");
	ft_printf("Left mouse button: use the mouse to look around\n");
	ft_printf("ESC: Quit\n");
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	t_map	map;
	t_game	game;
	size_t	i;

	if (argc != 2)
		return (ft_printf("Invalid arguments\nUsage: ./cub3D map.cub\n"));
	if (init(&mlx, &game, &map, argv[1]))
		return (1);
	print_keybindings();
	mlx_hook(mlx.win, KeyPress, KeyPressMask, key_press, &game);
	mlx_hook(mlx.win, MotionNotify, Button1MotionMask, mouse_move, &game);
	mlx_mouse_hook(mlx.win, NULL, NULL);
	mlx_hook(mlx.win, KeyRelease, KeyReleaseMask, key_release, &game);
	mlx_hook(mlx.win, DestroyNotify, NoEventMask, window_cross, &game);
	mlx_loop_hook(mlx.ptr, render, &game);
	mlx_loop(game.mlx->ptr);
	i = 4;
	while (i--)
		mlx_destroy_image(mlx.ptr, game.textures[i].frame.img);
	destroy_mlx(&mlx);
	free(game.textures);
	free_map(map);
	return (0);
}
