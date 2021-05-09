#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	static char * const dcron[] = {"/usr/sbin/crond", NULL};

	execve(dcron[0], dcron, NULL);
	return EXIT_FAILURE;
}
