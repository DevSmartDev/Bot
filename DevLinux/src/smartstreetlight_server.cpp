#include "smartstreetlight_server.h"
#include "smartstreetlight_soap.h"
#include "smartstreetlight_ui_method.h"
#include "smartstreetlight_login.h"
#include "smartstreetlight_log.h"
#include "smartstreetlight_error.h"
#include "smartstreetlight_user.h"
#include "smartstreetlight_utils.h"

struct SPL_SERVER_Widgets *server_widgets = NULL;

struct SPL_SERVER_LOG_POPUP_MENU *server_log_popup_menu = NULL;

static gboolean smartstreetlight_server_log_treeview_init(void);
static gboolean smartstreetlight_server_log_liststore_init(void);
static gboolean smartstreetlight_server_log_popup_menu_init(void);
static gboolean smartstreetlight_server_log_callback_init(void);
static void smartstreetlight_server_log_fill_infomation(gint id, gchar *content, gchar *time, gboolean readed);
static void on_server_log_button_clicked (GtkButton *button, gpointer user_data);
static void spl_server_log_set_selection_all(gboolean is_select);
static void on_server_log_renderer_toggled (GtkCellRendererToggle *cell_renderer,
                                            gchar *path,
                                            gpointer user_data);
static void spl_server_log_popupmenu_clicked(GtkWidget *popup_menu_item, gpointer userdata);

static gboolean on_spl_server_log_treeview_clicked (GtkTreeView *treeview,
                                    GdkEventButton     *event,
                                    gpointer           userdata);
static void spl_server_log_selection_toggle();
static void spl_server_log_delete_one_item();
static void spl_server_log_delete_mark_item();
static void spl_server_log_delete_all_item();

#define SERVER_IMAGE_ID "server_image_checkbox"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum
{
    SERVER_LOG_READED_COLUMN = EVENT_LOG_NUM_COLUMNS,
    SERVER_LOG_NUM_COLUMNS
};
static SplLogPaging paging  = {1, 1, 0, FALSE};

static SplDataObject ObjData = {NULL, NULL, &paging, NULL};

static void spl_serverlog_update_information()
{
    gchar *curStr = g_strdup_printf("%d-%d", paging.minIndex, paging.maxIndex);
    gtk_label_set_text(GTK_LABEL(SPL_OBJECT("lb_serverlog_cur")),curStr);
    gchar *total = g_strdup_printf("%d", paging.totalItem);
    gtk_label_set_text(GTK_LABEL(SPL_OBJECT("lb_serverlog_total")), (gchar*)total);
    checkbox_set_image(SERVER_IMAGE_ID, paging.selected);
    if(paging.maxIndex > paging.totalItem)
        paging.maxIndex = paging.totalItem;
    gboolean min = (paging.curPage != 1);
    gboolean max = (paging.curPage != ((paging.totalItem / MAX_PAGE_VIEW_NUM) + 1));
    gtk_widget_set_sensitive(GTK_WIDGET(SPL_OBJECT("btn_serverlog_back")), min);
    gtk_widget_set_sensitive(GTK_WIDGET(SPL_OBJECT("btn_serverlog_next")), max);

}

