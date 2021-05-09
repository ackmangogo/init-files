all:
	make -C cluster
	make -C proxy
	make -C server

install:
	make -C cluster install
	make -C proxy install
	make -C server install

clean:
	make -C cluster clean
	make -C proxy clean
	make -C server clean

uninstall:
	make -C cluster uninstall
	make -C proxy uninstall
	make -C server uninstall
	rmdir $(ROOT)/etc/boot.d/mysql 2>/dev/null || true
