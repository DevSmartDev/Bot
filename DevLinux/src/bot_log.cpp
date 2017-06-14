#include "bot_log.h"
#include "bot_soap.h"
#include "bot_login.h"
#include "bot_error.h"

botLogWidget *log_widget = NULL;


static void bot_log_init_function(GtkTreeView *view, GtkTreeStore **store)
{

    GtkTreeViewColumn   *column;
    GtkCellRenderer     *renderer;
    //init store
    *store = gtk_tree_store_new(DCU_LOG_NUM_COLUMNS,
                                            G_TYPE_INT,
                                            G_TYPE_STRING,
                                            G_TYPE_STRING,
                                            G_TYPE_INT,
                                            G_TYPE_STRING);
    //init tree
//    renderer = gtk_cell_renderer_text_new();
//    column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", DCU_LOG_ID_COLUMN, NULL);
//    gtk_tree_view_column_set_resizable(column,TRUE);
//    gtk_tree_view_column_set_reorderable(column, TRUE);
//    gtk_tree_view_append_column(view, column);


    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Mã trạm", renderer, "text", DCU_LOG_DCU_ID_COLUMN, NULL);
    gtk_tree_view_column_set_resizable(column,TRUE);
    gtk_tree_view_column_set_reorderable(column, TRUE);
    gtk_tree_view_append_column(view, column);



    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Nội dung", renderer, "text", DCU_LOG_CONTENT_COLUMN, NULL);
    gtk_tree_view_column_set_resizable(column,TRUE);
    gtk_tree_view_column_set_reorderable(column, TRUE);
    gtk_tree_view_append_column(view, column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Loại", renderer, "text", DCU_LOG_TYPE_COLUMN, NULL);
    gtk_tree_view_column_set_resizable(column,TRUE);
    gtk_tree_view_column_set_reorderable(column, TRUE);
    gtk_tree_view_append_column(view, column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Thời gian", renderer, "text", DCU_LOG_TIME_COLUMN, NULL);
    gtk_tree_view_column_set_resizable(column,TRUE);
    gtk_tree_view_column_set_reorderable(column, TRUE);
    gtk_tree_view_append_column(view, column);

    if(view == log_widget->log_conn_view)
    {
        gtk_tree_view_set_enable_search(GTK_TREE_VIEW(view), TRUE);
        gtk_tree_view_set_search_column(GTK_TREE_VIEW(view), DCU_LOG_DCU_ID_COLUMN);
        gtk_tree_view_set_search_entry(GTK_TREE_VIEW(view),
                                   GTK_ENTRY(gtk_builder_get_object (bot_builder, "???")));
    }

    //assign store into trees
    gtk_tree_view_set_model(GTK_TREE_VIEW(view),
                            GTK_TREE_MODEL(*store));
    g_object_unref(*store);
}
static void bot_log_connect_view_init()
{
    log_widget->log_conn_view = GTK_TREE_VIEW(bot_OBJECT("dcu_log_connect_treeview"));
    bot_log_init_function(log_widget->log_conn_view, &log_widget->log_conn_store);
}

static void bot_log_lcu_view_init()
{
    log_widget->log_lcu_view = GTK_TREE_VIEW(bot_OBJECT("dcu_log_lcu_treeview"));
    bot_log_init_function(log_widget->log_lcu_view, &log_widget->log_lcu_store);
}

static void bot_log_dcu_view_init()
{
    log_widget->log_dcu_view = GTK_TREE_VIEW(bot_OBJECT("dcu_log_dcu_treeview"));
    bot_log_init_function(log_widget->log_dcu_view, &log_widget->log_dcu_store);
}

static void bot_log_line_view_init()
{
    log_widget->log_line_view = GTK_TREE_VIEW(bot_OBJECT("dcu_log_line_treeview"));
    bot_log_init_function(log_widget->log_line_view, &log_widget->log_line_store);
}

gboolean bot_log_init()
{
    if(!log_widget)
    {
        log_widget = g_new0(botLogWidget, 1);
        bot_log_connect_view_init();
        bot_log_dcu_view_init();
        bot_log_lcu_view_init();
        bot_log_line_view_init();
        return TRUE;
    }
    return FALSE;
}

void bot_log_final()
{
    g_free(log_widget);
}

void static bot_log_fill_information(GtkTreeStore *store,
                                     const gint event_id,
                                     const gchar *event_dcu_id,
                                     const gint event_type,
                                     const gchar *event_content,
                                     const gchar *event_time)
{
    GtkTreeIter iter;
    gtk_tree_store_append(store, &iter, NULL);
    gtk_tree_store_set(store, &iter,
                       DCU_LOG_ID_COLUMN, event_id,
                       DCU_LOG_DCU_ID_COLUMN, event_dcu_id,
                       DCU_LOG_TYPE_COLUMN, event_type,
                       DCU_LOG_CONTENT_COLUMN, event_content,
                       DCU_LOG_TIME_COLUMN, event_time,
                       -1);
}

void bot_log_view_fill_information(gint index,
                                const gint event_id,
                                const gchar *event_dcu_id,
                                const gint event_type,
                                const gchar *event_content,
                                const gchar *event_time)
{
    DEBUG_1();
    GtkTreeStore *store = NULL;
    switch(index)
    {
    case bot_LOG_CONN:
        store = log_widget->log_conn_store;
        break;
    case bot_LOG_LINE:
        store = log_widget->log_line_store;
        break;
    case bot_LOG_LCU:
        store = log_widget->log_lcu_store;
        break;
    case bot_LOG_DCU:
        store = log_widget->log_dcu_store;
        break;
    }
    if(store)
    {
        bot_log_fill_information(store, event_id, event_dcu_id, event_type, event_content, event_time);
    }
}

void bot_log_clear_store(gint index)
{
    GtkTreeStore *store = NULL;
    switch(index)
    {
    case bot_LOG_CONN:
        store = log_widget->log_conn_store;
        break;
    case bot_LOG_LINE:
        store = log_widget->log_line_store;
        break;
    case bot_LOG_LCU:
        store = log_widget->log_lcu_store;
        break;
    case bot_LOG_DCU:
        store = log_widget->log_dcu_store;
        break;
    }
    if(store)
        gtk_tree_store_clear(store);
}

void bot_log_clear_all_store()
{
    gtk_tree_store_clear(log_widget->log_dcu_store);
    gtk_tree_store_clear(log_widget->log_line_store);
    gtk_tree_store_clear(log_widget->log_lcu_store);
    gtk_tree_store_clear(log_widget->log_conn_store);
}

static void bot_log_show()
{
    gint response_id;
    bot_DIALOG_SHOW(main_widgets->devices_log_dialog);
    while(response_id = gtk_dialog_run(GTK_DIALOG(main_widgets->devices_log_dialog)))
    {
        gboolean exit = FALSE;
        switch(response_id)
        {
        case GTK_RESPONSE_OK:
        case GTK_RESPONSE_CANCEL:
        case GTK_RESPONSE_DELETE_EVENT:
            exit = TRUE;
            break;
        }
        if(exit)
            break;
    }
    bot_DIALOG_HIDE(main_widgets->devices_log_dialog);
}

gboolean bot_dcu_view_log(pbotDcu dcu)
{
    if(!dcu)
        return FALSE;
    bot_log_clear_all_store();
    botSoap bot_soap;
    ns1__EVENT_USCORELOG_USCOREINFO_USCOREType **eventlog_list = NULL;
    /*
        enum ns1__EVENTLOG_USCORETYPE_USCOREEnum
        {
            ns1__EVENTLOG_USCORETYPE_USCOREEnum__CONNECT_USCOREDCU_USCORELOG,	///< xs:string value="CONNECT_DCU_LOG"
            ns1__EVENTLOG_USCORETYPE_USCOREEnum__LIFECYCLE_USCORESERVER_USCORELOG,	///< xs:string value="LIFECYCLE_SERVER_LOG"
            ns1__EVENTLOG_USCORETYPE_USCOREEnum__DCU_USCOREERR_USCORELOG,	///< xs:string value="DCU_ERR_LOG"
            ns1__EVENTLOG_USCORETYPE_USCOREEnum__LCU_USCOREERR_USCORELOG,	///< xs:string value="LCU_ERR_LOG"
            ns1__EVENTLOG_USCORETYPE_USCOREEnum__LINE_USCOREERR_USCORELOG,	///< xs:string value="LINE_ERR_LOG"
        };
    */
    gint eventlog_list_size;
    DEBUG_1();
    gint soap_err = bot_get_event_log_nofree_execute(&bot_soap,dcu->priv->id, (ns1__EVENTLOG_USCORETYPE_USCOREEnum)bot_LOG_CONN,
                                             &eventlog_list, &eventlog_list_size);
    if (soap_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
    {
        if (eventlog_list != NULL)
        {
            bot_log_clear_store(bot_LOG_CONN);
            for(gint i=0; i<eventlog_list_size; i++)
            {
                ns1__EVENT_USCORELOG_USCOREINFO_USCOREType *event =  eventlog_list[i];
                bot_log_view_fill_information(bot_LOG_CONN,
                                            event->eventlog_USCOREid,
                                            event->eventlog_USCOREdcuid,
                                            (gint)event->eventlog_USCOREtype,
                                            event->eventlog_USCOREcontent,
                                            event->eventlog_USCOREtime);
            }
        }
    } else {
        gchar * msg = g_strconcat("Lỗi lấy thông tin nhật ký kết nối của trạm có id là ", dcu->priv->id,". ", NULL);
        GtkWidget *parent = stack_widget_active_top();
        bot_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
        g_char_free(msg);
    }
    bot_free_soap_operation(&bot_soap);

    soap_err = bot_get_event_log_nofree_execute(&bot_soap,dcu->priv->id, (ns1__EVENTLOG_USCORETYPE_USCOREEnum)bot_LOG_DCU,
                                             &eventlog_list, &eventlog_list_size);
    if (soap_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
    {
        if (eventlog_list != NULL)
        {
            bot_log_clear_store(bot_LOG_DCU);
            for(gint i=0; i<eventlog_list_size; i++)
            {
                ns1__EVENT_USCORELOG_USCOREINFO_USCOREType *event =  eventlog_list[i];
                bot_log_view_fill_information(bot_LOG_DCU,
                                            event->eventlog_USCOREid,
                                            event->eventlog_USCOREdcuid,
                                            (gint)event->eventlog_USCOREtype,
                                            event->eventlog_USCOREcontent,
                                            event->eventlog_USCOREtime);
            }
        }

    }
    else
    {
        gchar * msg = g_strconcat("Lỗi lấy thông tin nhật ký hoạt động  của trạm có id là ", dcu->priv->id,". ", NULL);
        GtkWidget *parent = stack_widget_active_top();
        bot_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
        g_char_free(msg);
    }
    bot_free_soap_operation(&bot_soap);



    soap_err = bot_get_event_log_nofree_execute(&bot_soap,dcu->priv->id, (ns1__EVENTLOG_USCORETYPE_USCOREEnum)bot_LOG_LCU,
                                             &eventlog_list, &eventlog_list_size);
    if (soap_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
    {
        if (eventlog_list != NULL)
        {
            bot_log_clear_store(bot_LOG_LCU);
            for(gint i=0; i<eventlog_list_size; i++)
            {
                ns1__EVENT_USCORELOG_USCOREINFO_USCOREType *event =  eventlog_list[i];
                bot_log_view_fill_information(bot_LOG_LCU,
                                            event->eventlog_USCOREid,
                                            event->eventlog_USCOREdcuid,
                                            (gint)event->eventlog_USCOREtype,
                                            event->eventlog_USCOREcontent,
                                            event->eventlog_USCOREtime);
            }
        }

    } else {
        gchar * msg = g_strconcat("Lỗi lấy thông tin nhật ký hoạt động các đèn của trạm có id là ", dcu->priv->id,". ", NULL);
        GtkWidget *parent = stack_widget_active_top();
        bot_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
        g_char_free(msg);
    }
    bot_free_soap_operation(&bot_soap);


    soap_err = bot_get_event_log_nofree_execute(&bot_soap,dcu->priv->id, (ns1__EVENTLOG_USCORETYPE_USCOREEnum)bot_LOG_LINE,
                                             &eventlog_list, &eventlog_list_size);
    if (soap_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
    {
        if (eventlog_list != NULL)
        {
            bot_log_clear_store(bot_LOG_LINE);
            for(gint i=0; i<eventlog_list_size; i++)
            {
                ns1__EVENT_USCORELOG_USCOREINFO_USCOREType *event =  eventlog_list[i];
                bot_log_view_fill_information(bot_LOG_LINE,
                                            event->eventlog_USCOREid,
                                            event->eventlog_USCOREdcuid,
                                            (gint)event->eventlog_USCOREtype,
                                            event->eventlog_USCOREcontent,
                                            event->eventlog_USCOREtime);
            }
        }
    }else {
        gchar * msg = g_strconcat("Lỗi lấy thông tin nhật ký hoạt động các cổng điều khiển đèn của trạm có id là ", dcu->priv->id,". ", NULL);
        GtkWidget *parent = stack_widget_active_top();
        bot_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
        g_char_free(msg);
    }
    bot_free_soap_operation(&bot_soap);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object (bot_builder, "dcu_log_connect_dcu_id")),
                               dcu->priv->id);
    bot_log_show();

     return FALSE;
}


