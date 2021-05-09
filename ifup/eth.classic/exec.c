#define ADDRESS IPv4(192, 168, 33, 5)
#define GATEWAY IPv4(192, 168, 33, 1)

#include <linux/sockios.h>
#include <net/if.h>
#ifdef GATEWAY
#include <net/route.h>
#endif
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define IPv4(a, b, c, d) ((a<<0)|(b<<8)|(c<<16)|(d<<24))

void _start(void)
{
	/* create and bring up eth1 */
	int sk = socket(AF_INET, SOCK_RAW, 253);
	if(sk != -1) {
		struct ifreq ifr;

		/* set interface name */
		memset(&ifr, 0, sizeof(ifr));
		strcpy(ifr.ifr_name, "ethX");

		/* read interface flags */
		if(ioctl(sk, SIOCGIFFLAGS, &ifr) >= 0
		&&(ifr.ifr_flags & IFF_UP) == 0) {
		#ifdef GATEWAY
			struct rtentry route;
		#endif
			((struct sockaddr_in*)&ifr.ifr_addr)->sin_family = AF_INET;
			((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr.s_addr = ADDRESS;
			ioctl(sk, SIOCSIFADDR, &ifr);

		#ifdef NETMASK
			((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr.s_addr = NETMASK;
			ioctl(sk, SIOCSIFNETMASK, &ifr);
		#endif
			/* if down, bring it up */
			ifr.ifr_flags |= (IFF_UP|IFF_RUNNING);
			ioctl(sk, SIOCSIFFLAGS, &ifr);
			if(ioctl(sk, SIOCGIFFLAGS, &ifr) >= 0
			&&(ifr.ifr_flags & (IFF_UP|IFF_RUNNING)) != (IFF_UP|IFF_RUNNING)) {
				ifr.ifr_flags |= (IFF_UP|IFF_RUNNING);
				ioctl(sk, SIOCSIFFLAGS, &ifr);
			}

		#ifdef GATEWAY
			memset(&route, 0, sizeof(route));
			/* INADDR_ANY == IPv4(0, 0, 0, 0), implied by memset */
			((struct sockaddr_in*)&route.rt_dst)->sin_family = AF_INET;
			((struct sockaddr_in*)&route.rt_gateway)->sin_family = AF_INET;
			((struct sockaddr_in*)&route.rt_gateway)->sin_addr.s_addr = GATEWAY;
			((struct sockaddr_in*)&route.rt_genmask)->sin_family = AF_INET;
			route.rt_flags = RTF_UP|RTF_GATEWAY;
			route.rt_dev = "ethX";
			ioctl(sk, SIOCADDRT, &route);
		#endif
		}

		close(sk);

		if(ifr.ifr_flags & IFF_UP)
			_exit(EXIT_SUCCESS);
	}

	_exit(EXIT_FAILURE);
}
