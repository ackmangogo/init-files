#include "conf.h"

#ifdef CONFIG_UEVENT_HELPER
#include <fcntl.h>
#endif
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>

void _start(void)
{
	static char * const udevd[] = {"/sbin/udevd", "--daemon", NULL};
#ifdef CONFIG_UEVENT_HELPER
	int fd = open("/sys/kernel/uevent_helper", O_WRONLY);
	if(fd != -1) {
		/* disable hotplug forking */
		write(fd, "\n", sizeof(char));

		close(fd);
	}
#endif
	/* maximum niceness, lowest priority */
	setpriority(PRIO_PROCESS, 0, PRIO_MAX);
	execve(udevd[0], udevd, NULL);
	_exit(EXIT_FAILURE);
}
