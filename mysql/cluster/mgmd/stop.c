#include <stdlib.h>
#include <unistd.h>

#include "../../../lib/stop.h"

int main(void)
{
	static char * const ndb_mgmd_stop[] = {"/usr/bin/ndb_mgm", "-e", "shutdown", NULL};

	/* ndb_mgm wastes time if daemon isn't running */
	if(kill_by_exec(0, "/usr/sbin/ndb_mgmd", NULL)) {
		execve(ndb_mgmd_stop[0], ndb_mgmd_stop, NULL);
		if(kill_by_exec(SIGTERM, "/usr/sbin/ndb_mgmd", NULL))
			return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}
