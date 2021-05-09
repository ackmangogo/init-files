#include <stdlib.h>
#include <unistd.h>

#include "../../lib/stop.h"

int main(void)
{
	int status = stop("/run/zabbix/zabbix_server.pid", "/usr/sbin/zabbix_server", NULL);

	unlink("/tmp/zabbix_server_alerter.sock");
	unlink("/tmp/zabbix_server_preprocessing.sock");

	return status;
}
