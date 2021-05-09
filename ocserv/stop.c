#include <stdlib.h>

#include "../lib/stop.h"

int main(void)
{
	return stop("/run/ocserv/ocserv.pid", "/usr/sbin/ocserv", NULL);
}

