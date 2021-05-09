all: exec stop

include ../make.conf

exec.o: exec.c Makefile ../make.conf
stop.o: stop.c Makefile ../make.conf

exec: exec.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $<
	@$(STRIP) $@

stop: stop.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $< -L../lib -lstop
	@$(STRIP) $@

install: all need want
	@mkdir -p $(ROOT)/etc/boot.d/netdata
	install -m755 exec $(ROOT)/etc/boot.d/netdata/exec
	install -m755 stop $(ROOT)/etc/boot.d/netdata/stop
	install -m644 need $(ROOT)/etc/boot.d/netdata/need
	install -m644 want $(ROOT)/etc/boot.d/netdata/want

clean:
	rm -f {exec,stop}{,.o}

uninstall:
	rm -f $(ROOT)/etc/boot.d/netdata/{exec,stop,need,want}
	rmdir $(ROOT)/etc/boot.d/netdata 2>/dev/null || true
