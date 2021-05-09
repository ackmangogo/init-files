#include <errno.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
	static char * const aria2[] = {"/usr/bin/aria2c", "--conf-path=/etc/aria2/aria2.conf", "-D", NULL};
	struct passwd *user;

	if((user = getpwnam("aria2")) ==  NULL)
		return EXIT_FAILURE;

	/* common access rights */
	umask(S_IWGRP | S_IWOTH);


	initgroups(user->pw_name, user->pw_gid);

	if(setgid(user->pw_gid) == 0 && setuid(user->pw_uid) == 0)
		execve(aria2[0], aria2, NULL);

	return EXIT_FAILURE;
}
