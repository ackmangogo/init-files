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

install: all want
	@mkdir -p $(ROOT)/etc/boot.d/tomcat
	install -m755 exec $(ROOT)/etc/boot.d/tomcat/exec
	install -m755 stop $(ROOT)/etc/boot.d/tomcat/stop
	install -m644 want $(ROOT)/etc/boot.d/tomcat/want

clean:
	rm -f {exec,stop}{,.o}

uninstall:
	rm -f $(ROOT)/etc/boot.d/tomcat/{exec,stop,want}
	rmdir $(ROOT)/etc/boot.d/tomcat 2>/dev/null || true
