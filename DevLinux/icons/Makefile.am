SUBDIRS =  16x16 32x32 light

#dist_noinst_DATA = ifast.ico
gtk_update_icon_cache = gtk-update-icon-cache -f -t /usr/share/icons/hicolor

install-data-hook:
	@-if test -z "$(DESTDIR)"; then					\
		echo "Updating Gtk icon cache.";			\
		echo $(datadir);					\
		$(gtk_update_icon_cache) ;				\
		$(gtk_update_icon_cache) "$(datadir)/icons/Tango"; 	\
	else								\
		echo "*** Icon cache not updated. Remember to run:";	\
		echo "***";						\
		echo "***   $(gtk_update_icon_cache)";			\
		echo "***";						\
	fi

uninstall-local:
	rm -f $(DESTDIR)$(datadir)/icons/hicolor/icon-theme.cache;
