#include "bot_admin_user.h"
#include "bot_soap.h"
#include "bot_login.h"
#include "bot_error.h"

struct ADMIN_USER_LIST_Widget       *admin_user_list_widget         = NULL;
struct ADMIN_USER_PRIVILEGE_Widget  *admin_user_privilege_widget    = NULL;
struct ADMIN_USER_CONFIG_Widget     *admin_user_config_widget       = NULL;
struct ADMIN_USER_INFO_Widget       *admin_user_info_widget         = NULL;
struct ADMIN_ZONE_OWN_Widgets        *admin_zone_own_choose_widget    = NULL;
struct ADMIN_USER_MANAGE_PopupMenu  *admin_user_manage_popup_menu   = NULL;
struct ADMIN_USER_MANAGER_ZONE_OWN_PopupMenu *admin_user_manage_zone_own_popup_menu   = NULL;

struct ADMIN_USER_MANAGE_EDIT_Widgets *admin_user_manage_edit_widgets = NULL;

static void bot_admin_user_manage_init_user_list(void);
static void bot_admin_user_manage_init_zone_list(void);

static void bot_admin_user_manage_init_specific_user(void);

static void bot_admin_user_manage_popup_menu_init();
static void bot_admin_user_manage_popup_menu_clicked(GtkWidget *popup_menu_item, gpointer userdata);
static void bot_admin_user_manage_popup_menu_clicked_add(void);
static void bot_admin_user_manage_popup_menu_clicked_edit(void);
static void bot_admin_user_manage_popup_menu_clicked_remove(void);
static void bot_admin_user_manage_popup_menu_show(GtkTreeView *treeview, GdkEventButton *event, gpointer userdata);
static gboolean on_admin_user_manage_treeview_clicked (GtkTreeView *treeview, GdkEventButton *event, gpointer userdata);

static void bot_admin_user_manage_zone_own_popup_menu_init();
static void bot_admin_user_manage_zone_own_popup_menu_clicked(void);
static void bot_admin_user_manage_zone_own_popup_menu_show(GtkTreeView *treeview, GdkEventButton *event, gpointer userdata);
static gboolean on_admin_user_manage_zone_own_treeview_clicked (GtkTreeView *treeview, GdkEventButton *event, gpointer userdata);
static void bot_admin_user_manage_zone_own_change_run(gint user_id, gint count_all_zone);
static void bot_admin_user_manage_show_specific_user(GtkTreeModel *model, GtkTreeIter *iter);

static void bot_admin_user_manage_edit_init();

static void bot_admin_user_manage_edit_execute();

static void bot_admin_user_manage_add_execute();

static void bot_admin_user_manage_user_list_store_insert(ns1__USER_USCOREINFO_USCOREType *user_info);

static void bot_admin_user_manage_user_list_store_update(ns1__USER_USCOREINFO_USCOREType *user_info);

static void on_admin_user_manage_edit_privilege_level_changed(GtkComboBox *widget, gpointer user_data);

static void on_admin_user_manage_edit_toggle_changed(GtkToggleButton *togglebutton, gpointer user_data);

static void bot_admin_user_manage_user_info_fill(ns1__USER_USCOREINFO_USCOREType *user_info);

static void bot_admin_zone_list_update(ns1__ZONE_USCOREINFO_USCOREType *zone_info[], gint zone_size);

static gboolean is_current_user_belong_to(gint zone_id);

static gint bot_admin_zone_own_choose_fill_list_zone();
/** ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ **/
/** ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ **/
/** ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ **/


