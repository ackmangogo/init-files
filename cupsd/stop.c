#include <stdlib.h>
#include <unistd.h>

#include "../lib/stop.h"

void _start(void)
{
	pid_t cupsd = kill_by_exec(SIGTERM, "/usr/sbin/cupsd", NULL);
	unlink("/run/cups/cups.sock");
	_exit(cupsd?EXIT_SUCCESS:EXIT_FAILURE);
}
