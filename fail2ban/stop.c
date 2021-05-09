#include <stdlib.h>
#include <unistd.h>

#include "../lib/stop.h"

int main(void)
{
	static char * const fail2ban_stop[] = {"/usr/bin/fail2ban-client", "stop", NULL};
	pid_t f2b_pid;

	execve(fail2ban_stop[0], fail2ban_stop, NULL);

	f2b_pid = kill_by_pidf(SIGTERM, "/run/fail2ban/fail2ban.pid");
	unlink("/run/fail2ban/fail2ban.sock");
	return f2b_pid?EXIT_SUCCESS:EXIT_FAILURE;
}
