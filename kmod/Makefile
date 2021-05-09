all:
	make -C evdev
	make -C fbcon
	make -C i915
	make -C rfkill
	make -C tg3
	make -C unix

install:
	make -C evdev install
	make -C fbcon install
	make -C i915 install
	make -C rfkill install
	make -C tg3 install
	make -C unix install

clean:
	make -C evdev clean
	make -C fbcon clean
	make -C i915 clean
	make -C rfkill clean
	make -C tg3 clean
	make -C unix clean

uninstall:
	make -C evdev uninstall
	make -C fbcon uninstall
	make -C i915 uninstall
	make -C rfkill uninstall
	make -C tg3 uninstall
	make -C unix uninstall
	rmdir $(ROOT)/etc/boot.d/kmod 2>/dev/null || true
