/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:24:40 by ccodere           #+#    #+#             */
/*   Updated: 2024/03/15 13:24:40 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


size_t	ft_strlen(char *s)
{
	size_t len;

	len = 0;
	if (s == NULL || *s == 0)
		return (0);
	while (s[len])
		len++;
	return (len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char *buffer;

	buffer = (char *)malloc(((ft_strlen(s1) + ft_strlen(s2)) + 1)
			* sizeof(char));
	if (!buffer)
		return (NULL);
	ft_strscat(buffer, s1, s2);
	return (buffer);
}

void	ft_strscat(char *buffer, char *s1, char *s2)
{
	while (*s1)
		*buffer++ = *s1++;
	while (*s2)
		*buffer++ = *s2++;
	*buffer = '\0';
}

char	*ft_strdup(char *src)
{
	char *buffer;

	if (!src)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * ft_strlen(src) + 1);
	if (!buffer)
		return (NULL);
	while (*src)
		*buffer++ = *src++;
	*buffer = '\0';
	return (buffer);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char *sub_s;
	size_t srclen;
	size_t i;

	if (!s)
		return (NULL);
	srclen = ft_strlen(s);
	if (start > srclen)
		return (malloc(1 * sizeof(char)));
	if (len > srclen - start)
		len = srclen - start;
	sub_s = (char *)malloc((len + 1) * sizeof(char));
	if (!sub_s)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub_s[i] = s[start + i];
		i++;
	}
	sub_s[i] = '\0';
	return (sub_s);
}
