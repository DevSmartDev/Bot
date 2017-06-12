#ifndef SMARTSTREETLIGHT_SERVER_H_INCLUDED
#define SMARTSTREETLIGHT_SERVER_H_INCLUDED

#include "main.h"
#include "smartstreetlight_utils.h"

enum
{
    SERVER_LOG_SELECT_ALL = 0,
    SERVER_LOG_DISSELECT_ALL
};

enum
{
     SPL_SERVER_LOG_POPUP_MENU_SELECT=0,
     SPL_SERVER_LOG_POPUP_MENU_DISSELECT,
     SPL_SERVER_LOG_POPUP_MENU_SELECT_ALL,
     SPL_SERVER_LOG_POPUP_MENU_DISSELECT_ALL,
     SPL_SERVER_LOG_POPUP_MENU_DELETE,
     SPL_SERVER_LOG_POPUP_MENU_DELETE_MARK,
     SPL_SERVER_LOG_POPUP_MENU_DELETE_ALL
};

typedef struct SPL_SERVER_LOG_POPUP_MENU
{
    GtkWidget *M_POPUP;
    GtkWidget *M_SELECT;
    GtkWidget *M_DISSELECT;
    GtkWidget *M_SELECT_ALL;
    GtkWidget *M_DISSELECT_ALL;
    GtkWidget *M_DELETE;
    GtkWidget *M_DELETE_MARK;
    GtkWidget *M_DELETE_ALL;

}SPL_SERVER_LOG_POPUP_MENU;

typedef struct SPL_SERVER_Widgets
{
    GtkTreeView         *server_log_treeview;
	GtkListStore        *server_log_liststore;
    GtkWidget           *spl_server_log_box;
    GtkTreeModelFilter  *server_log_filter;

} SPL_SERVER_Widgets;

extern struct SPL_SERVER_Widgets *server_widgets;

extern struct SPL_USER_LOG_POPUP_MENU *user_log_popup_menu;

gboolean smartstreetlight_server_log_init(void);

void smartstreetlight_server_log_finalize(void);

void smartstreetlight_server_log_show_all(void);

void spl_server_log_popupmenu_show(GdkEventButton *event, gpointer userdata);

void spl_server_log_selection_config(gboolean setSelection, gboolean selectAll);

void spl_user_log_delete_marked_iter();

#endif // SMARTSTREETLIGHT_SERVER_H_INCLUDED
