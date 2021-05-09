all: keep

include ../../make.conf

keep.o: keep.c Makefile ../../make.conf

keep: keep.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $< -nostartfiles
	@$(STRIP) $@

install: all ../need ../want
	@mkdir -p $(ROOT)/etc/boot.d/mingetty/2
	install -m755 keep $(ROOT)/etc/boot.d/mingetty/2/keep
	ln -sf keep $(ROOT)/etc/boot.d/mingetty/2/exec
	install -m644 ../need $(ROOT)/etc/boot.d/mingetty/2/need
	install -m644 ../want $(ROOT)/etc/boot.d/mingetty/2/want

clean:
	rm -f keep{,.o}

uninstall:
	rm -f $(ROOT)/etc/boot.d/mingetty/2/{exec,keep,need,want}
	rmdir $(ROOT)/etc/boot.d/mingetty/2 2>/dev/null || true
