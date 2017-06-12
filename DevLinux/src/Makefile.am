## Process this file with automake to produce Makefile.in
# $Id: Makefile.am 5839 2011-06-13 18:41:15Z colombanw $

#MYSQL_CFLAGS = -I/usr/include/mysql -DBIG_JOINS=1  -fno-strict-aliasing
#MYSQL_LIBS = -L/usr/lib/i386-linux-gnu -lmysqlclient -lpthread -lz -lm -lrt -ldl
bot_CONFIG_DIR = .bot

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

bin_PROGRAMS = bot

RESOURCE_DIR=$(srcdir)/../../resource
SRCS =  main.cpp main.h							\
	mapviewer.cpp mapviewer.h						\
	bot_gui.h						\
	bot_method.h					\
	bot_ui_method.cpp bot_ui_method.h	\
	bot_login.cpp bot_login.h		\
	bot_utils.cpp bot_utils.h		\
	bot_sql.cpp bot_sql.h			\
	bot_dcu.cpp bot_dcu.h			\
	bot_lcu.cpp bot_lcu.h			\
	bot_callback.cpp bot_callback.h	\
	bot_database.h bot_database.cpp	\
	bot_schedule.h bot_schedule.cpp	\
	bot_line.h bot_line.cpp		\
	bot_server.h bot_server.cpp		\
	bot_user.h bot_user.cpp		\
	bot_zone.h bot_zone.cpp		\
	bot_log.h bot_log.cpp			\
	bot_dcu_program_process.h				\
	bot_dcu_program_process.cpp			\
	bot_admin_user.h bot_admin_user.cpp	\
	bot_admin_zone.h bot_admin_zone.cpp	\
	bot_error.h bot_error.cpp		\
	bot_event_thread.h bot_event_thread.cpp\
	bot_common.h					\
	botService.nsmap                   		\
	bot_soap_thread.h bot_soap_thread.cpp \
	bot_soap.h bot_soap.cpp		\
	gsoap/soapClient.cpp    					\
	gsoap/soapC.cpp                                         	\
	gsoap/soapH.h 							\
	gsoap/soapStub.h      						\
	gsoap/stdsoap2.cpp      					\
	gsoap/stdsoap2.h						
							


bot_includedir = $(includedir)/bot
# only install headers that define types or macros, not just functions
bot_include_HEADERS = bot_gui.h
if MINGW
AM_CPPFLAGS = 	-D__clang__ -I$(top_srcdir)\
	        @GTK_CFLAGS@ @GTHREAD_CFLAGS@ @GMODULE_CFLAGS@ \
		-I$(srcdir)/../../lib/osm-gps-map/win/include/osmgpsmap-1.0 

bot_SOURCES = $(SRCS)


bot_LDADD = $(srcdir)/../../lib/osm-gps-map/win/lib/libosmgpsmap-1.0.a \
  @GTK_LIBS@ @GTHREAD_LIBS@ @GMODULE_LIBS@ $(INTLLIBS) @XML2_LIBS@  $(OSMGPSMAP_LIBS)       \
    $(GTHREAD_LIBS) bot_private.res	


AM_CFLAGS =		 -g -ggdb  -fpermissive \
			-Dbot_DATADIR=\""$(datadir)"\" \
			-Dbot_DOCDIR=\""$(docdir)"\" \
			-Dbot_LIBDIR=\""$(libdir)"\" \
			-Dbot_LOCALEDIR=\""$(localedir)"\" \
			-Dbot_PREFIX=\""$(prefix)"\" \
			-Dbot_PRIVATE \
			-DGTK \
			-DGNOME\
			-DG_LOG_DOMAIN=\""bot"\" \
			-Bstatic \
			$(OSMGPSMAP_CFLAGS)

AM_CXXFLAGS =		-g -ggdb -fpermissive \
			-Dbot_DATADIR=\""$(datadir)"\" \
			-Dbot_DOCDIR=\""$(docdir)"\" \
			-Dbot_LIBDIR=\""$(libdir)"\" \
			-Dbot_LOCALEDIR=\""$(localedir)"\" 	-Dbot_PREFIX=\""$(prefix)"\" \
			-Dbot_PREFIX=\""$(prefix)"\" \
			-Dbot_PRIVATE \
			-DGTK \
			-DGNOME\
			-DG_LOG_DOMAIN=\""bot"\" \
			-Bstatic				

#bot_LDFLAGS = -lgmodule-2.0  -lws2_32 -lstdc++ -lpthread  -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic
bot_LDFLAGS = -mms-bitfields  -mwindows -ffast-math -lgmodule-2.0 -static -lws2_32 -lstdc++ -lpthread  -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic

WINDCPP = $(host_alias)-cpp
WINDRES = $(host_alias)-windres

bot_private.res: $(srcdir)/../bot_private.rc
	$(WINDCPP) -Dbot_ICON="\"$(srcdir)/../icons/light.ico\""  $(srcdir)/../bot_private.rc | $(WINDRES) --input-format=rc -o bot_private.res -O coff;

clean-local:
	rm -f bot_private.res

else
AM_CPPFLAGS = 	-D__clang__ -I$(top_srcdir)\
	        @GTK_CFLAGS@ @GTHREAD_CFLAGS@ @GMODULE_CFLAGS@ \
		-I$(srcdir)/../../lib/osm-gps-map/linux/include/osmgpsmap-1.0 

bot_SOURCES = $(SRCS)



bot_LDADD = $(srcdir)/../../lib/osm-gps-map/linux/lib/libosmgpsmap-1.0.a \
  @GTK_LIBS@ @GTHREAD_LIBS@ @GMODULE_LIBS@ $(INTLLIBS) @XML2_LIBS@ $(OSMGPSMAP_LIBS)       \
    $(GTHREAD_LIBS)	


AM_CFLAGS =		-Wl,--export-dynamic -g -ggdb -rdynamic -fpermissive\
			-Dbot_DATADIR=\""$(datadir)"\" \
			-Dbot_DOCDIR=\""$(docdir)"\" \
			-Dbot_LIBDIR=\""$(libdir)"\" \
			-Dbot_LOCALEDIR=\""$(localedir)"\" \
			-Dbot_PREFIX=\""$(prefix)"\" \
			-Dbot_PRIVATE \
			-DGTK \
			-DGNOME\
			-DG_LOG_DOMAIN=\""bot"\" \
			-Bstatic \
			$(OSMGPSMAP_CFLAGS)

AM_CXXFLAGS =		-Wl,--export-dynamic -g -ggdb -rdynamic -fpermissive\
			-Dbot_DATADIR=\""$(datadir)"\" \
			-Dbot_DOCDIR=\""$(docdir)"\" \
			-Dbot_LIBDIR=\""$(libdir)"\" \
			-Dbot_LOCALEDIR=\""$(localedir)"\" 	-Dbot_PREFIX=\""$(prefix)"\" \
			-Dbot_PREFIX=\""$(prefix)"\" \
			-Dbot_PRIVATE \
			-DGTK \
			-DGNOME\
			-DG_LOG_DOMAIN=\""bot"\" \
			-Bstatic				

bot_LDFLAGS = -lgmodule-2.0 -rdynamic -static
endif
$(srcdir)/bot_gui.h: $(srcdir)/bot.glade
	$(srcdir)/gen_gui.sh  bot_gui $(srcdir)/bot.glade $(srcdir)/bot_gui.h

clean-local:

