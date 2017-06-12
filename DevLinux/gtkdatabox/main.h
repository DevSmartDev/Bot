#ifndef OPTION_H_INCLUDED
#define OPTION_H_INCLUDED
#include <gtk/gtk.h>
/*! Define for byte value of character ('0','A' and 'a')------------------------------------*/
#define CHR_ZEROS   48
#define CHR_UPPER   65
#define CHR_LOWER   97

#ifndef __RELEASE__
	#define __DEBUG__(format, ...) fprintf (stderr, format, ## __VA_ARGS__)
#else
	#define __DEBUG__(format, ...) { };
#endif

#define DEBUG(fmt, args...) __DEBUG__("%s():%d:: " fmt "\n",__FUNCTION__, __LINE__, ##args)
#define DEBUG_0(format, ...) DEBUG(format, ## __VA_ARGS__)
#define DEBUG_1() DEBUG("\n")

struct PROGRAM_OPTION{
    gchar* begin_time;
    gchar* end_time;
    gchar* account;
    gchar* url;
    gchar * lcu_id;
    gint   account_id;
};
extern GtkWidget *window ;
gboolean getOptCommandLine(int argc, char **argv, struct PROGRAM_OPTION* option_t);
void spl_chart_help(const gchar* programName);
gint spl_utils_message_box(GtkWindow *parent, GtkMessageType type, GtkButtonsType btn, const gchar* msg);
#endif
