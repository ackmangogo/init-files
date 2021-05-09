#include <stdlib.h>

#include "../lib/stop.h"

int main(void)
{
	return kill_by_pidf(SIGTERM, "/run/tomcat.pid")?EXIT_SUCCESS:EXIT_FAILURE;
}
