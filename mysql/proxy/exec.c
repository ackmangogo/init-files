#include <stdlib.h>
#include <unistd.h>

void _start(void)
{
	static char * const mysql_proxy[] = {"/usr/bin/mysql-proxy", "--defaults-file=/etc/mysql/mysql-proxy.cnf", NULL};

	execve(mysql_proxy[0], mysql_proxy, NULL);
	_exit(EXIT_FAILURE);
}
