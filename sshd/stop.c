#include <stdlib.h>

#include "../lib/stop.h"

int main(void)
{
	int status = EXIT_FAILURE;

	if(kill_by_pidf(SIGTERM, "/run/sshd.pid"))
		status = EXIT_SUCCESS;

	if(kill_by_exec(SIGTERM, "/usr/sbin/sshd", NULL))
		status = EXIT_SUCCESS;

	return status;
}

