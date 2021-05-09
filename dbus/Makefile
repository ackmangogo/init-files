all: exec stop

include ../make.conf

exec.o: exec.c Makefile ../make.conf
stop.o: stop.c ../lib/stop.h Makefile ../make.conf

exec: exec.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $<
	@$(STRIP) $@

stop: stop.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $< -L../lib -lstop
	@$(STRIP) $@

install: all need want
	@mkdir -p $(ROOT)/etc/boot.d/dbus
	install -m755 exec $(ROOT)/etc/boot.d/dbus/exec
	install -m755 stop $(ROOT)/etc/boot.d/dbus/stop
	install -m644 need $(ROOT)/etc/boot.d/dbus/need
	install -m644 want $(ROOT)/etc/boot.d/dbus/want

clean:
	rm -f {exec,stop}{,.o}

uninstall:
	rm -f $(ROOT)/etc/boot.d/dbus/{exec,need,stop,want}
	rmdir $(ROOT)/etc/boot.d/dbus 2>/dev/null || true
