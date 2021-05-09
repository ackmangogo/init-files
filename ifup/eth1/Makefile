all: exec

include ../../make.conf

exec.o: exec.c Makefile ../../make.conf

exec: exec.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $<
	@$(STRIP) $@

install: all want
	@mkdir -p $(ROOT)/etc/boot.d/ifup/eth1
	install -m755 exec $(ROOT)/etc/boot.d/ifup/eth1/exec
	install -m644 want $(ROOT)/etc/boot.d/ifup/eth1/want

clean:
	rm -f exec{,.o}

uninstall:
	rm -f $(ROOT)/etc/boot.d/ifup/eth1/{exec,want}
	rmdir $(ROOT)/etc/boot.d/ifup/eth1 2>/dev/null || true
