all: exec

include ../make.conf

exec.o: exec.c Makefile ../make.conf

exec: exec.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $<
	@$(STRIP) $@

install: all need
	@mkdir -p $(ROOT)/etc/boot.d/default
	install -m755 exec $(ROOT)/etc/boot.d/default/exec
	cp -n need $(ROOT)/etc/boot.d/default/need

clean:
	rm -f exec{,.o}

uninstall:
	rm -f $(ROOT)/etc/boot.d/default/exec
	rmdir $(ROOT)/etc/boot.d/default 2>/dev/null || true