static gboolean smartstreetlight_server_log_treeview_init(void)
{
    server_widgets->server_log_treeview = GTK_TREE_VIEW(SPL_OBJECT("server_log_treeview"));

    GtkTreeViewColumn *server_log_column;
    GtkCellRenderer *server_log_renderer;

    server_log_renderer = gtk_cell_renderer_toggle_new();
    server_log_column = gtk_tree_view_column_new_with_attributes("", server_log_renderer, "active", EVENT_LOG_IS_SELECT_COLUMN, NULL);
    gtk_tree_view_column_set_resizable(server_log_column,TRUE);
    gtk_tree_view_column_set_reorderable(server_log_column, TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(server_widgets->server_log_treeview), server_log_column);
    g_signal_connect (server_log_renderer, "toggled", G_CALLBACK (on_event_log_renderer_toggled), &ObjData);

    server_log_renderer = gtk_cell_renderer_text_new();
    server_log_column = gtk_tree_view_column_new_with_attributes("Nội dung", server_log_renderer, "text", EVENT_LOG_IS_CONTENT_COLUMN, NULL);
    gtk_tree_view_column_set_resizable(server_log_column,TRUE);
    gtk_tree_view_column_set_reorderable(server_log_column, TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(server_widgets->server_log_treeview), server_log_column);

    server_log_renderer = gtk_cell_renderer_text_new();
    server_log_column = gtk_tree_view_column_new_with_attributes("Thời gian", server_log_renderer, "text", EVENT_LOG_IS_TIME_COLUMN, NULL);
    gtk_tree_view_column_set_resizable(server_log_column,TRUE);
    gtk_tree_view_column_set_reorderable(server_log_column, TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(server_widgets->server_log_treeview), server_log_column);

    gtk_tree_view_set_enable_search(GTK_TREE_VIEW(server_widgets->server_log_treeview), TRUE);
    gtk_tree_view_set_search_column(GTK_TREE_VIEW(server_widgets->server_log_treeview), EVENT_LOG_IS_CONTENT_COLUMN);
    gtk_tree_view_set_search_entry(GTK_TREE_VIEW(server_widgets->server_log_treeview),
                                   GTK_ENTRY(gtk_builder_get_object (smartstreetlight_builder, "server_log_search_entry")));

    return TRUE;
}


