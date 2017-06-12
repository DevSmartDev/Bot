#include    <getopt.h>
#include "main.h"
#include "smartstreetlight_gui.h"
#include "smartstreetlight_login.h"
#include "smartstreetlight_utils.h"
#include "smartstreetlight_callback.h"
#include "smartstreetlight_sql.h"
#include "smartstreetlight_dcu.h"
#include "smartstreetlight_line.h"
#include "smartstreetlight_lcu.h"
#include "smartstreetlight_database.h"
#include "smartstreetlight_schedule.h"
#include "smartstreetlight_server.h"
#include "smartstreetlight_user.h"
#include "smartstreetlight_admin_user.h"
#include "smartstreetlight_admin_zone.h"
#include "smartstreetlight_error.h"
#include "smartstreetlight_event_thread.h"
#include "smartstreetlight_ui_method.h"
#include "smartstreetlight_utils.h"
#include "mapviewer.h"


extern void free_smartstreetlight_username();
gchar* INSTALL_PATH = NULL;
char * smartstreetlight_server_url;
pSplObjectMove ObjMove = NULL;

GtkTextBuffer *notification_text_buffer = NULL;

SPL_Object *spl_object;

const gchar* icon_name[ICON_DEF_ICON_NAME_COUNT] = {
#ifdef WIN32
    "share\\icons\\hicolor\\16x16\\apps\\light_on.png",
    "share\\icons\\hicolor\\16x16\\apps\\light_off.png",
    "share\\icons\\hicolor\\16x16\\apps\\light_broken.png",
    "share\\icons\\hicolor\\16x16\\apps\\light_on_selected.png",
    "share\\icons\\hicolor\\16x16\\apps\\light_off_selected.png",
    "share\\icons\\hicolor\\16x16\\apps\\light_broken_selected.png",
    "share\\icons\\hicolor\\16x16\\apps\\light_on_p_selected.png",
    "share\\icons\\hicolor\\16x16\\apps\\light_off_p_selected.png",
    "share\\icons\\hicolor\\16x16\\apps\\light_broken_p_selected.png",
    "share\\icons\\hicolor\\16x16\\apps\\add.png",
    "share\\icons\\hicolor\\16x16\\apps\\back.png",
    "share\\icons\\hicolor\\16x16\\apps\\next.png",
    "share\\icons\\hicolor\\16x16\\apps\\edit.png",
    "share\\icons\\hicolor\\16x16\\apps\\tick.png",
    "share\\icons\\hicolor\\16x16\\apps\\remove.png",
    "share\\icons\\hicolor\\16x16\\apps\\down.png",
    "share\\icons\\hicolor\\16x16\\apps\\find.png",
    "share\\icons\\hicolor\\16x16\\apps\\home.png",
    "share\\icons\\hicolor\\16x16\\apps\\zoom_out.png",
    "share\\icons\\hicolor\\16x16\\apps\\zoom_in.png",
    "share\\icons\\hicolor\\16x16\\apps\\checkbox_non.png",
    "share\\icons\\hicolor\\16x16\\apps\\checkbox_checked.png",
    "share\\icons\\hicolor\\16x16\\apps\\checkbox_partial.png",
    "share\\icons\\hicolor\\16x16\\apps\\notification.png",
#else
    "icons/hicolor/16x16/apps/light_on.png",
    "icons/hicolor/16x16/apps/light_off.png",
    "icons/hicolor/16x16/apps/light_broken.png",
    "icons/hicolor/16x16/apps/light_on_selected.png",
    "icons/hicolor/16x16/apps/light_off_selected.png",
    "icons/hicolor/16x16/apps/light_broken_selected.png",
    "icons/hicolor/16x16/apps/light_on_p_selected.png",
    "icons/hicolor/16x16/apps/light_off_p_selected.png",
    "icons/hicolor/16x16/apps/light_broken_p_selected.png",
    "icons/hicolor/16x16/apps/add.png",
    "icons/hicolor/16x16/apps/back.png",
    "icons/hicolor/16x16/apps/next.png",
    "icons/hicolor/16x16/apps/edit.png",
    "icons/hicolor/16x16/apps/tick.png",
    "icons/hicolor/16x16/apps/remove.png",
    "icons/hicolor/16x16/apps/down.png",
    "icons/hicolor/16x16/apps/find.png",
    "icons/hicolor/16x16/apps/home.png",
    "icons/hicolor/16x16/apps/zoom_out.png",
    "icons/hicolor/16x16/apps/zoom_in.png",
    "icons/hicolor/16x16/apps/checkbox_non.png",
    "icons/hicolor/16x16/apps/checkbox_checked.png",
    "icons/hicolor/16x16/apps/checkbox_partial.png",
    "icons/hicolor/16x16/apps/notification.png",
#endif // WIN32
};

