all:

install: need want
	@mkdir -p $(ROOT)/etc/boot.d/init/gui
	install -m644 need $(ROOT)/etc/boot.d/init/gui/need
	install -m644 want $(ROOT)/etc/boot.d/init/gui/want

clean:

uninstall:
	rm -f $(ROOT)/etc/boot.d/init/gui/{need,want}
	rmdir $(ROOT)/etc/boot.d/init/gui 2>/dev/null || true
