#include <stdlib.h>
#include <unistd.h>

void _start(void)
{
	/* default --configdir=/usr/mysql-cluster omitted */
	static char * const ndb_mgmd[] = {"/usr/sbin/ndb_mgmd", "-f", "/var/lib/mysql/cluster/config.ini", NULL};

	/* need: bind/a.b.c.d mount/CONFIG_DIR */
	execve(ndb_mgmd[0], ndb_mgmd, NULL);
	_exit(EXIT_FAILURE);
}
