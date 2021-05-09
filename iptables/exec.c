#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void _start(void)
{
	/* /sbin/iptables-restore < /var/lib/iptables/firewall.rules */
	static char * const iptables_restore[] = {"/sbin/iptables-restore", NULL};

	close(STDIN_FILENO);
	if(open("/var/lib/iptables/firewall.rules", O_RDONLY) == STDIN_FILENO)
		execve(iptables_restore[0], iptables_restore, NULL);

	_exit(EXIT_FAILURE);
}
