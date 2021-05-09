#include <stdlib.h>
#include <unistd.h>

#include "../../lib/stop.h"

int main(void)
{
	return kill_by_pidf(SIGTERM, "/var/tmp/gitlabhq-12.8/pids/unicorn.pid")?EXIT_SUCCESS:EXIT_FAILURE;
}

