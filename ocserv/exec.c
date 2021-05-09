#include <errno.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
	static char * const ocserv[] = {"/usr/sbin/ocserv", "-c" , "/etc/ocserv/default.config",  NULL};
	struct passwd *user;

	/* common access rights */
	umask(S_IWGRP | S_IWOTH);

	/* ocserv needs /run/ocserv, create the link target */
	if((mkdir("/run/ocserv", S_IRUSR|S_IWUSR|S_IXUSR | S_IRGRP|S_IXGRP | S_IROTH|S_IXOTH) && errno != EEXIST)
	||(user = getpwnam("ocserv")) == NULL || chown("/run/ocserv", user->pw_uid, user->pw_gid))
		return EXIT_FAILURE;

//	initgroups(user->pw_name, user->pw_gid);

//	if(setgid(user->pw_gid) == 0 && setuid(user->pw_uid) == 0)
		execve(ocserv[0], ocserv, NULL);

	return EXIT_FAILURE;
}
