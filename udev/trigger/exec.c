#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	static char * const udev_trigger[] = {"/sbin/udevadm", "trigger", "--action=add", NULL};

	execve(udev_trigger[0], udev_trigger, NULL);
	return EXIT_FAILURE;
}
