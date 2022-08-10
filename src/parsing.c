/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:57:30 by rcarles           #+#    #+#             */
/*   Updated: 2022/07/16 20:21:27 by rcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_color	parse_color(char *str)
{
	char	**splitted;
	int		r;
	int		g;
	int		b;

	if (count_char_in_str(str, ',') != 2)
		return (0 << 24);
	splitted = ft_split(str, ',');
	if (!splitted)
		return (0);
	if (!str_is_numeric(splitted[0]) || !str_is_numeric(splitted[1])
		|| !str_is_numeric(splitted[2]))
	{
		free_tab(splitted);
		return (0 << 24);
	}
	r = ft_atoi(splitted[0]);
	g = ft_atoi(splitted[1]);
	b = ft_atoi(splitted[2]);
	free_tab(splitted);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0 << 24);
	return (1 << 24 | r << 16 | g << 8 | b);
}

static int	fill_textures_and_colors(t_map *map, char **splitted_line)
{
	if (**splitted_line == '\0' || **splitted_line == '\n')
		return (0);
	if (!splitted_line[1] || splitted_line[2])
		return (-1);
	if (!ft_strncmp(splitted_line[0], "NO", 3) && !map->north_texture_path)
		map->north_texture_path = strip_newline(splitted_line[1]);
	else if (!ft_strncmp(splitted_line[0], "SO", 3) && !map->south_texture_path)
		map->south_texture_path = strip_newline(splitted_line[1]);
	else if (!ft_strncmp(splitted_line[0], "WE", 3) && !map->west_texture_path)
		map->west_texture_path = strip_newline(splitted_line[1]);
	else if (!ft_strncmp(splitted_line[0], "EA", 3) && !map->east_texture_path)
		map->east_texture_path = strip_newline(splitted_line[1]);
	else if (!ft_strncmp(splitted_line[0], "F", 2) && !map->floor_color)
		map->floor_color = parse_color(splitted_line[1]);
	else if (!ft_strncmp(splitted_line[0], "C", 2) && !map->ceiling_color)
		map->ceiling_color = parse_color(splitted_line[1]);
	else
		return (-1);
	if (errno)
		return (-1);
	return (0);
}

static int	parse_textures_and_colors(t_map *map, int fd, char **first_line)
{
	char	*line;
	char	**splitted_line;

	line = get_next_line(fd);
	while (line && !str_is_numeric(line))
	{
		splitted_line = ft_split(line, ' ');
		free(line);
		if (!splitted_line)
			return (MEM_ERR);
		if (fill_textures_and_colors(map, splitted_line))
		{
			free_tab(splitted_line);
			return (-1);
		}
		free_tab(splitted_line);
		line = get_next_line(fd);
		if (str_is_numeric(line))
			*first_line = line;
	}
	if (line && !*first_line)
		free(line);
	if (!map_params_complete(map))
		return (-1);
	return (0);
}

static int	parse_map(t_map *map, int fd, char *first_line, char *path)
{
	int		new_fd;

	if (get_map_size(map, fd, first_line) == -1)
		return (-1);
	map->map = malloc(sizeof(char *) * map->max_y);
	if (!map->map)
		return (MEM_ERR);
	new_fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("open()");
		return (-1);
	}
	if (fill_map(map, new_fd) == -1)
	{
		clean_gnl(new_fd);
		return (-1);
	}
	remove_newlines(map);
	if (get_spawn_direction(map) == -1
		|| !is_map_valid(map->map, map->max_x, map->max_y))
		return (-1);
	close(new_fd);
	return (0);
}

int	parse_map_file(t_map *map, char *path)
{
	int		fd;
	char	*first_line;

	if (!str_ends_with(path, ".cub"))
		return (-1);
	first_line = NULL;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("open()");
		return (-1);
	}
	if (parse_textures_and_colors(map, fd, &first_line))
	{
		free(first_line);
		clean_gnl(fd);
		free_map(*map);
		return (-1);
	}
	if (parse_map(map, fd, first_line, path))
	{
		free_map(*map);
		return (-1);
	}
	return (0);
}
