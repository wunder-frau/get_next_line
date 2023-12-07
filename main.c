#include "get_next_line.h"
#include <fcntl.h>

size_t	ft_strlen (const char *str);
char    *get_next_line (int fd);

int  main(int ac, char **av)
{
	int	fd;
	char    *line;
	(void) av;
	if (ac != 2)
		return (1);
	fd = open("your_file.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		write (1, line, ft_strlen(line));
		free (line);
	}
	return (0);
}
