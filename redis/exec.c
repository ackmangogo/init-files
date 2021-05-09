#include <errno.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
	static char * const redis_server[] = {"/usr/sbin/redis-server", "/etc/redis/redis.conf",  NULL};
	struct passwd *user;

	/* common access rights */
	umask(S_IWGRP | S_IWOTH);

	/* postgresql needs /run/postgresql, create the link target */
	if((mkdir("/run/redis", S_IRUSR|S_IWUSR|S_IXUSR | S_IRGRP|S_IXGRP | S_IROTH|S_IXOTH) && errno != EEXIST)
	||(user = getpwnam("redis")) == NULL || chown("/run/redis", user->pw_uid, user->pw_gid))
		return EXIT_FAILURE;

	initgroups(user->pw_name, user->pw_gid);

	if(setgid(user->pw_gid) == 0 && setuid(user->pw_uid) == 0)
		execve(redis_server[0], redis_server, NULL);

	return EXIT_FAILURE;
}