static void bot_admin_user_manage_init_specific_user(void)
{
    /** ************************************************************************** **/
    /*
        struct ADMIN_USER_PRIVILEGE_Widget  *admin_user_privilege_widget    = NULL;
        struct ADMIN_USER_CONFIG_Widget     *admin_user_config_widget       = NULL;
        struct ADMIN_USER_INFO_Widget       *admin_user_info_widget         = NULL;
    */
    admin_user_privilege_widget = g_slice_new(ADMIN_USER_PRIVILEGE_Widget);

    admin_user_privilege_widget->dcu_box
                                    = GTK_WIDGET(bot_OBJECT("dcu_box"));
    admin_user_privilege_widget->lcu_box
                                    = GTK_WIDGET(bot_OBJECT("lcu_box"));
    admin_user_privilege_widget->lcu_2_box
                                    = GTK_WIDGET(bot_OBJECT("lcu_2_box"));
    admin_user_privilege_widget->device_box
                                    = GTK_WIDGET(bot_OBJECT("device_box"));
    admin_user_privilege_widget->program_box
                                    = GTK_WIDGET(bot_OBJECT("program_box"));
    admin_user_privilege_widget->email_box
                                    = GTK_WIDGET(bot_OBJECT("email_box"));
    admin_user_privilege_widget->sms_box
                                    = GTK_WIDGET(bot_OBJECT("sms_box"));

    /** ************************************************************************** **/

    admin_user_config_widget = g_slice_new(ADMIN_USER_CONFIG_Widget);

    admin_user_config_widget->email_allow_box
                                    = GTK_WIDGET(bot_OBJECT("email_allow_box"));
    admin_user_config_widget->sms_allow_box
                                    = GTK_WIDGET(bot_OBJECT("sms_allow_box"));



    /** ************************************************************************** **/

    admin_user_info_widget = g_slice_new(ADMIN_USER_INFO_Widget);
    admin_user_info_widget->admin_user_id_label
                                    = GTK_LABEL(bot_OBJECT("admin_user_id_label"));
    admin_user_info_widget->admin_user_name_label
                                    = GTK_LABEL(bot_OBJECT("admin_user_name_label"));
    admin_user_info_widget->admin_user_phone_label
                                    = GTK_LABEL(bot_OBJECT("admin_user_phone_label"));
    admin_user_info_widget->admin_user_email_label
                                    = GTK_LABEL(bot_OBJECT("admin_user_email_label"));
    admin_user_info_widget->admin_user_level_label
                                    = GTK_LABEL(bot_OBJECT("admin_user_level_label"));

}
static void bot_admin_user_manage_init_user_list(void)
{
    /** ************************* Treeview list user init ************************* **/
    GtkTreeViewColumn *column;
    GtkCellRenderer   *renderer;

    admin_user_list_widget = g_slice_new(ADMIN_USER_LIST_Widget);

    /*
        enum
        {
            ADMIN_USER_ACCOUNT_COLUMN = 0,
            ADMIN_USER_PHONE_COLUMN,
            ADMIN_USER_EMAIL_COLUMN,

            ADMIN_USER_PRIVILEGE_DCU_MANAGE_COLUMN,
            ADMIN_USER_PRIVILEGE_LCU_LINE_MANAGE_COLUMN,
            ADMIN_USER_PRIVILEGE_LCU_LINE_CONTROL_COLUMN,
            ADMIN_USER_PRIVILEGE_SETUP_DEVICE_COLUMN,
            ADMIN_USER_PRIVILEGE_PROGRAM_COLUMN,
            ADMIN_USER_PRIVILEGE_EMAIL_NOTIFY_COLUMN,
            ADMIN_USER_PRIVILEGE_SMS_NOTIFY_COLUMN,

            ADMIN_USER_PRIVILEGE_EMAIL_ENABLE_COLUMN,
            ADMIN_USER_PRIVILEGE_SMS_ENABLE_COLUMN,

            ADMIN_USER_ID_COLUMN,

            ADMIN_ZONE_ID_COLUMN,
            ADMIN_ZONE_NOTE_COLUMN,
            ADMIN_ZONE_NAME_COLUMN,

            ADMIN_USER_PIXBUF_COLUMN,
            ADMIN_USER_RGBA_COLUMN,

            ADMIN_USER_NUMBER_COLUMN
        };
    */
    admin_user_list_widget->admin_user_treeview = GTK_WIDGET(bot_OBJECT("admin_user_treeview"));

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes ("Tên Tài Khoản", renderer, "text", ADMIN_USER_ACCOUNT_COLUMN, NULL);
    gtk_tree_view_column_set_resizable(column,TRUE);
    gtk_tree_view_column_set_reorderable(column, TRUE);
    gtk_tree_view_append_column (GTK_TREE_VIEW(admin_user_list_widget->admin_user_treeview), column);

//    renderer = gtk_cell_renderer_text_new();
//    column = gtk_tree_view_column_new_with_attributes ("Số Điện Thoại", renderer, "text", ADMIN_USER_PHONE_COLUMN, NULL);
//    gtk_tree_view_column_set_resizable(column,TRUE);
//    gtk_tree_view_column_set_reorderable(column, TRUE);
//    gtk_tree_view_append_column (GTK_TREE_VIEW(admin_user_list_widget->admin_user_treeview), column);
//
//    renderer = gtk_cell_renderer_text_new();
//    column = gtk_tree_view_column_new_with_attributes ("Địa chỉ Email:", renderer, "text", ADMIN_USER_EMAIL_COLUMN, NULL);
//    gtk_tree_view_column_set_resizable(column,TRUE);
//    gtk_tree_view_column_set_reorderable(column, TRUE);
//    gtk_tree_view_append_column (GTK_TREE_VIEW(admin_user_list_widget->admin_user_treeview), column);
//
//    renderer = gtk_cell_renderer_toggle_new();
//    column = gtk_tree_view_column_new_with_attributes ("Quản lý Trạm& LINE:", renderer, "active", ADMIN_USER_PRIVILEGE_DCU_MANAGE_COLUMN, NULL);
//    gtk_tree_view_column_set_resizable(column,TRUE);
//    gtk_tree_view_column_set_reorderable(column, TRUE);
//    gtk_tree_view_append_column (GTK_TREE_VIEW(admin_user_list_widget->admin_user_treeview), column);
//
//    renderer = gtk_cell_renderer_toggle_new();
//    column = gtk_tree_view_column_new_with_attributes ("Quản lý LCU/LINE:", renderer, "active", ADMIN_USER_PRIVILEGE_LCU_LINE_MANAGE_COLUMN, NULL);
//    gtk_tree_view_column_set_resizable(column,TRUE);
//    gtk_tree_view_column_set_reorderable(column, TRUE);
//    gtk_tree_view_append_column (GTK_TREE_VIEW(admin_user_list_widget->admin_user_treeview), column);
//
//    renderer = gtk_cell_renderer_toggle_new();
//    column = gtk_tree_view_column_new_with_attributes ("Điều khiển LCU/LINE:", renderer, "active", ADMIN_USER_PRIVILEGE_LCU_LINE_CONTROL_COLUMN, NULL);
//    gtk_tree_view_column_set_resizable(column,TRUE);
//    gtk_tree_view_column_set_reorderable(column, TRUE);
//    gtk_tree_view_append_column (GTK_TREE_VIEW(admin_user_list_widget->admin_user_treeview), column);
//
//    renderer = gtk_cell_renderer_toggle_new();
//    column = gtk_tree_view_column_new_with_attributes ("Điều khiển LCU/LINE:", renderer, "active", ADMIN_USER_PRIVILEGE_SETUP_DEVICE_COLUMN, NULL);
//    gtk_tree_view_column_set_resizable(column,TRUE);
//    gtk_tree_view_column_set_reorderable(column, TRUE);
//    gtk_tree_view_append_column (GTK_TREE_VIEW(admin_user_list_widget->admin_user_treeview), column);
//
//    renderer = gtk_cell_renderer_toggle_new();
//    column = gtk_tree_view_column_new_with_attributes ("Device setup", renderer, "active", ADMIN_USER_PRIVILEGE_SETUP_DEVICE_COLUMN, NULL);
//    gtk_tree_view_column_set_resizable(column,TRUE);
//    gtk_tree_view_column_set_reorderable(column, TRUE);
//    gtk_tree_view_append_column (GTK_TREE_VIEW(admin_user_list_widget->admin_user_treeview), column);
//
//    renderer = gtk_cell_renderer_toggle_new();
//    column = gtk_tree_view_column_new_with_attributes ("Lập lịch", renderer, "active", ADMIN_USER_PRIVILEGE_PROGRAM_COLUMN, NULL);
//    gtk_tree_view_column_set_resizable(column,TRUE);
//    gtk_tree_view_column_set_reorderable(column, TRUE);
//    gtk_tree_view_append_column (GTK_TREE_VIEW(admin_user_list_widget->admin_user_treeview), column);
//
//    renderer = gtk_cell_renderer_toggle_new();
//    column = gtk_tree_view_column_new_with_attributes ("Nhận thông báo qua email", renderer, "active", ADMIN_USER_PRIVILEGE_EMAIL_NOTIFY_COLUMN, NULL);
//    gtk_tree_view_column_set_resizable(column,TRUE);
//    gtk_tree_view_column_set_reorderable(column, TRUE);
//    gtk_tree_view_append_column (GTK_TREE_VIEW(admin_user_list_widget->admin_user_treeview), column);
//
//    renderer = gtk_cell_renderer_toggle_new();
//    column = gtk_tree_view_column_new_with_attributes ("Nhận thông báo qua sms", renderer, "active", ADMIN_USER_PRIVILEGE_SMS_NOTIFY_COLUMN, NULL);
//    gtk_tree_view_column_set_resizable(column,TRUE);
//    gtk_tree_view_column_set_reorderable(column, TRUE);
//    gtk_tree_view_append_column (GTK_TREE_VIEW(admin_user_list_widget->admin_user_treeview), column);
//
//    renderer = gtk_cell_renderer_toggle_new();
//    column = gtk_tree_view_column_new_with_attributes ("Cho phép nhận thông báo qua sms", renderer, "active", ADMIN_USER_PRIVILEGE_EMAIL_ENABLE_COLUMN, NULL);
//    gtk_tree_view_column_set_resizable(column,TRUE);
//    gtk_tree_view_column_set_reorderable(column, TRUE);
//    gtk_tree_view_append_column (GTK_TREE_VIEW(admin_user_list_widget->admin_user_treeview), column);
//
//    renderer = gtk_cell_renderer_toggle_new();
//    column = gtk_tree_view_column_new_with_attributes ("Cho phép nhận thông báo qua sms", renderer, "active", ADMIN_USER_PRIVILEGE_SMS_ENABLE_COLUMN, NULL);
//    gtk_tree_view_column_set_resizable(column,TRUE);
//    gtk_tree_view_column_set_reorderable(column, TRUE);
//    gtk_tree_view_append_column (GTK_TREE_VIEW(admin_user_list_widget->admin_user_treeview), column);


    gtk_tree_view_set_enable_search(GTK_TREE_VIEW(admin_user_list_widget->admin_user_treeview), TRUE);
    gtk_tree_view_set_search_column(GTK_TREE_VIEW(admin_user_list_widget->admin_user_treeview), ADMIN_USER_ACCOUNT_COLUMN);
    gtk_tree_view_set_search_entry(GTK_TREE_VIEW(admin_user_list_widget->admin_user_treeview),
                                   GTK_ENTRY(bot_OBJECT("admin_user_manage_search_entry")));

    /** ************************* Liststore list user init ************************* **/
    /*
        enum
        {
            ADMIN_USER_ACCOUNT_COLUMN = 0,
            ADMIN_USER_PHONE_COLUMN,
            ADMIN_USER_EMAIL_COLUMN,

            ADMIN_USER_PRIVILEGE_DCU_MANAGE_COLUMN,
            ADMIN_USER_PRIVILEGE_LCU_LINE_MANAGE_COLUMN,
            ADMIN_USER_PRIVILEGE_LCU_LINE_CONTROL_COLUMN,
            ADMIN_USER_PRIVILEGE_SETUP_DEVICE_COLUMN,
            ADMIN_USER_PRIVILEGE_PROGRAM_COLUMN,
            ADMIN_USER_PRIVILEGE_EMAIL_NOTIFY_COLUMN,
            ADMIN_USER_PRIVILEGE_SMS_NOTIFY_COLUMN,

            ADMIN_USER_PRIVILEGE_EMAIL_ENABLE_COLUMN,
            ADMIN_USER_PRIVILEGE_SMS_ENABLE_COLUMN,

            ADMIN_USER_ID_COLUMN,

            ADMIN_ZONE_ID_COLUMN,
            ADMIN_ZONE_NOTE_COLUMN,
            ADMIN_ZONE_NAME_COLUMN,

            ADMIN_USER_PIXBUF_COLUMN,
            ADMIN_USER_RGBA_COLUMN,

            ADMIN_USER_NUMBER_COLUMN
        };
    */

    admin_user_list_widget->admin_user_liststore = gtk_list_store_new(ADMIN_USER_NUMBER_COLUMN,
                                                                        G_TYPE_STRING,
                                                                        G_TYPE_STRING,
                                                                        G_TYPE_STRING,
                                                                        G_TYPE_STRING,
                                                                        G_TYPE_BOOLEAN,
                                                                        G_TYPE_BOOLEAN,
                                                                        G_TYPE_BOOLEAN,
                                                                        G_TYPE_BOOLEAN,
                                                                        G_TYPE_BOOLEAN,
                                                                        G_TYPE_BOOLEAN,
                                                                        G_TYPE_BOOLEAN,
                                                                        G_TYPE_BOOLEAN,
                                                                        G_TYPE_BOOLEAN,
                                                                        G_TYPE_BOOLEAN,
                                                                        G_TYPE_INT,
                                                                        G_TYPE_INT,
                                                                        G_TYPE_STRING,
                                                                        G_TYPE_STRING,
                                                                        GDK_TYPE_PIXBUF,
                                                                        GDK_TYPE_RGBA);

    gtk_tree_view_set_model(GTK_TREE_VIEW(admin_user_list_widget->admin_user_treeview),
                            GTK_TREE_MODEL(admin_user_list_widget->admin_user_liststore));

    g_object_unref(G_OBJECT(admin_user_list_widget->admin_user_liststore));

    /** ************************* Callback list user init ************************* **/
    g_signal_connect(GTK_TREE_VIEW(admin_user_list_widget->admin_user_treeview),
                     "button-press-event",
                     G_CALLBACK(on_admin_user_manage_treeview_clicked), NULL);
}

static void bot_admin_user_manage_init_zone_list(void)
{
    /** ************************* Treeview list user init ************************* **/
    GtkTreeViewColumn *column;
    GtkCellRenderer   *renderer;
    /*
        enum
        {
            ADMIN_USER_ZONE_NAME_COLUMN = 0,
            ADMIN_USER_ZONE_NOTE_COLUMN,
            ADMIN_USER_ZONE_ID_COLUMN,

            ADMIN_USER_ZONE_PIXBUF_COLUMN,
            ADMIN_USER_ZONE_RGBA_COLUMN,

            ADMIN_USER_ZONE_TYPE_COLUMN,

            ADMIN_USER_ZONE_NUNBER_COLUMN
        }
    */
    admin_user_list_widget->admin_user_list_zone_treeview = GTK_WIDGET(bot_OBJECT("admin_user_list_zone_treeview"));

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes ("Tên Khu Vực", renderer, "text", 0, NULL);
    gtk_tree_view_column_set_resizable(column,TRUE);
    gtk_tree_view_column_set_reorderable(column, TRUE);
    gtk_tree_view_append_column (GTK_TREE_VIEW(admin_user_list_widget->admin_user_list_zone_treeview), column);

    /** ************************* Liststore list user init ************************* **/
    /*
        enum
        {
            ADMIN_USER_ZONE_NAME_COLUMN = 0,
            ADMIN_USER_ZONE_NOTE_COLUMN,
            ADMIN_USER_ZONE_ID_COLUMN,

            ADMIN_USER_ZONE_PIXBUF_COLUMN,
            ADMIN_USER_ZONE_RGBA_COLUMN,

            ADMIN_USER_ZONE_TYPE_COLUMN,

            ADMIN_USER_ZONE_NUNBER_COLUMN
        }
    */
    admin_user_list_widget->admin_user_list_zone_treestore = gtk_tree_store_new(2,
                                                                        G_TYPE_STRING,
                                                                        G_TYPE_INT);

    gtk_tree_view_set_model(GTK_TREE_VIEW(admin_user_list_widget->admin_user_list_zone_treeview),
                            GTK_TREE_MODEL(admin_user_list_widget->admin_user_list_zone_treestore));

    g_object_unref(G_OBJECT(admin_user_list_widget->admin_user_list_zone_treestore));

    /** ************************* Callback list user init ************************* **/

    g_signal_connect(GTK_TREE_VIEW(admin_user_list_widget->admin_user_list_zone_treeview),
                     "button-press-event",
                     G_CALLBACK(on_admin_user_manage_zone_own_treeview_clicked), NULL);

        g_signal_connect (GTK_BUTTON(bot_OBJECT("admin_user_zone_own_change_button")),
                     "clicked", G_CALLBACK (bot_admin_user_manage_zone_own_popup_menu_clicked), NULL);
}

