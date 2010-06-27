configdir = $(sysconfdir)/xdg/@PACKAGE@
config_DATA = bashrun.rc 

plugindir = $(configdir)/plugins
plugin_DATA = plugins/terminal.rc

completiondir = $(sysconfdir)/bash_completion.d
completion_DATA = bash_completion.d/bashrun

install-data-hook : 
	$(SED) -i 's|__TERMINAL__|@ac_with_terminal@|g' $(DESTDIR)$(configdir)/bashrun.rc
	$(SED) -i 's|__TERMINAL__|@ac_with_terminal@|g' $(DESTDIR)$(configdir)/plugins/terminal.rc

	$(SED) -i 's|__EXEC_TERMINAL__|@ac_with_exec_terminal@|g' $(DESTDIR)$(configdir)/bashrun.rc
