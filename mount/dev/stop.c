#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	/* save random seed, will be read by exec */
	int fd = open("/dev/urandom", O_RDONLY);
	if(fd != -1) {
		char seed[512]; /* random seed buffer */
		ssize_t size = read(fd, seed, sizeof(seed));
		close(fd);

		if(size == sizeof(seed)) {
			fd = open("/var/lib/misc/random-seed", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR|S_IWUSR);
			if(fd != -1) {
				size = write(fd, seed, sizeof(seed));
				close(fd);

				if(size == sizeof(seed))
					return EXIT_SUCCESS;

				unlink("/var/lib/misc/random-seed");
			}
		}
	}

	return EXIT_FAILURE;
}
