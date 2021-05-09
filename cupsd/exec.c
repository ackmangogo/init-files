#include <errno.h>
#include <grp.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

void _start(void)
{
	static char * const cupsd[] = {"/usr/sbin/cupsd", "-c", "/etc/cups/cupsd.conf", NULL};
	struct group *grp;
	struct stat run_cups;

	if((grp = getgrnam("lp")) == NULL || grp->gr_gid == 0)
		_exit(EXIT_FAILURE);

	/* cupsd needs /var/run/cups, create the link target */
	if(mkdir("/run/cups", S_IRUSR|S_IWUSR|S_IXUSR | S_IRGRP|S_IXGRP | S_IROTH|S_IXOTH) == 0
	||(errno == EEXIST && stat("/run/cups", &run_cups) == 0 && S_ISDIR(run_cups.st_mode)))
		if(chown("/run/cups", 0, grp->gr_gid) == 0)
			execve(cupsd[0], cupsd, NULL);

	_exit(EXIT_FAILURE);
}
