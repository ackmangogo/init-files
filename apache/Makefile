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
	@mkdir -p $(ROOT)/etc/boot.d/apache
	install -m755 exec $(ROOT)/etc/boot.d/apache/exec
	install -m755 stop $(ROOT)/etc/boot.d/apache/stop
	install -m644 need $(ROOT)/etc/boot.d/apache/need
	install -m644 want $(ROOT)/etc/boot.d/apache/want

clean:
	rm -f {exec,stop}{,.o}

uninstall:
	rm -f $(ROOT)/etc/boot.d/apache/{exec,stop,need,want}
	rmdir $(ROOT)/etc/boot.d/apache 2>/dev/null || true
