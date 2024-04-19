/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:53:43 by ccodere           #+#    #+#             */
/*   Updated: 2024/04/19 09:39:17 by ccodere          ###   ########.fr       */
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

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (fd < 0 || fd > FD_MAX || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
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
// #include <fcntl.h>
// #include <stdio.h>
// int	main(void)
// {
// 	int		fd[FD_MAX];
// 	char	*line;
// 	char	*text[2];
// 	size_t	len1;
// 	size_t	len2;

// 	text[0] = "Lorem\nipsum\ndolor\nsit\namet\nconsectetur\nadipiscing.\n";
// 	len1 = ft_strlen(text[0]);

// 	text[1] = "Arrays\nare used\nto store\nmultiple\nvalues.\n";
// 	len2 = ft_strlen(text[1]);
// 	fd[0] = open("text1.txt", O_RDONLY | O_CREAT , 0777);
// 	if (fd[0] == -1)
// 	{
// 		perror("Error opening the file.");
// 		return (1);
// 	}
// 	fd[1] = open("text1.txt", O_RDWR | O_TRUNC);
// 	write(fd[1], text[0], len1 + 1);
// 	fd[2] = open("text2.txt", O_RDONLY | O_CREAT , 0777);
// 	if (fd[2] == -1)
// 	{
// 		perror("Error opening the file.");
// 		return (1);
// 	}
// 	fd[3] = open("text2.txt", O_RDWR | O_TRUNC);
// 	write(fd[3], text[1], len2 + 1);

// 	printf("%s", get_next_line(fd[0]));
// 	printf("%s", get_next_line(fd[2]));
// 	printf("%s", get_next_line(fd[0]));
// 	printf("%s", get_next_line(fd[2]));
// 	printf("%s", get_next_line(fd[0]));
// 	printf("%s", get_next_line(fd[2]));
// 	printf("%s", get_next_line(fd[0]));
// 	printf("%s", get_next_line(fd[2]));

// 	close(fd[0]);
// 	close(fd[1]);
// 	close(fd[2]);
// 	close (fd[3]);
// 	if (remove("text1.txt") == 0 && remove("text2.txt") == 0)
// 		printf("->File ended<-\n...deleted texts files successfully...\n");
// 	else
// 		printf("->Unable to delete the file<-");
// 	return (0);
// }
