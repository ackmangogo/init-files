#include <stdlib.h>
#include <unistd.h>

void _start(void)
{
	static char * const ux11[] = {"/usr/bin/ux11", NULL};

	execve(ux11[0], ux11, NULL);
	_exit(EXIT_FAILURE);
}
