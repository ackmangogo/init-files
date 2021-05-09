all: exec stop want

include ../make.conf

exec.o: exec.c Makefile ../make.conf
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
	@echo -n > $@
	@! grep -q ^CONFIG_UNIX=m $< || echo "kmod/unix" >>$@
	@echo "mount/run" >>$@
	@echo "time" >>$@

install: all need
	@mkdir -p $(ROOT)/etc/boot.d/metalog
	install -m755 exec $(ROOT)/etc/boot.d/metalog/exec
	install -m755 stop $(ROOT)/etc/boot.d/metalog/stop
	install -m644 need $(ROOT)/etc/boot.d/metalog/need
	install -m644 want $(ROOT)/etc/boot.d/metalog/want

clean:
	rm -f {exec,stop}{,.o} want

uninstall:
	rm -f $(ROOT)/etc/boot.d/metalog/{exec,need,stop,want}
	rmdir $(ROOT)/etc/boot.d/metalog 2>/dev/null || true
