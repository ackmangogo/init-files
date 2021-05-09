#include <stdlib.h>
#include <unistd.h>

#include "../lib/stop.h"

int main(void)
{
	return stop("/run/samba/smbd.pid", "/usr/sbin/smbd", NULL);
}