static void spl_main_notebook_setting(gboolean is_admin);
/** *********************************************************************************************** **/

static void spl_init_style(const gchar *dir)
{
     /* ----------------- CSS ----------------------------------------------------------------------------------------------*/
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    provider = gtk_css_provider_new ();
    display = gdk_display_get_default ();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider),
                                               GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    const gchar* home = "splStyle.css";
    gchar *filename = g_strconcat(dir, G_DIR_SEPARATOR_S, home,NULL);
    GError *error = 0;

    DEBUG("FileName: %s\n", filename);
    if(!gtk_css_provider_load_from_file(provider, g_file_new_for_path(filename), &error))
    {
        DEBUG("[[[[Fail]]]] msg: %s\n", error->message);
        g_error_free(error);
    }
    g_free(filename);
    g_object_unref (provider);
    /* --------------------------------------------------------------------------------------------------------------------*/
}

static void smartstreetlight_save_config(void)
{
    GKeyFile *config;
    gchar *filename;
    gchar *data;
    config = g_key_file_new();
    filename = utils_get_locale_from_utf8(spl_object->configure_full_path);

    g_key_file_load_from_file(config, filename, G_KEY_FILE_NONE, NULL);

    DEBUG("%s-%s\n", spl_object->chart->startTime, spl_object->chart->endTime);
    g_key_file_set_string(config, "chart_settings", "startTime", spl_object->chart->startTime);
    g_key_file_set_string(config, "chart_settings", "endTime", spl_object->chart->endTime);
    g_key_file_set_boolean(config, "chart_settings", "remember", spl_object->chart->isSave);

    data = g_key_file_to_data(config, NULL, NULL);

    if(!utils_write_file(filename, data))
    {
        GtkWidget *parent = stack_widget_active_top();
        SPL_ERROR_POPUP(parent, "Không thể lưu thông tin cấu hình.");
    }

    g_free(filename);
	g_key_file_free(config);
}


void smartstreetlight_finalize(GtkWidget *object, gpointer user_data)
{
    DEBUG("\n\n*************************** ENTER smartstreetlight_finalize!! *******************\n\n");

    GtkWidget *parent = stack_widget_active_top();
    gint response = SPL_QUESTION_POPUP(parent, "Bạn thật sự muốn thoát chương trình ?");
    if(response==GTK_RESPONSE_OK)
    {
        smartstreetlight_save_config();
        free_smartstreetlight_username();
        g_free(spl_object->configure_dir);
        g_free(spl_object->configure_full_path);
        g_free(spl_object->username);
        g_free(spl_object->password);
        g_free(spl_object->server_url);
        g_free(spl_object->server_port);
        g_free(spl_object);
        g_free(ObjMove);

        spl_ui_methods_finalize();
        smartstreetlight_login_finalize();
        smartstreetlight_error_finalize();
        smartstreetlight_database_finalize();
        smartstreetlight_lcu_finalize();
        smartstreetlight_dcu_finalize();
        smartstreetlight_program_schedule_finalize();
        smartstreetlight_server_log_finalize();
        smartstreetlight_user_log_finalize();
        smartstreetlight_event_thread_finalize();
        g_slice_free(SmartStreetLight_Widgets, main_widgets);

        if(is_admin_mode)
        {
            spl_admin_user_manage_finalize();
            spl_admin_zone_manage_finalize();
        }

        gtk_main_quit();
    }
}

