#ifndef BOT_LCU_H_INCLUDED
#define BOT_LCU_H_INCLUDED

#include "main.h"
#include "mapviewer.h"
#include "bot_dcu.h"
#include "bot_utils.h"
#include "bot_callback.h"
#include "bot_database.h"
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
typedef struct _botLcu
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
    pbotDcu         parent;
    OsmGpsMapImage  *icon; /**Be careful when use this component because it have been free usually*/

}botLcu, *pbotLcu;


typedef struct _botLcuLog
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
}botLcuLog, *pbotLcuLog;
extern GSList *LcuLogList;

/*
    gint bot_get_log_lcu_nofree_execute(botSoap* bot_soap, gchar * lcu_id, gchar * time_from,
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

typedef struct _botLcuPopup
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
}botLcuPopup, *pbotLcuPopup;


typedef enum bot_LCU_POPUP_MENU_Enum
{
    bot_LCU_M_ADD = 0,
    bot_LCU_M_ADD_FROM_FILE,
    bot_LCU_M_CONTROL,
    bot_LCU_M_REMOVE,
    bot_LCU_M_REMOVE_ALL,
    bot_LCU_M_EDIT,
    bot_LCU_M_LOCATION,
    bot_LCU_M_CHART,
    bot_LCU_M_NUMBER,
} bot_LCU_POPUP_MENU_Enum;


enum
{
    DIbotAY_FOLLOW_DCU =0,
    DIbotAY_FOLLOW_ZONE,
    DIbotAY_ALL,

};

enum
{
    LIGHT_ID = 0,
    LIGHT_POINTER,
    LIGHT_VISIBLE,
    LIGHT_COUNT,
};


typedef enum bot_LCU_MODE_Enum
{
    bot_LCU_ScheduleMode = 1,
    bot_LCU_ManualMode   = 2,
    bot_LCU_OffMode      = 3

}bot_LCU_MODE_Enum;



extern GtkComboBox *cbb_light_spl;
extern pbotLcu lastSelectedLcu;
extern pbotLcuPopup lcuPopupMenu;


typedef struct bot_LCU_Widgets
{
    GtkAdjustment	    *lcu_adjustment_light_level;
	GtkWidget	        *lcu_scale_light_level;
	GtkTreeView         *lcu_control_treeview_schedule;
	GtkListStore        *lcu_control_liststore_schedule;

} bot_LCU_Widgets;

extern struct bot_LCU_Widgets *lcu_widgets;

void bot_lcu_fill_infomation(gchar *lcu_name,
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
    pbotLcu lcu;
    gint isOn;
    gint mode;
    gint scale;
    gboolean istemp;
    gint rsp_lcu_list_size;
    ns1__LCU_USCOREINFO_USCOREType **rsp_lcu_list;
};


void bot_lcu_show_list(gchar *dcu_id);

void bot_lcu_liststore_clean();

void bot_lcu_dialog_show(GtkTreeModel *model, GtkTreeIter iter);

gboolean bot_lcu_info_init(void);

void bot_lcu_finalize(void);

void bot_lcu_popup_menu_show(GtkTreeView *treeview, GdkEventButton *event, gpointer userdata);

gchar * bot_lcu_get_status_name(gint status);

gchar * bot_lcu_get_mode_name(gint mode);

void bot_lcu_control_mode_combobox_change(void);

void bot_lcu_control_schedule_fill(gchar *schedule_month,
                                                gchar *schedule_starttime,
                                                gchar *schedule_timeon,
                                                gchar *schedule_level,
                                                gchar *schedule_program_name);

void bot_get_all_light();
void light_update_information(pbotLcu lcu, gboolean setmapcenter);
void popup_light_view_show(GdkEventButton *event);

GdkPixbuf *bot_get_light_icon(pbotLcu lcu, gboolean selected, gboolean iszone);
void bot_lcu_remove_iter_and_image(pbotDcu dcu, pbotLcu lcu);
void bot_lcu_free(pbotLcu lcu);
gboolean bot_light_add_new_request();
gboolean bot_light_chart_show(pbotLcu lcu_log);
gboolean bot_light_edit(pbotLcu lcu);
gboolean bot_lcu_popup_menu_control(pbotLcu lcu);
void bot_light_remove_request(pbotLcu lcu);
pbotLcu bot_lcu_init();
pbotLcuLog bot_lcu_log_init();
void bot_lcu_log_free(pbotLcuLog lcu_log);
void bot_lcu_add_image(pbotLcu lcu, GdkPixbuf *buf, gfloat *lat, gfloat *lon);
void create_new_light_instances(pbotDcu dcu);
void on_lcu_selection_changed (GtkTreeSelection *selection, gpointer user_data);
#endif // BOT_LCU_H_INCLUDED

