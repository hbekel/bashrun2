configdir = $(sysconfdir)/xdg/@PACKAGE@
config_DATA = bashrun2.rc 

plugindir = $(configdir)/plugins
plugin_DATA = plugins/terminal.rc

completiondir = $(sysconfdir)/bash_completion.d
completion_DATA = bash_completion.d/bashrun2

install-data-hook : 
	$(SED) -i 's|__TERMINAL__|@ac_with_terminal@|g' $(DESTDIR)$(configdir)/bashrun2.rc
	$(SED) -i 's|__TERMINAL__|@ac_with_terminal@|g' $(DESTDIR)$(configdir)/plugins/terminal.rc

	$(SED) -i 's|__EXEC_TERMINAL__|@ac_with_exec_terminal@|g' $(DESTDIR)$(configdir)/bashrun2.rc
