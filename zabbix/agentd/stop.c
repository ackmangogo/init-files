#include <stdlib.h>
#include <unistd.h>

#include "../../lib/stop.h"

int main(void)
{
	return stop("/run/zabbix/zabbix_agentd.pid", "/usr/sbin/zabbix_agentd", NULL);
}
