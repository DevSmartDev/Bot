iconsdir = $(datadir)/icons/hicolor/16x16/apps

icons_DATA = \
	zoom_in.png	\
	zoom_out.png	\
	home.png	\
	notification.png

EXTRA_DIST = $(icons_DATA) 

all: copyfile

copyfile:
	cd $(abs_srcdir); \
        for file in $(icons_DATA); do \
           cp -f $$file $(abs_builddir);  \
        done;