static gboolean smartstreetlight_gui_init(void)
{
    DEBUG("\n\n*************************** ENTER smartstreetlight_init!! *******************\n\n");

    main_widgets = g_slice_new(SmartStreetLight_Widgets);

    main_widgets->login_dialog = NULL;
    main_widgets->main_window = NULL;

    main_widgets->create_schedule_dialog = NULL;
    main_widgets->starttime_choose_dialog = NULL;
    main_widgets->dcu_update_window = NULL;
    main_widgets->program_choose_dialog = NULL;
    main_widgets->add_dcu_dialog = NULL;
    main_widgets->delete_element_dialog = NULL;
    main_widgets->notification_dialog = NULL;
    main_widgets->edit_dcu_dialog = NULL;
    main_widgets->add_lcu_dialog = NULL;

    main_widgets->new_schedule_dialog = NULL;
    main_widgets->lcu_control_dialog = NULL;
    main_widgets->devices_log_dialog = NULL;
    main_widgets->day_schedule_dialog_new = NULL;
    main_widgets->schedule_item_new_dialog = NULL;
    main_widgets->dcu_custom_program_dialog = NULL;
    main_widgets->user_information_dialog = NULL;
    main_widgets->main_notebook = NULL;
    main_widgets->lcu_slope_datetime_dialog = NULL;

    smartstreetlight_builder = gtk_builder_new ();
    gtk_builder_add_from_string (smartstreetlight_builder, smartstreetlight_gui, strlen(smartstreetlight_gui), NULL);

    main_widgets->login_dialog = (GtkWidget *)gtk_builder_get_object (smartstreetlight_builder, "login_dialog");

    main_widgets->main_window = (GtkWidget *)gtk_builder_get_object (smartstreetlight_builder, "main_window");
    g_signal_connect (main_widgets->main_window, "destroy", G_CALLBACK (smartstreetlight_finalize), NULL);
#ifdef WIN32
    GdkScreen *screen = gdk_screen_get_default();
    if(screen)
        gtk_widget_set_size_request(main_widgets->main_window,
                                gdk_screen_get_width(screen), gdk_screen_get_height(screen));
#else
    gtk_window_maximize(GTK_WINDOW(main_widgets->main_window));
    gtk_window_set_resizable(GTK_WINDOW(main_widgets->main_window), TRUE);
#endif

    //gtk_window_fullscreen(GTK_WINDOW(main_widgets->main_window));
    g_signal_connect(GTK_BUTTON(SPL_OBJECT("main_window_quit_button")), "clicked", G_CALLBACK(smartstreetlight_finalize), NULL);

    main_widgets->main_notebook = GTK_WIDGET(SPL_OBJECT("main_notebook"));

    main_widgets->program_choose_dialog = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "program_choose_dialog"));

    main_widgets->add_dcu_dialog = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "add_dcu_dialog"));

    main_widgets->delete_element_dialog = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "delete_element_dialog"));

//    main_widgets->notification_dialog = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "notification_dialog"));

    main_widgets->edit_dcu_dialog = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "edit_dcu_dialog"));

    main_widgets->add_lcu_dialog = GTK_WIDGET(SPL_OBJECT("add_lcu_dialog"));

