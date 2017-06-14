#ifndef BOT_SCHEDULE_H_INCLUDED
#define BOT_SCHEDULE_H_INCLUDED

#include "main.h"
#include "bot_dcu.h"
//
#define MAX_MINUTE 1440
#define MAX_SCHEDULE_ITEM 10
#define MAX_LIGHT_LEVEL 10

#define ACTIVE_STATUS					0x0
#define ERROR_RF_DCU_STATUS 			(1<<7)
#define ERROR_SYNC_MODE_STATUS 			(1<<8)
#define ERROR_SYNC_LCU_STATUS 			(1<<9)
#define ERROR_SYNC_LINE_STATUS 			(1<<10)
#define ERROR_SCHEDULE_LCU_STATUS 		(1<<11)
#define ERROR_SCHEDULE_LINE_STATUS 		(1<<12)
#define ERROR_LOCK_DCU_STATUS 			(1<<13)
#define ERROR_MEM_STATUS 				(1<<14)
#define MODE_MANUAL_STATUS 				(1<<15)


#define DIV_BRIGHTNESS                  10

const gint PROGRAM_ID_COLUMN            = OBJECT_NUM_COLUMNS;

enum
{
    PROGRAM_LCU_NO_MODE 		    = 0,
    PROGRAM_LCU_SCHEDULE_MODE 		= 1,
	PROGRAM_LCU_MANUAL_MODE			= 2,
	PROGRAM_LCU_OFF_MODE			= 3
};

typedef enum bot_PROGRAM_POPUP_MENU_Enum
{
    bot_PROGRAM_M_ADD = 0,
    bot_PROGRAM_M_SCHEDULE,
    bot_PROGRAM_M_REMOVE,

    bot_PROGRAM_M_NUMBER
} bot_PROGRAM_POPUP_MENU_Enum;
typedef struct _botDaySchedule
{
    gint        Id;
    gint        programId;
    gchar       *name;
    GtkTreeIter iter;
    GSList      *itemlist;
    GSList      *itemlistTmp;
}botDaySchedule;

typedef struct _botDayScheduleItem
{
    gint            Id;
    gint            timeBegin;
    gint            timeOn;
    gint            level;
    botDaySchedule  *parent;
}botDayScheduleItem;
typedef struct bot_PROGRAM_POPUP_MENU
{
    GtkWidget *M_Popup;
    GtkWidget *M_Add;
    GtkWidget *M_Schedule;
    GtkWidget *M_Remove;
}bot_PROGRAM_POPUP_MENU;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum bot_SCHEDULE_POPUP_Enum
{
    bot_SCHEDULE_M_ADD = 0,
    bot_SCHEDULE_M_REMOVE,
    bot_SCHEDULE_M_SCHEDULE,

    bot_SCHEDULE_M_NUMBER
} bot_SCHEDULE_POPUP_Enum;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


typedef struct bot_SCHEDULE_DAY_POPUP_MENU
{
    GtkWidget *M_Popup;
    GtkWidget *M_Add;
    GtkWidget *M_Schedule;
    GtkWidget *M_Remove;
}bot_SCHEDULE_DAY_POPUP_MENU;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct bot_SCHEDULE_LIST_POPUP_MENU
{
    GtkWidget *M_Popup;
    GtkWidget *M_Add;
    GtkWidget *M_Remove;
}bot_SCHEDULE_LIST_POPUP_MENU;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct bot_SCHEDULE_ITEM_POPUP_MENU
{
    GtkWidget *M_Popup;
    GtkWidget *M_Add;
    GtkWidget *M_Remove;
}bot_SCHEDULE_ITEM_POPUP_MENU;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct bot_SCHEDULE_LIST_NAME_POPUP_MENU
{
    GtkWidget *M_Popup;
    GtkWidget *M_Add;
    GtkWidget *M_Remove;
}bot_SCHEDULE_LIST_NAME_POPUP_MENU;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct bot_SCHEDULE_LIST_CONTENT_POPUP_MENU
{
    GtkWidget *M_Popup;
    GtkWidget *M_Add;
    GtkWidget *M_Remove;
}bot_SCHEDULE_LIST_CONTENT_POPUP_MENU;


typedef struct bot_SCHEDULE_TIME_RANGE
{
    gint schedule_item_min_starttime_value;
    gint schedule_item_max_starttime_value;

    gint schedule_item_count;
}bot_SCHEDULE_TIME_RANGE;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


enum
{
    SCHEDULE_MONTH_STORE_MONTH_COLUMN = 0,
    SCHEDULE_MONTH_STORE_NAME_COLUMN,
    SCHEDULE_MONTH_STORE_ID_COLUMN,
    SCHEDULE_MONTH_STORE_MONTH_INT_COLUMN,
    SCHEDULE_MONTH_STORE_SCHEDULE_ID_COLUMN,
    SCHEDULE_MONTH_STORE_COUNT_COLUMNS,
};

