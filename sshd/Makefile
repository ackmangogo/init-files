all: keep stop

include ../make.conf

keep.o: keep.c Makefile ../make.conf
stop.o: stop.c ../lib/stop.h Makefile ../make.conf

keep: keep.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $< -nostartfiles
	@$(STRIP) $@

stop: stop.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $< -L../lib -lstop
	@$(STRIP) $@

install: all need want
	@mkdir -p $(ROOT)/etc/boot.d/sshd
	install -m755 keep $(ROOT)/etc/boot.d/sshd/keep
	ln -sf keep $(ROOT)/etc/boot.d/sshd/exec
	install -m755 stop $(ROOT)/etc/boot.d/sshd/stop
	cp -n need $(ROOT)/etc/boot.d/sshd/need
	cp -n want $(ROOT)/etc/boot.d/sshd/want

clean:
	rm -f {keep,stop}{,.o}

uninstall:
	rm -f $(ROOT)/etc/boot.d/sshd/{exec,keep,need,stop,want}
	rmdir $(ROOT)/etc/boot.d/sshd 2>/dev/null || true

