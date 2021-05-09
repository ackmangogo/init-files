#include <libmnl/libmnl.h>
#include <linux/rtnetlink.h>
#include <net/if.h>
#include <netdb.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

static int attr_cb(const struct nlattr *attr, void *host)
{
	if(mnl_attr_get_type(attr) != IFA_LOCAL)
		return MNL_CB_OK;

	if(mnl_attr_validate(attr, MNL_TYPE_BINARY) < 0)
		return MNL_CB_ERROR;

	if(memcmp(mnl_attr_get_payload(attr), ((struct hostent*)host)->h_addr, ((struct hostent*)host)->h_length))
		return MNL_CB_OK;

	((struct hostent*)host)->h_length = 0;
	return MNL_CB_STOP;
}

static int data_cb(const struct nlmsghdr *nlh, void *host)
{
	if(nlh->nlmsg_type != RTM_NEWADDR)
		return MNL_CB_OK;

	return mnl_attr_parse(nlh, sizeof(struct ifaddrmsg), attr_cb, host);
}

int main(void)
{
	struct hostent *host;
	struct mnl_socket *nl;
	char buf[MNL_SOCKET_BUFFER_SIZE];
	struct nlmsghdr *nlh;
	struct rtgenmsg *rt;
	int len;

	/* make sure we can bind to host (see /etc/hosts) */
	host = gethostbyname("localhost");
	if(host == NULL)
		goto err;

	nl = mnl_socket_open(NETLINK_ROUTE);
	if(nl == NULL)
		goto err;

	if(mnl_socket_bind(nl, (host->h_addrtype == AF_INET)?RTMGRP_IPV4_IFADDR:RTMGRP_IPV6_IFADDR, MNL_SOCKET_AUTOPID) < 0)
		goto err1;

	nlh = mnl_nlmsg_put_header(buf);
	nlh->nlmsg_type	= RTM_GETADDR;
	nlh->nlmsg_flags = NLM_F_REQUEST|NLM_F_DUMP;
	rt = mnl_nlmsg_put_extra_header(nlh, sizeof(*rt));
	rt->rtgen_family = host->h_addrtype;

	/* trigger initial dump */
	if(mnl_socket_sendto(nl, nlh, nlh->nlmsg_len) < 0)
		goto err1;

	signal(SIGALRM, exit);
	alarm(60);

	/* and listen to events */
	while((len = mnl_socket_recvfrom(nl, buf, sizeof(buf))) > 0) {
		if(mnl_cb_run(buf, len, 0, 0, data_cb, host) < 0)
			goto err1;
		if(host->h_length == 0) {
			mnl_socket_close(nl);
			return EXIT_SUCCESS;
		}
	}

err1:	mnl_socket_close(nl);
err:	return EXIT_FAILURE;
}
