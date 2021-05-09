#include <stdlib.h>
#include <unistd.h>

#include "../lib/stop.h"

int main(void)
{
	static char * const udev_exit[] = {"/sbin/udevadm", "control", "-e", NULL};

	execve(udev_exit[0], udev_exit, NULL);
	return kill_by_exec(SIGTERM, "/sbin/udevd", NULL)?EXIT_SUCCESS:EXIT_FAILURE;
}
