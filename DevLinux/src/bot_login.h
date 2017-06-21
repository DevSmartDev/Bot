#ifndef BOT_LOGIN_H_INCLUDED
#define BOT_LOGIN_H_INCLUDED

#include "main.h"

extern gboolean isLogined;
typedef struct BOT_LOGIN_WIDGET
{
    GtkDialog   *dlg;
    GtkWidget   *user;
    GtkWidget   *pass;
    GtkWidget   *remember;
    GtkWidget   *server;
    GtkWidget   *port;
    GtkWidget   *db_name;
    GtkWidget   *db_user;
    GtkWidget   *db_pass;
    GtkLabel    *lb_err;
} botLogin, *pBotLogin;

extern pBotLogin wLogin;
gboolean botLogin();
gboolean botLogout();

#endif // BOT_LOGIN_H_INCLUDED
