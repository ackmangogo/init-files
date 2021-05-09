#include <stdio.h>
#include <stdlib.h>

#include "mntopts.h"

int main(void)
{
	puts("%readonly-tables");
	puts("%define lookup-function-name mntopts");
	puts("%{");
	puts("#include <string.h>\n");
	puts("#include \"mntopts.h\"\n");
	puts("#define _CLR(opt) 0, ~(opt)");
	puts("#define _SET(opt) (opt), ~0");
	puts("%}");
	puts("%omit-struct-type");
	puts("struct mntopts");
	puts("%%");
	puts("defaults, 0, 0");
#ifdef MS_RDONLY
	puts("ro, _SET(MS_RDONLY)");
	puts("rw, _CLR(MS_RDONLY)");
#endif
#ifdef MS_NOEXEC
	puts("exec, _CLR(MS_NOEXEC)");
	puts("noexec, _SET(MS_NOEXEC)");
#endif
#ifdef MS_NOSUID
	puts("suid, _CLR(MS_NOSUID)");
	puts("nosuid, _SET(MS_NOSUID)");
#endif
#ifdef MS_NODEV
	puts("dev, _CLR(MS_NODEV)");
	puts("nodev, _SET(MS_NODEV)");
#endif
#ifdef MS_SYNCHRONOUS
	puts("sync, _SET(MS_SYNCHRONOUS)");
	puts("async, _CLR(MS_SYNCHRONOUS)");
#endif
#ifdef MS_DIRSYNC
	puts("dirsync, _SET(MS_DIRSYNC)");
#endif
#ifdef MS_REMOUNT
	puts("remount, _SET(MS_REMOUNT)");
#endif
#ifdef MS_BIND
	puts("bind, _SET(MS_BIND)");
#ifdef MS_REC
	puts("rbind, _SET(MS_BIND | MS_REC)");
#endif
#endif
#ifdef MS_NOSUB
	puts("sub, _CLR(MS_NOSUB)");
	puts("nosub, _SET(MS_NOSUB)");
#endif
#ifdef MS_SILENT
	puts("silent, _SET(MS_SILENT)");
	puts("loud, _CLR(MS_SILENT)");
#endif
#ifdef MS_MANDLOCK
	puts("mand, _SET(MS_MANDLOCK)");
	puts("nomand, _CLR(MS_MANDLOCK)");
#endif
#ifdef MS_NOATIME
	puts("atime, _CLR(MS_NOATIME)");
	puts("noatime, _SET(MS_NOATIME)");
#endif
#ifdef MS_I_VERSION
	puts("iversion, _SET(MS_I_VERSION)");
	puts("noiversion, _CLR(MS_I_VERSION)");
#endif
#ifdef MS_NODIRATIME
	puts("diratime, _CLR(MS_NODIRATIME)");
	puts("nodiratime, _SET(MS_NODIRATIME)");
#endif
#ifdef MS_RELATIME
	puts("relatime, _SET(MS_RELATIME)");
	puts("norelatime, _CLR(MS_RELATIME)");
#endif
#ifdef MS_STRICTATIME
	puts("strictatime, _SET(MS_STRICTATIME)");
	puts("nostrictatime, _CLR(MS_STRICTATIME)");
#endif
#ifdef MS_LAZYTIME
	puts("lazytime, _SET(MS_LAZYTIME)");
	puts("nolazytime, _CLR(MS_LAZYTIME)");
#endif
#ifdef MS_PROPAGATION
	puts("unbindable, _SET(MS_UNBINDABLE)");
	puts("private, _SET(MS_PRIVATE)");
	puts("slave, _SET(MS_SLAVE)");
	puts("shared, _SET(MS_SHARED)");
#ifdef MS_REC
	puts("runbindable, _SET(MS_UNBINDABLE | MS_REC)");
	puts("rprivate, _SET(MS_PRIVATE | MS_REC)");
	puts("rslave, _SET(MS_SLAVE | MS_REC)");
	puts("rshared, _SET(MS_SHARED | MS_REC)");
#endif
#endif
	puts("%%");

	return EXIT_SUCCESS;
}
