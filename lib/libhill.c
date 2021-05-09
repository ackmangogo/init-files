#include <errno.h>
#include <fstab.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "hill.h"
#include "mntdata.h"
#include "mntopts.h"

int hill(const char *file)
{
	struct fstab *fstab = getfsfile(file);
	int ERRNO = ENOENT;

	if(fstab) {
		unsigned long int options = 0;
		char *data = fstab->fs_mntops;

		if(data) {
			char *tok = data;

			/* no spaces here, great */
			while(*tok == ',')
				tok++;

			while(*tok) {
				char *end = strchrnul(tok, ',');
				int len = end - tok;
				const struct mntopts *opt;

				if(*end) {
					*end++ = 0;

					while(*end == ',')
						end++;
				}

				if((opt = mntopts(tok, len))) {
					/* collect options */
					options |= opt->set;
					options &= opt->clr;

					tok = end;
					continue;
				}

				if((len = mntdata(tok, len)) < 0)
					goto stat; /* errno set */

				/* collect data in place */
				if(len) {
					if(data > fstab->fs_mntops)
						*data++ = ',';

					memcpy(data, tok, len);
					data += len;
				}

				tok = end;
			}

			/* terminate data */
			*data = 0;

			/* check if there is data for mount(2) */
			data = *fstab->fs_mntops?fstab->fs_mntops:NULL;
		}

		/* root already mounted */
		if(strcmp(file, "/") == 0)
			options |= MS_REMOUNT;

		/* check if already mounted (tmpfs only) */
		if((options & MS_REMOUNT) == 0 && strcmp(fstab->fs_vfstype, "tmpfs") == 0) {
			size_t len = strlen(file);
			struct stat dir2, dir1;
			char path[len + 4];

			memcpy(path, file, len);
			strcpy(path + len, "/..");
			if(stat(path, &dir2))
				goto stat;

			/* "%s/." */
			path[len + 2] = 0;
			if(stat(path, &dir1))
				goto stat;

			if(dir1.st_dev != dir2.st_dev) {
				ERRNO = EBUSY;
				goto fail;
			}
		}

		if(mount(fstab->fs_spec, file, fstab->fs_vfstype, options, data) == 0) {
			endfsent();
			return 0;
		}

	stat:	ERRNO = errno;
	}

fail:	endfsent();

	errno = ERRNO;

	return -1;
}
