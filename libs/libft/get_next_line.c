/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarles <rcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:09:34 by rcarles           #+#    #+#             */
/*   Updated: 2022/06/13 20:43:13 by rcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

char	*get_line(char **prev)
{
	char	*result;
	char	*end_idx;
	char	*temp;

	if (!*prev || *prev[0] == '\0')
		return (NULL);
	if (!ft_strchr(*prev, '\n'))
	{
		result = ft_strdup(*prev);
		ft_free(prev);
		return (result);
	}
	temp = *prev;
	end_idx = ft_strchr(*prev, '\n');
	result = ft_substr(*prev, 0, end_idx - *prev + 1);
	*prev = ft_substr(*prev, end_idx - *prev + 1, ft_strlen(end_idx + 1));
	if (!result || !*prev)
		return (NULL);
	ft_free(&temp);
	if (*prev[0] == '\0')
		ft_free(prev);
	return (result);
}

int	concat(char **line, char *buf, ssize_t bytes_read)
{
	char	*temp;
	size_t	line_len;

	if (bytes_read == -1)
		return (-1);
	buf[bytes_read] = '\0';
	line_len = ft_strlen(*line);
	temp = malloc(sizeof(*temp) * (line_len + bytes_read + 1));
	if (!temp)
		return (-1);
	ft_strlcpy(temp, *line, line_len + 1);
	ft_strlcpy(&temp[line_len], buf, line_len + bytes_read + 1);
	ft_free(&(*line));
	*line = temp;
	return (0);
}

char	*read_file(int fd, char *previous)
{
	ssize_t	bytes_read;
	char	*buf;

	buf = malloc(sizeof(*buf) * (GNL_BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	bytes_read = GNL_BUFFER_SIZE;
	while (bytes_read == GNL_BUFFER_SIZE && !ft_strchr(previous, '\n'))
	{
		bytes_read = read(fd, buf, GNL_BUFFER_SIZE);
		if (concat(&previous, buf, bytes_read) == -1)
		{
			ft_free(&previous);
			ft_free(&buf);
			return (NULL);
		}
	}
	ft_free(&buf);
	return (previous);
}

char	*get_next_line(int fd)
{
	char		*result;
	static char	*prev_tab[GNL_FD_SIZE];

	if (GNL_BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	if (!prev_tab[fd])
	{
		prev_tab[fd] = malloc(sizeof(char));
		if (!prev_tab[fd])
			return (NULL);
		prev_tab[fd][0] = '\0';
	}
	prev_tab[fd] = read_file(fd, prev_tab[fd]);
	result = get_line(&prev_tab[fd]);
	if (!result)
		ft_free(&prev_tab[fd]);
	return (result);
}
