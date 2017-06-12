iconsdir = $(datadir)/icons/hicolor/16x16/apps

icons_DATA = light_broken.png \
	light_on.png	\
	light_off.png \
	light_broken_selected.png \
	light_on_selected.png	\
	light_off_selected.png \
	light_broken_p_selected.png \
	light_on_p_selected.png	\
	light_off_p_selected.png
EXTRA_DIST = $(icons_DATA) 

all: copyfile

copyfile:
	cd $(abs_srcdir); \
        for file in $(icons_DATA); do \
           cp -f $$file $(abs_builddir);  \
        done

