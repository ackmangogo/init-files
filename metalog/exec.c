#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>

void _start(void)
{
	static char * const metalog[] = {"/usr/sbin/metalog", "-BN", NULL};

	/* maximum niceness, lowest priority */
	setpriority(PRIO_PROCESS, 0, PRIO_MAX);
	execve(metalog[0], metalog, NULL);
	_exit(EXIT_FAILURE);
}
