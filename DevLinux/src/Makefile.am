## Process this file with automake to produce Makefile.in
# $Id: Makefile.am 5839 2011-06-13 18:41:15Z colombanw $

#MYSQL_CFLAGS = -I/usr/include/mysql -DBIG_JOINS=1  -fno-strict-aliasing
#MYSQL_LIBS = -L/usr/lib/i386-linux-gnu -lmysqlclient -lpthread -lz -lm -lrt -ldl
SPL_CONFIG_DIR = .smartstreetlight

OSMGPSMAP_CFLAGS =          \
    $(GLIB_CFLAGS)          \
    $(GTK_CFLAGS)           \
    $(CAIRO_CFLAGS)         \
    $(SOUP24_CFLAGS)

OSMGPSMAP_LIBS =            \
    $(GLIB_LIBS)            \
    $(GTK_LIBS)             \
    $(CAIRO_LIBS)           \
    $(SOUP24_LIBS)

bin_PROGRAMS = SmartPublicLight

RESOURCE_DIR=$(srcdir)/../../resource
SRCS =  main.cpp main.h							\
	mapviewer.cpp mapviewer.h						\
	smartstreetlight_gui.h						\
	smartstreetlight_method.h					\
	smartstreetlight_ui_method.cpp smartstreetlight_ui_method.h	\
	smartstreetlight_login.cpp smartstreetlight_login.h		\
	smartstreetlight_utils.cpp smartstreetlight_utils.h		\
	smartstreetlight_sql.cpp smartstreetlight_sql.h			\
	smartstreetlight_dcu.cpp smartstreetlight_dcu.h			\
	smartstreetlight_lcu.cpp smartstreetlight_lcu.h			\
	smartstreetlight_callback.cpp smartstreetlight_callback.h	\
	smartstreetlight_database.h smartstreetlight_database.cpp	\
	smartstreetlight_schedule.h smartstreetlight_schedule.cpp	\
	smartstreetlight_line.h smartstreetlight_line.cpp		\
	smartstreetlight_server.h smartstreetlight_server.cpp		\
	smartstreetlight_user.h smartstreetlight_user.cpp		\
	smartstreetlight_zone.h smartstreetlight_zone.cpp		\
	smartstreetlight_log.h smartstreetlight_log.cpp			\
	smartstreetlight_dcu_program_process.h				\
	smartstreetlight_dcu_program_process.cpp			\
	smartstreetlight_admin_user.h smartstreetlight_admin_user.cpp	\
	smartstreetlight_admin_zone.h smartstreetlight_admin_zone.cpp	\
	smartstreetlight_error.h smartstreetlight_error.cpp		\
	smartstreetlight_event_thread.h smartstreetlight_event_thread.cpp\
	smartstreetlight_common.h					\
	smartstreetlightService.nsmap                   		\
	smartstreetlight_soap_thread.h smartstreetlight_soap_thread.cpp \
	smartstreetlight_soap.h smartstreetlight_soap.cpp		\
	gsoap/soapClient.cpp    					\
	gsoap/soapC.cpp                                         	\
	gsoap/soapH.h 							\
	gsoap/soapStub.h      						\
	gsoap/stdsoap2.cpp      					\
	gsoap/stdsoap2.h						
							


SmartPublicLight_includedir = $(includedir)/SmartPublicLight
# only install headers that define types or macros, not just functions
SmartPublicLight_include_HEADERS = smartstreetlight_gui.h
if MINGW
AM_CPPFLAGS = 	-D__clang__ -I$(top_srcdir)\
	        @GTK_CFLAGS@ @GTHREAD_CFLAGS@ @GMODULE_CFLAGS@ \
		-I$(srcdir)/../../lib/osm-gps-map/win/include/osmgpsmap-1.0 

SmartPublicLight_SOURCES = $(SRCS)


SmartPublicLight_LDADD = $(srcdir)/../../lib/osm-gps-map/win/lib/libosmgpsmap-1.0.a \
  @GTK_LIBS@ @GTHREAD_LIBS@ @GMODULE_LIBS@ $(INTLLIBS) @XML2_LIBS@  $(OSMGPSMAP_LIBS)       \
    $(GTHREAD_LIBS) spl_private.res	


