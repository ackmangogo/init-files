#include <errno.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
	static char * const netdata[] = {"/usr/sbin/netdata", "-d", NULL};
	struct passwd *user;

	/* common access rights */
	umask(S_IWGRP | S_IWOTH);

	/* netdata needs /run/netdata, create the link target */
	if((mkdir("/var/cache/netdata", S_IRUSR|S_IWUSR|S_IXUSR | S_IRGRP|S_IXGRP | S_IROTH|S_IXOTH) && errno != EEXIST)
	||(user = getpwnam("netdata")) == NULL || chown("/var/cache/netdata", user->pw_uid, user->pw_gid))
		return EXIT_FAILURE;

	initgroups(user->pw_name, user->pw_gid);

	if(setgid(user->pw_gid) == 0 && setuid(user->pw_uid) == 0)
		execve(netdata[0], netdata, NULL);

	return EXIT_FAILURE;
}
