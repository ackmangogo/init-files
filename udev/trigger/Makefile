all: exec

include ../../make.conf

exec.o: exec.c Makefile ../../make.conf

exec: exec.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $<
	@$(STRIP) $@

clean:
	rm -f exec{,.o}

install: all need
	@mkdir -p $(ROOT)/etc/boot.d/udev/trigger
	install -m755 exec $(ROOT)/etc/boot.d/udev/trigger/exec
	install -m644 need $(ROOT)/etc/boot.d/udev/trigger/need

uninstall:
	rm -f $(ROOT)/etc/boot.d/udev/trigger/{exec,need}
	rmdir $(ROOT)/etc/boot.d/udev/trigger 2>/dev/null || true
