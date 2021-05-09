all:

install: need want
	@mkdir -p $(ROOT)/etc/boot.d/init
	install -m644 need $(ROOT)/etc/boot.d/init/need
	install -m644 want $(ROOT)/etc/boot.d/init/want

clean:

uninstall:
	rm -f $(ROOT)/etc/boot.d/init/{need,want}
	rmdir $(ROOT)/etc/boot.d/init 2>/dev/null || true
