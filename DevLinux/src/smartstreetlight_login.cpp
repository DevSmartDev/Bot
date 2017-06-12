#include <sys/stat.h>
#include "smartstreetlight_login.h"
#include "smartstreetlight_soap.h"
#include "smartstreetlight_error.h"
#include "smartstreetlight_utils.h"
#include "smartstreetlight_event_thread.h"

#include <libgen.h>

struct CURRENT_ACCOUNT_LOGIN *current_account;
struct CURRENT_ACCOUNT_WIDGET *current_account_widget;

gboolean is_admin_mode;
gboolean isLogining = TRUE;

static gboolean on_smartstreetlight_user_logout_clicked(GtkButton *button, gpointer userdata);

static void smartstreetlight_current_account_show_clean_info();

static void smartstreetlight_current_account_show_fill_info();

static void smartstreetlight_current_account_show_update_info();

static void smartstreetlight_login_save_config(void);

static void smartstreetlight_login_load_config(gboolean *remember_config);

static void smartstreetlight_login_settup_gui(gboolean is_admin);

static gboolean spl_login_passwd_accelerator_pressed(GtkWidget *widget, GdkEventKey *event, gpointer data);
static gboolean spl_login_username_accelerator_pressed(GtkWidget *widget, GdkEventKey *event, gpointer data);
/** *********************************************************************************************** **/


gboolean smartstreetlight_login_init(void)
{
    current_account = g_slice_new(CURRENT_ACCOUNT_LOGIN);

    current_account->spl_current_username = g_strdup_printf("");
    current_account->spl_current_password = g_strdup_printf("");
    current_account->spl_current_phone = g_strdup_printf("");
    current_account->spl_current_email = g_strdup_printf("");

    current_account->spl_current_user_is_admin_mode = FALSE;
    current_account->spl_current_user_is_enable_email_notify = FALSE;
    current_account->spl_current_user_is_enable_sms_notify  = FALSE;

    g_signal_connect(GTK_BUTTON(gtk_builder_get_object (smartstreetlight_builder, "user_login_button")),
                     "clicked",
                     G_CALLBACK(on_smartstreetlight_user_logout_clicked), NULL);

    gtk_widget_set_visible(GTK_WIDGET(SPL_OBJECT("current_session_id_login")), FALSE);

    current_account_widget = g_slice_new(CURRENT_ACCOUNT_WIDGET);

    current_account_widget->user_info_account_label = (GTK_LABEL(SPL_OBJECT("user_info_account_label")));
    current_account_widget->user_info_password_entry = (GTK_ENTRY(SPL_OBJECT("user_info_password_entry")));
    current_account_widget->user_info_password_2_entry = (GTK_ENTRY(SPL_OBJECT("user_info_password_2_entry")));
    current_account_widget->user_info_phone_entry = (GTK_ENTRY(SPL_OBJECT("user_info_phone_entry")));
    current_account_widget->user_info_email_entry = (GTK_ENTRY(SPL_OBJECT("user_info_email_entry")));

    current_account_widget->user_enable_notify_email_checkbutton = (GTK_CHECK_BUTTON(SPL_OBJECT("user_enable_notify_email_checkbutton")));
    current_account_widget->user_enable_notify_sms_checkbutton = (GTK_CHECK_BUTTON(SPL_OBJECT("user_enable_notify_sms_checkbutton")));

    current_account_widget->user_info_retype_passwd_new_grid = (GTK_GRID(SPL_OBJECT("user_info_retype_passwd_new_grid")));

    gtk_widget_set_visible(GTK_WIDGET(current_account_widget->user_info_retype_passwd_new_grid), FALSE);
//
//    g_signal_connect(GTK_ENTRY(current_account_widget->user_info_password_entry)),
//                     "preedit-changed",
//                     G_CALLBACK(on_smartstreetlight_user_password_changed), NULL);
    g_signal_connect(GTK_WIDGET(SPL_OBJECT("dialog_login_username")),
                     "key_press_event", G_CALLBACK(spl_login_username_accelerator_pressed), NULL);

    g_signal_connect(GTK_WIDGET(SPL_OBJECT("dialog_login_password")),
                     "key_press_event", G_CALLBACK(spl_login_passwd_accelerator_pressed), NULL);

    return TRUE;
}
static gboolean spl_login_username_accelerator_pressed(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
    if (event->keyval == GDK_KEY_Return || event->keyval == GDK_KEY_Tab)
    {
        gtk_widget_grab_focus(GTK_WIDGET(SPL_OBJECT("dialog_login_password")));
    }
    else
        return FALSE;
}

