all: exec keep

include ../../make.conf

exec.o: exec.c Makefile ../../make.conf
keep.o: keep.c Makefile ../../make.conf

exec: exec.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $< -nostartfiles
	@$(STRIP) $@

keep: keep.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $< -nostartfiles
	@$(STRIP) $@

install: all ../need ../want
	@mkdir -p $(ROOT)/etc/boot.d/mingetty/1
	install -m755 exec $(ROOT)/etc/boot.d/mingetty/1/exec
	install -m755 keep $(ROOT)/etc/boot.d/mingetty/1/keep
	install -m644 ../need $(ROOT)/etc/boot.d/mingetty/1/need
	install -m644 ../want $(ROOT)/etc/boot.d/mingetty/1/want

clean:
	rm -f {exec,keep}{,.o}

uninstall:
	rm -f $(ROOT)/etc/boot.d/mingetty/1/{exec,keep,need,want}
	rmdir $(ROOT)/etc/boot.d/mingetty/1 2>/dev/null || true
