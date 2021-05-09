all: exec stop want

include ../make.conf

conf.h: $(KCONFIG) Makefile ../make.conf
	@echo " GEN  $@"
	@echo "/* Generated automatically, do not edit! */" >$@
	@! grep -q ^CONFIG_UEVENT_HELPER=y $< || echo "#define CONFIG_UEVENT_HELPER" >> $@

exec.o: exec.c conf.h
stop.o: stop.c ../lib/stop.h Makefile ../make.conf

exec: exec.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $< -nostartfiles
	@$(STRIP) $@

stop: stop.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $< -L../lib -lstop
	@$(STRIP) $@

want: $(KCONFIG) Makefile ../make.conf
	@echo " GEN  $@"
	@echo -n >$@
	@! grep -q ^CONFIG_UNIX=m $< || echo "kmod/unix" >>$@

install: all need
	@mkdir -p $(ROOT)/etc/boot.d/udev
	install -m755 exec $(ROOT)/etc/boot.d/udev/exec
	install -m755 stop $(ROOT)/etc/boot.d/udev/stop
	install -m644 need $(ROOT)/etc/boot.d/udev/need
	@rm -f $(ROOT)/etc/boot.d/udev/want
	@echo "refresh -m644 want $(ROOT)/etc/boot.d/udev/want"
	@! test -s want || install -m644 want $(ROOT)/etc/boot.d/udev/want

clean:
	rm -f conf.h {exec,stop}{,.o} want

uninstall:
	rm -f $(ROOT)/etc/boot.d/udev/{exec,stop,need,want}
	rmdir $(ROOT)/etc/boot.d/udev 2>/dev/null || true
