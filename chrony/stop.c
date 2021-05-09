#include <stdlib.h>

#include "../lib/stop.h"

int main(void)
{
	return stop("/run/chronyd.pid", "/usr/sbin/chronyd", NULL);
}

