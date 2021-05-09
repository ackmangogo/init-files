all: stop

include ../make.conf

stop.o: stop.c Makefile ../make.conf

stop: stop.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $< -nostartfiles
	@$(STRIP) $@

install: all need
	@mkdir -p $(ROOT)/etc/boot.d/alsa
	install -m755 stop $(ROOT)/etc/boot.d/alsa/stop
	install -m644 need $(ROOT)/etc/boot.d/alsa/need

clean:
	rm -f stop{,.o}

uninstall:
	rm -f $(ROOT)/etc/boot.d/alsa/stop
	rmdir $(ROOT)/etc/boot.d/alsa 2>/dev/null || true