static gboolean spl_login_passwd_accelerator_pressed(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
    if (event->keyval == GDK_KEY_Return)
    {
        gtk_dialog_response(GTK_DIALOG(main_widgets->login_dialog), GTK_RESPONSE_OK);
    }
    else if (event->keyval == GDK_KEY_Tab)
    {
        gtk_widget_grab_focus(GTK_WIDGET(SPL_OBJECT("remember_login_checkbutton")));
    }
    else
        return FALSE;
}

void smartstreetlight_user_logout(void)
{
    if (!isLogining)
    {
        SplSoap spl_soap;
        smartstreetlight_event_thread_finalize();
        smartstreetlight_logout_execute(&spl_soap);
        map_image_remove_all();
    }
}
static gboolean on_smartstreetlight_user_logout_clicked(GtkButton *button, gpointer userdata)
{
    smartstreetlight_user_logout();
    spl_login();
    return FALSE;
}

gboolean smartstreetlight_login_finalize(void)
{
    g_free(current_account->spl_current_username);
    g_free(current_account->spl_current_password);
    g_free(current_account->spl_current_phone);
    g_free(current_account->spl_current_email);

    g_slice_free(CURRENT_ACCOUNT_LOGIN, current_account);

    g_slice_free(CURRENT_ACCOUNT_WIDGET, current_account_widget);

    return TRUE;
}


void smartstreetlight_login_success(gint user_id,
                                    const gchar *username,
                                    const gchar *password,
                                    const gchar *phone,
                                    const gchar *email,
                                    gboolean sms_notify,
                                    gboolean email_notify,
                                    gboolean admin_privilege)
{
    GtkAllocation allocation;
    gint width, height;
    gtk_button_set_label(GTK_BUTTON(gtk_builder_get_object (smartstreetlight_builder, "current_username_login")), username);

    width = gtk_widget_get_allocated_width(GTK_WIDGET(SPL_OBJECT("box_placehold_1")));

    gtk_widget_set_size_request(GTK_WIDGET(SPL_OBJECT("box_placehold_2")), width, -1);

    gtk_widget_get_size_request(GTK_WIDGET(SPL_OBJECT("box_placehold_2")), &width, &height);
    DEBUG("placeholder2: %d-%d\n", width, height);

    current_account->spl_current_username = g_strdup(username);
    current_account->spl_current_password = g_strdup(password);
    current_account->spl_current_phone = g_strdup(phone);
    current_account->spl_current_email = g_strdup(email);
    current_account->spl_current_user_is_enable_sms_notify = sms_notify;
    current_account->spl_current_user_is_enable_email_notify = email_notify;
    current_account->spl_current_user_is_admin_mode = admin_privilege;
    current_account->spl_current_id = user_id;
    is_admin_mode = admin_privilege;

    /** new **/
    spl_object->username = g_strdup(username);
    spl_object->password = g_strdup(password);
    spl_object->server_url = g_strdup(gtk_entry_get_text(GTK_ENTRY(SPL_OBJECT("login_server_url_entry"))));
    spl_object->server_port = g_strdup(gtk_entry_get_text(GTK_ENTRY(SPL_OBJECT("login_server_port_entry"))));
    smartstreetlight_login_save_config();

    smartstreetlight_login_settup_gui(is_admin_mode);
}


void smartstreetlight_logout(const gchar* notifice_content)
{
    GtkWidget *login_label_error = GTK_WIDGET(SPL_OBJECT("login_label_error"));

    if(notifice_content)
        gtk_label_set_text(GTK_LABEL(login_label_error), notifice_content);

    spl_login();
}


