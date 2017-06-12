#ifndef SMARTSTREETLIGHT_LCU_H_INCLUDED
#define SMARTSTREETLIGHT_LCU_H_INCLUDED

#include "main.h"
#include "mapviewer.h"
#include "smartstreetlight_dcu.h"
#include "smartstreetlight_utils.h"
#include "smartstreetlight_callback.h"
#include "smartstreetlight_database.h"
#include "gsoap/soapH.h"

#define LCU_BRIGHTNESS_MAX_LEVEL 255

/* ===================*/
#define NOERROR_STATUS 					(0<<0)
#define ERROR_RF_LCU_STATUS 			(1<<0)
#define ERROR_LIGHT_STATUS 				(1<<1)
#define ERROR_CLOCK_LCU_STATUS 			(1<<2)
#define ERROR_CURRENT_STATUS 			(1<<3)
#define DELETE_STATUS 					(1<<25)


#define IS_ERROR_LCU(status)               \
                           (status & (ERROR_RF_LCU_STATUS         | \
                                            ERROR_LIGHT_STATUS           | \
                                            ERROR_SYNC_LCU_STATUS       | \
                                            ERROR_CLOCK_LCU_STATUS      | \
                                            ERROR_CURRENT_STATUS            ))
typedef struct _SplLcu
{
    /** Private elements*/
    gchar           *id;
    gchar           *gps;
    gchar           *note;
    gfloat         lat;
    gfloat         lon;
    gint            mode;
    gint            status;
    gfloat          volt;
    gfloat          brightness;
    gboolean        isOn;
    gboolean        isBroken;
    gint            power;
    gchar           *lightname;
	gint            tolerance;
    pSplDcu         parent;
    OsmGpsMapImage  *icon; /**Be careful when use this component because it have been free usually*/

}SplLcu, *pSplLcu;


typedef struct _SplLcuLog
{
    /** Private elements*/
    gint            id;
    gchar           *lcuId;
    gdouble         power_consum; // cong suat tieu thu 10mW -> bieu do
    gdouble         power_ctrl; // cong suat dieu khien 10mW -> bieu do
    gdouble         power; // cong suat den 10mW
    gint            tolerance;
    gchar*          date_time; // time
    gchar*          lightname;
    gint            status;
    gint            mode;
}SplLcuLog, *pSplLcuLog;
extern GSList *LcuLogList;

/*
    gint smartstreetlight_get_log_lcu_nofree_execute(SplSoap* spl_soap, gchar * lcu_id, gchar * time_from,
                                                    gchar * time_to, ns1__LCULOGINFOType*** lcu_log_list,
                                                    gint * lcu_log_list_size);
*/
struct SlopeLcuThread
{
    gchar *lcu_id;
    gchar *time_from;
    gchar *time_to;

    ns1__LCULOGINFOType **lcu_log_list;
    gint lcu_log_list_size;
};

typedef struct _SplLcuPopup
{
    GtkWidget           *own;
    GtkWidget           *menu_add;
    GtkWidget           *menu_add_from_file;
    GtkWidget           *menu_edit;
    GtkWidget           *menu_remove;
    GtkWidget           *menu_remove_all;
    GtkWidget           *menu_control;
    GtkWidget           *menu_location;
    GtkWidget           *menu_chart;
}SplLcuPopup, *pSplLcuPopup;


typedef enum SPL_LCU_POPUP_MENU_Enum
{
    SPL_LCU_M_ADD = 0,
    SPL_LCU_M_ADD_FROM_FILE,
    SPL_LCU_M_CONTROL,
    SPL_LCU_M_REMOVE,
    SPL_LCU_M_REMOVE_ALL,
    SPL_LCU_M_EDIT,
    SPL_LCU_M_LOCATION,
    SPL_LCU_M_CHART,
    SPL_LCU_M_NUMBER,
} SPL_LCU_POPUP_MENU_Enum;


