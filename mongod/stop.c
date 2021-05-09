#include <stdlib.h>

#include "../lib/stop.h"

int main(void)
{
	return stop("/run/mongodb/mongod.pid", "/usr/bin/mongod", NULL);
}

