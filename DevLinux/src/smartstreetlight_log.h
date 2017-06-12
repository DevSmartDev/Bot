#ifndef __SMARTSTREETLIGHT_LOG_H__
#define __SMARTSTREETLIGHT_LOG_H__

#include "main.h"
#include "smartstreetlight_utils.h"
#include "smartstreetlight_dcu.h"
#include "smartstreetlight_lcu.h"

#include "smartstreetlight_callback.h"
#include "gsoap/soapH.h"


/*
    enum ns1__EVENTLOG_USCORETYPE_USCOREEnum
    {
        ns1__EVENTLOG_USCORETYPE_USCOREEnum__CONNECT_USCOREDCU_USCORELOG,	///< xs:string value="CONNECT_DCU_LOG"
        ns1__EVENTLOG_USCORETYPE_USCOREEnum__LIFECYCLE_USCORESERVER_USCORELOG,	///< xs:string value="LIFECYCLE_SERVER_LOG"
        ns1__EVENTLOG_USCORETYPE_USCOREEnum__DCU_USCOREERR_USCORELOG,	///< xs:string value="DCU_ERR_LOG"
        ns1__EVENTLOG_USCORETYPE_USCOREEnum__LCU_USCOREERR_USCORELOG,	///< xs:string value="LCU_ERR_LOG"
        ns1__EVENTLOG_USCORETYPE_USCOREEnum__LINE_USCOREERR_USCORELOG,	///< xs:string value="LINE_ERR_LOG"
    };
*/
enum
{
    SPL_LOG_CONN = ns1__EVENTLOG_USCORETYPE_USCOREEnum__CONNECT_USCOREDCU_USCORELOG,
    SPL_LOG_DCU = ns1__EVENTLOG_USCORETYPE_USCOREEnum__DCU_USCOREERR_USCORELOG,
    SPL_LOG_LCU = ns1__EVENTLOG_USCORETYPE_USCOREEnum__LCU_USCOREERR_USCORELOG,
    SPL_LOG_LINE = ns1__EVENTLOG_USCORETYPE_USCOREEnum__LINE_USCOREERR_USCORELOG,
};

typedef struct _SplLogWidget
{
    GtkTreeView         *log_conn_view;
    GtkTreeStore        *log_conn_store;

    GtkTreeView         *log_dcu_view;
    GtkTreeStore        *log_dcu_store;

    GtkTreeView         *log_lcu_view;
    GtkTreeStore        *log_lcu_store;

    GtkTreeView         *log_line_view;
    GtkTreeStore        *log_line_store;
}SplLogWidget;

extern SplLogWidget *log_widget;

gboolean spl_log_init();

void spl_log_final();

void spl_log_clear_store(gint index);

void spl_log_clear_all_store();

void spl_log_view_fill_information(gint index,
                                const gint event_id,
                                const gchar *event_dcu_id,
                                const gint event_type,
                                const gchar *event_content,
                                const gchar *event_time);


gboolean smartstreetlight_dcu_view_log(pSplDcu dcu);

#endif //__SMARTSTREETLIGHT_LOG_H__
