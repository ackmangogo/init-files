#include <fcntl.h>
#include <linux/rtc.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

int main(void)
{
	sigset_t mask;
	pid_t pid;
	struct timeval sys;
	struct tm *hc;

	int fd = open("/dev/rtc", O_RDONLY);
	if(fd == -1) {
		fd = open("/dev/rtc0", O_RDONLY);
		if(fd == -1)
			_exit(EXIT_FAILURE);
	}

	/* block signals */
	sigfillset(&mask);
	sigprocmask(SIG_SETMASK, &mask, NULL);

	if((pid = fork())) /* parent process */
		return pid != -1?EXIT_SUCCESS:EXIT_FAILURE;

	/* minimum niceness, highest priority */
	setpriority(PRIO_PROCESS, 0, PRIO_MIN);

	/* the hardware clock updates precisely 500 ms after time setting */
	do gettimeofday(&sys, NULL);
	while(sys.tv_usec < (500-10)*1000 || sys.tv_usec > (500+10)*1000);

	/* we still might be off up to 10 ms, which is acceptable */
	if((hc = gmtime(&sys.tv_sec)))
		ioctl(fd, RTC_SET_TIME, hc);

	_exit(EXIT_SUCCESS);
}
