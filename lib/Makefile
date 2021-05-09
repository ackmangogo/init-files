all: libhill.so libstop.so

include ../make.conf

CFLAGS += -fPIC

GPERF := gperf -tLANSI-C

libhill.o: libhill.c hill.h mntopts.h mntdata.h Makefile ../make.conf
libstop.o: libstop.c stop.h Makefile ../make.conf

gperf.mntopts.o: gperf.mntopts.c mntopts.h Makefile ../make.conf
mntopts.o: mntopts.c mntopts.h
mntdata.o: mntdata.c mntdata.h Makefile ../make.conf

gperf.mntopts: gperf.mntopts.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $^
	@$(STRIP) $@

mntopts.gperf: gperf.mntopts
	@echo " GEN  $@"
	@./gperf.mntopts >$@

mntopts.c: mntopts.gperf
	@echo " GEN  $@"
	@$(GPERF) $< >$@

mntdata.c: mntdata.gperf
	@echo " GEN  $@"
	@$(GPERF) $< >$@

libhill.so: libhill.o mntopts.o mntdata.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $^ -shared
	@$(STRIP) $@

libstop.so: libstop.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $< -shared -Wl,-init,_bury
	@$(STRIP) $@

install: all init.conf
	@mkdir -p $(ROOT)/etc/boot.d/lib
	install -m755 libhill.so $(ROOT)/lib/libhill.so
	install -m755 libstop.so $(ROOT)/lib/libstop.so
	@mkdir -p $(ROOT)/etc/prelink.conf.d
	install -m644 init.conf $(ROOT)/etc/prelink.conf.d/init.conf

clean:
	rm -f lib{hill,stop}.{o,so} mntopts.{c,gperf,o} gperf.mntopts{,.o} mntdata.{c,o}

uninstall:
	rm -f $(ROOT)/lib/lib{hill,stop}.so
	rm -f $(ROOT)/etc/prelink.conf.d/init.conf
	rmdir $(ROOT)/etc/prelink.conf.d 2>/dev/null || true
