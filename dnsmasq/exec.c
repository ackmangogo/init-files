#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>

int main(void)
{
	static char * const dnsmasq[] = {"/usr/sbin/dnsmasq", "--log-async", NULL};

	/* maximum niceness, lowest priority */
	setpriority(PRIO_PROCESS, 0, PRIO_MAX);
	execve(dnsmasq[0], dnsmasq, NULL);
	return EXIT_FAILURE;
}

