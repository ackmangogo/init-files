#include <stdlib.h>

#include "../../lib/stop.h"

int main(void)
{
	return stop("/run/mysql-proxy.pid", "/usr/bin/mysql-proxy", NULL);
}
