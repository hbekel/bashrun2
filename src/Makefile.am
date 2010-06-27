bin_PROGRAMS = brwctl
brwctl_SOURCES = brwctl.c
AM_CFLAGS = -Wall

bin_SCRIPTS = bashrun

sitedir = $(datadir)/@PACKAGE@
site_DATA = actions bashrc bindings bookmarks bootstrap command completion config core engine frontend globals handlers interface message modes object objects plugin progress readline registry remote rules terminals utils window xdgbase

install-exec-hook : 
	$(SED) -i 's|__PREFIX__|@prefix@|g' $(DESTDIR)$(bindir)/bashrun

install-data-hook : 
	$(SED) -i 's|__PREFIX__|@prefix@|g' $(DESTDIR)$(sitedir)/frontend
	$(SED) -i 's|__PREFIX__|@prefix@|g' $(DESTDIR)$(sitedir)/bashrc
	$(SED) -i 's|__PREFIX__|@prefix@|g' $(DESTDIR)$(sitedir)/globals

	$(SED) -i 's|__TERMINAL__|@ac_with_terminal@|g' $(DESTDIR)$(sitedir)/core
	$(SED) -i 's|__TERMINAL__|@ac_with_terminal@|g' $(DESTDIR)$(sitedir)/modes

	$(SED) -i 's|__EXEC_TERMINAL__|@ac_with_exec_terminal@|g' $(DESTDIR)$(sitedir)/core
	$(SED) -i 's|__EXEC_TERMINAL__|@ac_with_exec_terminal@|g' $(DESTDIR)$(sitedir)/terminals

