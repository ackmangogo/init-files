#include <stdlib.h>
#include <unistd.h>

#include "../lib/stop.h"

int main(void)
{
        return(
	kill_by_exec(SIGKILL, "/usr/libexec/netdata/plugins.d/apps.plugin", NULL) &&
	kill_by_exec(SIGKILL, "/usr/sbin/netdata", NULL)
	)
	?EXIT_SUCCESS:EXIT_FAILURE;
}

