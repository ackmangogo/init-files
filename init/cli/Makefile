all: want

include ../../make.conf

want: $(KCONFIG) Makefile ../../make.conf
	@echo " GEN  $@"
	@echo -n >$@
	@! grep -q ^CONFIG_FRAMEBUFFER_CONSOLE=m $< || echo "kmod/fbcon" >>$@
	@echo "mingetty/1" >>$@
	@echo "mingetty/2" >>$@
	@echo "mingetty/3" >>$@
	@echo "mingetty/4" >>$@
	@echo "mingetty/5" >>$@
	@echo "mingetty/6" >>$@

install: all need
	@mkdir -p $(ROOT)/etc/boot.d/init/cli
	install -m644 need $(ROOT)/etc/boot.d/init/cli/need
	install -m644 want $(ROOT)/etc/boot.d/init/cli/want

clean:
	rm -f want

uninstall:
	rm -f $(ROOT)/etc/boot.d/init/cli/{need,want}
	rmdir $(ROOT)/etc/boot.d/init/cli 2>/dev/null || true
