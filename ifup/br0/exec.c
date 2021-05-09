#include <linux/sockios.h>
#include <net/if.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define IPv4(a, b, c, d) ((a<<0)|(b<<8)|(c<<16)|(d<<24))

void _start(void)
{
	/* create and bring up br0 */
	int sk = socket(AF_INET, SOCK_RAW, 253);
	if(sk != -1) {
		struct ifreq ifr;

		/* set interface name */
		memset(&ifr, 0, sizeof(ifr));
		strcpy(ifr.ifr_name, "br0");
		ioctl(sk, SIOCBRADDBR, &ifr);

		/* read interface flags */
		if(ioctl(sk, SIOCGIFFLAGS, &ifr) >= 0
		&&(ifr.ifr_flags & IFF_UP) == 0) {
			((struct sockaddr_in*)&ifr.ifr_addr)->sin_family = AF_INET;
			((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr.s_addr = IPv4(192, 168, 0, 1);
			ioctl(sk, SIOCSIFADDR, &ifr);

		#if 0	/* enable this to override assigned netmask */
			((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr.s_addr = IPv4(255, 255, 255, 0);
			ioctl(sk, SIOCSIFNETMASK, &ifr);
		#endif
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
