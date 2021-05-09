CPPFLAGS += -DTID=1

all: exec

include ../../make.conf

exec.o: exec.c ../../make.conf

exec: exec.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $< -lmnl
	@$(STRIP) $@

install: all
	@mkdir -p $(ROOT)/etc/boot.d/ifup/ethX
	install -m755 exec $(ROOT)/etc/boot.d/ifup/ethX/exec

clean:
	rm -f exec{,.o}

uninstall:
	rm -f $(ROOT)/etc/boot.d/ifup/ethX/exec
	rmdir $(ROOT)/etc/boot.d/ifup/ethX 2>/dev/null || true
