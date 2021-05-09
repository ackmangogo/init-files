#include <stdlib.h>
#include <unistd.h>

#include "../lib/stop.h"

int main(void)
{
	int status = stop("/run/dbus.pid", "/usr/bin/dbus-daemon", "/usr/bin/dbus-daemon", "--system", NULL);
	unlink("/run/dbus/system_bus_socket");
	return status;
}
