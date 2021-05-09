#include <stdlib.h>
#include <unistd.h>

void _start(void)
{
	static char * const ndbd[] = {"/usr/sbin/ndbd", NULL};

	/* need: bind/a.b.c.d */
	execve(ndbd[0], ndbd, NULL);
	_exit(EXIT_FAILURE);
}
