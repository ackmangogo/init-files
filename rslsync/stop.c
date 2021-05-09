#include <stdlib.h>
#include <unistd.h>

#include "../lib/stop.h"

int main(void)
{
	return stop("/run/resilio-sync/resilio-sync.pid", "/usr/bin/rslsync", NULL);
}
