#ifndef BOT_LINE_H_INCLUDED
#define BOT_LINE_H_INCLUDED

#include "main.h"
#include "bot_utils.h"
#include "bot_callback.h"

typedef enum bot_LINE_POPUP_MENU_Enum
{
    bot_LINE_M_ADD = 0,
    bot_LINE_M_REMOVE,
    bot_LINE_M_REMOVE_ALL,

    bot_LINE_M_NUMBER
} bot_LINE_POPUP_MENU_Enum;

typedef struct bot_LINE_POPUP_MENU
{
    GtkWidget *M_Popup;
    GtkWidget *M_Add;
    GtkWidget *M_Remove;
    GtkWidget *M_Remove_all;
}bot_LINE_POPUP_MENU;


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

extern struct bot_LINE_POPUP_MENU *line_info_popup_menu;


void bot_line_fill_infomation(gint line_name,
                                           gchar *line_dcuid,
                                           gchar *line_status,
                                           gchar *line_note,
                                           gchar *line_mode,
                                           gchar *line_ison,
                                           gchar *line_current
                                           );

gboolean bot_line_info_init(void);

void bot_line_show_list(gchar *dcu_id);

void bot_line_liststore_clean(void);

void bot_line_popup_menu_show(GtkTreeView *treeview, GdkEventButton *event, gpointer userdata);
#endif // BOT_LINE_H_INCLUDED
