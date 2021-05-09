#include <errno.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAXCHAR 255
int read_passwd()
{
	FILE *fp;
	char str[MAXCHAR];
	char* filename = "/etc/openconnect/passwd";

	if(fp = fopen(filename, "r")) {
        printf("Could not open file %s",filename);

        return EXIT_FAILURE;
	}

	fputs("alkslik0079", stdin);
	fclose(fp);

	return 0;
}

int main(void)
{
	static char * const opc[] = {"/usr/sbin/openconnect",
				     "--config", "/etc/openconnect/huayun.conf",
				     "--user=liliangsong",
				     "218.90.171.229:9443",  NULL};

	struct passwd *user;

	/* common access rights */
	umask(S_IWGRP | S_IWOTH);

	if((user = getpwnam("nobody")) == NULL)
		return EXIT_FAILURE;

	initgroups(user->pw_name, user->pw_gid);

	if(setgid(user->pw_gid) == 0 && setuid(user->pw_uid) == 0) {
		execve(opc[0], opc, NULL);
		read_passwd();
	}

	return EXIT_FAILURE;

}
