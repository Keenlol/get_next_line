#include <stdio.h>
#include <fcntl.h>

#include "get_next_line.h"

int main(void)
{
	int		fd;
	char	*thing;
    int     line_no;

	fd = open("test", O_RDONLY);
	if (fd == -1)
	{
		printf("error opening the file\n");
		return (0);
	}
	printf("read sucess!\n");
    line_no = 1;
	while (1)
	{
		thing = get_next_line(fd);
		if (!thing)
			break;
		printf("%03d : %s",line_no,thing);
		free(thing);
        line_no++;
	}
}