enum
{
    ITEM_START_TIME_COLUMN = OBJECT_NUM_COLUMNS,
    ITEM_END_TIME_COLUMN,
    ITEM_BRIGHTNESS_COLUMN,
    ITEM_ID_COLUMN,
    ITEM_COUNT_COLUMNS,
};

enum
{
    PROGRAM_NAME_COL_INDEX = 0,
    PROGRAM_CONTENT_COL_INDEX
};

enum
{
    /* show */
    PROGRAM_DCU_LIST_NAME_COLUMN = 0,
    PROGRAM_DCU_LIST_STATUS_COLUMN,
    PROGRAM_DCU_LIST_RGBA_COLUMN,

    /* not show */
    PROGRAM_DCU_LIST_ZONEID_COLUMN,
    PROGRAM_DCU_LIST_TYPE_COLUMN,

    /* count */
    PROGRAM_DCU_LIST_NUM_COLUMNS
};

/*
    SCHEDULE_NUM_COLUMNS,
    G_TYPE_STRING,      // Thang + name schedule
    G_TYPE_INT,         // starttime
    G_TYPE_INT,         // ontine
    G_TYPE_INT,         // level
    G_TYPE_INT,         // month
    G_TYPE_INT,         // program id
    G_TYPE_INT,         // day schedule id
    G_TYPE_INT,         // list schedule id
    G_TYPE_STRING,      // list schedule name
    G_TYPE_INT,         // schedule id
    G_TYPE_INT);        // type column
*/
enum /** DATE SCHEDULE Enum**/
{
    SCHEDULE_NAME_COLUMN = 0,

    SCHEDULE_STARTTIME_COLUMN,
    SCHEDULE_TIMEON_COLUMN,
    SCHEDULE_LEVEL_COLUMN,

    SCHEDULE_MONTH_COLUMN,
    SCHEDULE_PROGRAM_ID_COLUMN,
    SCHEDULE_DAY_ID_COLUMN,
    SCHEDULE_LIST_ID_COLUMN,
    SCHEDULE_LIST_NAME_COLUMN,
    SCHEDULE_ITEM_ID_COLUMN,

    SCHEDULE_TYPE_COLUMN,

    SCHEDULE_NUM_COLUMNS
};

enum SCHEDULE_COMLUMN_TYPE_Enum
{
    SCHEDULE_MONTH_COL_INDEX = 0,
    SCHEDULE_NAME_COL_INDEX,
    SCHEDULE_CONTENT_COL_INDEX
};


enum /** ITEM SCHEDULE Enum**/
{
    ITEM_SCHEDULE_NAME_COLUMN = 0,

    ITEM_SCHEDULE_STARTTIME_COLUMN,
    ITEM_SCHEDULE_TIMEON_COLUMN,
    ITEM_SCHEDULE_LEVEL_COLUMN,

    ITEM_SCHEDULE_PROGRAM_ID_COLUMN,
    ITEM_SCHEDULE_LIST_ID_COLUMN,
    ITEM_SCHEDULE_ID_COLUMN,

    ITEM_SCHEDULE_TYPE_COLUMN,

    ITEM_SCHEDULE_NUM_COLUMNS
};

enum /** NEW ITEM SCHEDULE Enum**/
{
    NEW_ITEM_SCHEDULE_STARTTIME_COLUMN = 0,
    NEW_ITEM_SCHEDULE_TIMEON_COLUMN,
    NEW_ITEM_SCHEDULE_LEVEL_COLUMN,

    NEW_ITEM_SCHEDULE_STARTTIME_INT_COLUMN,
    NEW_ITEM_SCHEDULE_TIMEON_INT_COLUMN,
    NEW_ITEM_SCHEDULE_LEVEL_INT_COLUMN,
    NEW_ITEM_SCHEDULE_POINTER_COLUMN,
    NEW_ITEM_SCHEDULE_NUM_COLUMNS
};


typedef struct bot_SCHEDULE_ITEM_Widgets
{
    GtkWidget	*schedule_item_name_entry;

    GtkWidget	*schedule_item_content_treeview;
    GtkListStore *schedule_item_content_liststore;

    GtkWidget	*schedule_item_commit_button;

    GtkScale   *schedule_item_starttime_scale;
    GtkAdjustment   *schedule_item_starttime_adjustment;
    GtkWidget   *schedule_item_starttime_label;

    GtkScale   *schedule_item_timeon_scale;
    GtkAdjustment   *schedule_item_timeon_adjustment;
    GtkWidget   *schedule_item_timeon_label;

    GtkScale   *schedule_item_level_scale;
    GtkAdjustment   *schedule_item_level_adjustment;
    GtkWidget   *schedule_item_level_label;

    GtkWidget   *schedule_item_min_starttime_value;

} bot_SCHEDULE_ITEM_Widgets;


