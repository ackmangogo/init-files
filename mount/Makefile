all:
	make -C dev
	make -C home
	make -C proc
	make -C root
	make -C run
	make -C sys

install:
	make -C dev install
	make -C home install
	make -C proc install
	make -C root install
	make -C run install
	make -C sys install

clean:
	make -C dev clean
	make -C home clean
	make -C proc clean
	make -C root clean
	make -C run clean
	make -C sys clean

uninstall:
	make -C dev uninstall
	make -C home uninstall
	make -C proc uninstall
	make -C root uninstall
	make -C run uninstall
	make -C sys uninstall
	rmdir $(ROOT)/etc/boot.d/mount 2>/dev/null || true
