#include "gsoap/soapH.h"
#include "bot_event_thread.h"
#include "bot_error.h"
#include "bot_utils.h"
#include "bot_soap.h"

#ifdef WIN32
#include <windows.h>
#endif

GThread * bot_event_thread = NULL;
static gboolean is_cancel_thread = FALSE;
gint is_cancel_thread_mutex = 0;

static gboolean is_started_thread;

G_LOCK_DEFINE_STATIC(is_cancel_thread_mutex);

static void      * bot_event_thread_execute(void *thread_arg);
static void      * do_event_notify_popup(gpointer data);
static GtkWidget * bot_event_create(gpointer data);
static void        bot_event_notify_window_focus (GtkWidget *widget,
                                                  GdkEvent  *event,
                                                  gpointer   user_data);
static void * bot_lcu_runtime_data_error_process(gpointer data);

typedef struct __botNotification{
    gint            notification_nums;
    GtkTreeStore    *store;
    GtkTreeView     *view;
    GtkLabel        *notifilabel;
    GtkWidget       *notifibtn;
    GtkWidget       *dlg;
    GMutex          lock;
}botNotification;

botNotification *notify = NULL;

enum
{
    NOTIFY_READ_COLUMN = 0,
    NOTIFY_TYPE_COLUMN,
    NOTIFY_SHORT_COLUMN,
    NOTIFY_FULL_COLUMN,
    NOTIFY_NUMS_COLUMN,

};
/** ********************************************************************************************************************** **/
/** ********************************************************************************************************************** **/
/** ********************************************************************************************************************** **/

static void notification_set_infomation()
{
    gtk_widget_set_visible(GTK_WIDGET(notify->notifibtn), notify->notification_nums > 0);
    gtk_label_set_text(notify->notifilabel, g_strdup_printf("%d", notify->notification_nums));
}

static gboolean on_notification_view_click(GtkTreeView *view, GdkEventButton *event, gpointer data)
{
    GtkTreeSelection    *selection;
    GtkTreeIter         iter;
    GtkTreeModel        *model;
    if(event->type !=  GDK_2BUTTON_PRESS || event->button != GDK_BUTTON_PRIMARY)
        return FALSE;
    while(1)
    {
        if(g_mutex_trylock(&notify->lock))
        {
            selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(view));
            if(selection)
            {
                if(gtk_tree_selection_get_selected(selection, &model, &iter))
                {
                    gchar* msg;
                    gtk_tree_model_get(model, &iter, NOTIFY_FULL_COLUMN, &msg, -1);
                    //bot_utils_message_box(GTK_WINDOW(notify->dlg), GTK_MESSAGE_INFO, GTK_BUTTONS_OK, msg);
                    bot_INFO_POPUP(GTK_WINDOW(notify->dlg), msg);
                    g_char_free(msg);
                    gtk_tree_store_remove(GTK_TREE_STORE(notify->store), &iter);
                    notify->notification_nums--;
                }
            }
            notification_set_infomation();
            g_mutex_unlock(&notify->lock);
            return TRUE;
        }
        #ifdef WIN32
        Sleep(1000);
        #else
        sleep(10);
        #endif // WIN32
    }
    return TRUE;
}

static void on_notification_btn_click(GtkWidget *w, GdkEventButton *event, gpointer data)
{
    gint responseId;
    gtk_widget_show_all(GTK_WIDGET(notify->dlg));
    while(responseId = gtk_dialog_run(GTK_DIALOG(notify->dlg)))
    {
        switch(responseId)
        {
            case GTK_RESPONSE_REJECT:
                while(1)
                {
                    if(g_mutex_trylock(&notify->lock))
                    {
                        gtk_tree_store_clear(GTK_TREE_STORE(notify->store));
                        notify->notification_nums = 0;
                        notification_set_infomation();
                        g_mutex_unlock(&notify->lock);
                        break;
                    }
                    #ifdef WIN32
                    Sleep(1000);
                    #else
                    sleep(10);
                    #endif // WIN32
                }
                break;
            case GTK_RESPONSE_OK:
            default:
                goto __exit_here;
                break;
        }

    }
__exit_here:
    gtk_widget_hide_on_delete(GTK_WIDGET(notify->dlg));
    return;
}

