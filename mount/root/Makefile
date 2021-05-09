all: exec

include ../../make.conf

exec.o: exec.c ../../lib/hill.h Makefile ../../make.conf

exec: exec.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $< -L../../lib -lhill
	@$(STRIP) $@

install: all
	@mkdir -p $(ROOT)/etc/boot.d/mount/root
	install -m755 exec $(ROOT)/etc/boot.d/mount/root/exec

clean:
	rm -f exec{,.o}

uninstall:
	rm -f $(ROOT)/etc/boot.d/mount/root/exec
	rmdir $(ROOT)/etc/boot.d/mount/root 2>/dev/null || true