void smartstreetlight_current_account_show(void)
{
    smartstreetlight_current_account_show_fill_info();

    SPL_DIALOG_SHOW(main_widgets->user_information_dialog);
    gint response_id = gtk_dialog_run((GtkDialog *)main_widgets->user_information_dialog);
    switch(response_id)
    {
        case DIALOG_OK_RESPONSE:
        {
            SplSoap spl_soap;
            gint soap_err = smartstreetlight_edit_user_by_user_execute(&spl_soap,current_account->spl_current_id,
                                                (gchar *)gtk_entry_get_text(GTK_ENTRY(current_account_widget->user_info_password_entry)),
                                                (gchar *)gtk_entry_get_text(GTK_ENTRY(current_account_widget->user_info_phone_entry)),
                                                (gchar *)gtk_entry_get_text(GTK_ENTRY(current_account_widget->user_info_email_entry)),
                                                gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(current_account_widget->user_enable_notify_sms_checkbutton)),
                                                gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(current_account_widget->user_enable_notify_email_checkbutton))
                                                );
            if(soap_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
            {
                smartstreetlight_current_account_show_update_info();
            }else
            {
                gchar * msg = g_strdup("Lỗi thay đổi thông tin tài khoản. "); // ham nay co roi sao lai viet moi ?????
                GtkWidget *parent = stack_widget_active_top();
        smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
                g_char_free(msg);
            }
        }
        break;
        case DIALOG_CANCEL_RESPONSE:
            break;
        default:
            break;
	}
    SPL_DIALOG_HIDE(main_widgets->user_information_dialog);
    smartstreetlight_current_account_show_clean_info();
}

static void smartstreetlight_current_account_show_clean_info()
{
    gtk_label_set_text(GTK_LABEL(current_account_widget->user_info_account_label), "");
    gtk_entry_set_text(GTK_ENTRY(current_account_widget->user_info_password_entry), "");
    gtk_entry_set_text(GTK_ENTRY(current_account_widget->user_info_password_2_entry), "");
    gtk_entry_set_text(GTK_ENTRY(current_account_widget->user_info_phone_entry), "");
    gtk_entry_set_text(GTK_ENTRY(current_account_widget->user_info_email_entry), "");

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(current_account_widget->user_enable_notify_email_checkbutton), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(current_account_widget->user_enable_notify_sms_checkbutton), FALSE);

    gtk_widget_set_visible(GTK_WIDGET(current_account_widget->user_info_retype_passwd_new_grid), FALSE);
}
static void smartstreetlight_current_account_show_update_info()
{
    current_account->spl_current_password                   = g_strdup(gtk_entry_get_text(GTK_ENTRY(current_account_widget->user_info_password_entry)));
    current_account->spl_current_phone                      = g_strdup(gtk_entry_get_text(GTK_ENTRY(current_account_widget->user_info_phone_entry)));
    current_account->spl_current_email                      = g_strdup(gtk_entry_get_text(GTK_ENTRY(current_account_widget->user_info_email_entry)));

    current_account->spl_current_user_is_enable_sms_notify  = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(current_account_widget->user_enable_notify_sms_checkbutton));
    current_account->spl_current_user_is_enable_email_notify= gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(current_account_widget->user_enable_notify_email_checkbutton));
}

static void smartstreetlight_current_account_show_fill_info()
{
    gtk_label_set_text(GTK_LABEL(current_account_widget->user_info_account_label), current_account->spl_current_username);
    gtk_entry_set_text(GTK_ENTRY(current_account_widget->user_info_password_entry), current_account->spl_current_password);
    gtk_entry_set_text(GTK_ENTRY(current_account_widget->user_info_password_2_entry), current_account->spl_current_password);
    gtk_entry_set_text(GTK_ENTRY(current_account_widget->user_info_phone_entry), current_account->spl_current_phone);
    gtk_entry_set_text(GTK_ENTRY(current_account_widget->user_info_email_entry), current_account->spl_current_email);

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(current_account_widget->user_enable_notify_email_checkbutton), current_account->spl_current_user_is_enable_email_notify);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(current_account_widget->user_enable_notify_sms_checkbutton), current_account->spl_current_user_is_enable_sms_notify);

    gtk_widget_set_visible(GTK_WIDGET(current_account_widget->user_info_retype_passwd_new_grid), FALSE);
}


