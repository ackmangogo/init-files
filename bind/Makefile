all:
	make -C 127.0.0.1
	make -C eth0
	make -C localhost
	make -C wlan0

install:
	make -C 127.0.0.1 install
	make -C eth0 install
	make -C localhost install
	make -C wlan0 install

clean:
	make -C 127.0.0.1 clean
	make -C eth0 clean
	make -C localhost clean
	make -C wlan0 clean

uninstall:
	make -C 127.0.0.1 uninstall
	make -C eth0 uninstall
	make -C localhost uninstall
	make -C wlan0 uninstall
	rmdir $(ROOT)/etc/boot.d/bind 2>/dev/null || true
