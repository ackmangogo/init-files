#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
	static char * const dnscrypt[] = {"/usr/bin/dnscrypt-proxy", "-config", "/etc/dnscrypt-proxy/dnscrypt-proxy.toml", "-syslog", NULL};
	pid_t  pid;

	/* dnscrypt-proxy doesn't daemonize */
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

		execve(dnscrypt[0], dnscrypt, NULL);
		_exit(EXIT_FAILURE);
	}

	/* parent process */
	return pid != -1?EXIT_SUCCESS:EXIT_FAILURE;
}

