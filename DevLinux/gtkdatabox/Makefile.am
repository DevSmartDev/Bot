# $Id: Makefile.am 4 2008-06-22 09:19:11Z rbock $

bin_PROGRAMS = splchart

splchart_SOURCES     = main.cpp option.cpp main.h chart.cpp chart.h\
			../src/smartstreetlight_soap.cpp	\
			../src/smartstreetlight_error.cpp	\
			../src/smartstreetlight_error.h	\
			../src/smartstreetlight_soap.h	\
			../src/gsoap/soapClient.cpp		\
			../src/gsoap/soapC.cpp              	\
			../src/gsoap/soapH.h 		\
			../src/gsoap/soapStub.h      	\
			../src/gsoap/stdsoap2.cpp      	\
			../src/gsoap/stdsoap2.h		\
			gtk/gtkdatabox.c\
			gtk/gtkdatabox_marshal.c\
			gtk/gtkdatabox_scale.c\
			gtk/gtkdatabox_graph.c\
			gtk/gtkdatabox_xyc_graph.c\
			gtk/gtkdatabox_xyyc_graph.c\
 			gtk/gtkdatabox_points.c\
           		gtk/gtkdatabox_lines.c\
            		gtk/gtkdatabox_bars.c\
            		gtk/gtkdatabox_offset_bars.c\
            		gtk/gtkdatabox_regions.c\
			gtk/gtkdatabox_markers.c\
            		gtk/gtkdatabox_cross_simple.c\
            		gtk/gtkdatabox_grid.c\
			gtk/gtkdatabox_ruler.c
			gtk/gtkdatabox_typedefs.h\
			gtk/gtkdatabox.h\
			gtk/gtkdatabox_marshal.h\
			gtk/gtkdatabox_scale.h\
			gtk/gtkdatabox_graph.h\
			gtk/gtkdatabox_xyc_graph.h\
			gtk/gtkdatabox_xyyc_graph.h\
 			gtk/gtkdatabox_points.h\
            		gtk/gtkdatabox_lines.h\
            		gtk/gtkdatabox_bars.h\
            		gtk/gtkdatabox_offset_bars.h\
            		gtk/gtkdatabox_regions.h\
			gtk/gtkdatabox_markers.h\
            		gtk/gtkdatabox_cross_simple.h\
            		gtk/gtkdatabox_grid.h\
			gtk/gtkdatabox_ruler.h			


splchart_CPPFLAGS		= -I$(top_srcdir)/gtkdatabox/gtk -D__SPL_CHART__ -D__clang__

splchart_CFLAGS			=\
			-g -ggdb -O2 \
			-DG_DISABLE_DEPRECATED\
			-DGDK_DISABLE_DEPRECATED\
			-DGDK_PIXBUF_DISABLE_DEPRECATED\
			-DGTK_DISABLE_DEPRECATED\
			-DGSEAL_ENABLED\
			-DGTK_DISABLE_SINGLE_INCLUDES\
		 	@GTK2_CFLAGS@ 
splchart_CXXFLAGS			=\
			-g -ggdb -O2 -fpermissive\
			-DG_DISABLE_DEPRECATED\
			-DGDK_DISABLE_DEPRECATED\
			-DGDK_PIXBUF_DISABLE_DEPRECATED\
			-DGTK_DISABLE_DEPRECATED\
			-DGSEAL_ENABLED\
			-DGTK_DISABLE_SINGLE_INCLUDES\
		 	@GTK2_CFLAGS@ 


LDADD 			= @GTK2_LIBS@ \
			-lm


if MINGW
splchart_LDFLAGS = -mms-bitfields  -mwindows -ffast-math -static $(LDADD) -lws2_32 -lstdc++ -lpthread  -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic
else
splchart_LDFLAGS = -static $(LDADD)
endif
clean-local:
