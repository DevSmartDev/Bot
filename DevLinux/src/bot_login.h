#ifndef BOT_LOGIN_H_INCLUDED
#define BOT_LOGIN_H_INCLUDED

#include "main.h"

typedef enum bot_LOGIN_RESULT_ENUM
{
    bot_LOGIN_OK,
    bot_LOGIN_FAIL,
    bot_LOGIN_CANCEL
} bot_LOGIN_RESULT_ENUM;

extern gboolean is_admin_mode;
extern gboolean isLogining;

typedef struct CURRENT_ACCOUNT_LOGIN
{
    gint   bot_current_id;
    gchar *bot_current_username;
    gchar *bot_current_password;
    gchar *bot_current_phone;
    gchar *bot_current_email;

    gboolean bot_current_user_is_admin_mode;

    gboolean bot_current_user_is_enable_sms_notify;
    gboolean bot_current_user_is_enable_email_notify;
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

//bot_LOGIN_RESULT_ENUM bot_login(void);

gboolean bot_login_init(void);

gboolean bot_login_finalize(void);

void bot_login_success(gint user_id,
                                    const gchar *username,
                                    const gchar *password,
                                    const gchar *phone,
                                    const gchar *email,
                                    gboolean sms_notify,
                                    gboolean email_notify,
                                    gboolean admin_privilege);
void bot_user_logout(void);
void bot_logout(const gchar* notifice_content);

void bot_current_account_show(void);

gboolean bot_login();

#endif // BOT_LOGIN_H_INCLUDED
