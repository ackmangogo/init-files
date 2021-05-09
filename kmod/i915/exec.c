#include <stdlib.h>
#include <unistd.h>

void _start(void)
{
	static char * const modprobe[] = {"/sbin/modprobe", "-q", "i915", NULL};

	execve(modprobe[0], modprobe, NULL);
	_exit(EXIT_FAILURE);
}
