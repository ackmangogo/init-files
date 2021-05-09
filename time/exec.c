#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

int main(void)
{
	if(open("/dev/rtc", O_RDONLY) == -1 && open("/dev/rtc0", O_RDONLY) == -1) {
		struct stat seed;

		if(stat("/var/lib/misc/random-seed", &seed) == -1
		|| stime(&seed.st_mtime) == -1)
			return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
