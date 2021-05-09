#include <errno.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
	static char * const fail2ban[] = {"/usr/bin/fail2ban-client", "start", NULL};
	struct stat run_f2b;

	/* fail2ban needs /var/run/fail2ban, create the link target */
	if(mkdir("/run/fail2ban", S_IRUSR|S_IWUSR|S_IXUSR | S_IRGRP|S_IXGRP | S_IROTH|S_IXOTH) == 0
	||(errno == EEXIST && stat("/run/fail2ban", &run_f2b) == 0 && S_ISDIR(run_f2b.st_mode))) {
		/* maximum niceness, lowest priority */
		setpriority(PRIO_PROCESS, 0, PRIO_MAX);
		execve(fail2ban[0], fail2ban, NULL);
	}

	return EXIT_FAILURE;
}
