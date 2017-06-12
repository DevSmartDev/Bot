iconsdir = $(datadir)/icons/hicolor/16x16/apps

icons_DATA = \
	next.png	\
	back.png	\
	find.png	\
	tick.png	\
	add.png		\
	remove.png	\
	edit.png	\
	down.png	\
	checkbox_non.png \
	checkbox_checked.png \
	checkbox_partial.png						

EXTRA_DIST = $(icons_DATA)

all: copyfile

copyfile:
	cd $(abs_srcdir);\
	for file in $(icons_DATA); do \
           cp -f $$file $(abs_builddir);  \
        done
