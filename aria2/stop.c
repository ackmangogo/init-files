#include <stdlib.h>
#include <unistd.h>

#include "../lib/stop.h"

int main(void)
{
	return kill_by_exec(SIGTERM, "/usr/bin/aria2c", NULL)?EXIT_SUCCESS:EXIT_FAILURE;
}
