#ifndef SMARTSTREETLIGHT_DCU_H_INCLUDED
#define SMARTSTREETLIGHT_DCU_H_INCLUDED

#include "main.h"
#include "smartstreetlight_utils.h"
#include "smartstreetlight_callback.h"
#include "smartstreetlight_ui_method.h"


typedef enum SPL_DCU_POPUP_MENU_Enum
{
    SPL_DCU_M_ADD = 0,
    SPL_DCU_M_EDIT,
    SPL_DCU_M_LOG,
    SPL_DCU_M_SCHEDULE,
    SPL_DCU_M_REMOVE,
    SPL_DCU_M_REMOVE_ALL,

    SPL_DCU_M_NUMBER
} SPL_DCU_POPUP_MENU_Enum;

typedef struct SPL_DCU_POPUP_MENU
{
    GtkWidget *M_Popup;
    GtkWidget *M_Add;
    GtkWidget *M_Edit;
    GtkWidget *M_Log;
    GtkWidget *M_Schedule;
    GtkWidget *M_Remove;
    GtkWidget *M_Remove_all;
}SPL_DCU_POPUP_MENU;

enum SPL_DCU_MODE_Enum
{
    SPL_DCU_UnknownMode = 0,
    SPL_DCU_WirelessMode,
    SPL_DCU_LineMode,
    SPL_DCU_Init
};

enum SPL_DCU_STATUS_Enum
{
    SPL_DCU_Active = 0,
    SPL_DCU_Unactive
};

enum SPL_DCU_TREE_STORE_TYPE_ROW_Enum
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



typedef struct SPL_DCU_Widgets
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

} SPL_DCU_Widgets;

extern struct SPL_DCU_Widgets *dcu_widgets;


extern GtkTreeView *dcu_info_tree_view;

extern GtkListStore *dcu_info_list_store;

extern struct SPL_DCU_POPUP_MENU *dcu_info_popup_menu;

/** ***************************************************************************************************** **/


gboolean smartstreetlight_dcu_info_init(void);

//void smartstreetlight_dcu_get_info_form_sql(MYSQL_RES *data);

void smartstreetlight_dcu_finalize(void);

void smartstreetlight_dcu_show_specific_info(gchar *dcu_id, gchar *dcu_phone, gchar *dcu_gps, gchar *dcu_address,
                                             gchar *dcu_note, gchar *dcu_mode, gchar *dcu_status,
                                             gchar *dcu_lcu_program, gchar *dcu_line_program,
                                             gint dcu_zone_id, gchar *dcu_zone_name);

void smartstreetlight_dcu_show_all();

void smartstreetlight_dcu_choose_time(void);

void smartstreetlight_dcu_update(void);

void smartstreetlight_dcu_liststore_clean(void);

void smartstreetlight_dcu_fill_infomation(GtkTreeIter *zone_tree_iter,
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

gchar * smartstreetlight_get_mode_name(SPL_DCU_MODE_Enum index);


void smartstreetlight_dcu_popup_menu_show(GtkTreeView *treeview, GdkEventButton *event, gpointer userdata);

gboolean smartstreetlight_dcu_set_program(const gint zone_id, gchar *dcu_id, gchar *new_program_name);

void smartstreetlight_show_button_combobox(void);

void smartstreetlight_hide_button_combobox(void);

void smartstreetlight_dcu_schedule_update(void);

void smartstreetlight_dcu_info_edit(void);

void smartstreetlight_dcu_log_connect_log_liststore_clean(void);
void smartstreetlight_dcu_log_dcu_log_liststore_clean(void);
void smartstreetlight_dcu_log_lcu_log_liststore_clean(void);
void smartstreetlight_dcu_log_line_log_liststore_clean(void);


void smartstreetlight_dcu_log_connect_log_fill_infomation(const gint event_id,
                                                          const gchar *event_dcu_id,
                                                          const gint event_type,
                                                          const gchar *event_content,
                                                          const gchar *event_time);

void smartstreetlight_dcu_log_dcu_log_fill_infomation(const gint event_id,
                                                      const gchar *event_dcu_id,
                                                      const gint event_type,
                                                      const gchar *event_content,
                                                      const gchar *event_time);

void smartstreetlight_dcu_log_lcu_log_fill_infomation(const gint event_id,
                                                      const gchar *event_dcu_id,
                                                      const gint event_type,
                                                      const gchar *event_content,
                                                      const gchar *event_time);

void smartstreetlight_dcu_log_line_log_fill_infomation(const gint event_id,
                                                      const gchar *event_dcu_id,
                                                      const gint event_type,
                                                      const gchar *event_content,
                                                      const gchar *event_time);

void smartstreetlight_zone_fill_infomation(const gint zone_id,
                                           const gchar *zone_name,
                                           const gchar *zone_note);
#endif // SMARTSTREETLIGHT_DCU_H_INCLUDED
