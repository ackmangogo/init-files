#include <stdlib.h>
#include <unistd.h>

void _start(void)
{
	static char * const sshd[] = {"/usr/sbin/sshd", NULL};

	/* sshd doesn't daemonize when ppid == init */
	execve(sshd[0], sshd, NULL);
	_exit(EXIT_FAILURE);
}

