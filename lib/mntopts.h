#ifndef __MNTOPTS_H
#define __MNTOPTS_H

#include <sys/mount.h>

/* mount(2) MS_* masks */
#ifndef MS_RDONLY
#define MS_RDONLY	(1<<0)	/* mount read-only */
#endif
#ifndef MS_NOSUID
#define MS_NOSUID	(1<<1)	/* ignore suid and sgid bits */
#endif
#ifndef MS_NODEV
#define MS_NODEV	(1<<2)	/* disallow access to device special files */
#endif
#ifndef MS_NOEXEC
#define MS_NOEXEC	(1<<3)	/* disallow program execution */
#endif
#ifndef MS_SYNCHRONOUS
#define MS_SYNCHRONOUS	(1<<4)	/* writes are synced at once */
#endif
#ifndef MS_REMOUNT
#define MS_REMOUNT	(1<<5)	/* alter flags of a mounted FS */
#endif
#ifndef MS_MANDLOCK
#define MS_MANDLOCK	(1<<6)	/* allow mandatory locks on an FS */
#endif
#ifndef MS_DIRSYNC
#define MS_DIRSYNC	(1<<7)	/* directory modifications are synchronous */
#endif
#ifndef MS_NOATIME
#define MS_NOATIME	(1<<10)	/* 1024: do not update access times. */
#endif
#ifndef MS_NODIRATIME
#define MS_NODIRATIME	(1<<11)	/* 2048: don't update directory access times */
#endif
#ifndef MS_BIND
#define MS_BIND		(1<<12)	/* 4096: mount existing tree elsewhere as well */
#endif
#ifndef MS_MOVE
#define MS_MOVE		(1<<13)	/* 8192: atomically move the tree */
#endif
#ifndef MS_REC
#define MS_REC		(1<<14)	/* 16384: recursive loopback */
#endif
#ifndef MS_SILENT
#define MS_SILENT	(1<<15)	/* 32768: don't emit certain kernel messages */
#endif
#ifndef MS_UNBINDABLE
#define MS_UNBINDABLE	(1<<17)	/* 131072: make unbindable */
#endif
#ifndef MS_PRIVATE
#define MS_PRIVATE	(1<<18)	/* 262144: make private */
#endif
#ifndef MS_SLAVE
#define MS_SLAVE	(1<<19)	/* 524288: make slave */
#endif
#ifndef MS_SHARED
#define MS_SHARED	(1<<20)	/* 1048576: make shared */
#endif
#ifndef MS_RELATIME
#define MS_RELATIME	(1<<21)	/* 2097152: update atime relative to mtime/ctime */
#endif
#ifndef MS_I_VERSION
#define MS_I_VERSION	(1<<23)	/* update the inode i_version field */
#endif
#ifndef MS_STRICTATIME
#define MS_STRICTATIME	(1<<24)	/* always perform atime updates */
#endif
#ifndef MS_LAZYTIME
#define MS_LAZYTIME	(1<<25)	/* update the on-disk [acm]times lazily */
#endif

/* shared-subtree options */
#define MS_PROPAGATION	(MS_SHARED|MS_SLAVE|MS_UNBINDABLE|MS_PRIVATE)

__attribute__((visibility("hidden")))
const struct mntopts {
	char *name;
	/* (opts | set) & clr */
	unsigned long int set;
	unsigned long int clr;
} *mntopts(register const char *str, register size_t len);

#endif /* __MNTOPTS_H */
