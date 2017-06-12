#ifndef SMARTSTREETLIGHT_LOGIN_H_INCLUDED
#define SMARTSTREETLIGHT_LOGIN_H_INCLUDED

#include "main.h"

typedef enum SPL_LOGIN_RESULT_ENUM
{
    SPL_LOGIN_OK,
    SPL_LOGIN_FAIL,
    SPL_LOGIN_CANCEL
} SPL_LOGIN_RESULT_ENUM;

extern gboolean is_admin_mode;
extern gboolean isLogining;

typedef struct CURRENT_ACCOUNT_LOGIN
{
    gint   spl_current_id;
    gchar *spl_current_username;
    gchar *spl_current_password;
    gchar *spl_current_phone;
    gchar *spl_current_email;

    gboolean spl_current_user_is_admin_mode;

    gboolean spl_current_user_is_enable_sms_notify;
    gboolean spl_current_user_is_enable_email_notify;
} CURRENT_ACCOUNT_LOGIN;

typedef struct CURRENT_ACCOUNT_WIDGET
{
    GtkLabel *user_info_account_label;
    GtkEntry *user_info_password_entry;
    GtkEntry *user_info_password_2_entry;
    GtkEntry *user_info_phone_entry;
    GtkEntry *user_info_email_entry;

    GtkCheckButton *user_enable_notify_sms_checkbutton;
    GtkCheckButton *user_enable_notify_email_checkbutton;

    GtkGrid *user_info_retype_passwd_new_grid;

} CURRENT_ACCOUNT_WIDGET;

extern struct CURRENT_ACCOUNT_LOGIN *current_account;

//SPL_LOGIN_RESULT_ENUM smartstreetlight_login(void);

gboolean smartstreetlight_login_init(void);

gboolean smartstreetlight_login_finalize(void);

void smartstreetlight_login_success(gint user_id,
                                    const gchar *username,
                                    const gchar *password,
                                    const gchar *phone,
                                    const gchar *email,
                                    gboolean sms_notify,
                                    gboolean email_notify,
                                    gboolean admin_privilege);
void smartstreetlight_user_logout(void);
void smartstreetlight_logout(const gchar* notifice_content);

void smartstreetlight_current_account_show(void);

gboolean spl_login();

#endif // SMARTSTREETLIGHT_LOGIN_H_INCLUDED
