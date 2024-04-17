/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:54:04 by ccodere           #+#    #+#             */
/*   Updated: 2024/04/17 14:00:09 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char			*strs;
	size_t			len;
	unsigned int	i;
	unsigned int	j;

	if (!s1 && !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	strs = (char *)malloc((len + 1) * sizeof(char));
	if (!strs)
		return (NULL);
	i = 0;
	j = 0;
	if (s1)
		while (s1[j])
			strs[i++] = s1[j++];
	j = 0;
	while (s2[j])
		strs[i++] = s2[j++];
	strs[i] = '\0';
	return (strs);
}

char	*ft_strchr(char *str, int c)
{
	unsigned int	i;
	size_t			len;

	if (!str)
		return (NULL);
	i = 0;
	len = ft_strlen(str);
	while (i < (len + 1))
	{
		if (str[i] == (char )c)
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}

char	*ft_strdup(char *src)
{
	unsigned int	i;
	unsigned int	j;
	char			*dst;
	size_t			len;

	if (!src)
		return (NULL);
	len = ft_strlen(src);
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	i = 0;
	j = 0;
	while (src[j])
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (dst);
}
