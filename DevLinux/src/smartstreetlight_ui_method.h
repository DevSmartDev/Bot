#ifndef SMARTSTREETLIGHT_UI_METHOD_H_INCLUDED
#define SMARTSTREETLIGHT_UI_METHOD_H_INCLUDED

#include "main.h"
#include "pthread.h"

typedef struct SPL_WAITING_Widgets
{
    GtkWidget *window;
    GtkWidget *spinner;
    gint       is_supports_alpha;

} SPL_WAITING_Widgets;

extern pthread_mutex_t waiting_show_mutex;

extern struct SPL_WAITING_Widgets *spl_waiting_widgets;

void smartstreetlight_clear_tree_store(GtkTreeModel *model);

void smartstreetlight_clear_list_store(GtkTreeModel *model);

void smartstreetlight_set_private_css_provide(CSSTYPE type, GtkWidget* widget);

void smartstreetlight_run_notification_dialog(const gchar *content_text);

gboolean spl_get_current_select_iter(GtkTreeView *treeview, GtkTreeModel **model, GtkTreeIter *iter);

void spl_notebook_tab_hide_show(GtkNotebook *notebook, gint pagenumber, gboolean is_show);

gboolean spl_ui_methods_init(void);

void spl_ui_methods_finalize(void);

void spl_waiting_hide();

void spl_waiting_show();
#endif // SMARTSTREETLIGHT_UI_METHOD_H_INCLUDED
