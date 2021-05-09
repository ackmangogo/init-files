#include <stdlib.h>
#include <unistd.h>

#include "../lib/stop.h"

int main(void)
{
	static char * const iperf3[] = {"/usr/bin/iperf3","-s", "-D", "-B192.168.88.11", NULL};

	execve(iperf3[0], iperf3, NULL);
	return EXIT_FAILURE;
}

