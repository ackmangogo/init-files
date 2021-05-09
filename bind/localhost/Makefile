all: exec stop

include ../../make.conf

exec.o: exec.c Makefile ../../make.conf
stop.o: stop.c Makefile ../../make.conf

exec: exec.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $< -lmnl
	@$(STRIP) $@

stop: stop.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $< -L../../lib -lstop
	@$(STRIP) $@

install: all need want
	@mkdir -p $(ROOT)/etc/boot.d/bind/localhost
	install -m755 exec $(ROOT)/etc/boot.d/bind/localhost/exec
	install -m755 stop $(ROOT)/etc/boot.d/bind/localhost/stop
	install -m644 need $(ROOT)/etc/boot.d/bind/localhost/need
	install -m644 want $(ROOT)/etc/boot.d/bind/localhost/want

clean:
	rm -f {exec,stop}{,.o}

uninstall:
	rm -f $(ROOT)/etc/boot.d/bind/localhost/{exec,stop,need,want}
	rmdir $(ROOT)/etc/boot.d/bind/localhost 2>/dev/null || true
