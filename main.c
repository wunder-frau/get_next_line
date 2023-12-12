#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char	*get_next_line(int fd);
int main(void)
{
 int  fd;
 char *line;
 int  count;

 count = 0;
 fd = open("your_file.txt", O_RDONLY);
 if (fd == -1)
 {
  printf("Error opening file");
  return (1);
 }
 while (1)
 {
  line = get_next_line(fd);
  if (line == NULL)
   break ;
  count++;
  printf("[%d]:%s\n", count, line);
  free(line);
  line = NULL;
 }
 close(fd);
 return (0);
}

// int main(void)
// {
//   int    fd;
//   char  *next_line;
//   int  count;

//   count = 0;
//   fd = open("your_file.txt", O_RDONLY);
//   next_line = get_next_line(fd);
//   count++;
//   printf("[%d]:%s\n", count, next_line); //count is to show you the line numbers
//   next_line = NULL;

//   close(fd);
//   return (0);
// }

// #include <fcntl.h>
// #include <unistd.h>
// #include <stdlib.h>

// size_t	ft_strlen(const char *str);

// char	*get_next_line(int fd);

// int	main(void)
// {
// 	int	fd;
// 	char	*line;

// 	fd = open("your_file.txt", O_RDONLY);

// 	line = get_next_line(fd);

// 	if (line)
// 	{
// 		write(1, line, ft_strlen(line));
// 		write(1, "\n", 1);  // Output a newline character
// 		free(line);
// 	}

// 	close(fd);
// 	return (0);
// }

// int	main(void)
// {
// 	int	fd;
// 	char	*line;

// 	fd = open("your_file.txt", O_RDONLY);

// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			break;
// 		write(1, line, ft_strlen(line));
// 		free(line);
// 	}

// 	return (0);
// }

// #include "get_next_line.h"
// #include <fcntl.h>

// size_t	ft_strlen (const char *str);
// char    *get_next_line (int fd);

// int  main(int ac, char **av)
// {
// 	int	fd;
// 	char    *line;

// 	(void) av;
// 	if (ac != 2)
// 		return (1);
// 	fd = open("your_file.txt", O_RDONLY);
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			break ;
// 		write (1, line, ft_strlen(line));
// 		free (line);
// 	}
// 	return (0);
// }
