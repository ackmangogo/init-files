all: exec stop

include ../make.conf

exec.o: exec.c Makefile ../make.conf
stop.o: stop.c ../lib/stop.h Makefile ../make.conf

exec: exec.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $< -nostartfiles
	@$(STRIP) $@

stop: stop.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $< -L../lib -lstop
	@$(STRIP) $@

install: all need want
	@mkdir -p $(ROOT)/etc/boot.d/ftpd
	install -m755 exec $(ROOT)/etc/boot.d/ftpd/exec
	install -m755 stop $(ROOT)/etc/boot.d/ftpd/stop
	install -m644 need $(ROOT)/etc/boot.d/ftpd/need
	install -m644 want $(ROOT)/etc/boot.d/ftpd/want

clean:
	rm -f {exec,stop}{,.o}

uninstall:
	rm -f $(ROOT)/etc/boot.d/ftpd/{exec,need,stop,want}
	rmdir $(ROOT)/etc/boot.d/ftpd 2>/dev/null || true
