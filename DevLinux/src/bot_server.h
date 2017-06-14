#ifndef BOT_SERVER_H_INCLUDED
#define BOT_SERVER_H_INCLUDED

#include "main.h"
#include "bot_utils.h"

enum
{
    SERVER_LOG_SELECT_ALL = 0,
    SERVER_LOG_DISSELECT_ALL
};

enum
{
     bot_SERVER_LOG_POPUP_MENU_SELECT=0,
     bot_SERVER_LOG_POPUP_MENU_DISSELECT,
     bot_SERVER_LOG_POPUP_MENU_SELECT_ALL,
     bot_SERVER_LOG_POPUP_MENU_DISSELECT_ALL,
     bot_SERVER_LOG_POPUP_MENU_DELETE,
     bot_SERVER_LOG_POPUP_MENU_DELETE_MARK,
     bot_SERVER_LOG_POPUP_MENU_DELETE_ALL
};

typedef struct bot_SERVER_LOG_POPUP_MENU
{
    GtkWidget *M_POPUP;
    GtkWidget *M_SELECT;
    GtkWidget *M_DISSELECT;
    GtkWidget *M_SELECT_ALL;
    GtkWidget *M_DISSELECT_ALL;
    GtkWidget *M_DELETE;
    GtkWidget *M_DELETE_MARK;
    GtkWidget *M_DELETE_ALL;

}bot_SERVER_LOG_POPUP_MENU;

typedef struct bot_SERVER_Widgets
{
    GtkTreeView         *server_log_treeview;
	GtkListStore        *server_log_liststore;
    GtkWidget           *bot_server_log_box;
    GtkTreeModelFilter  *server_log_filter;

} bot_SERVER_Widgets;

extern struct bot_SERVER_Widgets *server_widgets;

extern struct bot_USER_LOG_POPUP_MENU *user_log_popup_menu;

gboolean bot_server_log_init(void);

void bot_server_log_finalize(void);

void bot_server_log_show_all(void);

void bot_server_log_popupmenu_show(GdkEventButton *event, gpointer userdata);

void bot_server_log_selection_config(gboolean setSelection, gboolean selectAll);

void bot_user_log_delete_marked_iter();

#endif // BOT_SERVER_H_INCLUDED
