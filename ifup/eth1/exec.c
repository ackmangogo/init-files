#include <net/if.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main(void)
{
        struct ifreq ifr;

        /* bring up eth1 */
        int sk = socket(PF_INET, SOCK_RAW, 253);
        if(sk == -1)
                return EXIT_FAILURE;

        /* set interface name */
        memset(&ifr, 0, sizeof(ifr));
        strcpy(ifr.ifr_name, "eth1");

        /* read interface flags */
        if(ioctl(sk, SIOCGIFFLAGS, &ifr) >= 0
        &&(ifr.ifr_flags & IFF_UP) == 0) {
                /* if down, bring it up */
                ifr.ifr_flags |= IFF_UP;
                ioctl(sk, SIOCSIFFLAGS, &ifr);
        }

	close(sk);

        return EXIT_SUCCESS;
}

