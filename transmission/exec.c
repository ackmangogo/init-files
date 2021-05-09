#include <errno.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
	static char * const trd[] = {"/usr/bin/transmission-daemon", "-x/run/transmission/transmission.pid", "-e/var/log/transmission.log", "-g/var/lib/transmission", NULL};
	struct passwd *user;

	/* common access rights */
	umask(S_IWGRP | S_IWOTH);

	/* transmission-daemon needs /var/run/transmission, create the link target */
	if((mkdir("/run/transmission", S_IRUSR|S_IWUSR|S_IXUSR | S_IRGRP|S_IXGRP | S_IROTH|S_IXOTH) && errno != EEXIST)
	||(user = getpwnam("transmission")) == NULL || chown("/run/transmission", user->pw_uid, user->pw_gid))
		return EXIT_FAILURE;

	initgroups(user->pw_name, user->pw_gid);

	if(setgid(user->pw_gid) == 0 && setuid(user->pw_uid) == 0)
		execve(trd[0], trd, NULL);

	return EXIT_FAILURE;
}
