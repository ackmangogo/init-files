#include <stdlib.h>
#include <unistd.h>

#include "../../lib/stop.h"

int main(void)
{
	static char * const mysqld_stop[] = {"/usr/bin/mysqladmin", "shutdown", NULL};
	int status;

	execve(mysqld_stop[0], mysqld_stop, NULL);

	status = stop("/run/mysql/mysqld.pid", "/usr/sbin/mysqld", NULL);
	unlink("/run/mysql/mysqld.sock");
	return status;
}