//    gtk_window_fullscreen(GTK_WINDOW(main_widgets->main_window));

    main_widgets->create_schedule_dialog = GTK_WIDGET(SPL_OBJECT("create_schedule_dialog"));

    main_widgets->new_schedule_dialog = GTK_WIDGET(SPL_OBJECT("new_schedule_dialog"));

    main_widgets->lcu_control_dialog = GTK_WIDGET(SPL_OBJECT("lcu_control_dialog"));

    main_widgets->devices_log_dialog = GTK_WIDGET(SPL_OBJECT("devices_log_dialog"));

    main_widgets->day_schedule_dialog_new = GTK_WIDGET(SPL_OBJECT("day_schedule_dialog_new"));

    main_widgets->schedule_item_new_dialog = GTK_WIDGET(SPL_OBJECT("schedule_item_new_dialog"));

    main_widgets->dcu_custom_program_dialog = GTK_WIDGET(SPL_OBJECT("dcu_custom_program_dialog"));

    main_widgets->user_information_dialog = GTK_WIDGET(SPL_OBJECT("user_information_dialog"));

    main_widgets->remember_login_checkbutton = GTK_WIDGET(SPL_OBJECT("remember_login_checkbutton"));

    main_widgets->lcu_chart_dialog = GTK_WIDGET(SPL_OBJECT("lcu_chart_dialog"));

    main_widgets->lcu_slope_datetime_dialog = GTK_WIDGET(SPL_OBJECT("lcu_slope_datetime_dialog"));

    gtk_entry_set_visibility(GTK_ENTRY(SPL_OBJECT("dialog_login_password")), FALSE);

    spl_main_notebook_setting(FALSE);
    /**
    set image for icon
    */
    DEBUG("==========================================>SET IMAGE FOR ALL ICON\n");
    DEBUG("Test name: %s\n", g_strconcat(INSTALL_PATH,G_DIR_SEPARATOR_S,icon_name[ICON_DEF_REMOVE], NULL));
    gtk_image_set_from_file(GTK_IMAGE(SPL_OBJECT("image_tick")),
                            (const gchar*)g_strconcat(INSTALL_PATH, G_DIR_SEPARATOR_S,icon_name[ICON_DEF_TICK], NULL));
    gtk_image_set_from_file(GTK_IMAGE(SPL_OBJECT("image_remove1")),
                            (const gchar*)g_strconcat(INSTALL_PATH,G_DIR_SEPARATOR_S,icon_name[ICON_DEF_REMOVE], NULL));
    gtk_image_set_from_file(GTK_IMAGE(SPL_OBJECT("image_remove")),
                            (const gchar*)g_strconcat(INSTALL_PATH,G_DIR_SEPARATOR_S,icon_name[ICON_DEF_REMOVE], NULL));
    gtk_image_set_from_file(GTK_IMAGE(SPL_OBJECT("image_edit1")),
                            (const gchar*)g_strconcat(INSTALL_PATH,G_DIR_SEPARATOR_S,icon_name[ICON_DEF_EDIT], NULL));
    gtk_image_set_from_file(GTK_IMAGE(SPL_OBJECT("image_edit")),
                            (const gchar*)g_strconcat(INSTALL_PATH,G_DIR_SEPARATOR_S,icon_name[ICON_DEF_EDIT], NULL));
    gtk_image_set_from_file(GTK_IMAGE(SPL_OBJECT("image_add1")),
                            (const gchar*)g_strconcat(INSTALL_PATH,G_DIR_SEPARATOR_S,icon_name[ICON_DEF_ADD], NULL));
    gtk_image_set_from_file(GTK_IMAGE(SPL_OBJECT("image_add")),
                            (const gchar*)g_strconcat(INSTALL_PATH,G_DIR_SEPARATOR_S,icon_name[ICON_DEF_ADD], NULL));
    gtk_image_set_from_file(GTK_IMAGE(SPL_OBJECT("image_zoom_in")),
                            (const gchar*)g_strconcat(INSTALL_PATH,G_DIR_SEPARATOR_S,icon_name[ICON_DEF_ZOOM_IN], NULL));
    gtk_image_set_from_file(GTK_IMAGE(SPL_OBJECT("image_zoom_out")),
                            (const gchar*)g_strconcat(INSTALL_PATH,G_DIR_SEPARATOR_S,icon_name[ICON_DEF_ZOOM_OUT], NULL));
    gtk_image_set_from_file(GTK_IMAGE(SPL_OBJECT("image_home")),
                            (const gchar*)g_strconcat(INSTALL_PATH,G_DIR_SEPARATOR_S,icon_name[ICON_DEF_HOME], NULL));
    gtk_image_set_from_file(GTK_IMAGE(SPL_OBJECT("image_search1")),
                            (const gchar*)g_strconcat(INSTALL_PATH,G_DIR_SEPARATOR_S,icon_name[ICON_DEF_FIND], NULL));
    gtk_image_set_from_file(GTK_IMAGE(SPL_OBJECT("image_search")),
                            (const gchar*)g_strconcat(INSTALL_PATH,G_DIR_SEPARATOR_S,icon_name[ICON_DEF_FIND], NULL));
    gtk_image_set_from_file(GTK_IMAGE(SPL_OBJECT("image_back1")),
                            (const gchar*)g_strconcat(INSTALL_PATH,G_DIR_SEPARATOR_S,icon_name[ICON_DEF_BACK], NULL));
    gtk_image_set_from_file(GTK_IMAGE(SPL_OBJECT("image_back")),
                            (const gchar*)g_strconcat(INSTALL_PATH,G_DIR_SEPARATOR_S,icon_name[ICON_DEF_BACK], NULL));
    gtk_image_set_from_file(GTK_IMAGE(SPL_OBJECT("image_next1")),
                            (const gchar*)g_strconcat(INSTALL_PATH,G_DIR_SEPARATOR_S,icon_name[ICON_DEF_NEXT], NULL));
    gtk_image_set_from_file(GTK_IMAGE(SPL_OBJECT("image_next")),
                            (const gchar*)g_strconcat(INSTALL_PATH,G_DIR_SEPARATOR_S,icon_name[ICON_DEF_NEXT], NULL));
    gtk_image_set_from_file(GTK_IMAGE(SPL_OBJECT("notification_image_next")),
                            (const gchar*)g_strconcat(INSTALL_PATH,G_DIR_SEPARATOR_S,icon_name[ICON_DEF_NEXT], NULL));
    gtk_image_set_from_file(GTK_IMAGE(SPL_OBJECT("notification_image_next")),
                            (const gchar*)g_strconcat(INSTALL_PATH,G_DIR_SEPARATOR_S,icon_name[ICON_DEF_BACK], NULL));
    gtk_image_set_from_file(GTK_IMAGE(SPL_OBJECT("image_notification")),
                            (const gchar*)g_strconcat(INSTALL_PATH,G_DIR_SEPARATOR_S,icon_name[ICON_DEF_NOTICATION], NULL));
    return TRUE;
}
#ifdef WIN32
gboolean show_debug=FALSE;
static void debug_setup_console()
{
	static const WORD MAX_CONSOLE_LINES = 500;
	gint	 hConHandle;
	glong	 lStdHandle;
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	FILE	*fp;

	/* allocate a console for this app */
	AllocConsole();

	/* set the screen buffer to be big enough to let us scroll text */
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
	coninfo.dwSize.Y = MAX_CONSOLE_LINES;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

	/* redirect unbuffered STDOUT to the console */
	lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen(hConHandle, "w");
	*stdout = *fp;
	setvbuf(stdout, NULL, _IONBF, 0);

	/* redirect unbuffered STDERR to the console */
	lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen(hConHandle, "w");
	*stderr = *fp;
	setvbuf(stderr, NULL, _IONBF, 0);
}