gboolean bot_admin_user_manage_init(void)
{
    bot_admin_user_manage_init_user_list();
    bot_admin_user_manage_init_zone_list();
    bot_admin_user_manage_init_specific_user();
    bot_admin_user_manage_hide_specific_user_element();
    bot_admin_user_manage_edit_init();

    bot_admin_user_manage_popup_menu_init();
    bot_admin_user_manage_zone_own_popup_menu_init();

    gtk_paned_set_position(GTK_PANED(bot_OBJECT("admin_user_manage_paned")), 350);

    gtk_paned_set_position(GTK_PANED(bot_OBJECT("admin_user_specific_manage_paned")), 350);

    return TRUE;
}


gboolean bot_admin_user_manage_finalize(void)
{
    gtk_widget_destroy(GTK_WIDGET(admin_user_manage_popup_menu->M_Popup));
    g_slice_free(ADMIN_USER_MANAGE_PopupMenu, admin_user_manage_popup_menu);

    gtk_widget_destroy(GTK_WIDGET(admin_user_manage_zone_own_popup_menu->M_Popup));
    g_slice_free(ADMIN_USER_MANAGER_ZONE_OWN_PopupMenu, admin_user_manage_zone_own_popup_menu);

    g_slice_free(ADMIN_ZONE_OWN_Widgets, admin_zone_own_choose_widget);

    g_slice_free(ADMIN_USER_LIST_Widget, admin_user_list_widget);
    /*
        struct ADMIN_USER_PRIVILEGE_Widget  *admin_user_privilege_widget    = NULL;
        struct ADMIN_USER_CONFIG_Widget     *admin_user_config_widget       = NULL;
        struct ADMIN_USER_INFO_Widget       *admin_user_info_widget         = NULL;
    */
    g_slice_free(ADMIN_USER_PRIVILEGE_Widget, admin_user_privilege_widget);
    g_slice_free(ADMIN_USER_CONFIG_Widget, admin_user_config_widget);
    g_slice_free(ADMIN_USER_INFO_Widget, admin_user_info_widget);
}

static void bot_admin_user_manage_user_list_store_insert(ns1__USER_USCOREINFO_USCOREType *user_info)
{
    GtkTreeIter iter;
    GtkListStore *model = GTK_LIST_STORE(admin_user_list_widget->admin_user_liststore);

    gboolean dcu_lcu_line_manage_privileges;
    gboolean user_privilege_is_supper_user = user_info->user_USCOREmanage_USCOREdcu_USCOREprivilege;

    if(user_privilege_is_supper_user)
        dcu_lcu_line_manage_privileges = TRUE;
    else
        dcu_lcu_line_manage_privileges = user_info->user_USCOREmanage_USCORElculine_USCOREprivilege;

//    DEBUG("\n USERNAME: %s", user_info->user_USCOREaccount);
//    DEBUG("\n ID: %d", user_info->user_USCOREid);
//
//    DEBUG_0("\n dcu manage:  %d", user_info->user_USCOREmanage_USCOREdcu_USCOREprivilege);
//    DEBUG_0("\n lcu manage:  %d", user_info->user_USCOREmanage_USCORElculine_USCOREprivilege);
//    DEBUG_0("\n lcu control: %d", user_info->user_USCOREcontrol_USCORElculine_USCOREprivilege);
//    DEBUG_0("\n lcu control: %d", user_info->user_USCOREcontrol_USCORElculine_USCOREprivilege);
//    DEBUG_0("\n device setup: %d", user_info->user_USCOREsetup_USCOREdevice_USCOREprivilege);
//    DEBUG_0("\n program     : %d", user_info->user_USCOREprogram_USCOREprivilege);
//    DEBUG_0("\n email       : %d", user_info->user_USCOREnotify_USCOREmail_USCOREprivilege);
//    DEBUG_0("\n sms         : %d", user_info->user_USCOREnotify_USCOREsms_USCOREprivilege);
//
//    DEBUG_0("\n email enable: %d", user_info->user_USCOREnotify_USCOREmail_USCOREenable);
//    DEBUG_0("\n sms   enable: %d", user_info->user_USCOREnotify_USCOREsms_USCOREenable);

    gtk_list_store_append(model, &iter);
    gtk_list_store_set(model, &iter,
                        ADMIN_USER_ACCOUNT_COLUMN                   , user_info->user_USCOREaccount,
                        ADMIN_USER_PASSWD_COLUMN                    , user_info->user_USCOREpass,
                        ADMIN_USER_PHONE_COLUMN                     , user_info->user_USCOREphone,
                        ADMIN_USER_EMAIL_COLUMN                     , user_info->user_USCOREemail,
                        ADMIN_USER_PRIVILEGE_IS_SUPPER_USER         , user_privilege_is_supper_user,
                        ADMIN_USER_PRIVILEGE_DCU_MANAGE_COLUMN      , user_info->user_USCOREmanage_USCOREdcu_USCOREprivilege,
                        ADMIN_USER_PRIVILEGE_LCU_LINE_MANAGE_COLUMN , dcu_lcu_line_manage_privileges,
                        ADMIN_USER_PRIVILEGE_LCU_LINE_CONTROL_COLUMN, user_info->user_USCOREcontrol_USCORElculine_USCOREprivilege,
                        ADMIN_USER_PRIVILEGE_SETUP_DEVICE_COLUMN    , user_info->user_USCOREsetup_USCOREdevice_USCOREprivilege,
                        ADMIN_USER_PRIVILEGE_PROGRAM_COLUMN         , user_info->user_USCOREprogram_USCOREprivilege,
                        ADMIN_USER_PRIVILEGE_EMAIL_NOTIFY_COLUMN    , user_info->user_USCOREnotify_USCOREmail_USCOREprivilege,
                        ADMIN_USER_PRIVILEGE_SMS_NOTIFY_COLUMN      , user_info->user_USCOREnotify_USCOREsms_USCOREprivilege,
                        ADMIN_USER_PRIVILEGE_EMAIL_ENABLE_COLUMN    , user_info->user_USCOREnotify_USCOREmail_USCOREenable,
                        ADMIN_USER_PRIVILEGE_SMS_ENABLE_COLUMN      , user_info->user_USCOREnotify_USCOREsms_USCOREenable,
                        ADMIN_USER_ID_COLUMN                        , user_info->user_USCOREid,
                       -1);
}

gboolean bot_admin_user_manage_run(void)
{
    ns1__USER_USCOREINFO_USCOREType **user_list = NULL;
    gint user_list_size;
    botSoap bot_soap;
    bot_clear_list_store(GTK_TREE_MODEL(admin_user_list_widget->admin_user_liststore));
    gint soap_err = bot_get_user_nofree_execute(&bot_soap,0,&user_list, &user_list_size);
    if (soap_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
    {
        if (user_list!=NULL)
        {
            for(gint i=0; i<user_list_size; i++)
            {
                bot_admin_user_manage_user_list_store_insert(user_list[i]);
            }
        }
    } else {
        gchar * msg = g_strdup("Lỗi lấy danh sách các tài khoản. ");
        GtkWidget *parent = stack_widget_active_top();
        bot_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
        g_char_free(msg);
    }
    bot_free_soap_operation(&bot_soap);
}

static void bot_admin_user_manage_popup_menu_init()
{
    GtkWidget *separator_item;

    admin_user_manage_popup_menu = g_slice_new(ADMIN_USER_MANAGE_PopupMenu);

    admin_user_manage_popup_menu->M_Popup = gtk_menu_new();
    bot_MENU_CSS(admin_user_manage_popup_menu->M_Popup);

    admin_user_manage_popup_menu->M_Add = gtk_menu_item_new_with_label("Thêm mới");
    gtk_menu_shell_append(GTK_MENU_SHELL(admin_user_manage_popup_menu->M_Popup),admin_user_manage_popup_menu->M_Add);
    g_signal_connect(admin_user_manage_popup_menu->M_Add, "activate",
                 (GCallback) bot_admin_user_manage_popup_menu_clicked, GINT_TO_POINTER(ADMIN_USER_M_ADD));

    separator_item = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(admin_user_manage_popup_menu->M_Popup), separator_item);

    admin_user_manage_popup_menu->M_Edit= gtk_menu_item_new_with_label("Chỉnh sửa");
    gtk_menu_shell_append(GTK_MENU_SHELL(admin_user_manage_popup_menu->M_Popup),admin_user_manage_popup_menu->M_Edit);
    g_signal_connect(admin_user_manage_popup_menu->M_Edit, "activate",
                 (GCallback) bot_admin_user_manage_popup_menu_clicked, GINT_TO_POINTER(ADMIN_USER_M_EDIT));

    separator_item = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(admin_user_manage_popup_menu->M_Popup), separator_item);

    admin_user_manage_popup_menu->M_Remove= gtk_menu_item_new_with_label("Xóa");
    gtk_menu_shell_append(GTK_MENU_SHELL(admin_user_manage_popup_menu->M_Popup),admin_user_manage_popup_menu->M_Remove);
    g_signal_connect(admin_user_manage_popup_menu->M_Remove, "activate",
                 (GCallback) bot_admin_user_manage_popup_menu_clicked, GINT_TO_POINTER(ADMIN_USER_M_REMOVE));
}

