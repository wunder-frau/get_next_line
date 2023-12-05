/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:30:59 by istasheu          #+#    #+#             */
/*   Updated: 2023/12/05 14:30:03 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

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

/*char *ft_strjoin(char *s1, char const *s2)
{
    if (s1 == NULL)
    {
        return ft_strdup(s2);  
    }

    char *s3;
    char *p3;
    char *p1;

    s3 = malloc(sizeof(*s3) * (ft_strlen(s1) + ft_strlen(s2) + 1));
    if (!s3)
    {
        free(s1);
        return NULL;
    }

    p3 = s3;
    p1 = s1;

    while (*p1)
        *p3++ = *p1++;

    while (*s2)
        *p3++ = *s2++;

    *p3 = '\0';

    free(s1);
    return s3;
}*/


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
/*int main()
{
    char *temp = ft_strdup("Hello\nWorld\nHow are you?");
    char *nextLine;

    while (*temp && (nextLine = ft_next(&temp)) != NULL)
    {
        printf("Next line: %s\n", nextLine);
        free(nextLine);
    }

    return 0;
}*/


int main() {
    // Open a file for reading (replace "your_file.txt" with the actual file path)
    int fd = open("your_file.txt", O_RDONLY);

    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Initialize the initial buffer
    char *temp = malloc(1);  // Start with an empty string
    if (!temp) {
        perror("Memory allocation error");
        close(fd);
        return 1;
    }

    // Initialize the buffer for reading
    char *buf = malloc(BUFFER_SIZE);
    if (!buf) {
        perror("Memory allocation error");
        free(temp);
        close(fd);
        return 1;
    }

    // Call the ft_read function
    temp = ft_read(temp, fd, buf);

    // Check if ft_read was successful
    if (!temp) {
        fprintf(stderr, "Error reading from file\n");
    } else {
        // Print the read content
        printf("Read content: %s\n", temp);

        // Free the memory allocated for the read content
        free(temp);
    }

    // Close the file descriptor
    close(fd);

    // Free the memory allocated for the buffer
    free(buf);

    return 0;
}


/*int main() {
    // Open a file for reading (replace "your_file.txt" with the actual file path)
    int fd = open("your_file.txt", O_RDONLY);

    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Initialize the buffer for reading
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    // Read from the file
    bytesRead = read(fd, buffer, sizeof(buffer));

    if (bytesRead == -1) {
        perror("Error reading from file");
        close(fd);
        return 1;
    }

    // Check if any data was read
    if (bytesRead > 0) {
        // Process the read data
        printf("Read %zd bytes from the file.\n", bytesRead);
        // You can use the 'buffer' content here or perform further processing.
    } else {
        // No data was read
        printf("No data read from the file.\n");
    }

    // Close the file descriptor
    close(fd);

    return 0;
}*/
