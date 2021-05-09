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
	static char * const unicorn_rails[] = { "/usr/bin/bundle",
						"exec", "unicorn_rails",
						"-c", 	"/opt/gitlabhq-12.8/config/unicorn.rb",
						"-E",	"production",
						"-D",  NULL};

//	static char * const rpath[] = {"/opt/gitlabhq-12.8", NULL};

	struct passwd *user;

	/* common access rights */
	umask(S_IWGRP | S_IWOTH);

	/* postgresql needs /run/postgresql, create the link target */
	if((user = getpwnam("git")) == NULL)// || chdir(* rpath))
		return EXIT_FAILURE;

	initgroups(user->pw_name, user->pw_gid);

//	if(setgid(user->pw_gid) == 0 && setuid(user->pw_uid) == 0) {
	if(setuid(user->pw_uid) == 0) {

//printf("gid=%i\nuid=%i\n",user->pw_gid, user->pw_uid);
		execve(unicorn_rails[0], unicorn_rails, NULL);
	}
	return EXIT_FAILURE;
}
