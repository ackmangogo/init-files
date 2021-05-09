/*
 * #!/bin/sh
 * ip tuntap del mode tun dev tsX
 * ip tunsafe stop tsX
 */
#if defined(TID) && defined(FWM)
#include <libmnl/libmnl.h>
#include <linux/fib_rules.h>
#include <linux/rtnetlink.h>
#include <net/if.h>
#include <string.h>
#endif
#include <stdlib.h>
#include <unistd.h>

/* interface name */
#define tsX "ts0"

int main(void)
{
	static char *const ts[] = {"/usr/bin/tunsafe", "stop", tsX, NULL};

#if defined(TID) && defined(FWM)
	struct mnl_socket *nl;
	char buf[MNL_SOCKET_BUFFER_SIZE];
	struct nlmsghdr *nlh;
	struct fib_rule_hdr *frh;

	nl = mnl_socket_open(NETLINK_ROUTE);
	if(nl == NULL)
		goto err;

	if(mnl_socket_bind(nl, 0, MNL_SOCKET_AUTOPID) < 0)
		goto errnl;

	/* ip rule del table main suppress_prefixlength 0 */
	nlh = mnl_nlmsg_put_header(buf);
	nlh->nlmsg_type = RTM_DELRULE;
	nlh->nlmsg_flags = NLM_F_REQUEST|NLM_F_CREATE|NLM_F_EXCL;
	frh = mnl_nlmsg_put_extra_header(nlh, sizeof(*frh));
	frh->family = AF_INET;
	frh->table = 254; /* reserved for main */

	frh->action = FR_ACT_TO_TBL;
	mnl_attr_put_u32(nlh, FRA_SUPPRESS_PREFIXLEN, 0);
	mnl_socket_sendto(nl, nlh, nlh->nlmsg_len);

	/* ip rule del fwmark FWM table TID */
	nlh = mnl_nlmsg_put_header(buf);
	nlh->nlmsg_type = RTM_DELRULE;
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
	frh->flags = FIB_RULE_INVERT;
	mnl_attr_put_u32(nlh, FRA_FWMARK, FWM);
	mnl_socket_sendto(nl, nlh, nlh->nlmsg_len);

	mnl_socket_close(nl);
#endif
	execve(ts[0], ts, NULL);
	return EXIT_FAILURE;

#if defined(TID) && defined(FWM)
errnl:	mnl_socket_close(nl);
err:	return EXIT_FAILURE;
#endif
}
