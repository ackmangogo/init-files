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
	@mkdir -p $(ROOT)/etc/boot.d/dnscrypt-proxy
	install -m755 exec $(ROOT)/etc/boot.d/dnscrypt-proxy/exec
	install -m755 stop $(ROOT)/etc/boot.d/dnscrypt-proxy/stop
	install -m644 want $(ROOT)/etc/boot.d/dnscrypt-proxy/want

clean:
	rm -f {exec,stop}{,.o}

uninstall:
	rm -f $(ROOT)/etc/boot.d/dnscrypt-proxy/{exec,stop,want}
	rmdir $(ROOT)/etc/boot.d/dnscrypt-proxy 2>/dev/null || true

