all:
	make -C 1
	make -C 2
	make -C 3
	make -C 4
	make -C 5
	make -C 6

install:
	make -C 1 install
	make -C 2 install
	make -C 3 install
	make -C 4 install
	make -C 5 install
	make -C 6 install

clean:
	make -C 1 clean
	make -C 2 clean
	make -C 3 clean
	make -C 4 clean
	make -C 5 clean
	make -C 6 clean

uninstall:
	make -C 1 uninstall
	make -C 2 uninstall
	make -C 3 uninstall
	make -C 4 uninstall
	make -C 5 uninstall
	make -C 6 uninstall
	rmdir $(ROOT)/etc/boot.d/mingetty 2>/dev/null || true
