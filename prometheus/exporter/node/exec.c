#include <errno.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
	static char * const node_exporter[] = {"/usr/sbin/node_exporter", "--web.listen-address=:10001", NULL};
	struct passwd *user;
	pid_t  pid;

	/* common access rights */
	umask(S_IWGRP | S_IWOTH);

	/* run node_exporter without privileged */
	if((user = getpwnam("node_exporter")) == NULL)
		return EXIT_FAILURE;

	initgroups(user->pw_name, user->pw_gid);

	if(setgid(user->pw_gid) == 0 && setuid(user->pw_uid) == 0) {

		/* node_exporter doesn't daemonize */
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

			execve(node_exporter[0], node_exporter, NULL);
			_exit(EXIT_FAILURE);
		}
	}

	/* parent process */
	return pid != -1?EXIT_SUCCESS:EXIT_FAILURE;
}
