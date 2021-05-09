#include <stdlib.h>
#include <unistd.h>

void _start(void)
{
	static char * const chronyd[] = {"/usr/sbin/chronyd", NULL};

	execve(chronyd[0], chronyd, NULL);
	_exit(EXIT_FAILURE);
}