void getOptCommandLine(int argc, char **argv)
{
    struct option longOption[] = {
            {"debug", no_argument,   0, 'd'},
            {0,0,0,0}
	};
   gint c;
   while (1) {

            /*! getopt_long stores the option index here.*/
            int option_index = 0;
            c = getopt_long (argc, argv, "d:d", longOption, &option_index);
            /*! Detect the end of the options.*/

            if (c == -1)
                break;
            switch (c) {
            case 'd':
                show_debug = TRUE;
                break;
            default:
                break;
            }
    }
}

#endif // WIN32

gint main (gint   argc,  gchar **argv)


{
    /*Here push main window*/
#ifdef WIN32
    getOptCommandLine(argc, argv);
    if (show_debug)
    {
        debug_setup_console();
    }
#endif
    if(smartstreetlight_application_init())
    {
        stack_widget_active_push(GTK_WIDGET(main_widgets->main_window));
        if(spl_login())
        {

            gtk_main();
        }
    }
    return 0;
}

gboolean smartstreetlight_application_init(void)
{
    spl_object          = g_new0(SPL_Object, 1);
    spl_object->chart   = g_new0(SplChartObject, 1);
    gchar *home_dir = get_homedir();

    spl_object->configure_full_path = g_strdup_printf("%s%s%s%s%s", home_dir, G_DIR_SEPARATOR_S,
                                                                    CONFIG_DIR, G_DIR_SEPARATOR_S,
                                                                    CONFIG_FILE);
    //DEBUG("spl_object->configure_full_path: %s\n", spl_object->configure_full_path);
#ifdef WIN32
    INSTALL_PATH = g_win32_get_package_installation_directory_of_module(NULL);
#else
    INSTALL_PATH = g_strdup(SPL_DATADIR);
#endif
    if(ObjMove == NULL)
    {
        ObjMove = g_new0(SplObjectMove, 1);
        ObjMove->name = NULL;
        ObjMove->image = NULL;
    }

    gboolean ret = TRUE;
    gtk_init(NULL, NULL);
//    gtk_main_iteration_do(TRUE);

    NEW_LIST_DCU;
    NEW_LIST_ZONE;
    if(!smartstreetlight_gui_init())
        return FALSE;

    if(!spl_ui_methods_init())
        return FALSE;

    if(!smartstreetlight_error_init())
        return FALSE;

    if(!smartstreetlight_login_init())
        return FALSE;

    gtk_entry_set_text(GTK_ENTRY(SPL_OBJECT("login_server_url_entry")), SPL_SERVER_URL_DEFAULT);
    gtk_entry_set_text(GTK_ENTRY(SPL_OBJECT("login_server_port_entry")), SPL_SERVER_PORT_DEFAULT);

    if(!smartstreetlight_database_init())
        ret =  FALSE;

    else  if(!smartstreetlight_dcu_info_init())
        ret =  FALSE;

    else  if(!smartstreetlight_lcu_info_init())
        ret =  FALSE;

    else  if(!smartstreetlight_line_info_init())
        ret =  FALSE;

    else  if(!smartstreetlight_program_schedule_init())
        ret =  FALSE;

    else  if(!smartstreetlight_server_log_init())
        ret =  FALSE;

    else if(!smartstreetlight_user_log_init())
        ret = FALSE;

    else  if(!smartstreetlight_callback_init())
        ret =  FALSE;

    else if(!spl_admin_user_manage_init())
        ret =   FALSE;

    else if(!spl_admin_zone_manage_init())
        ret = FALSE;

    else if(!smartstreetlight_event_thread_init())
        ret =   FALSE;

    map_main();
#ifdef WIN32
    gchar *dir = g_strdup_printf("%s\\share\\smartpubliclight", INSTALL_PATH);
    spl_init_style(dir);
#else
    gchar *dir = g_strdup_printf("%s/smartpubliclight", SPL_DATADIR);
    spl_init_style(dir);
#endif
    g_free(dir);
    return ret;
}