static void bot_admin_user_manage_popup_menu_show(GtkTreeView *treeview, GdkEventButton *event, gpointer userdata)
{
    DEBUG_1();
    gtk_widget_show_all(GTK_WIDGET(admin_user_manage_popup_menu->M_Popup));
    gtk_menu_popup(GTK_MENU(admin_user_manage_popup_menu->M_Popup), NULL, NULL, NULL, NULL,
                   (event != NULL) ? event->button : 0, gdk_event_get_time((GdkEvent*)event));
}

static void bot_admin_user_manage_popup_menu_clicked(GtkWidget *popup_menu_item, gpointer userdata)
{
    ADMIN_USER_MANAGE_POPUP_Enum type = (ADMIN_USER_MANAGE_POPUP_Enum)GPOINTER_TO_INT(userdata);
    switch(type)
    {
    case ADMIN_USER_M_ADD:
        bot_admin_user_manage_popup_menu_clicked_add();
        break;
    case ADMIN_USER_M_EDIT:
        bot_admin_user_manage_popup_menu_clicked_edit();
        break;
    case ADMIN_USER_M_REMOVE:
        bot_admin_user_manage_popup_menu_clicked_remove();
        break;
    default:
        break;
    }
}

static void bot_admin_user_manage_popup_menu_clicked_add(void)
{
    struct ADMIN_USER_MANAGE_EDIT_Widgets *p = admin_user_manage_edit_widgets;

    gtk_widget_set_visible(p->admin_user_manage_edit_grid, FALSE);
    gtk_widget_set_visible(p->admin_user_manage_new_grid, TRUE);

    gtk_entry_set_text(GTK_ENTRY(p->admin_user_manage_new_account_entry), "");
    gtk_entry_set_text(GTK_ENTRY(p->admin_user_manage_edit_password_entry), "");
    gtk_entry_set_text(GTK_ENTRY(p->admin_user_manage_edit_phone_entry), "");
    gtk_entry_set_text(GTK_ENTRY(p->admin_user_manage_edit_email_entry), "");

    gtk_combo_box_set_active(GTK_COMBO_BOX(p->admin_user_manage_edit_level_comboboxtext), NORMAL_USER);
    gtk_widget_set_visible(p->admin_user_manage_edit_manage_dcu_box, FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(p->admin_user_manage_edit_manage_dcu_checkbutton), FALSE);

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(p->admin_user_manage_edit_manage_lcu_checkbutton), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(p->admin_user_manage_edit_control_lcu_checkbutton), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(p->admin_user_manage_edit_setup_device_checkbutton), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(p->admin_user_manage_edit_create_program_checkbutton), FALSE);

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(p->admin_user_manage_edit_email_checkbutton), TRUE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(p->admin_user_manage_edit_sms_checkbutton), TRUE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(p->admin_user_manage_edit_email_notify_checkbutton), TRUE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(p->admin_user_manage_edit_sms_notify_checkbutton), TRUE);

    gchar *edit_main_label = g_strdup("TẠO MỚI NGƯỜI DÙNG");
    gtk_label_set_text(GTK_LABEL(p->admin_user_manage_edit_main_label), edit_main_label);
    gboolean is_ok = TRUE;
//    stack_widget_active_push(p->admin_user_manage_edit_dialog);
    do
    {
        bot_DIALOG_SHOW(p->admin_user_manage_edit_dialog);
        gint response_id = gtk_dialog_run(GTK_DIALOG(p->admin_user_manage_edit_dialog));
        switch(response_id)
        {
            case DIALOG_OK_RESPONSE:
            {
                gchar *account = (gchar *)gtk_entry_get_text(GTK_ENTRY(p->admin_user_manage_new_account_entry));
                gchar *password= (gchar *)gtk_entry_get_text(GTK_ENTRY(p->admin_user_manage_edit_password_entry));
                gchar tmp[100];
                if(g_strcmp0(account, "")== 0 || g_strcmp0(password, "")==0)
                {
                    gtk_label_set_text(GTK_LABEL(p->admin_user_manage_edit_error_label), "Tên đăng nhập và mật khẩu không thể để trống");
                    gtk_widget_set_visible(p->admin_user_manage_edit_error_label, TRUE);
                    is_ok = FALSE;
                }
                else if(sscanf(account, "%[0-9a-zA-Z_]", &tmp) != 1)
                {
                    gtk_label_set_text(GTK_LABEL(p->admin_user_manage_edit_error_label), "Tên đăng nhập sử dụng các kí tự [A-Za-z0-9_]");
                    gtk_widget_set_visible(p->admin_user_manage_edit_error_label, TRUE);
                    is_ok = FALSE;
                }
                else
                {
                    gtk_label_set_text(GTK_LABEL(p->admin_user_manage_edit_error_label), "");
                    gtk_widget_set_visible(p->admin_user_manage_edit_error_label, FALSE);
                    is_ok = TRUE;
                }
                if(is_ok)
                    bot_admin_user_manage_add_execute();
            }
            break;
            case DIALOG_CANCEL_RESPONSE:
                is_ok=TRUE;
                break;
        };
    }
    while(!is_ok);
    bot_DIALOG_HIDE(p->admin_user_manage_edit_dialog);
    g_free(edit_main_label);
}

static void bot_admin_user_manage_popup_menu_clicked_edit(void)
{
    GtkTreeIter iter;
    GtkTreeView      *treeview = GTK_TREE_VIEW(admin_user_list_widget->admin_user_treeview);
    GtkTreeModel     *model;

    struct ADMIN_USER_MANAGE_EDIT_Widgets *p = admin_user_manage_edit_widgets;

    gtk_widget_set_visible(p->admin_user_manage_edit_grid, TRUE);
    gtk_widget_set_visible(p->admin_user_manage_new_grid, FALSE);

    if(bot_get_current_select_iter(treeview, &model, &iter))
    {
        gchar *edit_name;
        gchar *edit_pass;
        gchar *edit_phone;
        gchar *edit_email;

        gint   edit_id;

        gboolean is_supper_user;

        gboolean config_notify_email;
        gboolean config_notify_sms;

        gboolean privilege_manage_dcu;
        gboolean privilege_manage_lcu;
        gboolean privilege_control_lcu;
        gboolean privilege_setup_device;
        gboolean privilege_create_program;
        gboolean privilege_email;
        gboolean privilege_sms;

        gtk_tree_model_get(model, &iter,
                           ADMIN_USER_ID_COLUMN                         , &edit_id,
                           ADMIN_USER_ACCOUNT_COLUMN                    , &edit_name,
                           ADMIN_USER_PASSWD_COLUMN                     , &edit_pass,
                           ADMIN_USER_PHONE_COLUMN                      , &edit_phone,
                           ADMIN_USER_EMAIL_COLUMN                      , &edit_email,
                           ADMIN_USER_PRIVILEGE_EMAIL_ENABLE_COLUMN     , &config_notify_email,
                           ADMIN_USER_PRIVILEGE_SMS_ENABLE_COLUMN       , &config_notify_sms,
                           ADMIN_USER_PRIVILEGE_IS_SUPPER_USER          , &is_supper_user,
                           ADMIN_USER_PRIVILEGE_DCU_MANAGE_COLUMN       , &privilege_manage_dcu,
                           ADMIN_USER_PRIVILEGE_LCU_LINE_MANAGE_COLUMN  , &privilege_manage_lcu,
                           ADMIN_USER_PRIVILEGE_LCU_LINE_CONTROL_COLUMN , &privilege_control_lcu,
                           ADMIN_USER_PRIVILEGE_SETUP_DEVICE_COLUMN     , &privilege_setup_device,
                           ADMIN_USER_PRIVILEGE_PROGRAM_COLUMN          , &privilege_create_program,
                           ADMIN_USER_PRIVILEGE_EMAIL_ENABLE_COLUMN     , &privilege_email,
                           ADMIN_USER_PRIVILEGE_SMS_ENABLE_COLUMN       , &privilege_sms,
                           -1);

        gchar *str = g_strdup_printf("%d", edit_id);
        gtk_label_set_text(GTK_LABEL(p->admin_user_manage_edit_id_label),
                                        str);
        g_free(str);

        gtk_label_set_text(GTK_LABEL(p->admin_user_manage_edit_account_label),
                                        edit_name);

        gtk_entry_set_text(GTK_ENTRY(p->admin_user_manage_edit_password_entry),
                                        edit_pass);

        gtk_entry_set_text(GTK_ENTRY(p->admin_user_manage_edit_phone_entry),
                                        edit_phone);

        gtk_entry_set_text(GTK_ENTRY(p->admin_user_manage_edit_email_entry),
                                        edit_email);

        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(p->admin_user_manage_edit_manage_dcu_checkbutton),
                                        privilege_manage_dcu);

        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(p->admin_user_manage_edit_manage_lcu_checkbutton),
                                        privilege_manage_lcu);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(p->admin_user_manage_edit_setup_device_checkbutton),
                                        privilege_control_lcu);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(p->admin_user_manage_edit_control_lcu_checkbutton),
                                        privilege_setup_device);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(p->admin_user_manage_edit_create_program_checkbutton),
                                        privilege_create_program);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(p->admin_user_manage_edit_email_checkbutton),
                                        privilege_email);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(p->admin_user_manage_edit_sms_checkbutton),
                                        privilege_sms);

        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(p->admin_user_manage_edit_email_notify_checkbutton),
                                        privilege_email?config_notify_email:FALSE);
        gtk_widget_set_sensitive(p->admin_user_manage_edit_email_notify_checkbutton, privilege_email);

        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(p->admin_user_manage_edit_sms_notify_checkbutton),
                                        privilege_sms?config_notify_sms:FALSE);
        gtk_widget_set_sensitive(p->admin_user_manage_edit_sms_notify_checkbutton, privilege_sms);

        gtk_combo_box_set_active(GTK_COMBO_BOX(p->admin_user_manage_edit_level_comboboxtext), privilege_manage_dcu?SUPPER_USER:NORMAL_USER);
        gtk_widget_set_visible(GTK_WIDGET(p->admin_user_manage_edit_manage_dcu_box), privilege_manage_dcu);


        gchar *edit_main_label = g_strdup("CHỈNH SỬA THÔNG TIN NGƯỜI DÙNG");
        gtk_label_set_text(GTK_LABEL(p->admin_user_manage_edit_main_label), edit_main_label);

        bot_DIALOG_SHOW(p->admin_user_manage_edit_dialog);
        gint response_id = gtk_dialog_run(GTK_DIALOG(p->admin_user_manage_edit_dialog));
        switch(response_id)
        {
            case DIALOG_OK_RESPONSE:
                bot_admin_user_manage_edit_execute();
                break;
            case DIALOG_CANCEL_RESPONSE:
                break;
        };
        bot_DIALOG_HIDE(p->admin_user_manage_edit_dialog);

        g_free(edit_main_label);
    }
}

