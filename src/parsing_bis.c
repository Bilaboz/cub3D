/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarles <rcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:53:26 by rcarles           #+#    #+#             */
/*   Updated: 2022/07/16 20:33:36 by rcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map_valid(char **map, size_t max_x, size_t max_y)
{
	t_upoint	p;

	p.y = -1;
	while (++p.y < max_y)
	{
		p.x = -1;
		while (map[p.y][++p.x])
		{
			if (map[p.y][p.x] == '0')
			{
				if (!p.y || !p.x || ft_strlen(map[p.y - 1]) < p.x
					|| p.y == max_y - 1 || ft_strlen(map[p.y + 1]) < p.x)
					return (0);
				if (p.y && !char_is_in_str(map[p.y - 1][p.x], "01"))
					return (0);
				if (p.x && !char_is_in_str(map[p.y][p.x - 1], "01"))
					return (0);
				if (map[p.y + 1] && !char_is_in_str(map[p.y + 1][p.x], "01"))
					return (0);
				if (p.x < max_x && !char_is_in_str(map[p.y][p.x + 1], "01"))
					return (0);
			}
		}
	}
	return (1);
}

static void	set_spawn_direction(t_map *map, char orientation)
{
	if (orientation == 'N')
	{
		map->spawn_direction = (t_vector){0, -1};
		map->spawn_plane = (t_vector){-0.60, 0};
	}
	else if (orientation == 'S')
	{
		map->spawn_direction = (t_vector){0, 1};
		map->spawn_plane = (t_vector){0.60, 0};
	}
	else if (orientation == 'E')
	{
		map->spawn_direction = (t_vector){1, 0};
		map->spawn_plane = (t_vector){0, -0.60};
	}
	else if (orientation == 'W')
	{
		map->spawn_direction = (t_vector){-1, 0};
		map->spawn_plane = (t_vector){0, 0.60};
	}
}

int	get_spawn_direction(t_map *map)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < map->max_y && map->map[y])
	{
		x = 0;
		while (x < map->max_x && map->map[y][x])
		{
			if (char_is_in_str(map->map[y][x], "NSWE"))
			{
				if (map->spawn_direction.x || map->spawn_direction.y)
					return (-1);
				set_spawn_direction(map, map->map[y][x]);
				map->spawn_position = (t_vector){x + 0.5, y + 0.5};
				map->map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	if (!map->spawn_direction.x && !map->spawn_direction.y)
		return (-1);
	return (0);
}

int	fill_map(t_map *map, int fd)
{
	char	*line;
	size_t	i;

	line = get_next_line(fd);
	while (line && !str_is_numeric(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	if (!line)
		return (-1);
	i = 0;
	while (line && i < map->max_y)
	{
		if (!ft_str_matches_charset(line, "01NSWE \n"))
		{
			free(line);
			return (-1);
		}
		map->map[i++] = line;
		line = get_next_line(fd);
	}
	if (line)
		return (-1);
	return (0);
}

int	get_map_size(t_map *map, int fd, char *first_line)
{
	char	*line;

	if (first_line)
	{
		map->max_y++;
		map->max_x = ft_strlen(first_line);
		free(first_line);
	}
	line = get_next_line(fd);
	while (line && ft_str_matches_charset(line, "01NSWE \n"))
	{
		map->max_y++;
		if (ft_strlen(line) > map->max_x)
			map->max_x = ft_strlen(line);
		free(line);
		line = get_next_line(fd);
	}
	if (line)
	{
		free(line);
		clean_gnl(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
