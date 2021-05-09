all: exec

include ../../make.conf

exec.o: exec.c Makefile ../../make.conf

exec: exec.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $< -nostartfiles
	@$(STRIP) $@

install: all
	@mkdir -p $(ROOT)/etc/boot.d/kmod/bnx2
	install -m755 exec $(ROOT)/etc/boot.d/kmod/bnx2/exec

clean:
	rm -f exec{,.o}

uninstall:
	rm -f $(ROOT)/etc/boot.d/kmod/bnx2/exec
	rmdir $(ROOT)/etc/boot.d/kmod/bnx2 2>/dev/null || true
