all: keep want

include ../make.conf

keep.o: keep.c Makefile ../make.conf

keep: keep.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $< -nostartfiles
	@$(STRIP) $@

want: $(KCONFIG) Makefile ../make.conf
	@echo " GEN  $@"
	@echo "dbus" >$@
	@! grep -q ^CONFIG_UNIX=m $< || echo "kmod/unix" >>$@
	@echo "#kmod/video" >>$@
	@echo "mount/run" >>$@
	@echo "sysctl" >>$@

install: all need
	@mkdir -p $(ROOT)/etc/boot.d/ux11
	install -m755 keep $(ROOT)/etc/boot.d/ux11/keep
	ln -sf keep $(ROOT)/etc/boot.d/ux11/exec
	install -m644 need $(ROOT)/etc/boot.d/ux11/need
	install -m644 want $(ROOT)/etc/boot.d/ux11/want

clean:
	rm -f keep{,.o} want

uninstall:
	rm -f $(ROOT)/etc/boot.d/ux11/{exec,keep,need,want}
	rmdir $(ROOT)/etc/boot.d/ux11 2>/dev/null || true