gboolean spl_login()
{
    const gchar* username;
    const gchar* password;
    const gchar* server_url;
    const gchar* server_port;
    gint response_id ;
    gboolean goback = FALSE;
    isLogining = TRUE;

    GtkWidget *entryuser, *entrypass, *entryhost, *entryport, *lberror;

    lastSelectedDcu = NULL;
    lastSelectedLcu = NULL;
    smartstreetlight_tree_store_clean(SPL_DCU_STORE);
    smartstreetlight_tree_store_clean(SPL_LCU_STORE);
    smartstreetlight_tree_store_clean(SPL_LCU_ALL_STORE);
    smartstreetlight_tree_store_clean(SPL_PROGRAM_STORE);
    smartstreetlight_tree_store_clean(SPL_DCU_PROGRAM_STORE);
    smartstreetlight_tree_store_clean(SPL_SCHEDULE_STORE);
    smartstreetlight_tree_store_clean(SPL_MONTH_STORE);

    //free zones
    if(!IS_EMPTY_LIST_ZONE)
        FREE_LIST_ZONE(spl_zone_free);
    //free all icon on map #This is needless at here, because it will remove when light free
    //osm_gps_map_image_remove_all(map);
    if(!IS_EMPTY_LIST_DCU)
    {
        DEBUG("\n size of DCU LIST: %d", g_slist_length(dculist));
        GSList *item;
        LIST_DCU_FOR_EACH_ENTRY(item)
        {
            pSplDcu dcu = (pSplDcu)item->data;
            if(!IS_EMPTY_LIST_LCU(dcu))
            {
                FREE_LIST_LCU(dcu,spl_lcu_free);
            }
        }
        FREE_LIST_DCU(spl_dcu_free);
    }
#ifdef HIEU_TEST
    GtkWidget *dlg = GTK_WIDGET(SPL_OBJECT("schedule_item_new_dialog"));
    gtk_widget_show(dlg);
    if(gtk_dialog_run(GTK_DIALOG(dlg)))
        return FALSE;
#endif // HIEU_TEST
    /*************************************************************/
    /*************************************************************/
//
//    GtkWidget *widget = GTK_WIDGET(SPL_OBJECT("waiting_window"));
//    gboolean is_ok = gtk_widget_is_composited(widget);
//    DEBUG("is_ok: %d and TRUE: %d", is_ok, TRUE);
//    gtk_widget_show_all(widget);
//    gtk_widget_set_opacity(GTK_WIDGET(widget), 0.2);
//    return;

    /*************************************************************/

    if(closestUsingDculist)
        spl_utils_free_slist(&closestUsingDculist, (GDestroyNotify)g_free);
    if(main_widgets->main_window)
        gtk_widget_set_sensitive(main_widgets->main_window, FALSE);


    //
    lberror     = GTK_WIDGET(SPL_OBJECT("login_label_error"));
    entryuser   = GTK_WIDGET(SPL_OBJECT("dialog_login_username"));
    entrypass   = GTK_WIDGET(SPL_OBJECT("dialog_login_password"));
    entryhost   = GTK_WIDGET(SPL_OBJECT("login_server_url_entry"));
    entryport   = GTK_WIDGET(SPL_OBJECT("login_server_port_entry"));

    //load config
    gboolean remember_config;
    smartstreetlight_login_load_config(&remember_config);

    //reset all input value
    if(remember_config)
    {
        gtk_entry_set_text(GTK_ENTRY(entryuser), spl_object->username);
        gtk_entry_set_text(GTK_ENTRY(entrypass), spl_object->password);
        gtk_entry_set_text(GTK_ENTRY(entryhost), spl_object->server_url);
        gtk_entry_set_text(GTK_ENTRY(entryport), spl_object->server_port);
    }
    else
    {
        gtk_entry_set_text(GTK_ENTRY(entrypass), "");
        gtk_entry_set_text(GTK_ENTRY(entryuser), "");
        gtk_entry_set_text(GTK_ENTRY(entryhost), SPL_SERVER_URL_DEFAULT);
        gtk_entry_set_text(GTK_ENTRY(entryport), SPL_SERVER_PORT_DEFAULT);
    }

    //gtk_widget_hide(lberror);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(main_widgets->remember_login_checkbutton), TRUE);
    /* Make window transient for the root window */
    SPL_DIALOG_SHOW(main_widgets->login_dialog);
__jumpPoint:
    gtk_label_set_markup (GTK_LABEL (lberror),
                                      "<span color=\"gray\"></span>");
    gtk_widget_grab_focus(GTK_WIDGET(SPL_OBJECT("dialog_login_username")));
    while(response_id = gtk_dialog_run(GTK_DIALOG(main_widgets->login_dialog)))
    {
        switch(response_id)
        {
        case GTK_RESPONSE_OK:
        {
            ns1__USER_USCOREINFO_USCOREType *user_info = NULL;
            gboolean is_admin;
            goback = FALSE;
            //check all input value != NULL and !+ ""
            username = gtk_entry_get_text(GTK_ENTRY(entryuser));
            password = gtk_entry_get_text(GTK_ENTRY(entrypass));
            server_url = gtk_entry_get_text(GTK_ENTRY(entryhost));
            server_port = gtk_entry_get_text(GTK_ENTRY(entryport));
            if(!username || !password || !server_port || !server_url)
                goto __jumpPoint;

            if(!g_strcmp0(username, "")
                || !g_strcmp0(password, ""))
            {
                gtk_label_set_markup (GTK_LABEL (lberror),
                                      "<span color=\"red\">Tên đăng nhập hoặc mật khẩu không được để trống.</span>");
                goto __jumpPoint;
            }
            else if(!g_strcmp0(server_url, "")
                || !g_strcmp0(server_port, ""))
            {
                gtk_label_set_markup (GTK_LABEL (lberror), "<span color=\"red\">Server hoặc Port không được để trống.</span>");
                goto __jumpPoint;
            }
            smartstreetlight_main_server_info_update(server_url, server_port);
            SplSoap spl_soap;
            gtk_label_set_markup (GTK_LABEL (lberror),
                                      "<span color=\"gray\">Đang kết nối tới máy chủ...</span>");
            gint login_err = smartstreetlight_login_nofree_execute(&spl_soap,username, password,&user_info,&is_admin);
            if(login_err ==ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
            {
                if (user_info!= NULL)
                {
                    smartstreetlight_login_success(user_info->user_USCOREid,
                                           username,
                                           password,
                                           user_info->user_USCOREphone,
                                           user_info->user_USCOREemail,
                                           user_info->user_USCOREnotify_USCOREsms_USCOREenable,
                                           user_info->user_USCOREnotify_USCOREmail_USCOREenable,
                                           is_admin);
                    isLogining = FALSE;

                    SPL_DIALOG_HIDE(main_widgets->login_dialog);
                    smartstreetlight_application_run();
                    return TRUE;
                }
            }
            smartstreetlight_free_soap_operation(&spl_soap);
            if (login_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__USER_USCOREPASSWD_USCOREERR)
            {
                gtk_label_set_markup (GTK_LABEL (lberror),
                                      "<span color=\"red\">Tên đăng nhập hoặc mật khẩu không đúng.</span>");
            }
            else if (login_err < 0)
            {
                gtk_label_set_markup (GTK_LABEL (lberror),
                                      "<span color=\"red\">Không kết nối được với Server</span>");
            }
        }
            break;
        case GTK_RESPONSE_CLOSE:
            DEBUG_1();
//            break;
        default:
            DEBUG_1();
            smartstreetlight_finalize(NULL, NULL);
            gtk_main_quit();
            isLogining = FALSE;
            return FALSE;
        }
    }
    isLogining = FALSE;
    SPL_DIALOG_HIDE(main_widgets->login_dialog);
    return FALSE;
}

static void smartstreetlight_login_save_config(void)
{
    gboolean remember_login = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(main_widgets->remember_login_checkbutton));
    GKeyFile *config;
    gchar *filename;
    gchar *data;
    config = g_key_file_new();

    struct stat st = {0};

    spl_object->configure_dir = g_path_get_dirname(spl_object->configure_full_path);

    if (!g_file_test(spl_object->configure_dir, G_FILE_TEST_IS_DIR))
    {
        if(!spl_utils_mkdir(spl_object->configure_dir, TRUE))
        {
            GtkWidget *parent = stack_widget_active_top();
            SPL_ERROR_POPUP(parent, "Không thể tạo thư mục lưu thông tin cấu hình.");
        }
    }

    #ifdef WIN32
    SetFileAttributes(spl_object->configure_dir, FILE_ATTRIBUTE_HIDDEN);
    #endif // WIN32

    filename = utils_get_locale_from_utf8(spl_object->configure_full_path);
    if(!g_file_test(filename, G_FILE_TEST_EXISTS))
    {
        gint _file = g_creat(filename, S_IWUSR | S_IWUSR);
    }

    g_key_file_load_from_file(config, filename, G_KEY_FILE_NONE, NULL);

    if(remember_login)
    {
        g_key_file_set_string(config, "login_settings", "username", spl_object->username);
        g_key_file_set_string(config, "login_settings", "password", spl_object->password);
        g_key_file_set_string(config, "login_settings", "server_url", spl_object->server_url);
        g_key_file_set_string(config, "login_settings", "server_port", spl_object->server_port);
    }
    else
    {
        g_key_file_set_string(config, "login_settings", "username", "");
        g_key_file_set_string(config, "login_settings", "password", "");
        g_key_file_set_string(config, "login_settings", "server_url", SPL_SERVER_URL_DEFAULT);
        g_key_file_set_string(config, "login_settings", "server_port", SPL_SERVER_PORT_DEFAULT);
    }
    g_key_file_set_boolean(config, "login_settings", "remember", remember_login);

    /* write the file */
	data = g_key_file_to_data(config, NULL, NULL);

	if(!utils_write_file(filename, data))
	{
        GtkWidget *parent = stack_widget_active_top();
        SPL_ERROR_POPUP(parent, "Không thể lưu thông tin cấu hình.");
	}

    g_free(filename);
	g_key_file_free(config);
}

