/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 09:51:49 by istasheu          #+#    #+#             */
/*   Updated: 2023/12/11 17:46:54 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_next(char **temp)
{
	char	*line;
	char	*ptr;

	ptr = *temp;
	while (*ptr != '\0' && *ptr != '\n')
		ptr++;
	if (*ptr == '\n')
		ptr++;
	line = ft_substr (*temp, 0, (size_t)(ptr - *temp));
	if (!line)
	{
		free (*temp);
		*temp = NULL;
		return (NULL);
	}
	ptr = ft_substr (ptr, 0, ft_strlen (ptr));
	free (*temp);
	*temp = ptr;
	return (line);
}

static char	*ft_read(char *temp, int fd, char *buf)
{
	ssize_t	i;

	i = 1;
	while (i && !ft_strchr(temp, '\n'))
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i == -1)
		{
			free(buf);
			free(temp);
			return (NULL);
		}
		buf[i] = '\0';
		temp = ft_strjoin(temp, buf);
		if (!temp)
		{
			free(buf);
			return (NULL);
		}
	}
	free(buf);
	return (temp);
}

static char	*ft_read_and_update(char *temp, int fd, char *buf)
{
	temp = ft_read(temp, fd, buf);
	if (!temp)
	{
		temp = NULL;
		return (NULL);
	}
	if (!*temp)
	{
		free(temp);
		temp = NULL;
		return (NULL);
	}
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*temp;
	char		*buf;

	if (fd == -1 || BUFFER_SIZE < 1)
		return (NULL);
	if (!temp)
		temp = ft_strdup("");
	if (!temp)
		return (NULL);
	buf = malloc(sizeof(*buf) * (BUFFER_SIZE + 1));
	if (!buf)
	{
		free (temp);
		temp = NULL;
		return (NULL);
	}
	temp = ft_read_and_update(temp, fd, buf);
	if (!temp)
		return (NULL);
	return (ft_next(&temp));
}
