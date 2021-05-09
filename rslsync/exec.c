#include <errno.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
	static char * const trd[] = {"/usr/bin/rslsync", "--config","/etc/resilio-sync/config.json", NULL};
	struct passwd *user;

	/* common access rights */
	umask(S_IWGRP | S_IWOTH);

	/* resilio-sync needs /run/resilio-sync, create the link target */
	if((mkdir("/run/resilio-sync", S_IRUSR|S_IWUSR|S_IXUSR | S_IRGRP|S_IXGRP | S_IROTH|S_IXOTH) && errno != EEXIST)
	||(user = getpwnam("rslsync")) == NULL || chown("/run/resilio-sync", user->pw_uid, user->pw_gid))
		_exit(EXIT_FAILURE);

	initgroups(user->pw_name, user->pw_gid);

	if(setgid(user->pw_gid) == 0 && setuid(user->pw_uid) == 0)
		execve(trd[0], trd, NULL);

	return EXIT_FAILURE;
}
