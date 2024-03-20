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
	int fd;
	char *line;

	fd = open("exemple.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error while opening the file!\n");
		return (1);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		// free(line);
			// Assurez-vous de libérer la mémoire allouée pour chaque ligne
		line = get_next_line(fd);
	}
	printf("\n");
	printf("%s", get_next_line(fd));
	printf("\n");
	printf("%s", get_next_line(fd));
	printf("\n");
	printf("%s", get_next_line(fd));
	printf("\n");
	free(line);
	close(fd);
	return (0);
}
