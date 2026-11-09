#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int fd1;
	int fd2;
	char *s1;
	char *s2;

    fd1 = open("test1.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	while ((s1 = get_next_line(fd1)) != NULL)
	{
		if(s1)
		{
			printf("%s", s1);
			free(s1);
		}
	}
	while ((s2 = get_next_line(fd2)) != NULL)
	{
		if(s2)
		{
			printf("%s", s2);
			free(s2);
		}
	}
	close(fd1);
	close(fd2);
	return (0);
}