#include <stdlib.h>
#include <sys/mount.h>

#include "../../lib/hill.h"

int main(void)
{
	/* try /etc/fstab first and fall back on failure */
	return hill("/") && mount("rootfs", "/", "rootfs", MS_REMOUNT | MS_NOATIME, NULL)?EXIT_FAILURE:EXIT_SUCCESS;
}
