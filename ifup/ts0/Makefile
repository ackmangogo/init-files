# Set routing table id (TID) and fwmark (FWM).
# Comment out if not needed on your box.
CPPFLAGS += -DTID=1 -DFWM=1

all: exec stop

include ../../make.conf

LDFLAGS += -lmnl

exec.o: exec.c Makefile ../../make.conf
stop.o: stop.c ../../lib/stop.h Makefile ../../make.conf

exec: exec.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $<
	@$(STRIP) $@

stop: stop.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $<
	@$(STRIP) $@

install: all need want
	@mkdir -p $(ROOT)/etc/boot.d/ifup/ts0
	install -m755 exec $(ROOT)/etc/boot.d/ifup/ts0/exec
	ln -sf exec $(ROOT)/etc/boot.d/ifup/ts0/keep
	install -m755 stop $(ROOT)/etc/boot.d/ifup/ts0/stop
	install -m644 need $(ROOT)/etc/boot.d/ifup/ts0/need
	install -m644 want $(ROOT)/etc/boot.d/ifup/ts0/want

clean:
	rm -f {exec,stop}{,.o}

uninstall:
	rm -f $(ROOT)/etc/boot.d/ifup/ts0/{exec,keep,stop,need,want}
	rmdir --ignore-fail-on-non-empty $(ROOT)/etc/boot.d/ifup/ts0
