all:
	make -C mgmd
	make -C ndbd

install:
	make -C mgmd install
	make -C ndbd install

clean:
	make -C mgmd clean
	make -C ndbd clean

uninstall:
	make -C mgmd uninstall
	make -C ndbd uninstall
	rmdir $(ROOT)/etc/boot.d/mysql/cluster 2>/dev/null || true
