#ifndef BOT_UI_METHOD_H_INCLUDED
#define BOT_UI_METHOD_H_INCLUDED

#include "main.h"
#include "pthread.h"

typedef struct bot_WAITING_Widgets
{
    GtkWidget *window;
    GtkWidget *spinner;
    gint       is_supports_alpha;

} bot_WAITING_Widgets;

extern pthread_mutex_t waiting_show_mutex;

extern struct bot_WAITING_Widgets *bot_waiting_widgets;

void bot_clear_tree_store(GtkTreeModel *model);

void bot_clear_list_store(GtkTreeModel *model);

void bot_set_private_css_provide(CSSTYPE type, GtkWidget* widget);

void bot_run_notification_dialog(const gchar *content_text);

gboolean bot_get_current_select_iter(GtkTreeView *treeview, GtkTreeModel **model, GtkTreeIter *iter);

void bot_notebook_tab_hide_show(GtkNotebook *notebook, gint pagenumber, gboolean is_show);

gboolean bot_ui_methods_init(void);

void bot_ui_methods_finalize(void);

void bot_waiting_hide();

void bot_waiting_show();
#endif // BOT_UI_METHOD_H_INCLUDED
