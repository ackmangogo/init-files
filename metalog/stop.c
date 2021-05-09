#include <stdlib.h>

#include "../lib/stop.h"

int main(void)
{
	return stop("/run/metalog.pid", "/usr/sbin/metalog", "metalog [MASTER]", NULL);
}
