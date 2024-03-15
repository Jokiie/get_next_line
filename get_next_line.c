/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:25:03 by ccodere           #+#    #+#             */
/*   Updated: 2024/03/15 13:25:07 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*set_line(int fd, char *remainder, char *buffer);
char	*set_next_line(char *line_buffer);
char	*ft_strchr(const char *str, int c);

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;
	char		*buffer;

	buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (fd == 0 || fd < 0 || BUFFER_SIZE < 0)
	{
		free(remainder);
		free(buffer);
		remainder = NULL;
		buffer = NULL;
		return (NULL);
	}
	if (buffer == NULL)
	{
		free(buffer);
		return (NULL);
	}
	line = set_line(fd, remainder, buffer);
	free(buffer);
	remainder = set_next_line(line);
	return (line);
}

char	*set_line(int fd, char *remainder, char *buffer)
{
	int		bytes_read;
	char	*stash;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > -1)
	{
		buffer[bytes_read] = 0;
		if (remainder == NULL)
			remainder = ft_strdup("");
		stash = remainder;
		remainder = ft_strjoin(stash, buffer);
		free(stash);
		stash = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
		if (ft_strchr(buffer, '\0'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(remainder);
			return (NULL);
		}
	}
	return (remainder);
}

char	*set_next_line(char *line_buffer)
{
	size_t	len;
	size_t	i;
	char	*remainder;

	len = ft_strlen(line_buffer);
	i = 0;
	remainder = line_buffer;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == '\n')
		remainder = ft_substr(line_buffer, i - 1, len + i);
	if (line_buffer[i] == '\0')
		remainder = ft_substr(line_buffer, i - 1, len + i);
	*remainder = '\0';
	return (remainder);
}

char	*ft_strchr(const char *str, int c)
{
	unsigned char	cptr;

	cptr = c;
	if (str == NULL)
		return (NULL);
	while (*str != cptr)
	{
		if (*str == '\0')
			return (0);
		str++;
	}
	return ((char *)str);
}
