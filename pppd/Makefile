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
	@mkdir -p $(ROOT)/etc/boot.d/pppd
	install -m755 exec $(ROOT)/etc/boot.d/pppd/exec
	install -m755 stop $(ROOT)/etc/boot.d/pppd/stop
	install -m644 need $(ROOT)/etc/boot.d/pppd/need
	install -m644 want $(ROOT)/etc/boot.d/pppd/want

clean:
	rm -f {exec,stop}{,.o}

uninstall:
	rm -f $(ROOT)/etc/boot.d/pppd/{exec,need,stop,want}
	rmdir $(ROOT)/etc/boot.d/pppd 2>/dev/null || true

