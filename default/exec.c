#include <stdlib.h>
#include <syslog.h>

int main(void)
{
	openlog("pid1", 0, LOG_DAEMON);
	syslog(LOG_INFO, "boot target reached");
	closelog();

	return EXIT_SUCCESS;
}

