all: exec

include ../../make.conf

exec.o: exec.c Makefile ../../make.conf

exec: exec.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $< -lmnl
	@$(STRIP) $@

install: all
	@mkdir -p $(ROOT)/etc/boot.d/ipset/hash:ip
	install -m755 exec $(ROOT)/etc/boot.d/ipset/hash:ip/exec

clean:
	rm -f exec{,.o}

uninstall:
	rm -f $(ROOT)/etc/boot.d/ipset/hash:ip/exec
	rmdir $(ROOT)/etc/boot.d/ipset/hash:ip 2>/dev/null || true
