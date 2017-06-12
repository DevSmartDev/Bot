## Process this file with automake to produce Makefile.in

SUBDIRS =src po icons
#SUBDIRS = src/gsoap src po icons

AUTOMAKE_OPTIONS =	1.7

ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = \
	autogen.sh \
	wscript \
	waf \
	bot.desktop.in \
	bot.pc.in \
	bot.spec \ \
	ChangeLog.pre-0-17 \
	HACKING \
	README.I18N \
	README.Packagers \
	po/intl_stats.sh \
	intltool-extract.in \
	intltool-merge.in \
	intltool-update.in \
	$(SYS_DATA_FILES) \
	$(WIN32_BUILD_FILES)\
	gnome-doc-utils.make

DISTCLEANFILES = \
	bot.desktop \
	intltool-extract \
	intltool-merge \
	intltool-update\
	gnome-doc-utils.make

uninstall-local:
	rm -rf $(DESTDIR)$(pkgdatadir);

install-data-local: install-data-only
	@$(NORMAL_INSTALL)

install-data-only:
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(pkgdatadir); \
	$(INSTALL_DATA) $(srcdir)/COPYING $(DESTDIR)$(pkgdatadir)/GPL-2; \
	$(INSTALL_DATA) $(srcdir)/src/botStyle.css $(DESTDIR)$(pkgdatadir)/; \
	for file in $(srcdir)/data/*; do \
	  if test -f $$file; then \
	    $(INSTALL_DATA) $$file $(DESTDIR)$(pkgdatadir)/; \
	  fi \
	done
	$(mkinstalldirs) $(DESTDIR)$(pkgdatadir)/templates;
	for file in $(srcdir)/data/templates/*; do \
	  if test -f $$file; then \
	    $(INSTALL_DATA) $$file $(DESTDIR)$(pkgdatadir)/templates/; \
	  fi \
	done
	$(mkinstalldirs) $(DESTDIR)$(pkgdatadir)/templates/files;
	for file in $(srcdir)/data/templates/files/*; do \
	  if test -f $$file; then \
	    $(INSTALL_DATA) $$file $(DESTDIR)$(pkgdatadir)/templates/files/; \
	  fi \
	done
	$(mkinstalldirs) $(DESTDIR)$(pkgdatadir)/colorschemes;
	for file in $(srcdir)/data/colorschemes/*; do \
	  if test -f $$file; then \
	    $(INSTALL_DATA) $$file $(DESTDIR)$(pkgdatadir)/colorschemes/; \
	  fi \
	done

BZIP2_ENV =--best

dist-bzip2: distdir
	BZIP2=$(BZIP2_ENV) $(AMTAR) --bzip2 -chof $(distdir).tar.bz2 $(distdir)
	-rm -rf $(distdir)

sign:
	if test -f $(PACKAGE)-$(VERSION).tar.gz; then \
		gpg --detach-sign --digest-algo SHA512 $(PACKAGE)-$(VERSION).tar.gz; fi
	if test -f $(PACKAGE)-$(VERSION).tar.bz2; then \
		gpg --detach-sign --digest-algo SHA512 $(PACKAGE)-$(VERSION).tar.bz2; fi

deb:
	dpkg-buildpackage -rfakeroot


rpm: dist
	rpmbuild -ta $(distdir).tar.gz


pkgconfig_DATA = bot.pc
pkgconfigdir = $(libdir)/pkgconfig

desktopdir = $(datadir)/applications
desktop_in_files = bot.desktop
desktop_DATA = $(desktop_in_files:.desktop.in=.desktop)
@INTLTOOL_DESKTOP_RULE@
