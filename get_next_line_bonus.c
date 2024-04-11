/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:53:43 by ccodere           #+#    #+#             */
/*   Updated: 2024/04/11 13:54:32 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*_append(char *remainder, char *buffer)
{
	char	*copy;

	if (!remainder)
		remainder = ft_strdup("");
	copy = remainder;
	remainder = ft_strjoin(copy, buffer);
	free(copy);
	copy = NULL;
	return (remainder);
}

static char	*_read_n_append(int fd, char *remainder, char *line)
{
	ssize_t	chars_read;

	chars_read = 1;
	while (chars_read > 0)
	{
		chars_read = read(fd, line, BUFFER_SIZE);
		if (chars_read == -1)
		{
			free(remainder);
			return (OK);
		}
		else if (chars_read == 0)
			break ;
		line[chars_read] = '\0';
		remainder = _append(remainder, line);
		if (ft_strchr(line, '\n'))
			break ;
	}
	return (remainder);
}

static char	*_put_next(char *line, char *remainder)
{
	char	*newline;
	ssize_t	i;

	i = 0;
	newline = ft_strchr(line, '\n');
	while (line[i] != '\n')
	{
		if (line[i] == '\0')
			return (OK);
		i++;
	}
	if (newline)
		remainder = ft_strdup(newline + 1);
	else
		remainder = ft_strdup("");
	if (*remainder == '\0')
	{
		free(remainder);
		remainder = NULL;
	}
	line[i + 1] = '\0';
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &buffer, 0) < 0)
	{
		free(buffer);
		free(remainder);
		buffer = NULL;
		remainder = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = _read_n_append(fd, remainder, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	remainder = _put_next(line, remainder);
	return (line);
}
