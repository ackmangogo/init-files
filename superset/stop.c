#include <stdlib.h>
#include <unistd.h>

#include "../lib/stop.h"

int main(void)
{
	return kill_by_pidf(SIGTERM, "/run/superset.pid")?EXIT_SUCCESS:EXIT_FAILURE;
}
