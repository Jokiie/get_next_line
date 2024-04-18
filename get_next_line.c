/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:25:03 by ccodere           #+#    #+#             */
/*   Updated: 2024/04/18 15:42:01 by ccodere          ###   ########.fr       */
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
		remainder = ft_strdup(newline + 1);
	else
		remainder = ft_strdup("");
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
	remainder = _extract_remainder(line, remainder);
	return (line);
}
/*
#include <fcntl.h>
#include <stdio.h>
int	main(void)
{
	int		fd;
	int 	fdw;
	char	*line;
	char	*text;
	size_t	len;

	text = "Lorem\nipsum\ndolor\nsit\namet\nconsectetur\nadipiscing\nelit.\n";
	len = ft_strlen(text);
	fd = open("text.txt", O_RDONLY | O_CREAT , 0777);
	if (fd == -1)
	{
		perror("Error opening the file.");
		return (1);
	}
	fdw = open("text.txt", O_RDWR | O_TRUNC);
	write(fdw, text, len + 1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
	 	line = get_next_line(fd);
	}
	close(fd);
	close(fdw);
	if (remove("text.txt") == 0)
		printf("->File ended. Deleting 'text.txt'<-\n");
	else
		printf("->Unable to delete the file<-");
	return (0);
}
*/