AM_CFLAGS =		 -g -ggdb  -fpermissive \
			-DSPL_DATADIR=\""$(datadir)"\" \
			-DSPL_DOCDIR=\""$(docdir)"\" \
			-DSPL_LIBDIR=\""$(libdir)"\" \
			-DSPL_LOCALEDIR=\""$(localedir)"\" \
			-DSPL_PREFIX=\""$(prefix)"\" \
			-DSPL_PRIVATE \
			-DGTK \
			-DGNOME\
			-DG_LOG_DOMAIN=\""SmartPublicLight"\" \
			-Bstatic \
			$(OSMGPSMAP_CFLAGS)

AM_CXXFLAGS =		-g -ggdb -fpermissive \
			-DSPL_DATADIR=\""$(datadir)"\" \
			-DSPL_DOCDIR=\""$(docdir)"\" \
			-DSPL_LIBDIR=\""$(libdir)"\" \
			-DSPL_LOCALEDIR=\""$(localedir)"\" 	-DSPL_PREFIX=\""$(prefix)"\" \
			-DSPL_PREFIX=\""$(prefix)"\" \
			-DSPL_PRIVATE \
			-DGTK \
			-DGNOME\
			-DG_LOG_DOMAIN=\""SmartPublicLight"\" \
			-Bstatic				

#SmartPublicLight_LDFLAGS = -lgmodule-2.0  -lws2_32 -lstdc++ -lpthread  -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic
SmartPublicLight_LDFLAGS = -mms-bitfields  -mwindows -ffast-math -lgmodule-2.0 -static -lws2_32 -lstdc++ -lpthread  -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic

WINDCPP = $(host_alias)-cpp
WINDRES = $(host_alias)-windres

spl_private.res: $(srcdir)/../smartstreetlight_private.rc
	$(WINDCPP) -DSPL_ICON="\"$(srcdir)/../icons/light.ico\""  $(srcdir)/../smartstreetlight_private.rc | $(WINDRES) --input-format=rc -o spl_private.res -O coff;

clean-local:
	rm -f spl_private.res

else
AM_CPPFLAGS = 	-D__clang__ -I$(top_srcdir)\
	        @GTK_CFLAGS@ @GTHREAD_CFLAGS@ @GMODULE_CFLAGS@ \
		-I$(srcdir)/../../lib/osm-gps-map/linux/include/osmgpsmap-1.0 

SmartPublicLight_SOURCES = $(SRCS)



SmartPublicLight_LDADD = $(srcdir)/../../lib/osm-gps-map/linux/lib/libosmgpsmap-1.0.a \
  @GTK_LIBS@ @GTHREAD_LIBS@ @GMODULE_LIBS@ $(INTLLIBS) @XML2_LIBS@ $(OSMGPSMAP_LIBS)       \
    $(GTHREAD_LIBS)	


AM_CFLAGS =		-Wl,--export-dynamic -g -ggdb -rdynamic -fpermissive\
			-DSPL_DATADIR=\""$(datadir)"\" \
			-DSPL_DOCDIR=\""$(docdir)"\" \
			-DSPL_LIBDIR=\""$(libdir)"\" \
			-DSPL_LOCALEDIR=\""$(localedir)"\" \
			-DSPL_PREFIX=\""$(prefix)"\" \
			-DSPL_PRIVATE \
			-DGTK \
			-DGNOME\
			-DG_LOG_DOMAIN=\""SmartPublicLight"\" \
			-Bstatic \
			$(OSMGPSMAP_CFLAGS)

AM_CXXFLAGS =		-Wl,--export-dynamic -g -ggdb -rdynamic -fpermissive\
			-DSPL_DATADIR=\""$(datadir)"\" \
			-DSPL_DOCDIR=\""$(docdir)"\" \
			-DSPL_LIBDIR=\""$(libdir)"\" \
			-DSPL_LOCALEDIR=\""$(localedir)"\" 	-DSPL_PREFIX=\""$(prefix)"\" \
			-DSPL_PREFIX=\""$(prefix)"\" \
			-DSPL_PRIVATE \
			-DGTK \
			-DGNOME\
			-DG_LOG_DOMAIN=\""SmartPublicLight"\" \
			-Bstatic				

SmartPublicLight_LDFLAGS = -lgmodule-2.0 -rdynamic -static
endif
$(srcdir)/smartstreetlight_gui.h: $(srcdir)/SmartStreetLight.glade
	$(srcdir)/gen_gui.sh  smartstreetlight_gui $(srcdir)/SmartStreetLight.glade $(srcdir)/smartstreetlight_gui.h

clean-local:

