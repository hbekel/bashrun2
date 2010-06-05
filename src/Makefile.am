bin_PROGRAMS = brwctl
brwctl_SOURCES = brwctl.c

bin_SCRIPTS = bashrun
sitedir = $(datadir)/@PACKAGE@
site_DATA = actions bashrc bindings bookmarks bootstrap command completion config core engine frontend geometry globals handlers message modes object objects plugin progress readline registry remote rules terminals utils window xdgbase

install-exec-hook : 
	$(SED) -i 's|__PREFIX__|@prefix@|g' $(DESTDIR)$(bindir)/bashrun

install-data-hook : 
	$(SED) -i 's|__PREFIX__|@prefix@|g' $(DESTDIR)$(sitedir)/bashrc
	$(SED) -i 's|__PREFIX__|@prefix@|g' $(DESTDIR)$(sitedir)/globals

