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
	@mkdir -p $(ROOT)/etc/boot.d/v2ray
	install -m755 exec $(ROOT)/etc/boot.d/v2ray/exec
	install -m755 stop $(ROOT)/etc/boot.d/v2ray/stop
	install -m644 want $(ROOT)/etc/boot.d/v2ray/want

clean:
	rm -f {exec,stop}{,.o}

uninstall:
	rm -f $(ROOT)/etc/boot.d/v2ray/{exec,stop,want}
	rmdir $(ROOT)/etc/boot.d/v2ray 2>/dev/null || true

