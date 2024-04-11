/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:01:05 by ccodere           #+#    #+#             */
/*   Updated: 2024/03/17 11:01:05 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(void)
{
	int		fd;
	int		count;
	char	*line;

	fd = open("text.txt", O_RDONLY | O_CREAT);
	if (fd == -1)
	{
		perror("Error opening the file.");
		return (KO);
	}
	count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		count += printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	printf("\nCounted %d characters.\n", count);
	close(fd);
	return (OK);
}
