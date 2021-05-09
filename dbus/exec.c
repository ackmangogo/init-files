#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
	static char * const dbus_daemon[] = {"/usr/bin/dbus-daemon", "--system", "--fork", NULL};
	struct stat run_dbus;

	/* dbus-daemon needs /var/run/dbus, create the link target */
	if(mkdir("/run/dbus", S_IRUSR|S_IWUSR|S_IXUSR | S_IRGRP|S_IXGRP | S_IROTH|S_IXOTH) == 0
	||(errno == EEXIST && stat("/run/dbus", &run_dbus) == 0 && S_ISDIR(run_dbus.st_mode)))
		execve(dbus_daemon[0], dbus_daemon, NULL);

	return EXIT_FAILURE;
}
