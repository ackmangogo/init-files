#include <stdlib.h>
#include <unistd.h>

void _start(void)
{
	static char * const sysctl[] = {"/usr/sbin/sysctl", "-eqp", NULL};

	execve(sysctl[0], sysctl, NULL);
	_exit(EXIT_FAILURE);
}