static void on_dlg_btn_quit_click(GtkWidget *w, gpointer p)
{
    gtk_widget_hide_on_delete(GTK_WIDGET(notify->dlg));
}

gboolean bot_event_thread_init(void)
{
    gboolean isInitThread = FALSE;
    if(!isInitThread)
    {
        GtkCellRenderer *render;
        GtkTreeViewColumn *column;
        notify = g_new0(botNotification, 1);
        g_mutex_init(&notify->lock);
        notify->notification_nums = 0;
        notify->dlg = GTK_WIDGET(bot_OBJECT("notification_dlg"));
        notify->view = GTK_TREE_VIEW(bot_OBJECT("notification_view"));
        notify->notifilabel = GTK_LABEL(bot_OBJECT("notification_lb"));
        notify->notifibtn = GTK_WIDGET(bot_OBJECT("btn_show_notify"));
		notify->store = gtk_tree_store_new(NOTIFY_NUMS_COLUMN, G_TYPE_BOOLEAN,
                                           G_TYPE_STRING,  G_TYPE_STRING, G_TYPE_STRING);

        render = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Đối tượng", render, "text", NOTIFY_TYPE_COLUMN, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(notify->view), column);

        render = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nội dung", render, "text", NOTIFY_SHORT_COLUMN, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(notify->view), column);

        gtk_tree_selection_set_mode(gtk_tree_view_get_selection(GTK_TREE_VIEW(notify->view)), GTK_SELECTION_SINGLE);

        gtk_tree_view_set_model(GTK_TREE_VIEW(notify->view), GTK_TREE_MODEL(notify->store));
        g_signal_connect(notify->view, "button-press-event",
                         G_CALLBACK(on_notification_view_click), NULL);
        g_signal_connect(notify->notifibtn, "button-press-event",
                         G_CALLBACK(on_notification_btn_click), NULL);
        g_signal_connect(bot_OBJECT("notification_btn_quit"), "clicked",
                         G_CALLBACK(on_dlg_btn_quit_click), NULL);
        isInitThread = TRUE;
    }
    return TRUE;
}

void bot_event_thread_finalize(void)
{
    if(is_started_thread==TRUE)
    {
        G_LOCK(is_cancel_thread_mutex);
        is_cancel_thread = TRUE;
        G_UNLOCK(is_cancel_thread_mutex);
        g_return_if_fail(bot_event_thread);
        if (g_thread_join(bot_event_thread) == 0)
        {
            DEBUG("\n bot_event_thread_run: child thread exiting is OK.\n\n");
        }
        is_started_thread = FALSE;
    }
}

void bot_event_thread_run(void)
{
    gint ret;
    notify->notification_nums = 0;
    gtk_widget_set_visible(GTK_WIDGET(notify->notifibtn), FALSE);
    G_LOCK(is_cancel_thread_mutex);
    is_cancel_thread = FALSE;
    G_UNLOCK(is_cancel_thread_mutex);

    #if 0
    ret = pthread_create(&bot_event_thread, NULL, bot_event_thread_execute, NULL);
    if (ret)
    {
        GtkWidget *parent = stack_widget_active_top();
        bot_ERROR_POPUP(parent, "Không thể tạo thread cập nhật dữ liệu runtime");
    }
    #else
    is_started_thread = TRUE;
    bot_event_thread = g_thread_new("event_thead", GThreadFunc(bot_event_thread_execute), NULL);
    if (bot_event_thread==NULL)
    {
        is_started_thread = FALSE;
        GtkWidget *parent = stack_widget_active_top();
        bot_ERROR_POPUP(parent, "Không thể tạo thread cập nhật dữ liệu runtime");
    }
    else
    {
        is_started_thread = TRUE;
    }
    #endif
}
static void * bot_lcu_runtime_data_error_process(gpointer data)
{
    gchar * msg = g_strdup("Lỗi lấy thông tin dữ liệu runtime. ");
    GtkWidget *parent = stack_widget_active_top();
    bot_error_check_message_result(GTK_WIDGET(parent), msg, *((gint *)data));
    g_free(data);
    g_char_free(msg);
    return NULL;
}

