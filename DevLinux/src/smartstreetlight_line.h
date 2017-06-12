#ifndef SMARTSTREETLIGHT_LINE_H_INCLUDED
#define SMARTSTREETLIGHT_LINE_H_INCLUDED

#include "main.h"
#include "smartstreetlight_utils.h"
#include "smartstreetlight_callback.h"

typedef enum SPL_LINE_POPUP_MENU_Enum
{
    SPL_LINE_M_ADD = 0,
    SPL_LINE_M_REMOVE,
    SPL_LINE_M_REMOVE_ALL,

    SPL_LINE_M_NUMBER
} SPL_LINE_POPUP_MENU_Enum;

typedef struct SPL_LINE_POPUP_MENU
{
    GtkWidget *M_Popup;
    GtkWidget *M_Add;
    GtkWidget *M_Remove;
    GtkWidget *M_Remove_all;
}SPL_LINE_POPUP_MENU;


enum
{
    LINE_CHECKBOX_COLUMN = 0,
    LINE_ID_COLUMN,
    LINE_DCUID_COLUMN,
    LINE_STATUS_COLUMN,
    LINE_NOTE_COLUMN,
    LINE_MODE_COLUMN,
    LINE_ISON_COLUMN,
    LINE_CURRENT_COLUMN,
    LINE_NUM_COLUMNS
};

extern GtkTreeView *line_info_tree_view;
extern GtkListStore *line_info_list_store;

extern struct SPL_LINE_POPUP_MENU *line_info_popup_menu;


void smartstreetlight_line_fill_infomation(gint line_name,
                                           gchar *line_dcuid,
                                           gchar *line_status,
                                           gchar *line_note,
                                           gchar *line_mode,
                                           gchar *line_ison,
                                           gchar *line_current
                                           );

gboolean smartstreetlight_line_info_init(void);

void smartstreetlight_line_show_list(gchar *dcu_id);

void smartstreetlight_line_liststore_clean(void);

void smartstreetlight_line_popup_menu_show(GtkTreeView *treeview, GdkEventButton *event, gpointer userdata);
#endif // SMARTSTREETLIGHT_LINE_H_INCLUDED
