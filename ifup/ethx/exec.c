#define ADDRESS IPv4(192, 168, 88, 5)
#define GATEWAY IPv4(192, 168, 88, 1)

#if defined(TID) && defined(GATEWAY)
#include <libmnl/libmnl.h>
#include <linux/fib_rules.h>
#include <linux/rtnetlink.h>
#endif
#include <linux/sockios.h>
#include <net/if.h>
#if !defined(TID) && defined(GATEWAY)
#include <net/route.h>
#endif
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define IPv4(a, b, c, d) ((a<<0)|(b<<8)|(c<<16)|(d<<24))

int main(void)
{
	/* create and bring up eth0 */
	int sk = socket(AF_INET, SOCK_RAW, 253);
	if(sk != -1) {
		struct ifreq ifr;
	#if defined(TID) && defined(GATEWAY)
		int ifindex;
	#endif
		/* set interface name */
		memset(&ifr, 0, sizeof(ifr));
		strcpy(ifr.ifr_name, "eth0");

		/* read interface flags */
		if(ioctl(sk, SIOCGIFFLAGS, &ifr) >= 0
		&&(ifr.ifr_flags & IFF_UP) == 0) {
		#if !defined(TID) && defined(GATEWAY)
			struct rtentry route;
		#endif
		#if defined(TID) && defined(GATEWAY)
			ioctl(sk, SIOCGIFINDEX, &ifr);
			ifindex = ifr.ifr_ifindex;
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

		#if !defined(TID) && defined(GATEWAY)
			memset(&route, 0, sizeof(route));
			/* INADDR_ANY == IPv4(0, 0, 0, 0), implied by memset */
			((struct sockaddr_in*)&route.rt_dst)->sin_family = AF_INET;
			((struct sockaddr_in*)&route.rt_gateway)->sin_family = AF_INET;
			((struct sockaddr_in*)&route.rt_gateway)->sin_addr.s_addr = GATEWAY;
			((struct sockaddr_in*)&route.rt_genmask)->sin_family = AF_INET;
			route.rt_flags = RTF_UP|RTF_GATEWAY;
			route.rt_dev = "eth0";
			ioctl(sk, SIOCADDRT, &route);
		#endif
		}

		close(sk);

		if(ifr.ifr_flags & IFF_UP) {
		#if defined(TID) && defined(GATEWAY)
			struct mnl_socket *nl;
			char buf[MNL_SOCKET_BUFFER_SIZE];
			struct nlmsghdr *nlh;
			struct ifinfomsg *ifi;
			struct nlattr *linkinfo;
			struct ifaddrmsg *ifa;
			struct rtmsg *rtm;
			int len;

			/* failures are not fatal, reduced functionality */
			nl = mnl_socket_open(NETLINK_ROUTE);
			if(nl == NULL)
				goto err;

			if(mnl_socket_bind(nl, 0, MNL_SOCKET_AUTOPID) < 0)
				goto err1;

			/* ip route add default via GATEWAY dev eth0 table TID */
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
			rtm->rtm_scope = RT_SCOPE_UNIVERSE;
			mnl_attr_put_u32(nlh, RTA_GATEWAY, GATEWAY);
			mnl_attr_put_u32(nlh, RTA_OIF, ifindex);
			if(mnl_socket_sendto(nl, nlh, nlh->nlmsg_len) > 0
			&&(len = mnl_socket_recvfrom(nl, buf, sizeof(buf))) > 0
			&& mnl_cb_run(buf, len, 0, 0, NULL, NULL) >= 0) {
				struct fib_rule_hdr *frh;

				/* ip route add GATEWAY/24 dev eth0 src ADDRESS table TID */
				nlh = mnl_nlmsg_put_header(buf);
				nlh->nlmsg_type = RTM_NEWROUTE;
				nlh->nlmsg_flags = NLM_F_REQUEST|NLM_F_CREATE|NLM_F_EXCL;
				rtm = mnl_nlmsg_put_extra_header(nlh, sizeof(*rtm));
				rtm->rtm_family = AF_INET;
				rtm->rtm_dst_len = 24;
				rtm->rtm_protocol = RTPROT_BOOT;
			#if TID > 255
				rtm->rtm_table = RT_TABLE_UNSPEC;
				mnl_attr_put_u32(nlh, RTA_TABLE, TID);
			#else
				rtm->rtm_table = TID;
			#endif
				rtm->rtm_type = RTN_UNICAST;
				rtm->rtm_scope = RT_SCOPE_LINK;
				mnl_attr_put_u32(nlh, RTA_DST, GATEWAY & IPv4(255, 255, 255, 0));
				mnl_attr_put_u32(nlh, RTA_PREFSRC, ADDRESS);
				mnl_attr_put_u32(nlh, RTA_OIF, ifindex);
				mnl_socket_sendto(nl, nlh, nlh->nlmsg_len);

				/* ip rule add from ADDRESS/32 table TID */
				nlh = mnl_nlmsg_put_header(buf);
				nlh->nlmsg_type = RTM_NEWRULE;
				nlh->nlmsg_flags = NLM_F_REQUEST|NLM_F_CREATE|NLM_F_EXCL;
				frh = mnl_nlmsg_put_extra_header(nlh, sizeof(*frh));
				frh->family = AF_INET;
				frh->src_len = 32;
			#if TID > 255
				frh->table = RT_TABLE_UNSPEC;
				mnl_attr_put_u32(nlh, FRA_TABLE, TID);
			#else
				frh->table = TID;
			#endif
				frh->action = FR_ACT_TO_TBL;
				mnl_attr_put_u32(nlh, RTA_SRC, ADDRESS);
				mnl_socket_sendto(nl, nlh, nlh->nlmsg_len);

				/* ip rule add to ADDRESS/32 table TID */
				nlh = mnl_nlmsg_put_header(buf);
				nlh->nlmsg_type = RTM_NEWRULE;
				nlh->nlmsg_flags = NLM_F_REQUEST|NLM_F_CREATE|NLM_F_EXCL;
				frh = mnl_nlmsg_put_extra_header(nlh, sizeof(*frh));
				frh->family = AF_INET;
				frh->dst_len = 32;
			#if TID > 255
				frh->table = RT_TABLE_UNSPEC;
				mnl_attr_put_u32(nlh, FRA_TABLE, TID);
			#else
				frh->table = TID;
			#endif
				frh->action = FR_ACT_TO_TBL;
				mnl_attr_put_u32(nlh, RTA_DST, ADDRESS);
				mnl_socket_sendto(nl, nlh, nlh->nlmsg_len);

				/* ip rule add to 10.72.171.31/32 table TID (for ntpd) */
				nlh = mnl_nlmsg_put_header(buf);
				nlh->nlmsg_type = RTM_NEWRULE;
				nlh->nlmsg_flags = NLM_F_REQUEST|NLM_F_CREATE|NLM_F_EXCL;
				frh = mnl_nlmsg_put_extra_header(nlh, sizeof(*frh));
				frh->family = AF_INET;
				frh->dst_len = 32;
			#if TID > 255
				frh->table = RT_TABLE_UNSPEC;
				mnl_attr_put_u32(nlh, FRA_TABLE, TID);
			#else
				frh->table = TID;
			#endif
				frh->action = FR_ACT_TO_TBL;
				mnl_attr_put_u32(nlh, RTA_DST, IPv4(10, 72, 171, 31));
				mnl_socket_sendto(nl, nlh, nlh->nlmsg_len);
			}

		err1:	mnl_socket_close(nl);
		#endif
		err:	return EXIT_SUCCESS;
		}
	}

	return EXIT_FAILURE;
}