#ifdef WIN32
#define PTHREAD_TESTCANCEL() pthread_testcancel()
#else
#define PTHREAD_TESTCANCEL()
#endif // WIN32

static void *bot_event_thread_execute(void *thread_arg)
{
    do
    {
        int is_thread_stop =0;
        int count_ms = 0;
        for (count_ms = 0; count_ms < 10; count_ms++)
        {
            G_LOCK(is_cancel_thread_mutex);
            if (is_cancel_thread)
            {
                G_UNLOCK(is_cancel_thread_mutex);
                is_thread_stop = 1;
                break;
            }
            G_UNLOCK(is_cancel_thread_mutex);

            #ifdef WIN32
            for(gint j=0; j<10; j++)
            {
                PTHREAD_TESTCANCEL();
                Sleep(100);
            }
            #else
            PTHREAD_TESTCANCEL();
            sleep(1);
            PTHREAD_TESTCANCEL();
            #endif // WIN32

        }
        if (is_thread_stop){
            DEBUG("Exit thread\n");
            break;
        }

#if 1
        ns1__DCU_USCOREINFO_USCOREType **dcu_list = NULL;
        gint dcu_list_size;
        ns1__LCU_USCOREINFO_USCOREType **lcu_list = NULL;
        gint lcu_list_size;
        ns1__EVENT_USCORELOG_USCOREINFO_USCOREType **eventlog_list = NULL;
        gint eventlog_list_size;
        botSoap bot_soap;

        /* check cancal request then disable recive cancel signal util free data's soap protocal */
        PTHREAD_TESTCANCEL();
        /* --------------------------------------------------------------------------------------- */

        gint soap_err = bot_event_runtime_update_nofree(&bot_soap,&dcu_list, &dcu_list_size, &lcu_list, &lcu_list_size,
                                                    &eventlog_list, &eventlog_list_size);

//        DEBUG("dcu_list_size: %d", dcu_list_size);
//        DEBUG("lcu_list_size: %d", lcu_list_size);
//        DEBUG("eventlog_list_size: %d", eventlog_list_size);
        if(soap_err==ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
        {
            for(gint i=0; i<eventlog_list_size; i++)
            {
                bot_new_event_data *data = g_slice_new(bot_new_event_data);

                #if 1
                data->event_log_time = g_strdup(eventlog_list[i]->eventlog_USCOREtime);
                data->event_log_content = g_strdup(eventlog_list[i]->eventlog_USCOREcontent);
                #else
                data->event_log_time = g_strdup("vvv");
                data->event_log_content = g_strdup("aaa");
                #endif

                g_idle_add((GSourceFunc)do_event_notify_popup, data);
            }

            for(gint i=0; i<lcu_list_size; i++)
            {
                bot_lcu_runtime_data *lcu_runtime_data;
                lcu_runtime_data = g_slice_new(bot_lcu_runtime_data);
                #if 1
                //DEBUG("=========> Recive LCU ID: %s, ison: %d", lcu_list[i]->lcu_USCOREid, lcu_list[i]->lcu_USCOREison);
                lcu_runtime_data->lcu_dcuid = g_strdup(lcu_list[i]->lcu_USCOREdcuid);
                lcu_runtime_data->lcu_gps = g_strdup(lcu_list[i]->lcu_USCOREgps);
                lcu_runtime_data->lcu_note = g_strdup(lcu_list[i]->lcu_USCOREnote);
                lcu_runtime_data->lcu_id = g_strdup(lcu_list[i]->lcu_USCOREid);
                lcu_runtime_data->lcu_mode = lcu_list[i]->lcu_USCOREmode;
                lcu_runtime_data->lcu_status = lcu_list[i]->lcu_USCOREstatus;
                lcu_runtime_data->lcu_ison = lcu_list[i]->lcu_USCOREison;
                lcu_runtime_data->lcu_current = lcu_list[i]->lcu_USCOREcurrent;
                lcu_runtime_data->lcu_level = lcu_list[i]->lcu_USCORElevel;
                lcu_runtime_data->lightname = g_strdup(lcu_list[i]->lcu_USCORElightname);
                lcu_runtime_data->power = lcu_list[i]->lcu_USCOREpower;
                lcu_runtime_data->tolerance = lcu_list[i]->lcu_USCOREtolerance;
//                DEBUG("=========> Recive LCU ID: %s, lightname: %s", lcu_list[i]->lcu_USCOREid, lcu_list[i]->lcu_USCORElightname);
                #else
                lcu_runtime_data->lcu_dcuid = g_strdup("D200001000");
                lcu_runtime_data->lcu_id = g_strdup("L200001010");
                lcu_runtime_data->lcu_gps = NULL;
                lcu_runtime_data->lcu_note = NULL;
                lcu_runtime_data->lcu_current = 100;
                lcu_runtime_data->lcu_level   = 8;
                #endif

                g_idle_add((GSourceFunc)bot_lcu_runtime_data_update, lcu_runtime_data);

            }

            for(gint i=0; i<dcu_list_size; i++)
            {
                bot_dcu_runtime_data *dcu_runtime_data;
                dcu_runtime_data = g_slice_new(bot_dcu_runtime_data);
                #if 1
                dcu_runtime_data->dcu_id = g_strdup(dcu_list[i]->dcu_USCOREid);
                dcu_runtime_data->dcu_phone = g_strdup(dcu_list[i]->dcu_USCOREphone);
                dcu_runtime_data->dcu_address = g_strdup(dcu_list[i]->dcu_USCOREaddress);
                dcu_runtime_data->dcu_gps = g_strdup(dcu_list[i]->dcu_USCOREgps);
                dcu_runtime_data->dcu_note = g_strdup(dcu_list[i]->dcu_USCOREnote);
                dcu_runtime_data->dcu_program_id = dcu_list[i]->dcu_USCOREprogram_USCOREid;
                dcu_runtime_data->dcu_zone_id = dcu_list[i]->dcu_USCOREzoneid;
                dcu_runtime_data->dcu_mode = dcu_list[i]->dcu_USCOREmode;
                dcu_runtime_data->dcu_status = dcu_list[i]->dcu_USCOREstatus;
                #else
                dcu_runtime_data->dcu_id = g_strdup("D200001000");
                dcu_runtime_data->dcu_phone = g_strdup("01226122460");
                dcu_runtime_data->dcu_address = NULL;
                dcu_runtime_data->dcu_gps = NULL;
                dcu_runtime_data->dcu_note = NULL;
                #endif

                g_idle_add((GSourceFunc)bot_dcu_runtime_data_update, dcu_runtime_data);
            }
        }
        else
        {
            gint* result = g_new(int, 1);
            *result =soap_err;
            g_idle_add((GSourceFunc)bot_lcu_runtime_data_error_process, (gpointer)result);
        }
        bot_free_soap_operation(&bot_soap);

       PTHREAD_TESTCANCEL();
#endif
        /* ----------------------------------------------- */
    }
    while(1);
}


static void* do_event_notify_popup(gpointer data)
{
#if 0
    bot_new_event_data *event_data = (bot_new_event_data *)data;

    GtkWidget *window = bot_event_create (event_data);
    gtk_widget_show_all(window);

    if(event_data->event_log_content)
        g_free(event_data->event_log_content);
    if(event_data->event_log_time)
        g_free(event_data->event_log_time);
    g_slice_free(bot_new_event_data, event_data);
    return NULL;
#else

    bot_new_event_data *event_data = (bot_new_event_data *)data;

    gchar *content = g_strdup_printf("[%s]: %s", event_data->event_log_time,
                                                 event_data->event_log_content);
    bot_event_notify_add(0, content);
    g_char_free(content);
    //bot_utils_message_box(GTK_WINDOW(main_widgets->main_window), GTK_MESSAGE_WARNING,
    //                             GTK_BUTTONS_OK, content);


    return NULL;
#endif // 0
}

static GtkWidget * bot_event_create(gpointer data)
{
    bot_new_event_data *event_data = (bot_new_event_data *)data;

    GtkWidget *window;
    GtkWidget *action;
    GtkWidget *vbox;
    GtkWidget *frame;
    GtkWidget *label;
    GtkWidget *bar;

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    action = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
    vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);

//    gint number = GPOINTER_TO_INT(data);
//    gchar *frame_buf = g_strdup_printf("Thông báo #%d", number);
    frame = gtk_frame_new ("Thông báo mới.");
//    g_free(frame_buf);

    bar = gtk_info_bar_new ();

    gtk_window_set_type_hint(GTK_WINDOW (window), GDK_WINDOW_TYPE_HINT_NOTIFICATION);
//    gtk_window_set_position(GTK_WINDOW (window), GTK_WIN_POS_CENTER);
    gtk_widget_set_size_request(window, 500, 200);

    gtk_container_set_border_width (GTK_CONTAINER (window), 20);
    g_signal_connect(GTK_WIDGET(window), "button-press-event", G_CALLBACK (bot_event_notify_window_focus), &window);

    gtk_container_add (GTK_CONTAINER (window), frame);
    gtk_container_add (GTK_CONTAINER (frame), vbox);
    gtk_box_pack_start (GTK_BOX (vbox), bar, FALSE, FALSE, 0);

    gtk_info_bar_set_message_type (GTK_INFO_BAR (bar), GTK_MESSAGE_INFO);
//    gtk_info_bar_set_show_close_button (GTK_INFO_BAR (bar), TRUE);
    gchar *content = g_strdup_printf("[%s]: %s", event_data->event_log_time, event_data->event_log_content);
    label = gtk_label_new (content);
    g_free(content);

    gtk_box_pack_start (GTK_BOX (gtk_info_bar_get_content_area (GTK_INFO_BAR (bar))), label, FALSE, FALSE, 0);

    gtk_widget_show_all (action);

    return window;
}

