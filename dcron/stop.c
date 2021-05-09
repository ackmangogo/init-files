#include <stdlib.h>

#include "../lib/stop.h"

int main(void)
{
	return stop("/run/crond.pid", "/usr/sbin/crond", NULL);
}
