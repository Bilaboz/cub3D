/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:07:19 by rcarles           #+#    #+#             */
/*   Updated: 2022/07/19 18:04:26 by rcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	str_ends_with(char *str, char *end)
{
	size_t	str_len;
	size_t	end_len;

	str_len = ft_strlen(str);
	end_len = ft_strlen(end);
	if (str_len < end_len)
		return (0);
	if (ft_strncmp(str + str_len - end_len, end, end_len))
		return (0);
	return (1);
}

size_t	count_char_in_str(char *str, char c)
{
	size_t	count;

	count = 0;
	if (!str)
		return (0);
	while (*str)
		if (*str++ == c)
			count++;
	return (count);
}

void	free_tab(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void	free_map(t_map map)
{
	size_t	i;

	i = 0;
	free(map.north_texture_path);
	free(map.south_texture_path);
	free(map.west_texture_path);
	free(map.east_texture_path);
	if (map.map)
	{
		while (i < map.max_y)
		{
			free(map.map[i]);
			i++;
		}
		free(map.map);
	}
}

int	destroy_mlx(t_mlx *mlx)
{
	mlx_destroy_image(mlx->ptr, mlx->frame2->img);
	mlx_destroy_image(mlx->ptr, mlx->frame->img);
	mlx_destroy_window(mlx->ptr, mlx->win);
	mlx_destroy_display(mlx->ptr);
	free(mlx->frame2);
	free(mlx->frame);
	free(mlx->ptr);
	return (0);
}
