/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:25:03 by ccodere           #+#    #+#             */
/*   Updated: 2024/03/18 21:44:23 by ccodere          ###   ########.fr       */
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

	remainder = NULL;
	buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (!buffer || fd <= 0 || BUFFER_SIZE <= 0)
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
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		if (!remainder)
			remainder = ft_strdup("");
		stash = remainder;
		remainder = ft_strjoin(stash, buffer);
		free(stash);
		if (ft_strchr(buffer, '\n') || ft_strchr(buffer, '\0'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read < 0)
	{
		free(remainder);
		free(buffer);
		return (NULL);
	}
	return (remainder);
}

char	*set_next_line(char *line_buffer)
{
	size_t	len;
	size_t	i;
	char	*remainder;
	char	*newline;

	if (!line_buffer)
		return (NULL);
	len = ft_strlen(line_buffer);
	newline = ft_strchr(line_buffer, '\n');
	if (newline)
	{
		i = newline - line_buffer;
		remainder = ft_substr(line_buffer, i + 1, len - (i + 1));
	}
	else
	{
		remainder = ft_strdup("");
	}
	return (remainder);
}

char	*ft_strchr(const char *str, int c)
{
	unsigned int	i;
	char			cp;
	
	cp = (char) c;
	i = 0;
	while (str[i])
	{
		if (str[i] == cp)
			return ((char *) &str[i]);
		i++;
	}
	if (str[i] == cp)
		return ((char *) &str[i]);
	return (NULL);
}
