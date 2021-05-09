#include <stdlib.h>
#include <unistd.h>

void _start(void)
{
	static char * const tomcat[] = {"/usr/sbin/tomcat", NULL};

	execve(tomcat[0], tomcat, NULL);
	_exit(EXIT_FAILURE);
}
