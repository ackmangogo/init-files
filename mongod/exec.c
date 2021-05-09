#include <errno.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdio.h>
int main(void)
{
	static char * const mongod[] = {"/usr/bin/mongod", "-f" ,"/etc/mongodb.conf", NULL};
	struct passwd *user;
	pid_t  pid;

	/* common access rights */
	umask(S_IWGRP | S_IWOTH);

	/* mongod needs /run/mongodb and /var/log/mongodb , create the link target */
	if((mkdir("/run/mongodb", S_IRUSR|S_IWUSR|S_IXUSR | S_IRGRP|S_IXGRP | S_IROTH|S_IXOTH) && errno != EEXIST)
	||(user = getpwnam("mongodb")) == NULL || chown("/run/mongodb", user->pw_uid, user->pw_gid))
		return EXIT_FAILURE;

	initgroups(user->pw_name, user->pw_gid);

	if(setgid(user->pw_gid) == 0 && setuid(user->pw_uid) == 0)
	{
		/* mongod doesn't daemonize */
		if((pid = fork()) == 0) {
			/* child process */
			int fd = open("/dev/null", O_RDWR);
			if(fd != -1) {
				dup2(fd, STDIN_FILENO);
				dup2(fd, STDOUT_FILENO);
				dup2(fd, STDERR_FILENO);
				if(fd > STDERR_FILENO)
					close(fd);
			}

			execve(mongod[0], mongod, NULL);
			_exit(EXIT_FAILURE);
		}
	}

	/* parent process */
	return pid != -1?EXIT_SUCCESS:EXIT_FAILURE;

}
