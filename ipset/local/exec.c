/* define desired set name */
#define SETNAME "local"

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <libmnl/libmnl.h>
#include <linux/netfilter.h>
#include <linux/netfilter/ipset/ip_set.h>
#include <linux/netfilter/nfnetlink.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>

int main(void)
{
	struct mnl_socket *nl;
	char buf[MNL_SOCKET_BUFFER_SIZE];
	struct nlmsghdr *nlh;
	struct nfgenmsg *nfg;
	int len;
	FILE *f;

	nl = mnl_socket_open(NETLINK_NETFILTER);
	if(nl == NULL)
		return EXIT_FAILURE;

	if(mnl_socket_bind(nl, 0, MNL_SOCKET_AUTOPID) < 0)
		goto err;

	nlh = mnl_nlmsg_put_header(buf);
	nlh->nlmsg_type = (NFNL_SUBSYS_IPSET << 8)|IPSET_CMD_CREATE;
	nlh->nlmsg_flags = NLM_F_REQUEST|NLM_F_CREATE|NLM_F_EXCL|NLM_F_ACK;
	nfg = mnl_nlmsg_put_extra_header(nlh, sizeof(*nfg));
	nfg->nfgen_family = AF_INET;
	nfg->version = NFNETLINK_V0;
	mnl_attr_put_u8(nlh, IPSET_ATTR_PROTOCOL, IPSET_PROTOCOL);
	mnl_attr_put(nlh, IPSET_ATTR_SETNAME, sizeof(SETNAME), SETNAME);
	mnl_attr_put(nlh, IPSET_ATTR_TYPENAME, 9, "hash:net");
	mnl_attr_put_u8(nlh, IPSET_ATTR_REVISION, 0);
	mnl_attr_put_u8(nlh, IPSET_ATTR_FAMILY, NFPROTO_IPV4);

	/* failures are not fatal, reduced functionality */
	if(mnl_socket_sendto(nl, nlh, nlh->nlmsg_len) <= 0
	||(len = mnl_socket_recvfrom(nl, buf, sizeof(buf))) <= 0
	|| mnl_cb_run(buf, len, 0, 0, NULL, NULL) < 0)
		goto err;

	/* restore from set file (optional) */
	f = fopen("/var/lib/ipset/"SETNAME, "r");
	if(f) {
		char *line = NULL;
		size_t size = 0;

		while((len = getline(&line, &size, f)) > 0) {
			char *mask;
			long int cidr = 32;
			struct in_addr addr;
			struct nlattr *nest, *data;

			/* normalize line */
			if(line[len - 1] == '\n')
				line[--len] = 0;

			if((mask = memchr(line, '/', len))) {
				char *end;

				*mask++ = 0;

				errno = 0;
				cidr = strtol(mask, &end, 10);
				if(end <= mask || *end || errno || cidr < 0 || cidr > 32)
					continue;
			}

			if(inet_aton(line, &addr) == 0)
				continue;

			nlh = mnl_nlmsg_put_header(buf);
			nlh->nlmsg_type = (NFNL_SUBSYS_IPSET << 8)|IPSET_CMD_ADD;
			nlh->nlmsg_flags = NLM_F_REQUEST|NLM_F_EXCL;
			nfg = mnl_nlmsg_put_extra_header(nlh, sizeof(*nfg));
			nfg->nfgen_family = AF_INET;
			nfg->version = NFNETLINK_V0;
			mnl_attr_put_u8(nlh, IPSET_ATTR_PROTOCOL, IPSET_PROTOCOL);
			mnl_attr_put(nlh, IPSET_ATTR_SETNAME, sizeof(SETNAME), SETNAME);
			data = mnl_attr_nest_start(nlh, IPSET_ATTR_DATA);
			nest = mnl_attr_nest_start(nlh, IPSET_ATTR_IP);
			mnl_attr_put_u32(nlh, IPSET_ATTR_IPADDR_IPV4|NLA_F_NET_BYTEORDER, addr.s_addr);
			mnl_attr_nest_end(nlh, nest);
			mnl_attr_put_u8(nlh, IPSET_ATTR_CIDR, cidr);
			mnl_attr_nest_end(nlh, data);
			mnl_socket_sendto(nl, nlh, nlh->nlmsg_len);
		}

		free(line);
		fclose(f);
	}

	mnl_socket_close(nl);
	return EXIT_SUCCESS;

err:	mnl_socket_close(nl);
	return EXIT_FAILURE;
}