static void smartstreetlight_login_load_config(gboolean *remember_config)
{
    gchar *filename = utils_get_locale_from_utf8(spl_object->configure_full_path);
	GKeyFile *config = g_key_file_new();

	if (g_file_test(filename, G_FILE_TEST_IS_REGULAR))
	{
        g_key_file_load_from_file(config, filename, G_KEY_FILE_NONE, NULL);
        g_free(filename);

        spl_object->username = utils_get_setting_string(config, "login_settings", "username", "");
        spl_object->password = utils_get_setting_string(config, "login_settings", "password", "");
        spl_object->server_url = utils_get_setting_string(config, "login_settings", "server_url", SPL_SERVER_URL_DEFAULT);
        spl_object->server_port = utils_get_setting_string(config, "login_settings", "server_port", SPL_SERVER_PORT_DEFAULT);

        spl_object->chart->startTime    = utils_get_setting_string(config, "chart_settings", "startTime", "");
        spl_object->chart->endTime      = utils_get_setting_string(config, "chart_settings", "endTime", "");
        if(!g_strcmp0(spl_object->chart->startTime, "") || !g_strcmp0(spl_object->chart->startTime, ""))
            spl_object->chart->isSave   = FALSE;
        else
            spl_object->chart->isSave   = utils_get_setting_boolean(config, "chart_settings", "remember", FALSE);

        *remember_config = TRUE;
	}
	else
    {
        spl_object->chart->isSave = FALSE;
        *remember_config = FALSE;

        spl_object->server_url = g_strdup(SPL_SERVER_URL_DEFAULT);
        spl_object->server_port = g_strdup(SPL_SERVER_PORT_DEFAULT);
    }
}


static void smartstreetlight_login_settup_gui(gboolean is_admin)
{

}
