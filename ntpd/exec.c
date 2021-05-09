#include <stdlib.h>
#include <unistd.h>

void _start(void)
{
	static char * const ntpd[] = {"/usr/sbin/ntpd", NULL};

	execve(ntpd[0], ntpd, NULL);
	_exit(EXIT_FAILURE);
}
