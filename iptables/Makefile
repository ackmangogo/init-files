all: exec

include ../make.conf

exec.o: exec.c Makefile ../make.conf

exec: exec.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $< -nostartfiles
	@$(STRIP) $@

install: all need
	@mkdir -p $(ROOT)/etc/boot.d/iptables
	install -m755 exec $(ROOT)/etc/boot.d/iptables/exec
	install -m644 need $(ROOT)/etc/boot.d/iptables/need

clean:
	rm -f exec{,.o}

uninstall:
	rm -f $(ROOT)/etc/boot.d/iptables/{exec,need}
	rmdir $(ROOT)/etc/boot.d/iptables 2>/dev/null || true
