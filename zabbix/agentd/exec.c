#include <errno.h>
#include <fcntl.h>
#include <pwd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
	static char * const zabbix_agentd[] = {"/usr/sbin/zabbix_agentd", "-c/etc/zabbix/zabbix_agentd.conf", NULL};
	struct passwd *zabbix;
	pid_t pid;

	/* common access rights */
	umask(S_IWGRP | S_IWOTH);

	/* zabbix_agentd needs /var/run/zabbix, create the link target */
	if((mkdir("/run/zabbix", S_IRUSR|S_IWUSR|S_IXUSR | S_IRGRP|S_IXGRP | S_IROTH|S_IXOTH) && errno != EEXIST)
	||(zabbix = getpwnam("zabbix")) == NULL || chown("/run/zabbix", zabbix->pw_uid, zabbix->pw_gid)
	|| access(zabbix_agentd[0], X_OK))
		return EXIT_FAILURE;

	execve(zabbix_agentd[0], zabbix_agentd, NULL);
	return EXIT_FAILURE;
}
