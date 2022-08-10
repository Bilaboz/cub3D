/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 21:01:21 by rcarles           #+#    #+#             */
/*   Updated: 2022/07/16 21:05:11 by rcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_params_complete(t_map *map)
{
	if (!map->east_texture_path || !map->west_texture_path
		|| !map->north_texture_path || !map->south_texture_path
		|| !(map->ceiling_color >> 24 & 0xff)
		|| !(map->floor_color >> 24 & 0xff))
		return (0);
	return (1);
}

int	str_is_numeric(char *str)
{
	if (!str || *str == '\n')
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != '\n' && *str != ' ')
			return (0);
		str++;
	}
	return (1);
}

char	*strip_newline(char *str)
{
	char	*result;

	if (!ft_strchr(str, '\n'))
		return (ft_strdup(str));
	result = malloc(sizeof(char) * ft_strlen(str));
	if (!result)
		return (NULL);
	ft_strlcpy(result, str, ft_strlen(str));
	return (result);
}

void	clean_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	remove_newlines(t_map *map)
{
	size_t	y;

	y = 0;
	while (y < map->max_y)
	{
		map->map[y][ft_strlen(map->map[y]) - 1] = '\0';
		y++;
	}
}
