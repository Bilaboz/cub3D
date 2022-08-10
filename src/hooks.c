/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 16:31:16 by rcarles           #+#    #+#             */
/*   Updated: 2022/07/14 16:39:10 by rcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	window_cross(t_game *game)
{
	mlx_loop_end(game->mlx->ptr);
	return (0);
}

int	mouse_move(int x, int y, t_game *game)
{
	int	delta;

	(void)y;
	delta = W_WIDTH / 2 - x;
	if (delta == 0)
		return (0);
	if (delta > 0)
		rotate(game, -ROTATION_STEP_SIZE / 2);
	else
		rotate(game, ROTATION_STEP_SIZE / 2);
	mlx_mouse_move(game->mlx->ptr, game->mlx->win, W_WIDTH / 2, W_HEIGHT / 2);
	return (0);
}

int	key_press(int key, t_game *game)
{
	if (key == 'w')
		game->press.up = true;
	else if (key == 's')
		game->press.down = true;
	else if (key == RIGHT)
		game->press.rot_right = true;
	else if (key == LEFT)
		game->press.rot_left = true;
	else if (key == 'a')
		game->press.left = true;
	else if (key == 'd')
		game->press.right = true;
	else
		return (0);
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == ESCAPE)
		mlx_loop_end(game->mlx->ptr);
	else if (key == 'w')
		game->press.up = false;
	else if (key == 's')
		game->press.down = false;
	else if (key == RIGHT)
		game->press.rot_right = false;
	else if (key == LEFT)
		game->press.rot_left = false;
	else if (key == 'a')
		game->press.left = false;
	else if (key == 'd')
		game->press.right = false;
	return (0);
}

int	render(t_game *game)
{
	if (game->press.up)
		translate(game, TRANSLATION_STEP_SIZE, 0);
	if (game->press.down)
		translate(game, -TRANSLATION_STEP_SIZE, 0);
	if (game->press.right)
		translate(game, 0, -TRANSLATION_STEP_SIZE);
	if (game->press.left)
		translate(game, 0, TRANSLATION_STEP_SIZE);
	if (game->press.rot_right)
		rotate(game, ROTATION_STEP_SIZE);
	if (game->press.rot_left)
		rotate(game, -ROTATION_STEP_SIZE);
	ft_bzero(game->mlx->frame->addr, W_HEIGHT * W_WIDTH * sizeof(int));
	raycasting(game);
	draw_map(game);
	mlx_put_image_to_window(game->mlx->ptr, game->mlx->win,
		game->mlx->frame->img, 0, 0);
	ft_swap((void *)&game->mlx->frame2, (void *)&game->mlx->frame);
	return (0);
}
