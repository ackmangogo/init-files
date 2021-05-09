#include <errno.h>
#include <stdlib.h>
#include <sys/mount.h>

#include "../../lib/hill.h"

int main(void)
{
	/* try /etc/fstab first and fall back on failure */
	if(hill("/sys/fs/cgroup") && errno != EBUSY)
		if(mount("cgroup", "/sys/fs/cgroup", "cgroup", MS_RELATIME, NULL)
		&& errno != EBUSY)
			return EXIT_FAILURE;

	/* report mounted */
	return EXIT_SUCCESS;
}
