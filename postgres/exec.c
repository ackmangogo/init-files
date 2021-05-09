#include <errno.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
	static char * const pg_ctl[] = {"/usr/bin/pg_ctl", "-D" ,"/data/1/postgres-data", "start",  NULL};
	struct passwd *user;

	/* common access rights */
	umask(S_IWGRP | S_IWOTH);

	/* postgresql needs /run/postgresql, create the link target */
	if((mkdir("/run/postgresql", S_IRUSR|S_IWUSR|S_IXUSR | S_IRGRP|S_IXGRP | S_IROTH|S_IXOTH) && errno != EEXIST)
	||(user = getpwnam("postgres")) == NULL || chown("/run/postgresql", user->pw_uid, user->pw_gid))
		return EXIT_FAILURE;

	initgroups(user->pw_name, user->pw_gid);

	if(setgid(user->pw_gid) == 0 && setuid(user->pw_uid) == 0)
		execve(pg_ctl[0], pg_ctl, NULL);

	return EXIT_FAILURE;
}
