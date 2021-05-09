#include <errno.h>
#include <fcntl.h>
#include <pwd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
	static char * const dockerd[] = {"dockerd", NULL};
	char * path = getenv("PATH");
	char  pathenv[strlen(path) + sizeof("PATH=")];
	sprintf(pathenv, "PATH=%s", path);
	char * envp[] = {pathenv, NULL};

	pid_t pid;

	/* dockerd doesn't daemonize */
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

		execvpe(dockerd[0], dockerd, envp);
		_exit(EXIT_FAILURE);
	}

	/* parent process */
	return pid != -1?EXIT_SUCCESS:EXIT_FAILURE;
}
