all: exec

include ../../make.conf

exec.o: exec.c ../../lib/hill.h Makefile ../../make.conf

exec: exec.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $< -L../../lib -lhill
	@$(STRIP) $@

install: all want
	@mkdir -p $(ROOT)/etc/boot.d/mount/cgroup
	install -m755 exec $(ROOT)/etc/boot.d/mount/cgroup/exec
	cp -n want $(ROOT)/etc/boot.d/mount/cgroup/want

clean:
	rm -f exec{,.o}

uninstall:
	rm -f $(ROOT)/etc/boot.d/mount/cgroup/exec
	rmdir $(ROOT)/etc/boot.d/mount/cgroup 2>/dev/null || true
