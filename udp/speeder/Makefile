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

install: all need
	@mkdir -p $(ROOT)/etc/boot.d/udp/speeder
	install -m755 exec $(ROOT)/etc/boot.d/udp/speeder/exec
	install -m755 stop $(ROOT)/etc/boot.d/udp/speeder/stop
	install -m644 need $(ROOT)/etc/boot.d/udp/speeder/need
	install -m644 want $(ROOT)/etc/boot.d/udp/speeder/want

clean:
	rm -f {exec,stop}{,.o}

uninstall:
	rm -f $(ROOT)/etc/boot.d/udp/speeder/{exec,need,stop,want}
	rmdir $(ROOT)/etc/boot.d/udp/speeder 2>/dev/null || true

