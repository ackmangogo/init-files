#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
	static char * const apache[] = {"/usr/sbin/apache2",
					"-DDAV", "-DDAV_FS",
					"-DSSL", "-DSSL_DEFAULT_VHOST", "-DDEFAULT_VHOST",
					"-DPHP", "-DCACHE", "-DPROXY", NULL};

	execve(apache[0], apache, NULL);
	return EXIT_FAILURE;
}
