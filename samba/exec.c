#include <stdlib.h>
#include <sys/mount.h>
#include <unistd.h>

int main(void)
{
	static char * const sambad[] = {"/usr/sbin/samba", NULL};

	execve(sambad[0], sambad, NULL);
	return EXIT_FAILURE;
}
