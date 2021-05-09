#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	static char * const udev_settle[] = {"/sbin/udevadm", "settle", "-t60", NULL};

	execve(udev_settle[0], udev_settle, NULL);
	return EXIT_FAILURE;
}
