#include <stdlib.h>

#include "../lib/stop.h"

int main(void)
{
	return stop("/run/apache2.pid", "/usr/sbin/apache2", NULL);
}
