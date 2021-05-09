all: exec stop

include ../../make.conf

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

clean:
	rm -f {exec,stop}{,.o}

install: all need
	@mkdir -p $(ROOT)/etc/boot.d/udev/settle
	install -m755 exec $(ROOT)/etc/boot.d/udev/settle/exec
	install -m755 stop $(ROOT)/etc/boot.d/udev/settle/stop
	install -m644 need $(ROOT)/etc/boot.d/udev/settle/need

uninstall:
	rm -f $(ROOT)/etc/boot.d/udev/settle/{exec,stop,need}
	rmdir $(ROOT)/etc/boot.d/udev/settle 2>/dev/null || true
