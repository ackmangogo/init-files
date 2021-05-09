#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>

void _start(void)
{
	static char * const rsync_daemon[] = {"/usr/bin/rsync", "--daemon", NULL};

	/* maximum niceness, lowest priority */
	setpriority(PRIO_PROCESS, 0, PRIO_MAX);
	execve(rsync_daemon[0], rsync_daemon, NULL);
	_exit(EXIT_FAILURE);
}
