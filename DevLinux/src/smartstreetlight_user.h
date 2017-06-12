#ifndef SMARTSTREETLIGHT_USER_H_INCLUDED
#define SMARTSTREETLIGHT_USER_H_INCLUDED

#include "main.h"
#include "smartstreetlight_utils.h"

typedef struct SPL_USER_Widgets
{
    GtkTreeView         *user_log_treeview;
    GtkTreeModelFilter  *user_log_filter;
	GtkListStore        *user_log_liststore;
	GtkWidget           *spl_user_log_box;

} SPL_USER_Widgets;


enum
{
    EVENT_LOG_IS_ID_COLUMN = 0,
    EVENT_LOG_IS_CONTENT_COLUMN,
    EVENT_LOG_IS_TIME_COLUMN,
    EVENT_LOG_IS_SELECT_COLUMN,
    EVENT_LOG_IS_DELETE_COLUMN,
    EVENT_LOG_NUM_COLUMNS,
};

enum
{
    USER_LOG_SELECT_ALL = 0,
    USER_LOG_DISSELECT_ALL
};

enum
{
     SPL_USER_LOG_POPUP_MENU_SELECT = 0,
     SPL_USER_LOG_POPUP_MENU_DISSELECT,
     SPL_USER_LOG_POPUP_MENU_SELECT_ALL,
     SPL_USER_LOG_POPUP_MENU_DISSELECT_ALL,
     SPL_USER_LOG_POPUP_MENU_DELETE,
     SPL_USER_LOG_POPUP_MENU_DELETE_MARK,
     SPL_USER_LOG_POPUP_MENU_DELETE_ALL
};

typedef struct SPL_USER_LOG_POPUP_MENU
{
    GtkWidget *M_POPUP;
    GtkWidget *M_SELECT;
    GtkWidget *M_DISSELECT;
    GtkWidget *M_SELECT_ALL;
    GtkWidget *M_DISSELECT_ALL;
    GtkWidget *M_DELETE;
    GtkWidget *M_DELETE_MARK;
    GtkWidget *M_DELETE_ALL;

}SPL_USER_LOG_POPUP_MENU;


extern struct SPL_USER_Widgets *user_widgets;

extern struct SPL_USER_LOG_POPUP_MENU *user_log_popup_menu;

gboolean smartstreetlight_user_log_init(void);

void smartstreetlight_user_log_finalize(void);

void smartstreetlight_user_log_show_all(void);

void spl_event_log_delete_marked_iter(SplDataObject *obj);

void spl_event_log_selection_config(SplDataObject *obj, gboolean setSelection, gboolean selectAll);

gboolean log_row_visible (GtkTreeModel *model, GtkTreeIter *iter, gpointer p);

void spl_log_delete_row_marked(GtkListStore *store, SplLogPaging *_paging);

void on_event_log_renderer_toggled (GtkCellRendererToggle *cell_renderer, gchar *path, gpointer user_data);

void on_event_log_btn_back_clicked(GtkButton *button, gpointer   user_data);

void on_event_log_btn_next_clicked(GtkButton *button, gpointer   user_data);

gboolean on_image_selection_click(GtkImage *image, gpointer   user_data);

void checkbox_set_image(const gchar* imageId, gint selected);
#endif // SMARTSTREETLIGHT_USER_H_INCLUDED