static void bot_admin_user_manage_popup_menu_clicked_remove(void)
{
    GtkTreeView *treeview = GTK_TREE_VIEW(admin_user_list_widget->admin_user_treeview);
    GtkTreeSelection *selection = gtk_tree_view_get_selection(treeview);
    GtkTreeModel *model;
    GtkTreeIter iter;
    if(!isLogining)
    if(gtk_tree_selection_get_selected(selection, &model, &iter))
    {
        gint user_id;
        gchar *user_name;
        gtk_tree_model_get(model, &iter, ADMIN_USER_ID_COLUMN, &user_id,
                                         ADMIN_USER_ACCOUNT_COLUMN, &user_name, -1 );
        gchar *buffer = g_strdup_printf("Bạn chắc chắn muốn xóa người dùng '%s' ?", user_name);
        GtkWidget *parent = stack_widget_active_top();
        switch(bot_QUESTION_POPUP(parent, buffer))
        {
            case GTK_RESPONSE_OK:
            {
                botSoap bot_soap;
                gint soap_err = bot_remove_user_execute(&bot_soap,user_id);
                if(soap_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
                {
                    gtk_list_store_remove(GTK_LIST_STORE(model), &iter);
                    if(g_strcmp0(gtk_label_get_text(admin_user_info_widget->admin_user_name_label), user_name)==0)
                    {
                        bot_admin_user_manage_hide_specific_user_element();
                    }
                }
                else
                {
                    gchar * msg = g_strdup("Lỗi xoá tài khoản. ");
                    GtkWidget *parent = stack_widget_active_top();
                    bot_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
                    g_char_free(msg);
                }
            }
            break;
            case GTK_RESPONSE_CANCEL:
                break;
            default:
                break;
        }
        g_free(user_name);
        g_free(buffer);
    }
}

static void bot_admin_user_manage_show_user_specific(ns1__USER_USCOREINFO_USCOREType *user_info)
{
    GtkTreeIter iter;
    GtkTreeStore *model = GTK_TREE_STORE(admin_user_list_widget->admin_user_list_zone_treestore);

    gint i;
    for(i=0; i<user_info->__sizezone_USCORElist; i++)
    {
        gtk_tree_store_append(model, &iter, NULL);
        gtk_tree_store_set(model, &iter,
                        0                   , user_info->zone_USCORElist[i]->zone_USCOREname,
                        1                     , user_info->zone_USCORElist[i]->zone_USCOREid,
                       -1);
    }

    gtk_label_set_text(GTK_LABEL(admin_user_info_widget->admin_user_id_label), g_strdup_printf("%d", user_info->user_USCOREid));
    gtk_label_set_text(GTK_LABEL(admin_user_info_widget->admin_user_name_label), user_info->user_USCOREaccount);
    gtk_label_set_text(GTK_LABEL(admin_user_info_widget->admin_user_phone_label), user_info->user_USCOREphone);
    gtk_label_set_text(GTK_LABEL(admin_user_info_widget->admin_user_email_label), user_info->user_USCOREemail);

//    DEBUG_0("\n\n\n\n\n SHOW RECIVE 11111");
//    DEBUG_0("\n dcu acc:  %s", user_info->user_USCOREaccount);
//    DEBUG_0("\n dcu pass:  %s", user_info->user_USCOREpass);
//    DEBUG_0("\n dcu mail:  %s", user_info->user_USCOREemail);
//    DEBUG_0("\n dcu phome:  %s", user_info->user_USCOREphone);
//    DEBUG_0("\n dcu id:  %d", user_info->user_USCOREid);
//
//    DEBUG_0("\n dcu manage:  %d", user_info->user_USCOREmanage_USCOREdcu_USCOREprivilege);
//    DEBUG_0("\n lcu manage:  %d", user_info->user_USCOREmanage_USCORElculine_USCOREprivilege);
//    DEBUG_0("\n lcu control: %d", user_info->user_USCOREcontrol_USCORElculine_USCOREprivilege);
//    DEBUG_0("\n lcu control: %d", user_info->user_USCOREcontrol_USCORElculine_USCOREprivilege);
//    DEBUG_0("\n device setup: %d", user_info->user_USCOREsetup_USCOREdevice_USCOREprivilege);
//    DEBUG_0("\n program     : %d", user_info->user_USCOREprogram_USCOREprivilege);
//    DEBUG_0("\n email       : %d", user_info->user_USCOREnotify_USCOREmail_USCOREprivilege);
//    DEBUG_0("\n sms         : %d", user_info->user_USCOREnotify_USCOREsms_USCOREprivilege);
//
//    DEBUG_0("\n email enable: %d", user_info->user_USCOREnotify_USCOREmail_USCOREenable);
//    DEBUG_0("\n sms   enable: %d", user_info->user_USCOREnotify_USCOREsms_USCOREenable);


    gtk_widget_set_visible(admin_user_config_widget->email_allow_box, user_info->user_USCOREnotify_USCOREmail_USCOREenable);

    gtk_widget_set_visible(admin_user_config_widget->sms_allow_box, user_info->user_USCOREnotify_USCOREsms_USCOREenable);

    gtk_widget_set_visible(admin_user_privilege_widget->dcu_box, user_info->user_USCOREmanage_USCOREdcu_USCOREprivilege);

    gtk_widget_set_visible(admin_user_privilege_widget->lcu_box, user_info->user_USCOREmanage_USCORElculine_USCOREprivilege);

    gtk_widget_set_visible(admin_user_privilege_widget->lcu_2_box, user_info->user_USCOREcontrol_USCORElculine_USCOREprivilege);

    gtk_widget_set_visible(admin_user_privilege_widget->device_box, user_info->user_USCOREsetup_USCOREdevice_USCOREprivilege);

    gtk_widget_set_visible(admin_user_privilege_widget->program_box, user_info->user_USCOREprogram_USCOREprivilege);

    gtk_widget_set_visible(admin_user_privilege_widget->email_box, user_info->user_USCOREnotify_USCOREmail_USCOREprivilege);

    gtk_widget_set_visible(admin_user_privilege_widget->sms_box, user_info->user_USCOREnotify_USCOREsms_USCOREprivilege);

    if(user_info->user_USCOREmanage_USCOREdcu_USCOREprivilege)
        gtk_label_set_text(GTK_LABEL(admin_user_info_widget->admin_user_level_label), (gchar *)"Người dùng đặc biệt");
    else
        gtk_label_set_text(GTK_LABEL(admin_user_info_widget->admin_user_level_label), (gchar *)"Người dùng bình thường");


}

static void bot_admin_user_manage_show_specific_user(GtkTreeModel *model, GtkTreeIter *iter)
{
    gint user_id;
    ns1__USER_USCOREINFO_USCOREType **user_list = NULL;
    gint user_list_size;
    gtk_tree_model_get(GTK_TREE_MODEL(model), iter, ADMIN_USER_ID_COLUMN , &user_id, -1);
    bot_clear_tree_store(GTK_TREE_MODEL(admin_user_list_widget->admin_user_list_zone_treestore));
    botSoap bot_soap;
    gint soap_err = bot_get_user_nofree_execute(&bot_soap, user_id, &user_list, &user_list_size);
    if (soap_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
    {
        if (user_list!=NULL && user_list_size==1)
        {
            bot_admin_user_manage_show_user_specific(user_list[0]);
        }
    } else {
        gchar * msg = g_strdup("Lỗi đọc thông tin tài khoản người dùng.");
        GtkWidget *parent = stack_widget_active_top();
        bot_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
        g_char_free(msg);
    }
    bot_free_soap_operation(&bot_soap);
}


static gboolean on_admin_user_manage_treeview_clicked (GtkTreeView        *treeview,
                                                       GdkEventButton     *event,
                                                       gpointer           userdata)
{
    if (event->type == GDK_2BUTTON_PRESS || event->type == GDK_BUTTON_PRESS)
    {
        GtkTreeIter      iter;
        GtkTreeModel     *model;
        GtkTreeSelection *selection;
        selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));

        gboolean is_selected = gtk_tree_selection_count_selected_rows(selection)>0?TRUE:FALSE;
        gtk_widget_set_sensitive(admin_user_manage_popup_menu->M_Edit, is_selected);
        gtk_widget_set_sensitive(admin_user_manage_popup_menu->M_Remove, is_selected);

        if(event->type == GDK_2BUTTON_PRESS)
        {
            switch(event->button)
            {
            case GDK_BUTTON_PRIMARY:
                if(gtk_tree_selection_get_selected(selection, &model, &iter))
                {
                    bot_admin_user_manage_show_specific_user(model, &iter);
                }
                break;
            }
        }
        else if(event->type == GDK_BUTTON_PRESS)
        {
            switch(event->button)
            {
            case GDK_BUTTON_SECONDARY:
                bot_admin_user_manage_popup_menu_show(treeview, event, userdata);
                break;
            }
        }
    }
    return FALSE;
}