enum
{
    DISPLAY_FOLLOW_DCU =0,
    DISPLAY_FOLLOW_ZONE,
    DISPLAY_ALL,

};

enum
{
    LIGHT_ID = 0,
    LIGHT_POINTER,
    LIGHT_VISIBLE,
    LIGHT_COUNT,
};


typedef enum SPL_LCU_MODE_Enum
{
    SPL_LCU_ScheduleMode = 1,
    SPL_LCU_ManualMode   = 2,
    SPL_LCU_OffMode      = 3

}SPL_LCU_MODE_Enum;



extern GtkComboBox *cbb_light_display;
extern pSplLcu lastSelectedLcu;
extern pSplLcuPopup lcuPopupMenu;


typedef struct SPL_LCU_Widgets
{
    GtkAdjustment	    *lcu_adjustment_light_level;
	GtkWidget	        *lcu_scale_light_level;
	GtkTreeView         *lcu_control_treeview_schedule;
	GtkListStore        *lcu_control_liststore_schedule;

} SPL_LCU_Widgets;

extern struct SPL_LCU_Widgets *lcu_widgets;

void smartstreetlight_lcu_fill_infomation(gchar *lcu_name,
                                           gchar *lcu_gps,
                                           gchar *lcu_note,
                                           gchar *lcu_mode,
                                           gboolean lcu_ison,
                                           gboolean lcu_status,
                                           gchar *lcu_current,
                                           gchar *lcu_lightlevel,
                                           gboolean lcu_isbroken,
                                           gchar *lcu_dcuid,
                                           gchar *lcu_updatetime
                                           );

struct CtrlLcuThread
{
    pSplLcu lcu;
    gint isOn;
    gint mode;
    gint scale;
    gboolean istemp;
    gint rsp_lcu_list_size;
    ns1__LCU_USCOREINFO_USCOREType **rsp_lcu_list;
};


void smartstreetlight_lcu_show_list(gchar *dcu_id);

void smartstreetlight_lcu_liststore_clean();

void smartstreetlight_lcu_dialog_show(GtkTreeModel *model, GtkTreeIter iter);

gboolean smartstreetlight_lcu_info_init(void);

void smartstreetlight_lcu_finalize(void);

void smartstreetlight_lcu_popup_menu_show(GtkTreeView *treeview, GdkEventButton *event, gpointer userdata);

gchar * smartstreetlight_lcu_get_status_name(gint status);

gchar * smartstreetlight_lcu_get_mode_name(gint mode);

void smartstreetlight_lcu_control_mode_combobox_change(void);

void smartstreetlight_lcu_control_schedule_fill(gchar *schedule_month,
                                                gchar *schedule_starttime,
                                                gchar *schedule_timeon,
                                                gchar *schedule_level,
                                                gchar *schedule_program_name);

void smartstreetlight_get_all_light();
void light_update_information(pSplLcu lcu, gboolean setmapcenter);
void popup_light_view_show(GdkEventButton *event);

GdkPixbuf *spl_get_light_icon(pSplLcu lcu, gboolean selected, gboolean iszone);
void spl_lcu_remove_iter_and_image(pSplDcu dcu, pSplLcu lcu);
void spl_lcu_free(pSplLcu lcu);
gboolean spl_light_add_new_request();
gboolean spl_light_chart_show(pSplLcu lcu_log);
gboolean spl_light_edit(pSplLcu lcu);
gboolean spl_lcu_popup_menu_control(pSplLcu lcu);
void spl_light_remove_request(pSplLcu lcu);
pSplLcu spl_lcu_init();
pSplLcuLog spl_lcu_log_init();
void spl_lcu_log_free(pSplLcuLog lcu_log);
void spl_lcu_add_image(pSplLcu lcu, GdkPixbuf *buf, gfloat *lat, gfloat *lon);
void create_new_light_instances(pSplDcu dcu);
void on_lcu_selection_changed (GtkTreeSelection *selection, gpointer user_data);
#endif // SMARTSTREETLIGHT_LCU_H_INCLUDED

