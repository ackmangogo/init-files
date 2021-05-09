#include <stdlib.h>
#include <sys/mount.h>
#include <unistd.h>

int main(void)
{
	static char * const smbd[] = {"/usr/sbin/smbd", NULL};

	execve(smbd[0], smbd, NULL);
	return EXIT_FAILURE;
}
