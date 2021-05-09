#include <stdlib.h>
#include <sys/mount.h>
#include <unistd.h>

int main(void)
{
	static char * const nmbd[] = {"/usr/sbin/nmbd", NULL};

	execve(nmbd[0], nmbd, NULL);
	return EXIT_FAILURE;
}
