#include <errno.h>
#include <stdlib.h>
#include <sys/mount.h>

#include "../../lib/hill.h"

int main(void)
{
	/* try /etc/fstab first and fall back on failure */
	if(hill("/sys") && errno != EBUSY)
		if(mount("sys", "/sys", "sysfs", MS_NOSUID | MS_NODEV | MS_NOEXEC | MS_NOATIME, NULL)
		&& errno != EBUSY)
			return EXIT_FAILURE;

	/* report mounted */
	return EXIT_SUCCESS;
}
