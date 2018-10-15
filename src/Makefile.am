bin_PROGRAMS = brwctl
brwctl_SOURCES = brwctl.c

AM_CFLAGS = -Wall $(CFLAGS) -I/usr/local/include
AM_LDFLAGS = $(LDFLAGS) -L/usr/local/lib

bin_SCRIPTS = bashrun2

sitedir = $(datadir)/@PACKAGE@
site_DATA = actions bashrc bindings bookmarks bootstrap command completion config core engine frontend globals handlers interface message modes object objects plugin progress readline registry remote rules templates terminals utils window xdgbase

install-exec-hook : 
	$(SED) -E -i.bak 's|__PREFIX__|@prefix@|g' $(DESTDIR)$(bindir)/bashrun2
	rm $(DESTDIR)$(bindir)/*.bak

install-data-hook : 
	$(SED) -E -i.bak 's|__PREFIX__|@prefix@|g' $(DESTDIR)$(sitedir)/frontend
	$(SED) -E -i.bak 's|__PREFIX__|@prefix@|g' $(DESTDIR)$(sitedir)/bashrc
	$(SED) -E -i.bak 's|__PREFIX__|@prefix@|g' $(DESTDIR)$(sitedir)/globals

	$(SED) -E -i.bak 's|__TERMINAL__|@ac_with_terminal@|g' $(DESTDIR)$(sitedir)/core
	$(SED) -E -i.bak 's|__TERMINAL__|@ac_with_terminal@|g' $(DESTDIR)$(sitedir)/modes
	$(SED) -E -i.bak 's|__TERMINAL__|@ac_with_terminal@|g' $(DESTDIR)$(sitedir)/utils

	$(SED) -E -i.bak 's|__EXEC_TERMINAL__|@ac_with_exec_terminal@|g' $(DESTDIR)$(sitedir)/core
	$(SED) -E -i.bak 's|__EXEC_TERMINAL__|@ac_with_exec_terminal@|g' $(DESTDIR)$(sitedir)/terminals
	$(SED) -E -i.bak 's|__EXEC_TERMINAL__|@ac_with_exec_terminal@|g' $(DESTDIR)$(sitedir)/utils
	rm $(DESTDIR)$(sitedir)/*.bak

uninstall-hook :
	-rmdir $(DESTDIR)$(sitedir)
