all: exec stop

include ../make.conf

exec.o: exec.c Makefile ../make.conf
stop.o: stop.c Makefile ../make.conf

exec: exec.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $<
	@$(STRIP) $@

stop: stop.o
	@echo "  LD  $@"
	@$(CC) $(LDFLAGS) -o $@ $<
	@$(STRIP) $@

install: all need
	@mkdir -p $(ROOT)/etc/boot.d/time
	@echo "install -m755 exec/stop $(ROOT)/etc/boot.d/time"
	@grep -q ^CONFIG_RTC_CLASS $(KCONFIG) || install -m755 exec $(ROOT)/etc/boot.d/time/exec
	@! grep -q ^CONFIG_RTC_CLASS $(KCONFIG) || install -m755 stop $(ROOT)/etc/boot.d/time/stop
	install -m644 need $(ROOT)/etc/boot.d/time/need

clean:
	rm -f {exec,stop}{,.o}

uninstall:
	rm -f $(ROOT)/etc/boot.d/time/{exec,stop,need}
	rmdir $(ROOT)/etc/boot.d/time 2>/dev/null || true
