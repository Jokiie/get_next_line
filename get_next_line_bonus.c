/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:53:43 by ccodere           #+#    #+#             */
/*   Updated: 2024/04/18 14:46:11 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*_append(char *remainder, char *buffer)
{
	char	*copy;

	if (!remainder)
		remainder = ft_strjoin("", "");
	copy = remainder;
	remainder = ft_strjoin(copy, buffer);
	free(copy);
	copy = NULL;
	return (remainder);
}

static char	*_read_n_append(int fd, char *remainder, char *buffer)
{
	ssize_t	chars_read;

	chars_read = 1;
	while (chars_read > 0)
	{
		chars_read = read(fd, buffer, BUFFER_SIZE);
		if (chars_read == -1)
		{
			free(remainder);
			return (0);
		}
		else if (chars_read == 0)
			break ;
		buffer[chars_read] = '\0';
		remainder = _append(remainder, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (remainder);
}

static char	*_extract_remainder(char *line, char *remainder)
{
	char	*newline;
	ssize_t	i;

	i = 0;
	newline = ft_strchr(line, '\n');
	while (line[i] != '\n')
	{
		if (line[i] == '\0')
			return (0);
		i++;
	}
	if (newline)
		remainder = ft_strjoin("", newline + 1);
	else
		remainder = ft_strjoin("", "");
	if (!*remainder)
	{
		free(remainder);
		remainder = NULL;
	}
	line[i + 1] = '\0';
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder[FD_MAX];
	char		*line;
	char		*buffer;

	if (fd > FD_MAX)
		fd = 10240;
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &buffer, 0) < 0)
	{
		free(buffer);
		free(remainder[fd]);
		buffer = NULL;
		remainder[fd] = NULL;
		return (NULL);
	}
	line = _read_n_append(fd, remainder[fd], buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	remainder[fd] = _extract_remainder(line, remainder[fd]);
	return (line);
}
