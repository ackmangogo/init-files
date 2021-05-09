#include <net/if.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

void _start(void)
{
	/* bring up local loopback (lo) */
	int sk = socket(AF_INET, SOCK_RAW, 253);
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

		if(ifr.ifr_flags & IFF_UP)
			_exit(EXIT_SUCCESS);
	}

	_exit(EXIT_FAILURE);
}
