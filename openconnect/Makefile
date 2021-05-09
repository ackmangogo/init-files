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

install: all want
	@mkdir -p $(ROOT)/etc/boot.d/openconnect
	install -m755 exec $(ROOT)/etc/boot.d/openconnect/exec
	install -m755 stop $(ROOT)/etc/boot.d/openconnect/stop
	install -m644 want $(ROOT)/etc/boot.d/openconnect/want

clean:
	rm -f {exec,stop}{,.o}

uninstall:
	rm -f $(ROOT)/etc/boot.d/openconnect/{exec,stop,want}
	rmdir $(ROOT)/etc/boot.d/openconnect 2>/dev/null || true