static gboolean smartstreetlight_server_log_liststore_init(void)
{
    server_widgets->server_log_liststore = gtk_list_store_new(SERVER_LOG_NUM_COLUMNS,
                                            G_TYPE_INT,
                                            G_TYPE_STRING,
                                            G_TYPE_STRING,
                                            G_TYPE_BOOLEAN,
                                            G_TYPE_BOOLEAN,
                                            G_TYPE_BOOLEAN);

    server_widgets->server_log_filter   = GTK_TREE_MODEL_FILTER(gtk_tree_model_filter_new(GTK_TREE_MODEL(server_widgets->server_log_liststore), NULL));

    gtk_tree_model_filter_set_visible_func(server_widgets->server_log_filter, (GtkTreeModelFilterVisibleFunc) log_row_visible, &paging, NULL);

    gtk_tree_view_set_model(GTK_TREE_VIEW(server_widgets->server_log_treeview),
                            GTK_TREE_MODEL(server_widgets->server_log_filter));

    g_object_unref(server_widgets->server_log_liststore);
    return TRUE;
}
static gboolean smartstreetlight_server_log_popup_menu_init(void)
{
    server_log_popup_menu = g_new0(struct SPL_SERVER_LOG_POPUP_MENU, 1);

    GtkWidget *separator_item;
    server_log_popup_menu->M_POPUP = gtk_menu_new();
    SPL_MENU_CSS(server_log_popup_menu->M_POPUP);

    server_log_popup_menu->M_DELETE= gtk_menu_item_new_with_label("Xóa");
    gtk_menu_shell_append(GTK_MENU_SHELL(server_log_popup_menu->M_POPUP),server_log_popup_menu->M_DELETE);
    g_signal_connect(server_log_popup_menu->M_DELETE, "activate",
                 (GCallback) spl_server_log_popupmenu_clicked, GINT_TO_POINTER(SPL_SERVER_LOG_POPUP_MENU_DELETE));

//    server_log_popup_menu->M_SELECT = gtk_menu_item_new_with_label("Chọn");
//    gtk_menu_shell_append(GTK_MENU_SHELL(server_log_popup_menu->M_POPUP),server_log_popup_menu->M_SELECT);
//    g_signal_connect(server_log_popup_menu->M_SELECT, "activate",
//                 (GCallback) spl_server_log_popupmenu_clicked, GINT_TO_POINTER(SPL_SERVER_LOG_POPUP_MENU_SELECT));
//
//    server_log_popup_menu->M_DISSELECT = gtk_menu_item_new_with_label("Bỏ chọn");
//    gtk_menu_shell_append(GTK_MENU_SHELL(server_log_popup_menu->M_POPUP),server_log_popup_menu->M_DISSELECT);
//    g_signal_connect(server_log_popup_menu->M_DISSELECT, "activate",
//                 (GCallback) spl_server_log_popupmenu_clicked, GINT_TO_POINTER(SPL_SERVER_LOG_POPUP_MENU_DISSELECT));
//
//    separator_item = gtk_separator_menu_item_new();
//    gtk_menu_shell_append(GTK_MENU_SHELL(server_log_popup_menu->M_POPUP), separator_item);
/*
    server_log_popup_menu->M_SELECT_ALL = gtk_menu_item_new_with_label("Chọn tất cả");
    gtk_menu_shell_append(GTK_MENU_SHELL(server_log_popup_menu->M_POPUP),server_log_popup_menu->M_SELECT_ALL);
    g_signal_connect(server_log_popup_menu->M_SELECT_ALL, "activate",
                 (GCallback) spl_server_log_popupmenu_clicked, GINT_TO_POINTER(SPL_SERVER_LOG_POPUP_MENU_SELECT_ALL));

    server_log_popup_menu->M_DISSELECT_ALL = gtk_menu_item_new_with_label("Bỏ chọn tất cả");
    gtk_menu_shell_append(GTK_MENU_SHELL(server_log_popup_menu->M_POPUP),server_log_popup_menu->M_DISSELECT_ALL);
    g_signal_connect(server_log_popup_menu->M_DISSELECT_ALL, "activate",
                 (GCallback) spl_server_log_popupmenu_clicked, GINT_TO_POINTER(SPL_SERVER_LOG_POPUP_MENU_DISSELECT_ALL));

    separator_item = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(server_log_popup_menu->M_POPUP), separator_item);

    server_log_popup_menu->M_DELETE_MARK= gtk_menu_item_new_with_label("Xóa đánh dấu");
    gtk_menu_shell_append(GTK_MENU_SHELL(server_log_popup_menu->M_POPUP),server_log_popup_menu->M_DELETE_MARK);
    g_signal_connect(server_log_popup_menu->M_DELETE_MARK, "activate",
                 (GCallback) spl_server_log_popupmenu_clicked, GINT_TO_POINTER(SPL_SERVER_LOG_POPUP_MENU_DELETE_MARK));

    separator_item = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(server_log_popup_menu->M_POPUP), separator_item);

    server_log_popup_menu->M_DELETE_ALL= gtk_menu_item_new_with_label("Xóa tất cả");
    gtk_menu_shell_append(GTK_MENU_SHELL(server_log_popup_menu->M_POPUP),server_log_popup_menu->M_DELETE_ALL);
    g_signal_connect(server_log_popup_menu->M_DELETE_ALL, "activate",
                 (GCallback) spl_server_log_popupmenu_clicked, GINT_TO_POINTER(SPL_SERVER_LOG_POPUP_MENU_DELETE_ALL));
*/
    return TRUE;
}
static gboolean smartstreetlight_server_log_callback_init(void)
{
    g_signal_connect(GTK_TREE_VIEW(server_widgets->server_log_treeview),
                     "button-press-event",
                     G_CALLBACK(on_spl_server_log_treeview_clicked), NULL);
    g_signal_connect(SPL_OBJECT("btn_serverlog_back"), "clicked", G_CALLBACK(on_event_log_btn_back_clicked), &ObjData);
    g_signal_connect(SPL_OBJECT("btn_serverlog_next"), "clicked", G_CALLBACK(on_event_log_btn_next_clicked), &ObjData);
    g_signal_connect(SPL_OBJECT("serverlog_btn_selection_click"), "clicked", G_CALLBACK(on_image_selection_click), &ObjData);
    return TRUE;
}


gboolean smartstreetlight_server_log_init(void)
{
    gboolean ret = FALSE;

    server_widgets = g_slice_new(SPL_SERVER_Widgets);

    server_widgets->spl_server_log_box = GTK_WIDGET(SPL_OBJECT("spl_server_log_box"));

    if(smartstreetlight_server_log_treeview_init())
    {
        if (smartstreetlight_server_log_liststore_init())
        {
            if (smartstreetlight_server_log_popup_menu_init())
            {
                if (smartstreetlight_server_log_callback_init())
                {
                    ObjData.filter = server_widgets->server_log_filter;
                    ObjData.store = server_widgets->server_log_liststore;
                    ObjData.update_information_func = &spl_serverlog_update_information;
                    ObjData.soap_delete_function = &smartstreetlight_delete_event_log_execute;
                    ret = TRUE;
                }
            }
        }
    }

//    gtk_widget_set_visible(GTK_WIDGET(SPL_OBJECT("grid27")), FALSE);

    return ret;
}

