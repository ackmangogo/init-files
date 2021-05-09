#include <stdlib.h>

#include "../lib/stop.h"

int main(void)
{
	return stop("/run/docker.pid", "/usr/bin/dockerd", NULL);
}

