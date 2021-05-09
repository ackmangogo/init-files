#include "conf.h"

#include <errno.h>
#include <fcntl.h>
#ifdef CONFIG_UNIX98_PTYS
#include <grp.h>
#endif
#include <linux/random.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/utsname.h>
#include <unistd.h>

#include "../../lib/hill.h"

__attribute__((noinline))
static char *mkpath(char *name)
{
	char *path;

	for(path = memcpy(name - 5, "/dev/", 5); (name = strchr(name, '/')); name++) {
		*name = 0;

		if(mkdir(path, S_IRUSR|S_IWUSR|S_IXUSR | S_IRGRP|S_IXGRP | S_IROTH|S_IXOTH)
		&& errno != EEXIST)
			return NULL;

		*name = '/';
	}

	return path;
}

__attribute__((noinline))
static void mkdevs(const char *p1, const char *p2)
{
	char buf[1024];
	FILE *f;

	if(p2) {
		if(snprintf(buf, sizeof(buf), p1, p2) >= sizeof(buf))
			return;

		p1 = buf;
	}

	if((f = fopen(p1, "r"))) {
		while(fgets(buf + 5, sizeof(buf) - 5, f)) {
			char *name, *spec;
			unsigned int maj, min;
			mode_t mode;

			name = strtok(buf + 5, "\t\n ");
			if(name == NULL || name[0] == '#')
				continue;

			if(p2) {
				name = strtok(NULL, "\t\n ");
				if(name == NULL)
					continue;
			}

			spec = strtok(NULL, "\t\n ");
			if(spec == NULL)
				continue;

			/* create the device node/link */
			switch(*spec++) {
			case 'b':
				mode = S_IFBLK | S_IRUSR|S_IWUSR;
				break;

			case 'c':
				mode = S_IFCHR | S_IRUSR|S_IWUSR;
				break;

			case 'l':
				if((*spec || (spec = strtok(NULL, "\t\n ")))
				&&(name = mkpath(name)))
					symlink(spec, name);
			default:/* fall through */
				continue;
			}

			if((*spec || (spec = strtok(NULL, "\t\n ")))
			&& sscanf(spec, "%u:%u%c", &maj, &min, buf) == 2
			&&(name = mkpath(name)))
				mknod(name, mode, makedev(maj, min));
		}

		fclose(f);
	}
}

int main(void)
{
	int fd;
	struct utsname kernel;

	/* try /etc/fstab first and fall back on failure */
	if(hill("/dev") && errno != EBUSY) {
	#ifdef CONFIG_DEVTMPFS
		/* devtmpfs options default to mode=755, mountable by kernel */
		if(mount("dev", "/dev", "devtmpfs", MS_NOSUID | MS_NOEXEC | MS_NOATIME, "size=128k,nr_inodes=4096")
		&& errno != EBUSY)
			return EXIT_FAILURE;
	#else
		/* support old style setups */
		struct stat dev1, dev2;

		/* mount unique tmpfs on /dev */
		if(stat("/dev/.", &dev1) || stat("/dev/..", &dev2) || (dev1.st_dev == dev2.st_dev
		&& mount("dev", "/dev", "tmpfs", MS_NOSUID | MS_NOEXEC | MS_NOATIME, "size=128k,mode=755")))
			return EXIT_FAILURE;

		/* create /dev/urandom device node */
		umask(0); /* get all access rights */
		mknod("/dev/urandom", S_IFCHR | S_IRUSR|S_IWUSR | S_IRGRP|S_IWGRP | S_IROTH|S_IWOTH, makedev(1, 9));
	#endif
	}

	/* load random seed, saved by stop */
	fd = open("/var/lib/misc/random-seed", O_RDONLY);
	if(fd != -1) {
		struct {
			int entropy_count;
			int buf_size;
			char buf[512];
		} seed; /* see struct rand_pool_info */

		seed.buf_size = read(fd, seed.buf, sizeof(seed.buf));
		close(fd);

		if(seed.buf_size == sizeof(seed.buf)) {
			fd = open("/dev/urandom", O_WRONLY);
			if(fd != -1) {
				seed.entropy_count = sizeof(seed.buf) * 8;
				ioctl(fd, RNDADDENTROPY, &seed);
				close(fd);
			}
		}
	}

#ifdef CONFIG_UNIX98_PTYS
	mkdir("/dev/pts", S_IRUSR|S_IWUSR|S_IXUSR | S_IRGRP|S_IXGRP | S_IROTH|S_IXOTH);
	if(hill("/dev/pts") && errno != EBUSY) {
		struct group *tty = getgrnam("tty");
		char gid_mode[(sizeof(unsigned) * 5) / 2 + 15];

		/* try /etc/group first, fall back to gid=5 */
		sprintf(gid_mode, "gid=%u,mode=620", tty?tty->gr_gid:5);
		mount("pts", "/dev/pts", "devpts", MS_NOSUID | MS_NOEXEC | MS_NOATIME, gid_mode);
	}
#endif

#ifdef CONFIG_SHMEM
#ifdef CONFIG_DEVTMPFS
	umask(0);
#endif
	fd = mkdir("/dev/shm", S_IRUSR|S_IWUSR|S_IXUSR | S_IRGRP|S_IWGRP|S_IXGRP | S_IROTH|S_IWOTH|S_IXOTH);
	if(hill("/dev/shm") && errno != EBUSY) {
		struct stat shm1, shm2;

		if(fd == 0 /* mount unique tmpfs on /dev/shm */
		||(stat("/dev/shm/.", &shm1) == 0 && stat("/dev/shm/..", &shm2) == 0 && shm1.st_dev == shm2.st_dev))
			mount("shm", "/dev/shm", "tmpfs", MS_NOSUID | MS_NOEXEC | MS_NOATIME, NULL);
	}
#endif

	/* populate /dev */
	if(uname(&kernel) >= 0)
		mkdevs("/lib/modules/%s/modules.devname", kernel.release);

	/* e.g.: root l sda1 */
	mkdevs("/etc/boot.d/mount/dev/seed", NULL);

	/* report mounted */
	return EXIT_SUCCESS;
}
