/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 09:51:49 by istasheu          #+#    #+#             */
/*   Updated: 2023/12/07 09:54:16 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_next(char **temp)
{
	char	*line;
	char	*ptr;

	ptr = *temp;
	while (*ptr && *ptr != '\n')
		++ptr;
	ptr += (*ptr == '\n');
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

static char *ft_read(char *temp, int fd, char *buf)
{
	ssize_t i;

	i = 1;
	while (i && !ft_strchr(temp, '\n'))
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i == -1) 
		{
			free(buf);
			free(temp);
			return(NULL);
		}
		buf[i] = 0;
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

char	*get_next_line(int fd)
{
	static char	*temp[1024];
	char		*buf;

	if (fd == -1 || BUFFER_SIZE < 1)
		return (NULL);
	if (!temp[fd])
		temp[fd] = ft_strdup("");
	if (!temp[fd])
		return (NULL);
	buf = malloc(sizeof(*buf) * (BUFFER_SIZE + 1));
	if (!buf)
	{
		free (temp[fd]);
		temp[fd] = NULL;
		return (NULL);
	}
	temp[fd] = ft_read(temp[fd], fd, buf);
	if (!temp[fd])
	{
		temp[fd] = NULL;
		return (NULL);
	}
	if (!*temp[fd])
	{
		free (temp[fd]);
		temp[fd] = NULL;
		return (NULL);
	}
	return (ft_next(&temp[fd]));
}
