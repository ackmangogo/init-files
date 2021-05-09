#include <stdlib.h>
#include <unistd.h>

void _start(void)
{
	static char * const alsactl[] = {"/usr/sbin/alsactl", "-g", "store", NULL};

	execve(alsactl[0], alsactl, NULL);
	_exit(EXIT_FAILURE);
}
