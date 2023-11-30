/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:30:59 by istasheu          #+#    #+#             */
/*   Updated: 2023/11/30 13:15:32 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	const char *p;

	p = str;
	while(*p)
		p++;
	return ((size_t)(p - str));
}

char	*ft_strchr(const char *s, int c)
{
	while(*s || (unsigned char)c == "\0")
	{
		if (*s == (unsigned char)c)
		{
			return ((char *)s);
		}
		s++;
	}
	return (0);
}

char	*ft_strdup(const char *s1)
{
	char	*dst;
	size_t	i;

	dst = (char *)malloc(sizeof(char) * (ft_strlen((char *)s1) + 1));
	i = 0;
	if (!dst)
		return (NULL);
	while (s1[i] != '\0')
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	len_s;
	char	*substr;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (start >= len_s)
		return (ft_strdup(""));
	if (len > len_s - start)
		len = len_s - start;
	substr = (char *)malloc(len + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[len] = '\0';
	return (substr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	char			*dst;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	dst = (char *)malloc(sizeof(*dst) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dst)
		return (NULL);
	while (*s1)
		dst[i++] = *s1++;
	while (*s2)
		dst[i++] = *s2++;
	dst[i] = '\0';
	return (dst);
}
