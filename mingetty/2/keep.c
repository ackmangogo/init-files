#include <stdlib.h>
#include <unistd.h>

void _start(void)
{
	static char * const mingetty[] = {"/sbin/mingetty", "tty2", NULL};

	execve(mingetty[0], mingetty, NULL);
	_exit(EXIT_FAILURE);
}
