all:
	make -C lib
	make -C alsa
	make -C apache
	make -C bind
	make -C connman
	make -C dbus
	make -C dcron
	make -C ftpd
	make -C init
	make -C init/cli
	make -C init/gui
	make -C iptables
	make -C kmod
	make -C metalog
	make -C mingetty
	make -C mount
	make -C mysql
	make -C rsync
	make -C sshd
	make -C sysctl
	make -C time
	make -C tomcat
	make -C udev
	make -C udev/settle
	make -C udev/trigger
	make -C ux11

install:
	make -C lib install
	make -C alsa install
	make -C apache install
	make -C bind install
	make -C connman install
	make -C dbus install
	make -C dcron install
	make -C ftpd install
	make -C init install
	make -C init/cli install
	make -C init/gui install
	make -C iptables install
	make -C kmod install
	make -C metalog install
	make -C mingetty install
	make -C mount install
	make -C mysql install
	make -C rsync install
	make -C sshd install
	make -C sysctl install
	make -C time install
	make -C tomcat install
	make -C udev install
	make -C udev/settle install
	make -C udev/trigger install
	make -C ux11 install

clean:
	make -C alsa clean
	make -C apache clean
	make -C bind clean
	make -C connman clean
	make -C dbus clean
	make -C dcron clean
	make -C ftpd clean
	make -C init/cli clean
	make -C init/gui clean
	make -C init clean
	make -C iptables clean
	make -C kmod clean
	make -C metalog clean
	make -C mingetty clean
	make -C mount clean
	make -C mysql clean
	make -C rsync clean
	make -C sshd clean
	make -C sysctl clean
	make -C time clean
	make -C tomcat clean
	make -C udev/settle clean
	make -C udev/trigger clean
	make -C udev clean
	make -C ux11 clean
	make -C lib clean

uninstall:
	make -C alsa uninstall
	make -C apache uninstall
	make -C bind uninstall
	make -C connman uninstall
	make -C dbus uninstall
	make -C dcron uninstall
	make -C ftpd uninstall
	make -C init/gui uninstall
	make -C init/cli uninstall
	make -C init uninstall
	make -C iptables uninstall
	make -C kmod uninstall
	make -C metalog uninstall
	make -C mingetty uninstall
	make -C mount uninstall
	make -C mysql uninstall
	make -C rsync uninstall
	make -C sshd uninstall
	make -C sysctl uninstall
	make -C time uninstall
	make -C tomcat uninstall
	make -C udev/settle uninstall
	make -C udev/trigger uninstall
	make -C udev uninstall
	make -C ux11 uninstall
	make -C lib uninstall
	rmdir $(ROOT)/etc/boot.d 2>/dev/null || true
