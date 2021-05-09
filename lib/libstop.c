#include <errno.h>
#include <dirent.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include "stop.h"

__attribute__((noinline))
pid_t kill_by_exec(int sig, const char *exec, ...)
{
	pid_t killed = 0;

	DIR *proc = opendir("/proc");
	if(proc) {
		struct dirent *dirent;

		while((dirent = readdir(proc))) if(dirent->d_name[0] >= '0' && dirent->d_name[0] <= '9') {
			char *line;

			pid_t pid = strtol(dirent->d_name, &line, 10);
			if(pid > 1 && *line == 0) {
				char path[(sizeof(unsigned) * 5) / 2 + 16];
				size_t size;
				ssize_t len;

				sprintf(path, "/proc/%u/exe", pid);

				size = 64;
			grow:	line = malloc(size);
				if(line == NULL)
					break;

				if((len = readlink(path, line, size)) <= 0)
					goto skip;

				if(len >= size) {
					free(line);
					size *= 2;
					goto grow;
				}

				line[len] = 0;
				if(strcmp(line, exec) == 0) {
					va_list args;
					char *cmd;

					va_start(args, exec);
					if((cmd = va_arg(args, char*))) {
						FILE *f;

						sprintf(path, "/proc/%u/cmdline", pid);
						if((f = fopen(path, "r"))) {
							if(getdelim(&line, &size, 0, f) > 0
							&& strcmp(line, cmd) == 0)
								while((cmd = va_arg(args, char*))
								&& getdelim(&line, &size, 0, f) > 0
								&& strcmp(line, cmd) == 0); /* ! */

							fclose(f);
						}
					}

					va_end(args);
					if(cmd == NULL && kill(pid, sig) == 0) {
						killed = pid;
						if(sig == 0) {
							/* ping */
							free(line);
							break;
						}
					}
				}

			skip:	free(line);
			}
		}

		closedir(proc);
	}

	return killed;
}

pid_t kill_by_pidf(int sig, const char *pidf)
{
	pid_t killed = 0;

	FILE *f = fopen(pidf, "r");
	if(f) {
		pid_t pid;

		if(fscanf(f, "%d", &pid) == 1 && pid > 1 && kill(pid, sig) == 0)
			killed = pid;

		fclose(f);

		if(sig)
			unlink(pidf);
	}

	return killed;
}

__attribute__((weak))
void _stop(void)
{
	exit(EXIT_SUCCESS);
}

__attribute__((visibility("hidden")))
void _bury(void)
{
	size_t size;
	ssize_t len;
	char *exec, *stop;

	size = 64;
grow:	exec = malloc(size);
	if(exec == NULL)
		return;

	/* must end with /exec or /stop */
	if((len = readlink("/proc/self/exe", exec, size)) < 5)
		goto fail;

	if(len >= size) {
		free(exec);
		size *= 2;
		goto grow;
	}

	/* verify exec/stop */
	*(stop = exec + len) = 0;
	if(stop[-5] == '/') {
		if(strcmp(stop -= 4, "stop") == 0) {
			memcpy(stop, "exec", 4);

			if(kill_by_exec(SIGKILL, exec, NULL)) {
				free(exec);

				_stop();
				return;
			}
		} else if(strcmp(stop, "exec") == 0) {
			memcpy(stop, "stop", 4);

			if(kill_by_exec(0, exec, NULL))
				exit(EXIT_FAILURE);
		}
	}

fail:	free(exec);
}
