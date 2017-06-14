#ifndef BOT_ADMIN_USER_H_INCLUDED
#define BOT_ADMIN_USER_H_INCLUDED

#include "main.h"
#include "bot_utils.h"
#include "bot_callback.h"
#include "bot_ui_method.h"

enum
{
    NORMAL_USER = 0,
    SUPPER_USER = 1
};

enum
{
    ADMIN_USER_ACCOUNT_COLUMN = 0,
    ADMIN_USER_PASSWD_COLUMN,
    ADMIN_USER_PHONE_COLUMN,
    ADMIN_USER_EMAIL_COLUMN,

    ADMIN_USER_PRIVILEGE_IS_SUPPER_USER,

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum ADMIN_USER_MANAGE_POPUP_Enum
{
    ADMIN_USER_M_ADD = 0,
    ADMIN_USER_M_EDIT,
    ADMIN_USER_M_REMOVE,

    ADMIN_USER_M_NUMBER
}ADMIN_USER_MANAGE_POPUP_Enum;

typedef struct ADMIN_USER_MANAGE_PopupMenu
{
    GtkWidget *M_Popup;
    GtkWidget *M_Add;
    GtkWidget *M_Edit;
    GtkWidget *M_Remove;
}ADMIN_USER_MANAGE_PopupMenu;

typedef struct ADMIN_USER_MANAGER_ZONE_OWN_PopupMenu
{
    GtkWidget *M_Popup;
    GtkWidget *M_Change;

}ADMIN_USER_MANAGER_ZONE_OWN_PopupMenu;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct ADMIN_USER_LIST_Widget
{
    GtkWidget *admin_user_treeview;
    GtkListStore *admin_user_liststore;

    GtkWidget *admin_user_list_zone_treeview;
    GtkTreeStore *admin_user_list_zone_treestore;

}ADMIN_USER_LIST_Widget;

extern struct ADMIN_USER_LIST_Widget *admin_user_list_widget;

typedef struct ADMIN_USER_PRIVILEGE_Widget
{
    GtkWidget *dcu_box;
    GtkWidget *lcu_box;
    GtkWidget *lcu_2_box;
    GtkWidget *device_box;
    GtkWidget *program_box;

    GtkWidget *email_box;
    GtkWidget *sms_box;

}ADMIN_USER_PRIVILEGE_Widget;

extern struct ADMIN_USER_PRIVILEGE_Widget *admin_user_privilege_widget;

typedef struct ADMIN_USER_CONFIG_Widget
{
    GtkWidget *email_allow_box;
    GtkWidget *sms_allow_box;

}ADMIN_USER_CONFIG_Widget;

extern struct ADMIN_USER_CONFIG_Widget *admin_user_config_widget;

typedef struct ADMIN_USER_INFO_Widget
{
    GtkLabel *admin_user_id_label;
    GtkLabel *admin_user_name_label;
    GtkLabel *admin_user_phone_label;
    GtkLabel *admin_user_email_label;
    GtkLabel *admin_user_level_label;

}ADMIN_USER_INFO_Widget;

typedef struct ADMIN_ZONE_OWN_Widgets
{
    GtkWidget *dialog;
    GtkWidget *treeview;
    GtkTreeStore *treestore;

}ADMIN_ZONE_OWN_Widgets;

typedef struct ADMIN_USER_MANAGE_EDIT_Widgets
{
    GtkWidget       *admin_user_manage_edit_dialog;
    GtkWidget       *admin_user_manage_edit_main_label;

    GtkWidget       *admin_user_manage_new_grid;
    GtkWidget       *admin_user_manage_new_account_entry;

    GtkWidget       *admin_user_manage_edit_grid;
    GtkWidget       *admin_user_manage_edit_id_label;
    GtkWidget       *admin_user_manage_edit_account_label;
    GtkWidget       *admin_user_manage_edit_password_entry;

    GtkWidget       *admin_user_manage_edit_password_entry_2;
    GtkWidget       *admin_user_manage_edit_retype_passwd_grid;

    GtkWidget       *admin_user_manage_edit_phone_entry;
    GtkWidget       *admin_user_manage_edit_email_entry;

    GtkWidget       *admin_user_manage_edit_email_notify_checkbutton;
    GtkWidget       *admin_user_manage_edit_sms_notify_checkbutton;

    GtkWidget       *admin_user_manage_edit_level_comboboxtext;

    GtkWidget       *admin_user_manage_edit_manage_dcu_box;
    GtkWidget       *admin_user_manage_edit_manage_dcu_checkbutton;

    GtkWidget       *admin_user_manage_edit_manage_lcu_checkbutton;
    GtkWidget       *admin_user_manage_edit_setup_device_checkbutton;
    GtkWidget       *admin_user_manage_edit_control_lcu_checkbutton;
    GtkWidget       *admin_user_manage_edit_create_program_checkbutton;
    GtkWidget       *admin_user_manage_edit_email_checkbutton;
    GtkWidget       *admin_user_manage_edit_sms_checkbutton;

    GtkWidget       *admin_user_manage_edit_error_label;

} ADMIN_USER_MANAGE_EDIT_Widgets;

extern struct ADMIN_USER_MANAGE_EDIT_Widgets *admin_user_manage_edit_widgets;

extern struct ADMIN_USER_INFO_Widget *admin_user_info_widget;

extern struct ADMIN_ZONE_OWN_Widgets *admin_zone_own_choose_widget;

gboolean bot_admin_user_manage_init(void);

gboolean bot_admin_user_manage_finalize(void);

gboolean bot_admin_user_manage_run(void);

void bot_admin_user_manage_hide_specific_user_element();

void bot_admin_zone_own_choose_init();

#endif // BOT_ADMIN_USER_H_INCLUDED

