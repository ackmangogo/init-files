#include <errno.h>
#include <fcntl.h>
#include <pwd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
	static char * const mysqld[] = {"/usr/sbin/mysqld", "--defaults-file=/etc/mysql/my.cnf", NULL};
	struct passwd *mysql;
	pid_t pid;

	/* common access rights */
	umask(S_IWGRP | S_IWOTH);

	/* mysqld needs /var/run/mysqld, create the link target */
	if((mkdir("/run/mysqld", S_IRUSR|S_IWUSR|S_IXUSR | S_IRGRP|S_IXGRP | S_IROTH|S_IXOTH) && errno != EEXIST)
	||(mysql = getpwnam("mysql")) == NULL || chown("/run/mysqld", mysql->pw_uid, mysql->pw_gid)
	|| access(mysqld[0], X_OK))
		return EXIT_FAILURE;

	/* mysqld doesn't daemonize */
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

		execve(mysqld[0], mysqld, NULL);
		_exit(EXIT_FAILURE);
	}

	/* parent process */
	return pid != -1?EXIT_SUCCESS:EXIT_FAILURE;
}
