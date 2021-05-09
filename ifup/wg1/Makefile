# Set routing table id (TID) and fwmark (FWM).
# Comment out if not needed on your box.
#CPPFLAGS += -DTID=1 -DFWM=1

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
	@$(CC) $(LDFLAGS) -o $@ $< -L../../lib -lstop
	@$(STRIP) $@

install: all want
	@mkdir -p $(ROOT)/etc/boot.d/ifup/wg1
	install -m755 exec $(ROOT)/etc/boot.d/ifup/wg1/exec
	install -m755 stop $(ROOT)/etc/boot.d/ifup/wg1/stop
	install -m644 want $(ROOT)/etc/boot.d/ifup/wg1/want

clean:
	rm -f {exec,stop}{,.o}

uninstall:
	rm -f $(ROOT)/etc/boot.d/ifup/wg1/{exec,stop,want}
	rmdir $(ROOT)/etc/boot.d/ifup/wg1 2>/dev/null || true