static void bot_event_notify_window_focus (GtkWidget *widget,
                                           GdkEvent  *event,
                                           gpointer   user_data)
{
    if (event->type == GDK_2BUTTON_PRESS)
    {
        gtk_widget_destroy(widget);
    }
}

#define MAX_STRING_SHOW 30

gboolean bot_event_notify_add(gint type, gchar * msg)
{
    DEBUG("[[[[[[[[[[%s]]]]]]]]]]\n", __FUNCTION__);
    while(1)
    {
        if(g_mutex_trylock(&notify->lock))
        {
            GtkTreeIter iter;
            gchar *stype, *shortString;
            switch(type)
            {
            case 0:
                stype = g_strdup("Hệ Thống");
                break;
            case 1:
                stype = g_strdup("Trạm");
                break;
            case 2:
                stype = g_strdup("Đèn");
                break;
            default:
                g_mutex_unlock(&notify->lock);
                return FALSE;
            }
            if(strlen(msg) > MAX_STRING_SHOW)
            {
                gint i = MAX_STRING_SHOW - 1;
                for( ; i > 1; i--)
                {
                    if(msg[i] == ' ' && msg[i-1] != ' ')
                        break;
                }
                gchar *tmp = g_strndup(msg, i);
                shortString = g_strdup_printf("%s...", tmp);
                g_char_free(tmp);

            }else
                shortString = g_strdup(msg);
            gtk_tree_store_append(notify->store, &iter, NULL);
            gtk_tree_store_set(notify->store, &iter, NOTIFY_TYPE_COLUMN, stype,
                               NOTIFY_SHORT_COLUMN, shortString,
                               NOTIFY_FULL_COLUMN, msg, -1);
            notify->notification_nums++;
            notification_set_infomation();
            g_mutex_unlock(&notify->lock);
            return TRUE;
        }
        #ifdef WIN32
        Sleep(1000);
        #else
        sleep(10);
        #endif // WIN32
    }
    return TRUE;
}

/** ********************************************************************************************************************** **/
/** ********************************************************************************************************************** **/
/** ********************************************************************************************************************** **/