static void bot_admin_user_manage_edit_init()
{
    admin_user_manage_edit_widgets = g_slice_new(ADMIN_USER_MANAGE_EDIT_Widgets);

    admin_user_manage_edit_widgets->admin_user_manage_edit_dialog = GTK_WIDGET(bot_OBJECT("admin_user_manage_edit_dialog"));
    admin_user_manage_edit_widgets->admin_user_manage_edit_main_label = GTK_WIDGET(bot_OBJECT("admin_user_manage_edit_main_label"));

    admin_user_manage_edit_widgets->admin_user_manage_edit_id_label = GTK_WIDGET(bot_OBJECT("admin_user_manage_edit_id_label"));
    admin_user_manage_edit_widgets->admin_user_manage_edit_account_label = GTK_WIDGET(bot_OBJECT("admin_user_manage_edit_account_label"));
    admin_user_manage_edit_widgets->admin_user_manage_edit_password_entry = GTK_WIDGET(bot_OBJECT("admin_user_manage_edit_password_entry"));

    admin_user_manage_edit_widgets->admin_user_manage_edit_password_entry_2 = GTK_WIDGET(bot_OBJECT("admin_user_manage_edit_password_entry_2"));
    admin_user_manage_edit_widgets->admin_user_manage_edit_retype_passwd_grid = GTK_WIDGET(bot_OBJECT("admin_user_manage_edit_retype_passwd_grid"));

    admin_user_manage_edit_widgets->admin_user_manage_edit_phone_entry = GTK_WIDGET(bot_OBJECT("admin_user_manage_edit_phone_entry"));
    admin_user_manage_edit_widgets->admin_user_manage_edit_email_entry = GTK_WIDGET(bot_OBJECT("admin_user_manage_edit_email_entry"));

    admin_user_manage_edit_widgets->admin_user_manage_edit_email_notify_checkbutton = GTK_WIDGET(bot_OBJECT("admin_user_manage_edit_email_notify_checkbutton"));
    admin_user_manage_edit_widgets->admin_user_manage_edit_sms_notify_checkbutton = GTK_WIDGET(bot_OBJECT("admin_user_manage_edit_sms_notify_checkbutton"));

    admin_user_manage_edit_widgets->admin_user_manage_edit_level_comboboxtext = GTK_WIDGET(bot_OBJECT("admin_user_manage_edit_level_comboboxtext"));

    admin_user_manage_edit_widgets->admin_user_manage_edit_manage_dcu_box = GTK_WIDGET(bot_OBJECT("admin_user_manage_edit_manage_dcu_box"));
    admin_user_manage_edit_widgets->admin_user_manage_edit_manage_dcu_checkbutton = GTK_WIDGET(bot_OBJECT("admin_user_manage_edit_manage_dcu_checkbutton"));

    admin_user_manage_edit_widgets->admin_user_manage_edit_create_program_checkbutton = GTK_WIDGET(bot_OBJECT("admin_user_manage_edit_create_program_checkbutton"));

    admin_user_manage_edit_widgets->admin_user_manage_edit_manage_lcu_checkbutton = GTK_WIDGET(bot_OBJECT("admin_user_manage_edit_manage_lcu_checkbutton"));
    admin_user_manage_edit_widgets->admin_user_manage_edit_setup_device_checkbutton = GTK_WIDGET(bot_OBJECT("admin_user_manage_edit_setup_device_checkbutton"));
    admin_user_manage_edit_widgets->admin_user_manage_edit_control_lcu_checkbutton = GTK_WIDGET(bot_OBJECT("admin_user_manage_edit_control_lcu_checkbutton"));
    admin_user_manage_edit_widgets->admin_user_manage_edit_email_checkbutton = GTK_WIDGET(bot_OBJECT("admin_user_manage_edit_email_checkbutton"));
    admin_user_manage_edit_widgets->admin_user_manage_edit_sms_checkbutton = GTK_WIDGET(bot_OBJECT("admin_user_manage_edit_sms_checkbutton"));

    admin_user_manage_edit_widgets->admin_user_manage_new_grid = GTK_WIDGET(bot_OBJECT("admin_user_manage_new_grid"));
    admin_user_manage_edit_widgets->admin_user_manage_new_account_entry = GTK_WIDGET(bot_OBJECT("admin_user_manage_new_account_entry"));

    admin_user_manage_edit_widgets->admin_user_manage_edit_grid = GTK_WIDGET(bot_OBJECT("admin_user_manage_edit_grid"));

    admin_user_manage_edit_widgets->admin_user_manage_edit_error_label = GTK_WIDGET(bot_OBJECT("admin_user_manage_edit_error_label"));
    gtk_widget_set_visible(admin_user_manage_edit_widgets->admin_user_manage_edit_error_label, FALSE);

    g_signal_connect (GTK_COMBO_BOX(admin_user_manage_edit_widgets->admin_user_manage_edit_level_comboboxtext), "changed",
                            G_CALLBACK(on_admin_user_manage_edit_privilege_level_changed), NULL);

    g_signal_connect (GTK_COMBO_BOX(admin_user_manage_edit_widgets->admin_user_manage_edit_email_checkbutton), "toggled",
                            G_CALLBACK(on_admin_user_manage_edit_toggle_changed), GINT_TO_POINTER(1));

    g_signal_connect (GTK_COMBO_BOX(admin_user_manage_edit_widgets->admin_user_manage_edit_sms_checkbutton), "toggled",
                            G_CALLBACK(on_admin_user_manage_edit_toggle_changed), GINT_TO_POINTER(2));

    gtk_widget_set_visible(admin_user_manage_edit_widgets->admin_user_manage_edit_retype_passwd_grid, FALSE);

    gtk_window_set_transient_for(GTK_WINDOW(admin_user_manage_edit_widgets->admin_user_manage_edit_dialog), GTK_WINDOW(main_widgets->main_window));

    gtk_widget_set_sensitive(GTK_WIDGET(bot_OBJECT("admin_user_manage_dcu_checkbutton")), FALSE);
}

