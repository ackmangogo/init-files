#include <stdlib.h>

#include "../lib/stop.h"

int main(void)
{
	return stop("/run/rsyncd.pid", "/usr/bin/rsync", "/usr/bin/rsync", "--daemon", NULL);
}
