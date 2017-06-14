#ifndef BOT_DCU_H_INCLUDED
#define BOT_DCU_H_INCLUDED

#include "main.h"
#include "bot_utils.h"
#include "bot_callback.h"
#include "bot_ui_method.h"


typedef enum bot_DCU_POPUP_MENU_Enum
{
    bot_DCU_M_ADD = 0,
    bot_DCU_M_EDIT,
    bot_DCU_M_LOG,
    bot_DCU_M_SCHEDULE,
    bot_DCU_M_REMOVE,
    bot_DCU_M_REMOVE_ALL,

    bot_DCU_M_NUMBER
} bot_DCU_POPUP_MENU_Enum;

typedef struct bot_DCU_POPUP_MENU
{
    GtkWidget *M_Popup;
    GtkWidget *M_Add;
    GtkWidget *M_Edit;
    GtkWidget *M_Log;
    GtkWidget *M_Schedule;
    GtkWidget *M_Remove;
    GtkWidget *M_Remove_all;
}bot_DCU_POPUP_MENU;

enum bot_DCU_MODE_Enum
{
    bot_DCU_UnknownMode = 0,
    bot_DCU_WirelessMode,
    bot_DCU_LineMode,
    bot_DCU_Init
};

enum bot_DCU_STATUS_Enum
{
    bot_DCU_Active = 0,
    bot_DCU_Unactive
};

enum bot_DCU_TREE_STORE_TYPE_ROW_Enum
{
    DCU_TREE_STORE_ZONE_TYPE = 0,
    DCU_TREE_STORE_DCU_TYPE
};


/**
        DCU_ZONE_NUM_COLUMNS,
        G_TYPE_STRING,  // name zone + dcu id
        G_TYPE_STRING,  // phone
        G_TYPE_STRING,  // gps
        G_TYPE_STRING,  // address
        G_TYPE_STRING,  // note
        G_TYPE_STRING,  // mode
        G_TYPE_STRING,  // status
        G_TYPE_INT,     // current schedule id
        G_TYPE_INT,     // program id
        G_TYPE_INT,     // zone_id
        G_TYPE_STRING,  // zone_name
        G_TYPE_STRING,  // zone_note
        G_TYPE_INT);    // column_type
**/

enum
{
    DCU_ZONE_NAME_COLUMN = 0,
    DCU_PHONE_COLUMN,
    DCU_GPS_COLUMN,
    DCU_ADDRESS_COLUMN,
    DCU_NOTE_COLUMN,
    DCU_MODE_COLUMN,
    DCU_STATUS_COLUMN,
    DCU_CURR_SCHEDULE_COLUMN,
    DCU_PROGRAM_COLUMN,
    ZONE_ID_COLUMN,
    ZONE_NAME_COLUMN,
    ZONE_NOTE_COLUMN,
    TYPE_ROW_COMLUMN,
    DCU_ZONE_NUM_COLUMNS
};



typedef struct bot_DCU_Widgets
{
    GtkTreeView         *dcu_log_connect_treeview;
	GtkListStore        *dcu_log_connect_liststore;
	GtkTreeView         *dcu_log_dcu_treeview;
	GtkListStore        *dcu_log_dcu_liststore;
	GtkTreeView         *dcu_log_lcu_treeview;
	GtkListStore        *dcu_log_lcu_liststore;
	GtkTreeView         *dcu_log_line_treeview;
	GtkListStore        *dcu_log_line_liststore;
	GtkTreeStore        *dcu_info_tree_store;

} bot_DCU_Widgets;

extern struct bot_DCU_Widgets *dcu_widgets;


extern GtkTreeView *dcu_info_tree_view;

extern GtkListStore *dcu_info_list_store;

extern struct bot_DCU_POPUP_MENU *dcu_info_popup_menu;

/** ***************************************************************************************************** **/


gboolean bot_dcu_info_init(void);

//void bot_dcu_get_info_form_sql(MYSQL_RES *data);

void bot_dcu_finalize(void);

void bot_dcu_show_specific_info(gchar *dcu_id, gchar *dcu_phone, gchar *dcu_gps, gchar *dcu_address,
                                             gchar *dcu_note, gchar *dcu_mode, gchar *dcu_status,
                                             gchar *dcu_lcu_program, gchar *dcu_line_program,
                                             gint dcu_zone_id, gchar *dcu_zone_name);

void bot_dcu_show_all();

void bot_dcu_choose_time(void);

void bot_dcu_update(void);

void bot_dcu_liststore_clean(void);

void bot_dcu_fill_infomation(GtkTreeIter *zone_tree_iter,
                                          gchar *dcu_name,
                                           gchar *dcu_phone,
                                           gchar *dcu_gps,
                                           gchar *dcu_address,
                                           gchar *dcu_note,
                                           gchar *dcu_mode,
                                           gchar *dcu_status,
                                           gint dcu_curr_schedule,
                                           gint dcu_program,
                                           gint dcu_zoneid);

gchar * bot_get_mode_name(bot_DCU_MODE_Enum index);


void bot_dcu_popup_menu_show(GtkTreeView *treeview, GdkEventButton *event, gpointer userdata);

gboolean bot_dcu_set_program(const gint zone_id, gchar *dcu_id, gchar *new_program_name);

void bot_show_button_combobox(void);

void bot_hide_button_combobox(void);

void bot_dcu_schedule_update(void);

void bot_dcu_info_edit(void);

void bot_dcu_log_connect_log_liststore_clean(void);
void bot_dcu_log_dcu_log_liststore_clean(void);
void bot_dcu_log_lcu_log_liststore_clean(void);
void bot_dcu_log_line_log_liststore_clean(void);


void bot_dcu_log_connect_log_fill_infomation(const gint event_id,
                                                          const gchar *event_dcu_id,
                                                          const gint event_type,
                                                          const gchar *event_content,
                                                          const gchar *event_time);

void bot_dcu_log_dcu_log_fill_infomation(const gint event_id,
                                                      const gchar *event_dcu_id,
                                                      const gint event_type,
                                                      const gchar *event_content,
                                                      const gchar *event_time);

void bot_dcu_log_lcu_log_fill_infomation(const gint event_id,
                                                      const gchar *event_dcu_id,
                                                      const gint event_type,
                                                      const gchar *event_content,
                                                      const gchar *event_time);

void bot_dcu_log_line_log_fill_infomation(const gint event_id,
                                                      const gchar *event_dcu_id,
                                                      const gint event_type,
                                                      const gchar *event_content,
                                                      const gchar *event_time);

void bot_zone_fill_infomation(const gint zone_id,
                                           const gchar *zone_name,
                                           const gchar *zone_note);
#endif // BOT_DCU_H_INCLUDED
