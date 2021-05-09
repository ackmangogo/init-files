#include <stdlib.h>

#include "../lib/stop.h"

int main(void)
{
	int status = EXIT_FAILURE;

	if(kill_by_pidf(SIGTERM, "/run/ppp0.pid"))
		status = EXIT_SUCCESS;

	if(kill_by_exec(SIGTERM, "/usr/sbin/pppd", NULL))
		status = EXIT_SUCCESS;

	return status;
}

