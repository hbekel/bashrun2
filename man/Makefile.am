man_MANS = bashrun2.1

install-data-hook : 
	$(SED) -i 's|__PREFIX__|@prefix@|g' $(DESTDIR)$(man1dir)/bashrun2.1
	$(SED) -i 's|__SYSCONFDIR__|@sysconfdir@|g' $(DESTDIR)$(man1dir)/bashrun2.1
	$(SED) -i 's|__TERMINAL__|@ac_with_terminal@|g' $(DESTDIR)$(man1dir)/bashrun2.1
	$(SED) -i 's|__EXEC_TERMINAL__|@ac_with_exec_terminal@|g' $(DESTDIR)$(man1dir)/bashrun2.1
	$(SED) -i 's|__TERMINAL_NAME__|@ac_with_terminal_name@|g' $(DESTDIR)$(man1dir)/bashrun2.1
