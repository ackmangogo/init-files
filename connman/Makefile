CONNMAN := /usr/lib/pkgconfig/connman.pc

all: exec stop want

include ../make.conf

conf.h: $(CONNMAN) Makefile
	@echo " GEN  $@"
	@echo "/* Generated automatically, do not edit! */" >$@
	@echo "#define LOOPBACK" >>$@
	@! pkg-config connman --atleast-version=1.31 || echo "#define CONNMAN_1_31" >>$@

exec.o: exec.c conf.h ../make.conf
stop.o: stop.c ../lib/stop.h Makefile ../make.conf

exec: exec.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $< -nostartfiles
	@$(STRIP) $@

stop: stop.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $< -L../lib -lstop
	@$(STRIP) $@

want: $(KCONFIG) Makefile ../make.conf
	@echo " GEN  $@"
	@echo -n >$@
	@! grep -q ^CONFIG_NETFILTER=y $< || echo "iptables" >$@
	@! grep -q ^CONFIG_RFKILL=m $< || echo "kmod/rfkill" >>$@

install: all need
	@mkdir -p $(ROOT)/etc/boot.d/connman
	install -m755 exec $(ROOT)/etc/boot.d/connman/exec
	install -m755 stop $(ROOT)/etc/boot.d/connman/stop
	install -m644 need $(ROOT)/etc/boot.d/connman/need
	@rm -f $(ROOT)/etc/boot.d/connman/want
	@echo "refresh -m644 want $(ROOT)/etc/boot.d/connman/want"
	@! test -s want || install -m644 want $(ROOT)/etc/boot.d/connman/want

clean:
	rm -f conf.h {exec,stop}{,.o} want

uninstall:
	rm -f $(ROOT)/etc/boot.d/connman/{exec,need,stop,want}
	rmdir $(ROOT)/etc/boot.d/connman 2>/dev/null || true
