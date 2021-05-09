/*
 * #!/bin/sh
 * ip tuntap add mode tun dev tsX
 *
 * tunsafe start -n tsX /etc/wireguard/tsX.conf
 */
#include <fcntl.h>
#include <libmnl/libmnl.h>
#if defined(TID) && defined(FWM)
#include <linux/fib_rules.h>
#endif
#include <linux/if_tun.h>
#include <linux/rtnetlink.h>
#include <net/if.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

/* interface name */
#define tsX "ts0"

int main(void)
{
	static char *const ts[] = {"/usr/bin/tunsafe", "start", "-n", tsX, "/etc/wireguard/"tsX".conf", NULL};

	int sk;
	struct ifreq ifr;
#if defined(TID) && defined(FWM)
	struct mnl_socket *nl;
	char buf[MNL_SOCKET_BUFFER_SIZE];
	struct nlmsghdr *nlh;
	struct rtmsg *rtm;
	int len;
#endif
	/* open the clone device */
	sk = open("/dev/net/tun", O_RDWR);
	if(sk == -1)
		goto err;

	memset(&ifr, 0, sizeof(ifr));
	ifr.ifr_flags = IFF_TUN | IFF_NO_PI;
	strcpy(ifr.ifr_name, tsX);

	/* create persistent tsX */
	if(ioctl(sk, TUNSETIFF, &ifr)
	|| ioctl(sk, TUNSETPERSIST, 1))
		goto errif;

	close(sk);

#if defined(TID) && defined(FWM)
	/* bring tsX up */
	sk = socket(AF_INET, SOCK_RAW, 253);
	if(sk == -1)
		goto err;

	ifr.ifr_flags = 0;
	if(ioctl(sk, SIOCGIFFLAGS, &ifr) < 0)
		goto errif;

	if((ifr.ifr_flags & IFF_UP) == 0) {
		ifr.ifr_flags |= IFF_UP;
		ioctl(sk, SIOCSIFFLAGS, &ifr);
	}

	close(sk);

	/* configure route and rules */
	nl = mnl_socket_open(NETLINK_ROUTE);
	if(nl == NULL)
		goto err;

	if(mnl_socket_bind(nl, 0, MNL_SOCKET_AUTOPID) < 0)
		goto errnl;

	/* ip route add default dev tsX table TID */
	nlh = mnl_nlmsg_put_header(buf);
	nlh->nlmsg_type = RTM_NEWROUTE;
	nlh->nlmsg_flags = NLM_F_REQUEST|NLM_F_CREATE|NLM_F_EXCL|NLM_F_ACK;
	rtm = mnl_nlmsg_put_extra_header(nlh, sizeof(*rtm));
	rtm->rtm_family = AF_INET;
	rtm->rtm_protocol = RTPROT_BOOT;
#if TID > 255
	rtm->rtm_table = RT_TABLE_UNSPEC;
	mnl_attr_put_u32(nlh, RTA_TABLE, TID);
#else
	rtm->rtm_table = TID;
#endif
	rtm->rtm_type = RTN_UNICAST;
	rtm->rtm_scope = RT_SCOPE_LINK;
	mnl_attr_put_u32(nlh, RTA_OIF, if_nametoindex(tsX));

	/* failures are not fatal, reduced functionality */
	if(mnl_socket_sendto(nl, nlh, nlh->nlmsg_len) > 0
	&&(len = mnl_socket_recvfrom(nl, buf, sizeof(buf))) > 0
	&& mnl_cb_run(buf, len, 0, 0, NULL, NULL) >= 0) {
		struct fib_rule_hdr *frh;

		/* ip rule add not fwmark FWM table TID */
		nlh = mnl_nlmsg_put_header(buf);
		nlh->nlmsg_type = RTM_NEWRULE;
		nlh->nlmsg_flags = NLM_F_REQUEST|NLM_F_CREATE|NLM_F_EXCL;
		frh = mnl_nlmsg_put_extra_header(nlh, sizeof(*frh));
		frh->family = AF_INET;
	#if TID > 255
		frh->table = RT_TABLE_UNSPEC;
		mnl_attr_put_u32(nlh, FRA_TABLE, TID);
	#else
		frh->table = TID;
	#endif
		frh->action = FR_ACT_TO_TBL;
//		frh->flags = FIB_RULE_INVERT;
		mnl_attr_put_u32(nlh, FRA_FWMARK, FWM);
		mnl_socket_sendto(nl, nlh, nlh->nlmsg_len);

		/* ip rule add table main suppress_prefixlength 0 */
		nlh = mnl_nlmsg_put_header(buf);
		nlh->nlmsg_type = RTM_NEWRULE;
		nlh->nlmsg_flags = NLM_F_REQUEST|NLM_F_CREATE|NLM_F_EXCL;
		frh = mnl_nlmsg_put_extra_header(nlh, sizeof(*frh));
		frh->family = AF_INET;
		frh->table = 254; /* reserved for main */

		frh->action = FR_ACT_TO_TBL;
		mnl_attr_put_u32(nlh, FRA_SUPPRESS_PREFIXLEN, 0);
		mnl_socket_sendto(nl, nlh, nlh->nlmsg_len);
	}

	mnl_socket_close(nl);
#endif
	execve(ts[0], ts, NULL);
	return EXIT_FAILURE;

errif:	close(sk);
err:	return EXIT_FAILURE;

#if defined(TID) && defined(FWM)
errnl:	mnl_socket_close(nl);
	return EXIT_FAILURE;
#endif
}
