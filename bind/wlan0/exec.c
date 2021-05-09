#include <libmnl/libmnl.h>
#include <linux/rtnetlink.h>
#include <net/if.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

static int attr_cb(const struct nlattr *attr, void *more)
{
	if(mnl_attr_get_type(attr) != IFA_LABEL)
		return MNL_CB_OK;

	if(mnl_attr_validate(attr, MNL_TYPE_STRING) < 0)
		return MNL_CB_ERROR;

	if(strcmp(mnl_attr_get_payload(attr), "wlan0"))
		return MNL_CB_OK;

	*((int*)more) = 0;
	return MNL_CB_STOP;
}

static int data_cb(const struct nlmsghdr *nlh, void *more)
{
	if(nlh->nlmsg_type != RTM_NEWADDR)
		return MNL_CB_OK;

	return mnl_attr_parse(nlh, sizeof(struct ifaddrmsg), attr_cb, more);
}

int main(void)
{
	struct mnl_socket *nl;
	char buf[MNL_SOCKET_BUFFER_SIZE];
	struct nlmsghdr *nlh;
	struct rtgenmsg *rt;
	int len;

	nl = mnl_socket_open(NETLINK_ROUTE);
	if(nl == NULL)
		goto err;

	if(mnl_socket_bind(nl, RTMGRP_IPV4_IFADDR, MNL_SOCKET_AUTOPID) < 0)
		goto err1;

	nlh = mnl_nlmsg_put_header(buf);
	nlh->nlmsg_type	= RTM_GETADDR;
	nlh->nlmsg_flags = NLM_F_REQUEST|NLM_F_DUMP;
	rt = mnl_nlmsg_put_extra_header(nlh, sizeof(*rt));
	rt->rtgen_family = AF_INET;

	/* trigger initial dump */
	if(mnl_socket_sendto(nl, nlh, nlh->nlmsg_len) < 0)
		goto err1;

	signal(SIGALRM, exit);
	alarm(60);

	/* and listen to events */
	while((len = mnl_socket_recvfrom(nl, buf, sizeof(buf))) > 0) {
		if(mnl_cb_run(buf, len, 0, 0, data_cb, &len) < 0)
			goto err1;
		if(len == 0) {
			mnl_socket_close(nl);
			return EXIT_SUCCESS;
		}
	}

err1:	mnl_socket_close(nl);
err:	return EXIT_FAILURE;
}