//extern GtkTreeView *program_tree_view;
//extern GtkListStore *program_list_store;

//extern struct bot_PROGRAM_POPUP_MENU *program_info_popup_menu;
//extern struct bot_SCHEDULE_POPUP_MENU *schedule_info_popup_menu;

//extern GtkTreeView *schedule_tree_view;
//extern GtkListStore *schedule_list_store;

//extern GtkListStore *combobox_hour_list_store;
//extern GtkListStore *combobox_minute_list_store;

//extern struct bot_Schedule_Widgets	*schedule_widgets;





typedef struct bot_PROGRAM_Widgets
{
    GtkListStore *program_day_schedule_liststore;

    GtkTreeView  *program_month_schedule_treeview;
    GtkTreeStore *program_month_schedule_treestore;

    GtkTreeView *program_year_schedule_treeview;
    GtkTreeStore *program_year_schedule_treestore;

    GtkListStore *program_month_schedule_new_liststore;
    GtkComboBoxText *program_month_schedule_new_combobox;

    GtkTreeView  *program_item_schedule_treeview;
    GtkTreeStore *program_item_schedule_treestore;

    GtkListStore *day_schedule_liststore_change;
    GtkComboBox *list_schedule_combobox_change;

    GtkTreeView  *program_dcu_list_treeview;
    GtkTreeStore *program_dcu_list_treestore;
    GtkTreeModelFilter  *program_dcu_list_filter;

} bot_PROGRAM_Widgets;



extern struct bot_PROGRAM_Widgets	*program_widgets;

extern struct bot_SCHEDULE_ITEM_Widgets	*schedule_item_widgets;


gboolean bot_program_schedule_init(void);

void bot_program_show_all(void);

void bot_program_schedule_finalize(void);

void bot_program_tree_store_clean(void);

void bot_program_fill_infomation(const gchar *program_name, gint program_id, gint zone_id, GtkTreeIter *parent_iter);

void bot_program_year_show_specific(gint program_id);


void bot_day_schedule_fill_infomation(gint day_schedule_id,
                                                   gint list_schedule_id,
                                                   gint program_id,
                                                   gint month);

void bot_schedule_fill_infomation(gint store_index,
                                               GtkTreeIter *parent_iter,
                                               gint schedule_id,
                                               gint schedule_listschedule_id,
                                               gint schedule_starttime,
                                               gint schedule_ontime,
                                               gint schedule_level);


void bot_schedule_name_fill_infomations(GtkTreeIter *parent_iter, gint listschedule_id, gchar *listschedule_name);

void bot_schedule_item_fill_infomations(gint listschedule_id, gchar *listschedule_name, gint listschedule_programid);

void bot_program_popup_menu_show(GtkTreeView *treeview, GdkEventButton *event, gpointer userdata);

void bot_schedule_day_popup_menu_show(GtkTreeView *treeview, GdkEventButton *event, gpointer userdata);

void bot_schedule_list_popup_menu_show(GtkTreeView *treeview, GdkEventButton *event, gpointer userdata);

void bot_schedule_item_popup_menu_show(GtkTreeView *treeview, GdkEventButton *event, gpointer userdata);

void bot_schedule_item_name_popup_menu_show(GtkTreeView *treeview, GdkEventButton *event, gpointer userdata);

void bot_schedule_item_content_popup_menu_show(GtkTreeView *treeview, GdkEventButton *event, gpointer userdata);

void bot_program_fill_program_of_zone(botZone *zone, GtkTreeIter *parent);

void bot_program_fill_infomation_dcu_list(gchar *dcu_id, gint dcu_status);

void bot_program_fill_infomation_lcu_list(gchar *lcu_id, gint lcu_status, gint lcu_mode, GtkTreeIter *parent_iter);
#if 0





















static gboolean bot_schedule_create_new(void);



void bot_schedule_liststore_clean(void);

//
//void bot_schedule_fill_infomation(gchar *schedule_month,
//                                               gchar *schedule_starttime,
//                                               gchar *schedule_timeon,
//                                               gchar *schedule_level,
//                                               gchar *schedule_program_name);

//void bot_program_popup_menu_show(GtkTreeView *treeview, GdkEventButton *event, gpointer userdata);

void bot_schedule_popup_menu_show(GtkTreeView *treeview, GdkEventButton *event, gpointer userdata);

//void bot_program_change(const gchar *dcu_id);

gchar *bot_program_get_active_name(void);

void bot_program_set_value(gchar *program_name);

#endif // 0

#endif // BOT_SCHEDULE_H_INCLUDED