void smartstreetlight_application_run(void)
{
    gtk_widget_set_visible(GTK_WIDGET(SPL_OBJECT("current_session_id_login")), FALSE);

    spl_admin_user_manage_hide_specific_user_element();

    spl_main_notebook_setting(is_admin_mode);

    smartstreetlight_dcu_show_all();
    smartstreetlight_get_all_light();
    smartstreetlight_program_show_all();
    smartstreetlight_event_thread_run();

    if(is_admin_mode)
        spl_admin_user_manage_run();

    // Reload current page when relogin //
    on_smartstreetlight_main_notebook_switch_page (GTK_NOTEBOOK(main_widgets->main_notebook), NULL,
                                                   gtk_notebook_get_current_page(GTK_NOTEBOOK(main_widgets->main_notebook)),
                                                   NULL);

    GtkWidget *line_page = gtk_notebook_get_nth_page(GTK_NOTEBOOK(SPL_OBJECT("notebook1")), 3);
    gtk_widget_set_visible(line_page, FALSE);
    gtk_widget_set_visible(GTK_WIDGET(SPL_OBJECT("admin_user_id_label")), FALSE);

}


void smartstreetlight_main_server_info_update(const gchar *server_url, const gchar *server_port)
{
    smartstreetlight_server_url = g_strdup_printf("%s:%s/%s", server_url, server_port, SPL_SERVER_SIDE_DEFAULT);
    //    smartstreetlight_server_url = g_strdup_printf("http://14.161.7.19:8447/axis2/services/smartstreetlightService");
}

static void spl_main_notebook_setting(gboolean is_admin)
{
    spl_notebook_tab_hide_show(GTK_NOTEBOOK(main_widgets->main_notebook), SPL_NOTEBOOK_SERVER_LOG_PAGE, is_admin);
    spl_notebook_tab_hide_show(GTK_NOTEBOOK(main_widgets->main_notebook), SPL_NOTEBOOK_USER_MANAGE_PAGE, is_admin);
    spl_notebook_tab_hide_show(GTK_NOTEBOOK(main_widgets->main_notebook), SPL_NOTEBOOK_ZONE_MANAGE_PAGE, is_admin);
}