static void bot_admin_user_manage_add_execute()
{
    ns1__USER_USCOREINFO_USCOREType user_info;
    gint new_user_id;
    struct ADMIN_USER_MANAGE_EDIT_Widgets *p = admin_user_manage_edit_widgets;
    botSoap bot_soap;
    bot_admin_user_manage_user_info_fill(&user_info);
    user_info.user_USCOREaccount = (gchar *)gtk_entry_get_text(GTK_ENTRY(p->admin_user_manage_new_account_entry));
    gint soap_err = bot_add_user_execute(&bot_soap,user_info, &new_user_id);
    if(soap_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
    {
        user_info.user_USCOREid = new_user_id;
        bot_admin_user_manage_user_list_store_insert(&user_info);
    } else {
        gchar * msg = g_strdup("Lỗi thêm mới tài khoản. "); // ham nay co roi sao lai viet moi ?????
        GtkWidget *parent = stack_widget_active_top();
        bot_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
        g_char_free(msg);

    }
}

static void bot_admin_user_manage_user_info_fill(ns1__USER_USCOREINFO_USCOREType *user_info)
{
    /*
        int user_USCOREid;
        char *user_USCOREaccount;
        char *user_USCOREpass;
        char *user_USCOREphone;
        char *user_USCOREemail;
        bool user_USCOREmanage_USCOREdcu_USCOREprivilege;
        bool user_USCOREmanage_USCORElculine_USCOREprivilege;
        bool user_USCOREcontrol_USCORElculine_USCOREprivilege;
        bool user_USCOREsetup_USCOREdevice_USCOREprivilege;
        bool user_USCOREprogram_USCOREprivilege;
        bool user_USCOREnotify_USCOREmail_USCOREprivilege;
        bool user_USCOREnotify_USCOREsms_USCOREprivilege;
        bool user_USCOREnotify_USCOREmail_USCOREenable;
        bool user_USCOREnotify_USCOREsms_USCOREenable;
        int __sizezone_USCORElist;
    */

    struct ADMIN_USER_MANAGE_EDIT_Widgets *p = admin_user_manage_edit_widgets;

    user_info->user_USCOREpass                                   = (gchar *)gtk_entry_get_text(GTK_ENTRY(p->admin_user_manage_edit_password_entry));
    user_info->user_USCOREphone                                  = (gchar *)gtk_entry_get_text(GTK_ENTRY(p->admin_user_manage_edit_phone_entry));
    user_info->user_USCOREemail                                  = (gchar *)gtk_entry_get_text(GTK_ENTRY(p->admin_user_manage_edit_email_entry));
    user_info->user_USCOREcontrol_USCORElculine_USCOREprivilege  = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(p->admin_user_manage_edit_control_lcu_checkbutton));
    user_info->user_USCOREsetup_USCOREdevice_USCOREprivilege     = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(p->admin_user_manage_edit_setup_device_checkbutton));
    user_info->user_USCOREprogram_USCOREprivilege                = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(p->admin_user_manage_edit_create_program_checkbutton));
    user_info->user_USCOREnotify_USCOREmail_USCOREprivilege      = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(p->admin_user_manage_edit_email_checkbutton));
    user_info->user_USCOREnotify_USCOREsms_USCOREprivilege       = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(p->admin_user_manage_edit_sms_checkbutton));

    if(gtk_combo_box_get_active(GTK_COMBO_BOX(p->admin_user_manage_edit_level_comboboxtext))==NORMAL_USER)
        user_info->user_USCOREmanage_USCOREdcu_USCOREprivilege = FALSE;
    else
        user_info->user_USCOREmanage_USCOREdcu_USCOREprivilege = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(p->admin_user_manage_edit_manage_dcu_checkbutton));

    if(user_info->user_USCOREmanage_USCOREdcu_USCOREprivilege)
        user_info->user_USCOREmanage_USCORElculine_USCOREprivilege = TRUE;
    else
        user_info->user_USCOREmanage_USCORElculine_USCOREprivilege   = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(p->admin_user_manage_edit_manage_lcu_checkbutton));

    if(user_info->user_USCOREnotify_USCOREmail_USCOREprivilege)
        user_info->user_USCOREnotify_USCOREmail_USCOREenable = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(p->admin_user_manage_edit_email_notify_checkbutton));
    else
        user_info->user_USCOREnotify_USCOREmail_USCOREenable = FALSE;

    if(user_info->user_USCOREnotify_USCOREsms_USCOREprivilege)
        user_info->user_USCOREnotify_USCOREsms_USCOREenable = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(p->admin_user_manage_edit_sms_notify_checkbutton));
    else
        user_info->user_USCOREnotify_USCOREmail_USCOREenable = FALSE;
}
static void bot_admin_user_manage_edit_execute()
{
    ns1__USER_USCOREINFO_USCOREType user_info;
    botSoap bot_soap;
    struct ADMIN_USER_MANAGE_EDIT_Widgets *p = admin_user_manage_edit_widgets;
    bot_admin_user_manage_user_info_fill(&user_info);
    gchar *id_value                                             = (gchar *)gtk_label_get_text(GTK_LABEL(p->admin_user_manage_edit_id_label));
    user_info.user_USCOREid = g_ascii_strtoll(id_value, NULL, 10);
    user_info.user_USCOREaccount                                = (gchar *)gtk_label_get_text(GTK_LABEL(p->admin_user_manage_edit_account_label));
    gint soap_err = bot_edit_user_execute(&bot_soap, user_info, FALSE);
    if(soap_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
    {
        bot_admin_user_manage_user_list_store_update(&user_info);
        if(g_strcmp0(gtk_label_get_text(admin_user_info_widget->admin_user_name_label), user_info.user_USCOREaccount)==0)
        {
            bot_admin_user_manage_show_user_specific(&user_info);
        }
    } else {
        gchar * msg = g_strdup("Lỗi thay đổi thông tin tài khoản. ");
        GtkWidget *parent = stack_widget_active_top();
        bot_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
        g_char_free(msg);
    }
}

static void bot_admin_user_manage_user_list_store_update(ns1__USER_USCOREINFO_USCOREType *user_info)
{
    GtkTreeIter iter;
    GtkTreeModel *model = GTK_TREE_MODEL(admin_user_list_widget->admin_user_liststore);
    gint user_id;

    if(gtk_tree_model_get_iter_first(model, &iter))
    {
        do
        {
            gtk_tree_model_get(model, &iter, ADMIN_USER_ID_COLUMN, &user_id, -1);
            if(user_id == user_info->user_USCOREid)
                break;
        }
        while(gtk_tree_model_iter_next(model, &iter));
    }

    gboolean dcu_lcu_line_manage_privileges;
    gboolean user_privilege_is_supper_user = user_info->user_USCOREmanage_USCOREdcu_USCOREprivilege;

    if(user_info->user_USCOREmanage_USCOREdcu_USCOREprivilege)
        dcu_lcu_line_manage_privileges = TRUE;
    else
        dcu_lcu_line_manage_privileges = user_info->user_USCOREmanage_USCORElculine_USCOREprivilege;

    gtk_list_store_set(GTK_LIST_STORE(model), &iter,
                        ADMIN_USER_ACCOUNT_COLUMN                   , user_info->user_USCOREaccount,
                        ADMIN_USER_PASSWD_COLUMN                    , user_info->user_USCOREpass,
                        ADMIN_USER_PHONE_COLUMN                     , user_info->user_USCOREphone,
                        ADMIN_USER_EMAIL_COLUMN                     , user_info->user_USCOREemail,
                        ADMIN_USER_PRIVILEGE_IS_SUPPER_USER         , user_privilege_is_supper_user,
                        ADMIN_USER_PRIVILEGE_DCU_MANAGE_COLUMN      , user_info->user_USCOREmanage_USCOREdcu_USCOREprivilege,
                        ADMIN_USER_PRIVILEGE_LCU_LINE_MANAGE_COLUMN , dcu_lcu_line_manage_privileges,
                        ADMIN_USER_PRIVILEGE_LCU_LINE_CONTROL_COLUMN, user_info->user_USCOREcontrol_USCORElculine_USCOREprivilege,
                        ADMIN_USER_PRIVILEGE_SETUP_DEVICE_COLUMN    , user_info->user_USCOREsetup_USCOREdevice_USCOREprivilege,
                        ADMIN_USER_PRIVILEGE_PROGRAM_COLUMN         , user_info->user_USCOREprogram_USCOREprivilege,
                        ADMIN_USER_PRIVILEGE_EMAIL_NOTIFY_COLUMN    , user_info->user_USCOREnotify_USCOREmail_USCOREprivilege,
                        ADMIN_USER_PRIVILEGE_SMS_NOTIFY_COLUMN      , user_info->user_USCOREnotify_USCOREsms_USCOREprivilege,
                        ADMIN_USER_PRIVILEGE_EMAIL_ENABLE_COLUMN    , user_info->user_USCOREnotify_USCOREmail_USCOREenable,
                        ADMIN_USER_PRIVILEGE_SMS_ENABLE_COLUMN      , user_info->user_USCOREnotify_USCOREsms_USCOREenable,
                        ADMIN_USER_ID_COLUMN                        , user_info->user_USCOREid,
                       -1);
}



static void on_admin_user_manage_edit_privilege_level_changed(GtkComboBox *widget, gpointer user_data)
{
    struct ADMIN_USER_MANAGE_EDIT_Widgets *p = admin_user_manage_edit_widgets;
    gtk_widget_set_visible(p->admin_user_manage_edit_manage_dcu_box, gtk_combo_box_get_active(widget)==SUPPER_USER?TRUE:FALSE);
}


static void on_admin_user_manage_edit_toggle_changed(GtkToggleButton *togglebutton, gpointer user_data)
{
    struct ADMIN_USER_MANAGE_EDIT_Widgets *p = admin_user_manage_edit_widgets;
    gboolean is_active = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton));
    switch(GPOINTER_TO_INT(user_data))
    {
        case 1:
        {
            gtk_widget_set_sensitive(p->admin_user_manage_edit_email_notify_checkbutton, is_active);
        }
        break;
        case 2:
        {
            gtk_widget_set_sensitive(p->admin_user_manage_edit_sms_notify_checkbutton, is_active);
        }
        break;
    };
}

void bot_admin_user_manage_hide_specific_user_element()
{
    DEBUG_1();
    gtk_widget_set_visible(admin_user_privilege_widget->dcu_box, FALSE);
    gtk_widget_set_visible(admin_user_privilege_widget->lcu_2_box, FALSE);
    gtk_widget_set_visible(admin_user_privilege_widget->lcu_box, FALSE);
    gtk_widget_set_visible(admin_user_privilege_widget->device_box, FALSE);
    gtk_widget_set_visible(admin_user_privilege_widget->program_box, FALSE);
    gtk_widget_set_visible(admin_user_privilege_widget->email_box, FALSE);
    gtk_widget_set_visible(admin_user_privilege_widget->sms_box, FALSE);

    gtk_widget_set_visible(admin_user_config_widget->email_allow_box, FALSE);
    gtk_widget_set_visible(admin_user_config_widget->sms_allow_box, FALSE);

    gtk_label_set_text(GTK_LABEL(admin_user_info_widget->admin_user_name_label), "");
    gtk_label_set_text(GTK_LABEL(admin_user_info_widget->admin_user_phone_label), "");
    gtk_label_set_text(GTK_LABEL(admin_user_info_widget->admin_user_email_label), "");
    gtk_label_set_text(GTK_LABEL(admin_user_info_widget->admin_user_level_label), "");
}

static void bot_admin_user_manage_zone_own_popup_menu_init()
{
    GtkWidget *separator_item;

    admin_user_manage_zone_own_popup_menu = g_slice_new(ADMIN_USER_MANAGER_ZONE_OWN_PopupMenu);

    admin_user_manage_zone_own_popup_menu->M_Popup = gtk_menu_new();
    bot_MENU_CSS(admin_user_manage_zone_own_popup_menu->M_Popup);

    admin_user_manage_zone_own_popup_menu->M_Change = gtk_menu_item_new_with_label("Thay Đổi");
    gtk_menu_shell_append(GTK_MENU_SHELL(admin_user_manage_zone_own_popup_menu->M_Popup),
                                         admin_user_manage_zone_own_popup_menu->M_Change);
    g_signal_connect(admin_user_manage_zone_own_popup_menu->M_Change, "activate",
                    (GCallback) bot_admin_user_manage_zone_own_popup_menu_clicked, NULL);
}

static void on_zone_own_selected_toggle_callback (GtkCellRendererToggle *cell,
                                                  gchar *path_str,
                                                  gpointer data)
{
    GtkTreeIter iter;
    GtkTreePath *path = gtk_tree_path_new_from_string (path_str);
    gboolean toggle;

    gboolean is_radio = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(admin_zone_own_choose_widget->dialog), "is_radio"));
    if(is_radio)
    {
        if(gtk_tree_model_get_iter_first(GTK_TREE_MODEL(admin_zone_own_choose_widget->treestore), &iter))
        {
            do
            {
                gtk_tree_store_set (GTK_TREE_STORE(admin_zone_own_choose_widget->treestore), &iter, 0, FALSE, -1);
            }
            while(gtk_tree_model_iter_next(GTK_TREE_MODEL(admin_zone_own_choose_widget->treestore), &iter));
        }
    }
    /* get toggled iter */
    gtk_tree_model_get_iter (GTK_TREE_MODEL(admin_zone_own_choose_widget->treestore), &iter, path);
    gtk_tree_model_get (GTK_TREE_MODEL(admin_zone_own_choose_widget->treestore), &iter, 0, &toggle, -1);
    /* set new value */
    gtk_tree_store_set (admin_zone_own_choose_widget->treestore, &iter, 0, !toggle, -1);
    gtk_tree_path_free (path);
}

