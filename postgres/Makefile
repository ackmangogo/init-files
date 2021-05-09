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
	@$(CC) $(LDFLAGS) -o $@ $<
	@$(STRIP) $@

install: all need want
	@mkdir -p $(ROOT)/etc/boot.d/postgres
	install -m755 exec $(ROOT)/etc/boot.d/postgres/exec
	install -m755 stop $(ROOT)/etc/boot.d/postgres/stop
	install -m644 need $(ROOT)/etc/boot.d/postgres/need
	install -m644 want $(ROOT)/etc/boot.d/postgres/want

clean:
	rm -f {exec,stop}{,.o}

uninstall:
	rm -f $(ROOT)/etc/boot.d/postgres/{exec,stop,need,want}
	rmdir $(ROOT)/etc/boot.d/postgres 2>/dev/null || true
