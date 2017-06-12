#ifndef SMARTSTREETLIGHT_EVENT_THREAD_H_INCLUDED
#define SMARTSTREETLIGHT_EVENT_THREAD_H_INCLUDED

#include "main.h"
#include <pthread.h>
#include "gsoap/soapH.h"

gboolean    smartstreetlight_event_thread_init(void);

void        smartstreetlight_event_thread_finalize(void);

void        smartstreetlight_event_thread_run(void);

typedef struct spl_new_event_data
{
    gchar *event_log_time;
    gchar *event_log_content;

}spl_new_event_data;

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
typedef struct spl_lcu_runtime_data
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

}spl_lcu_runtime_data;

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
typedef struct spl_dcu_runtime_data
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

}spl_dcu_runtime_data;


gboolean spl_event_notify_add(gint type, gchar * msg);
//
//
//
//typedef struct spl_event_notify_data
//{
//   gint   size_eventlog_list;
//   struct ns1__EVENT_USCORELOG_USCOREINFO_USCOREType **eventlog_list;
//
//}spl_event_notify_data;
//
//
//
//typedef struct SPL_EVENT_NOTIFY_Widgets
//{
//    GtkWidget *spl_event_bar_actions;
//    GtkWidget *spl_event_window;
//    GtkWidget *spl_event_content_box;
//
//}SPL_EVENT_NOTIFY_Widgets;
//
//extern struct SPL_EVENT_NOTIFY_Widgets *spl_event_notify_widgets;
//

//
//void        smartstreetlight_event_thread_run(void);



#endif // SMARTSTREETLIGHT_EVENT_THREAD_H_INCLUDED
