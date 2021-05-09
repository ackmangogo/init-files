#include <stdlib.h>

#include "../../lib/stop.h"

int main(void)
{
	return kill_by_exec(SIGTERM, "/sbin/udevadm", "/sbin/udevadm", "settle", NULL)?EXIT_SUCCESS:EXIT_FAILURE;
}
