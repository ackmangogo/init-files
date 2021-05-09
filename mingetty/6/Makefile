all: keep

include ../../make.conf

keep.o: keep.c Makefile ../../make.conf

keep: keep.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $< -nostartfiles
	@$(STRIP) $@

install: all ../need ../want
	@mkdir -p $(ROOT)/etc/boot.d/mingetty/6
	install -m755 keep $(ROOT)/etc/boot.d/mingetty/6/keep
	ln -sf keep $(ROOT)/etc/boot.d/mingetty/6/exec
	install -m644 ../need $(ROOT)/etc/boot.d/mingetty/6/need
	install -m644 ../want $(ROOT)/etc/boot.d/mingetty/6/want

clean:
	rm -f keep{,.o}

uninstall:
	rm -f $(ROOT)/etc/boot.d/mingetty/6/{exec,keep,need,want}
	rmdir $(ROOT)/etc/boot.d/mingetty/6 2>/dev/null || true
