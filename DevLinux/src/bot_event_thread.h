#ifndef BOT_EVENT_THREAD_H_INCLUDED
#define BOT_EVENT_THREAD_H_INCLUDED

#include "main.h"
#include <pthread.h>
#include "gsoap/soapH.h"

gboolean    bot_event_thread_init(void);

void        bot_event_thread_finalize(void);

void        bot_event_thread_run(void);

typedef struct bot_new_event_data
{
    gchar *event_log_time;
    gchar *event_log_content;

}bot_new_event_data;

/*
    char *lcu_USCOREid;
	char *lcu_USCOREgps;
	char *lcu_USCOREnote;
	int lcu_USCOREmode;
	int lcu_USCOREison;
	int lcu_USCOREstatus;
	int lcu_USCOREcurrent;
	int lcu_USCORElevel;
	int lcu_USCOREistemp;
	char *lcu_USCOREdcuid;
*/
typedef struct bot_lcu_runtime_data
{
    gchar *lcu_id;
    gchar *lcu_gps;
    gchar *lcu_dcuid;
    gchar *lcu_note;
    gchar *lightname;
	gint   tolerance;
	gint   power;
    gint lcu_mode;
    gint lcu_ison;
    gint lcu_status;
    gint lcu_current;
    gint lcu_level;
    gint lcu_istemp;

}bot_lcu_runtime_data;

/*
    char *dcu_USCOREid;
	char *dcu_USCOREphone;
	char *dcu_USCOREgps;
	char *dcu_USCOREaddress;
	char *dcu_USCOREnote;
	int dcu_USCOREmode;
	int dcu_USCOREstatus;
	int dcu_USCOREprogram_USCOREid;
	int dcu_USCOREzoneid;
	struct soap *soap;
*/
typedef struct bot_dcu_runtime_data
{
    gchar *dcu_id;
    gchar *dcu_phone;
    gchar *dcu_gps;
    gchar *dcu_address;
    gchar *dcu_note;
    gint dcu_mode;
    gint dcu_status;
    gint dcu_program_id;
    gint dcu_zone_id;

}bot_dcu_runtime_data;


gboolean bot_event_notify_add(gint type, gchar * msg);
//
//
//
//typedef struct bot_event_notify_data
//{
//   gint   size_eventlog_list;
//   struct ns1__EVENT_USCORELOG_USCOREINFO_USCOREType **eventlog_list;
//
//}bot_event_notify_data;
//
//
//
//typedef struct bot_EVENT_NOTIFY_Widgets
//{
//    GtkWidget *bot_event_bar_actions;
//    GtkWidget *bot_event_window;
//    GtkWidget *bot_event_content_box;
//
//}bot_EVENT_NOTIFY_Widgets;
//
//extern struct bot_EVENT_NOTIFY_Widgets *bot_event_notify_widgets;
//

//
//void        bot_event_thread_run(void);



#endif // BOT_EVENT_THREAD_H_INCLUDED