void smartstreetlight_server_log_finalize(void)
{
    if(server_widgets->spl_server_log_box)
        gtk_widget_destroy(GTK_WIDGET(server_widgets->spl_server_log_box));
    g_slice_free(SPL_SERVER_Widgets, server_widgets);
}

static void smartstreetlight_server_log_fill_infomation(gint id, gchar *content, gchar *time, gboolean readed)
{

    GtkTreeIter iter;
    gtk_list_store_append(server_widgets->server_log_liststore, &iter);
    gtk_list_store_set(server_widgets->server_log_liststore, &iter,
                       EVENT_LOG_IS_ID_COLUMN, id,
                       EVENT_LOG_IS_CONTENT_COLUMN, content,
                       EVENT_LOG_IS_TIME_COLUMN, time,
                       SERVER_LOG_READED_COLUMN, readed,
                       EVENT_LOG_IS_SELECT_COLUMN, FALSE,
                       EVENT_LOG_IS_DELETE_COLUMN, FALSE,
                       -1);
}

void smartstreetlight_server_log_show_all(void)
{

    g_return_if_fail(server_widgets);

    ns1__EVENT_USCORELOG_USCOREINFO_USCOREType **eventlog_list = NULL;
    gint eventlog_list_size;

    smartstreetlight_clear_list_store(GTK_TREE_MODEL(server_widgets->server_log_liststore));

    gchar *device_id = g_strdup("Server");
    SplSoap spl_soap;
    paging.curPage      = 1;
    paging.minIndex     = 1;
    paging.maxIndex     =  MAX_PAGE_VIEW_NUM;
    checkbox_set_image(SERVER_IMAGE_ID, 0);
    gint soap_err = smartstreetlight_get_event_log_nofree_execute(&spl_soap,device_id,
            ns1__EVENTLOG_USCORETYPE_USCOREEnum__LIFECYCLE_USCORESERVER_USCORELOG,
            &eventlog_list, &eventlog_list_size);
    if(soap_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
    {
        if (eventlog_list != NULL)
        {
            spl_log_clear_store(SPL_LOG_LCU);
            for(gint i=0; i<eventlog_list_size; i++)
            {
                ns1__EVENT_USCORELOG_USCOREINFO_USCOREType *event =  eventlog_list[i];
                smartstreetlight_server_log_fill_infomation(event->eventlog_USCOREid,
                                                            event->eventlog_USCOREcontent,
                                                            event->eventlog_USCOREtime,
                                                            FALSE);
            }
        }
        DEBUG("server log: %d\n", eventlog_list_size);
    } else {
        gchar * msg = g_strdup("Lỗi lấy thông tin nhật ký của Server.");
        GtkWidget *parent = stack_widget_active_top();
        smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
        g_char_free(msg);
    }
    paging.totalItem    = eventlog_list_size;
    paging.selected     = 0;
    if(paging.totalItem < paging.maxIndex)
        paging.maxIndex = paging.totalItem;
    spl_serverlog_update_information();
    smartstreetlight_free_soap_operation(&spl_soap);
    g_free(device_id);
}

static void spl_server_log_popupmenu_clicked(GtkWidget *popup_menu_item, gpointer userdata)
{
    switch(GPOINTER_TO_INT(userdata))
    {
    case SPL_SERVER_LOG_POPUP_MENU_DELETE:
        spl_event_log_delete_marked_iter(&ObjData);
//        spl_server_log_delete_one_item();
        break;
    };
}

void spl_server_log_popupmenu_show(GdkEventButton *event, gpointer userdata)
{
    gtk_widget_show_all(GTK_WIDGET(server_log_popup_menu->M_POPUP));
    gtk_menu_popup(GTK_MENU(server_log_popup_menu->M_POPUP), NULL, NULL, NULL, NULL,
                   (event != NULL) ? event->button : 0, gdk_event_get_time((GdkEvent*)event));
}


static gboolean on_spl_server_log_treeview_clicked (GtkTreeView *treeview,
                                    GdkEventButton     *event,
                                    gpointer           userdata)
{
    if(event->type == GDK_BUTTON_PRESS && event->button == GDK_BUTTON_SECONDARY)
    {
        spl_server_log_popupmenu_show(event, NULL);
    }
    return FALSE;
}



