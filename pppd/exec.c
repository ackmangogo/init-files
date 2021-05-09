#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	static char * const pppd[] = {"/usr/sbin/pppd", NULL};

	execve(pppd[0], pppd, NULL);
	return EXIT_FAILURE;
}

