#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	static char * const superset[] = {"/usr/bin/gunicorn",
		"-c", "/etc/superset.conf",
		"superset:app", NULL};

	static char * const env[] = {
		"PATH=/usr/bin:usr/sbin",
		"LANG=en_US.UTF-8",
		"NLS_LANG=SIMPLIFIED CHINESE_CHINA.UTF8",
		NULL};

	execve(superset[0], superset, env);
	return EXIT_FAILURE;
}
