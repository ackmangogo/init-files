all: exec

include ../../make.conf

exec.o: exec.c ../../make.conf

exec: exec.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $< -nostartfiles
	@$(STRIP) $@

install: all
	@mkdir -p $(ROOT)/etc/boot.d/ifup/eth0
	install -m755 exec $(ROOT)/etc/boot.d/ifup/eth0/exec

clean:
	rm -f exec{,.o}

uninstall:
	rm -f $(ROOT)/etc/boot.d/ifup/eth0/exec
	rmdir $(ROOT)/etc/boot.d/ifup/eth0 2>/dev/null || true
