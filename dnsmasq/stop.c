#include <stdlib.h>

#include "../lib/stop.h"

int main(void)
{
	return stop("/run/dnsmasq.pid", "/usr/sbin/dnsmasq", NULL);
}

