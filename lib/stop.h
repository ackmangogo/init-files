/*
 * stop.h: Minimalistic stop helper
 * Copyright 2012 Herbert Waldegger
 */

#ifndef __STOP_H
#define __STOP_H

#include <signal.h>

#define stop(pidf, exec, ...) (( \
	((pidf) && kill_by_pidf(SIGTERM, (pidf))) || \
	((exec) && kill_by_exec(SIGTERM, (exec), __VA_ARGS__)))?EXIT_SUCCESS:EXIT_FAILURE)

pid_t kill_by_exec(int sig, const char *exec, ...);
pid_t kill_by_pidf(int sig, const char *pidf);

#endif /* __STOP_H */
