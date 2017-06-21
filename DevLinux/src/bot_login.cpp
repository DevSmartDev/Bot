#include <sys/stat.h>
#include "bot_login.h"

gboolean isLogined = FALSE;
pBotLogin wLogin = NULL;

gboolean botLogin()
{
    if(isLogined)
    {
        return TRUE;
    }
    static gboolean isInitWidget = FALSE;
    if(!isInitWidget)
    {
        wLogin = g_new0(BOT_LOGIN_WIDGET, 1);
        wLogin->dlg     = GTK_DIALOG(bot_lookup_w_by_name("BOT_login_dialoge"));
        wLogin->user    = GTK_WIDGET(bot_lookup_w_by_name("entry_bot_user"));
        wLogin->pass    = GTK_WIDGET(bot_lookup_w_by_name("entry_bot_pass"));
        wLogin->remember= GTK_WIDGET(bot_lookup_w_by_name("cb_remember_me"));
        wLogin->server  = GTK_WIDGET(bot_lookup_w_by_name("entry_bot_server_ip"));
        wLogin->port    = GTK_WIDGET(bot_lookup_w_by_name("entry_bot_port"));
        wLogin->db_name = GTK_WIDGET(bot_lookup_w_by_name("entry_bot_db_name"));
        wLogin->db_user = GTK_WIDGET(bot_lookup_w_by_name("entry_bot_db_user"));
        wLogin->db_pass = GTK_WIDGET(bot_lookup_w_by_name("entry_bot_db_pass"));
        wLogin->lb_err  = GTK_LABEL(bot_lookup_w_by_name("lb_bot_login_error"));
        isInitWidget = TRUE;
    }
    gtk_widget_hide(GTK_WIDGET(wLogin->lb_err));
    gtk_widget_show(GTK_WIDGET(wLogin->dlg));
    gint responseID;
    gchar *user, *pass, *dbServer, *dbPort, *dbName, *dbUser, *dbPass;
    while( 1)
    {
        responseID = gtk_dialog_run(wLogin->dlg);
        if(responseID == GTK_RESPONSE_OK)
        {
            user = gtk_entry_get_text(GTK_ENTRY(wLogin->user));
            pass = gtk_entry_get_text(GTK_ENTRY(wLogin->pass));
            dbServer = gtk_entry_get_text(GTK_ENTRY(wLogin->server));
            dbPort = gtk_entry_get_text(GTK_ENTRY(wLogin->port));
            dbName = gtk_entry_get_text(GTK_ENTRY(wLogin->db_name));
            dbUser = gtk_entry_get_text(GTK_ENTRY(wLogin->db_user));
            dbPass = gtk_entry_get_text(GTK_ENTRY(wLogin->db_pass));
            if(user == NULL || strlen(user) == 0)
            {
                gtk_label_set_text(wLogin->lb_err, "Username is empty");
                goto __error;
            }
            if(pass == NULL || strlen(pass) == 0)
            {
                gtk_label_set_text(wLogin->lb_err, "Password is empty");
                goto __error;
            }
            if(!dbServer || !dbPort || !dbName  || !dbUser || !dbPass)
                goto __db_error;

            break;
__db_error:
            gtk_label_set_text(wLogin->lb_err, "Please configure database in 'Advance Settings'");
__error:
            gtk_widget_show_all(wLogin->dlg);
        }
    }
    saveLoginConfig(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(wLogin->remember)));
    gtk_widget_hide(GTK_WIDGET(wLogin->dlg));
}

gboolean botLogout()
{

}

