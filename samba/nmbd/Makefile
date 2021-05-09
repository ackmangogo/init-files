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
	@$(CC) $(LDFLAGS) -o $@ $< -L../lib -lstop
	@$(STRIP) $@

install: all need
	@mkdir -p $(ROOT)/etc/boot.d/samba/nmbd
	install -m755 exec $(ROOT)/etc/boot.d/samba/nmbd/exec
	install -m755 stop $(ROOT)/etc/boot.d/samba/nmbd/stop
	install -m644 need $(ROOT)/etc/boot.d/samba/nmbd/need

clean:
	rm -f {exec,stop}{,.o}

uninstall:
	rm -f $(ROOT)/etc/boot.d/samba/nmbd/{exec,need,stop}
	rmdir $(ROOT)/etc/boot.d/samba/nmbd 2>/dev/null || true
