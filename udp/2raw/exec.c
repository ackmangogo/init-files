#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
	static char * const udp2raw[] = {"/usr/bin/udp2raw", "--conf-file", "/etc/udp/udp2raw.conf", NULL};
	struct passwd *user;
	pid_t pid;

	if((user = getpwnam("root")) ==  NULL)
		return EXIT_FAILURE;

	/* common access rights */
	umask(S_IWGRP | S_IWOTH);

	initgroups(user->pw_name, user->pw_gid);

	if(setgid(user->pw_gid) || setuid(user->pw_uid))
		return EXIT_FAILURE;

        /* udpspeeder doesn't daemonize */
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

		setpriority(PRIO_PROCESS, 0, PRIO_MAX);
		execve(udp2raw[0], udp2raw, NULL);
		_exit(EXIT_FAILURE);
	}

	/* parent process */
	return pid != -1?EXIT_SUCCESS:EXIT_FAILURE;
}

