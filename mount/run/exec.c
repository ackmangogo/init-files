#include <errno.h>
#include <fcntl.h>
#include <grp.h>
#include <stdlib.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../../lib/hill.h"

int main(void)
{
	int fd;

	/* try /etc/fstab first and fall back on failure */
	if(hill("/run") && errno != EBUSY) {
		struct stat run1, run2;

		/* mount unique tmpfs on /run */
		if(stat("/run/.", &run1) || stat("/run/..", &run2) || (run1.st_dev == run2.st_dev
		&& mount("run", "/run", "tmpfs", MS_NOSUID | MS_NODEV | MS_NOATIME, "size=4m,mode=755")))
			return EXIT_FAILURE;
	}

	/* adjust access rights */
	umask(S_IWOTH);

	/* create /run/utmp, /var/run points to /run */
	fd = open("/run/utmp", O_CREAT | O_WRONLY, S_IRUSR|S_IWUSR | S_IRGRP|S_IWGRP | S_IROTH);
	if(fd != -1) {
		struct group *utmp = getgrnam("utmp");
		if(utmp)
			fchown(fd, (uid_t)-1, utmp->gr_gid);

		close(fd);
	}

	/* create /run/lock pointed to by /var/lock */
	if(mkdir("/run/lock", S_IRUSR|S_IWUSR|S_IXUSR | S_IRGRP|S_IWGRP|S_IXGRP | S_IROTH|S_IXOTH) == 0
	|| errno == EEXIST) {
		struct group *lock = getgrnam("lock");
		if(lock || (lock = getgrnam("uucp")))
			chown("/run/lock", (uid_t)-1, lock->gr_gid);
	}

	/* report mounted */
	return EXIT_SUCCESS;
}
