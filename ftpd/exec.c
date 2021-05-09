#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>

void _start(void)
{
	static char * const ftpd[] = {"/usr/bin/ftpd", "-AD", NULL};

	/* maximum niceness, lowest priority */
	setpriority(PRIO_PROCESS, 0, PRIO_MAX);
	execve(ftpd[0], ftpd, NULL);
	_exit(EXIT_FAILURE);
}