void bot_admin_zone_own_choose_init()
{
    if(admin_zone_own_choose_widget)
        return;

    admin_zone_own_choose_widget = g_slice_new(struct ADMIN_ZONE_OWN_Widgets);
    admin_zone_own_choose_widget->dialog = GTK_WIDGET(bot_OBJECT("bot_admin_zone_own_choose_dialog"));
    admin_zone_own_choose_widget->treeview = GTK_WIDGET(bot_OBJECT("bot_admin_zone_own_choose_treeview"));

    GtkTreeViewColumn *column;
    GtkCellRenderer   *renderer;

    renderer = gtk_cell_renderer_toggle_new();
    column = gtk_tree_view_column_new_with_attributes("", renderer, "active", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(admin_zone_own_choose_widget->treeview), column);
    g_signal_connect (renderer, "toggled", G_CALLBACK (on_zone_own_selected_toggle_callback), NULL);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes ("Tên khu vực", renderer, "text", 1, NULL);
    gtk_tree_view_column_set_resizable(column,TRUE);
    gtk_tree_view_column_set_reorderable(column, TRUE);
    gtk_tree_view_append_column (GTK_TREE_VIEW(admin_zone_own_choose_widget->treeview), column);

    admin_zone_own_choose_widget->treestore = gtk_tree_store_new(3, G_TYPE_BOOLEAN, G_TYPE_STRING, G_TYPE_INT);

    gtk_tree_view_set_model(GTK_TREE_VIEW(admin_zone_own_choose_widget->treeview),
                            GTK_TREE_MODEL(admin_zone_own_choose_widget->treestore));
    g_object_unref(G_OBJECT(admin_zone_own_choose_widget->treestore));
}

static gboolean is_current_user_belong_to(gint zone_id)
{
    GtkTreeIter iter;
    gint zone_id_treestore;
    GtkTreeModel *model = GTK_TREE_MODEL(admin_user_list_widget->admin_user_list_zone_treestore);
    if(gtk_tree_model_get_iter_first(model, &iter))
    {
        do
        {
            gtk_tree_model_get(model, &iter, 1, &zone_id_treestore, -1);
            if(zone_id==zone_id_treestore)
            {
                return TRUE;
            }
        }
        while(gtk_tree_model_iter_next(model, &iter));
    }
    return FALSE;
}

static gint bot_admin_zone_own_choose_fill_list_zone()
{
    GtkTreeIter iter;
    gboolean is_own;
    GtkTreeStore *store = admin_zone_own_choose_widget->treestore;
    GSList *zonelist_iter = NULL;
    gint zone_count = 0;
    LIST_ZONE_FOR_EACH_ENTRY(zonelist_iter)
    {
        pbotZone _zone = (pbotZone)zonelist_iter->data;
        is_own = is_current_user_belong_to(_zone->zonecode);
        gtk_tree_store_append(store, &iter, NULL);
        gtk_tree_store_set(store, &iter, 0, is_own, 1, _zone->zonename, 2, _zone->zonecode, -1);
        zone_count++;
    }
    return zone_count;
}

static void bot_admin_user_manage_zone_own_change_run(gint user_id, gint count_all_zone)
{
    /* Get user's information */
    ns1__USER_USCOREINFO_USCOREType user_info;
    botSoap bot_soap;
    user_info.user_USCOREid = user_id;
    user_info.user_USCOREaccount = g_strdup(gtk_label_get_text(GTK_LABEL(admin_user_info_widget->admin_user_name_label)));
    user_info.user_USCOREemail = g_strdup("");
    user_info.user_USCOREphone = g_strdup("");
    user_info.user_USCOREpass = g_strdup("");

    /* Get list zone here */
    GtkTreeIter iter;
    GtkTreeModel *model = GTK_TREE_MODEL(admin_zone_own_choose_widget->treestore);
    gint zone_id;
    gchar *zone_name;
    gboolean is_own;
    gint count_own_zone = 0;
    DEBUG("count_all_zone: %d", count_all_zone);
    ns1__ZONE_USCOREINFO_USCOREType *zone_list[count_all_zone];
    if(gtk_tree_model_get_iter_first(model, &iter))
    {
        do
        {
            gtk_tree_model_get(model, &iter, 0, &is_own, 1, &zone_name, 2, &zone_id, -1);
            if(is_own)
            {
                ns1__ZONE_USCOREINFO_USCOREType *zone = new ns1__ZONE_USCOREINFO_USCOREType();
                zone_list[count_own_zone]=zone;
                zone->zone_USCOREname = g_strdup(zone_name);
                zone->zone_USCOREnote = g_strdup("");
                zone->zone_USCOREid   = zone_id;
                DEBUG_0("\n zone_list[%d].zoneid = %d", count_own_zone, zone_id);
                count_own_zone++;
            }
            g_free(zone_name);
        }
        while(gtk_tree_model_iter_next(model, &iter));
    }

    for(gint i=0; i<count_own_zone; i++)
    {
        DEBUG_0("\n zonelist[%d]: %d", i, zone_list[i]->zone_USCOREid);
    }

    user_info.__sizezone_USCORElist = count_own_zone;
    user_info.zone_USCORElist = zone_list;

    DEBUG_0("\n username: %s", user_info.user_USCOREaccount);
    DEBUG_0("\n userid: %d", user_info.user_USCOREid);
    DEBUG_0("\n size zonelist: %d", user_info.__sizezone_USCORElist);
    for(gint i=0; i<user_info.__sizezone_USCORElist; i++)
    {
        DEBUG_0("\n i: %d", i);
        DEBUG_0("\n zonelist[%d]: %d", i, user_info.zone_USCORElist[i]->zone_USCOREid);
    }
    DEBUG_1();

    gint soap_err = bot_edit_user_execute(&bot_soap, user_info, TRUE);
    if(soap_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
    {
        /* update for new zonelist */
        DEBUG_1();
        bot_admin_zone_list_update(zone_list, count_own_zone);
    }
    else
    {
        gchar * msg = g_strdup_printf("Lỗi cập nhật danh sách khu vực quản lý của người dùng '%s'", user_info.user_USCOREaccount);
        GtkWidget *parent = stack_widget_active_top();
        bot_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
        g_char_free(msg);
    }
    for(gint j=0; j<count_own_zone; j++)
    {
        g_free(zone_list[j]->zone_USCOREname);
        g_free(zone_list[j]->zone_USCOREnote);
        g_free(zone_list[j]);
    }
}

static void bot_admin_user_manage_zone_own_popup_menu_clicked(void)
{
    bot_admin_zone_own_choose_init();
    const gchar *tmp = gtk_label_get_text(GTK_LABEL(admin_user_info_widget->admin_user_id_label));
    g_return_if_fail(tmp);
    if(g_strcmp0(tmp, "")==0)
    {
        GtkWidget *parent = stack_widget_active_top();
        bot_ERROR_POPUP(parent, "Xin chọn một tài khoản người dùng.");
        return;
    }
    gint user_id = (gint)g_ascii_strtoll(tmp, NULL, 10);
    bot_clear_tree_store(GTK_TREE_MODEL(admin_zone_own_choose_widget->treestore));
    gint count_all_zone = bot_admin_zone_own_choose_fill_list_zone();
    g_object_set_data(G_OBJECT(admin_zone_own_choose_widget->dialog), "is_radio", GINT_TO_POINTER(FALSE));

    bot_DIALOG_SHOW(admin_zone_own_choose_widget->dialog);
    gint response_id = gtk_dialog_run(GTK_DIALOG(admin_zone_own_choose_widget->dialog));
    switch(response_id)
    {
    case DIALOG_OK_RESPONSE:
        {
            bot_admin_user_manage_zone_own_change_run(user_id, count_all_zone);
        }
        break;
    case DIALOG_CANCEL_RESPONSE:
        break;
    }
    bot_DIALOG_HIDE(admin_zone_own_choose_widget->dialog);
}

static void bot_admin_user_manage_zone_own_popup_menu_show(GtkTreeView *treeview, GdkEventButton *event, gpointer userdata)
{
    gtk_widget_show_all(GTK_WIDGET(admin_user_manage_zone_own_popup_menu->M_Popup));
    gtk_menu_popup(GTK_MENU(admin_user_manage_zone_own_popup_menu->M_Popup), NULL, NULL, NULL, NULL,
                   (event != NULL) ? event->button : 0, gdk_event_get_time((GdkEvent*)event));
}


static gboolean on_admin_user_manage_zone_own_treeview_clicked (GtkTreeView        *treeview,
                                                                GdkEventButton     *event,
                                                                gpointer           userdata)
{
    DEBUG_1();
    if (event->type == GDK_BUTTON_PRESS)
    {
        GtkTreeIter      iter;
        GtkTreeModel     *model;
        GtkTreeSelection *selection;
        selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));

        if(event->type == GDK_BUTTON_PRESS)
        {
            switch(event->button)
            {
            case GDK_BUTTON_SECONDARY:
                bot_admin_user_manage_zone_own_popup_menu_show(treeview, event, userdata);
                break;
            }
        }
    }
    return FALSE;
}

static void bot_admin_zone_list_update(ns1__ZONE_USCOREINFO_USCOREType *zone_info[], gint zone_size)
{
    GtkTreeIter iter;
    GtkTreeStore *store = admin_user_list_widget->admin_user_list_zone_treestore;

    bot_clear_tree_store(GTK_TREE_MODEL(store));

    for(gint i=0; i<zone_size; i++)
    {
        gtk_tree_store_append(store, &iter, NULL);
        gtk_tree_store_set(store, &iter, 0, zone_info[i]->zone_USCOREname,
                                         1, zone_info[i]->zone_USCOREid, -1);
    }
}
/** ================================================================================================================================== **/


