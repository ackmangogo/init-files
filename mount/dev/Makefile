all: exec stop

include ../../make.conf

conf.h: $(KCONFIG) Makefile ../../make.conf
	@echo " GEN  $@"
	@echo "/* Generated automatically, do not edit! */" >$@
	@! grep -q ^CONFIG_DEVTMPFS=y $< || echo "#define CONFIG_DEVTMPFS" >>$@
	@! grep -q ^CONFIG_SHMEM=y $< || echo "#define CONFIG_SHMEM" >>$@
	@! grep -q ^CONFIG_UNIX98_PTYS=y $< || echo "#define CONFIG_UNIX98_PTYS" >>$@

exec.o: exec.c conf.h ../../lib/hill.h
stop.o: stop.c Makefile ../../make.conf

exec: exec.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $< -L../../lib -lhill
	@$(STRIP) $@

stop: stop.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $< -L../../lib -lstop
	@$(STRIP) $@

install: all
	@mkdir -p $(ROOT)/etc/boot.d/mount/dev
	install -m755 exec $(ROOT)/etc/boot.d/mount/dev/exec
	install -m755 stop $(ROOT)/etc/boot.d/mount/dev/stop

clean:
	rm -f {exec,stop}{,.o} conf.h

uninstall:
	rm -f $(ROOT)/etc/boot.d/mount/dev/{exec,stop}
	rmdir $(ROOT)/etc/boot.d/mount/dev 2>/dev/null || true
