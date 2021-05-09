#include <stdlib.h>
#include <unistd.h>

#include "../lib/stop.h"

int main(void)
{
	return stop("/run/redis.pid", "/usr/sbin/redis-server", NULL);
}
