#include <stdlib.h>

#include "../lib/stop.h"

int main(void)
{
	return kill_by_exec(SIGTERM, "/usr/sbin/ntpd", NULL)?EXIT_SUCCESS:EXIT_FAILURE;
}
