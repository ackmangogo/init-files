#include "conf.h"

#ifdef LOOPBACK
#include <net/if.h>
#endif
#include <stdlib.h>
#ifdef LOOPBACK
#include <string.h>
#include <sys/ioctl.h>
#endif
#include <sys/resource.h>
#ifdef CONNMAN_1_31
#include <sys/stat.h>
#endif
#include <unistd.h>

void _start(void)
{
	static char * const connmand[] = {"/usr/sbin/connmand", NULL};
#ifdef LOOPBACK
	/* bring up local loopback (lo) */
	int sk = socket(PF_INET, SOCK_RAW, 253);
	if(sk != -1) {
		struct ifreq ifr;

		/* set interface name */
		memset(&ifr, 0, sizeof(ifr));
		strcpy(ifr.ifr_name, "lo");

		/* read interface flags */
		if(ioctl(sk, SIOCGIFFLAGS, &ifr) >= 0
		&&(ifr.ifr_flags & IFF_UP) == 0) {
			/* if down, bring it up */
			ifr.ifr_flags |= IFF_UP;
			ioctl(sk, SIOCSIFFLAGS, &ifr);
		}

		close(sk);
	}
#endif
#ifdef CONNMAN_1_31
        /* with version 1.31 connmand wants /var/run/connman, create the link target */
        mkdir("/run/connman", S_IRUSR|S_IWUSR|S_IXUSR | S_IRGRP|S_IXGRP | S_IROTH|S_IXOTH);
#endif
	/* maximum niceness, lowest priority */
	setpriority(PRIO_PROCESS, 0, PRIO_MAX);
	execve(connmand[0], connmand, NULL);
	_exit(EXIT_FAILURE);
}
