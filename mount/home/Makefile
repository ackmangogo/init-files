all: exec

include ../../make.conf

exec.o: exec.c ../../lib/hill.h Makefile ../../make.conf

exec: exec.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $< -L../../lib -lhill
	@$(STRIP) $@

install: all
	mkdir -p $(ROOT)/etc/boot.d/mount/home
	install -m755 exec $(ROOT)/etc/boot.d/mount/home/exec
	install -m644 need $(ROOT)/etc/boot.d/mount/home/need

clean:
	rm -f exec{,.o}

uninstall:
	rm -f $(ROOT)/etc/boot.d/mount/home/{exec,need}
	rmdir $(ROOT)/etc/boot.d/mount/home 2>/dev/null || true
