#ifndef BOT_ERROR_H_INCLUDED
#define BOT_ERROR_H_INCLUDED
#ifndef __bot_CHART__
#include "main.h"
#include "bot_utils.h"
#else
#include "../gtkdatabox/main.h"
#endif
#include "gsoap/soapStub.h"
#include <map>


#define LOGOUT_TIMOUT_ERROR ((gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__INVALID_USCORELOGIN_USCOREERR)
#define LOGOUT_OTHER_ERROR ((gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__LOGIN_USCOREWITH_USCOREOTHER_USCOREDEV_USCOREERR)



#define bot_ERROR_POPUP(parent, message)           \
    bot_utils_message_box(GTK_WINDOW(parent),      \
                          GTK_MESSAGE_ERROR,       \
                          GTK_BUTTONS_OK,          \
                          (gchar *)message         \
                          )

#define bot_WARNING_POPUP(parent, message)        \
    bot_utils_message_box(GTK_WINDOW(parent),     \
                          GTK_MESSAGE_WARNING,    \
                          GTK_BUTTONS_OK,         \
                          (gchar *)message        \
                          )

#define bot_QUESTION_POPUP(parent, message)           \
    bot_utils_message_box(GTK_WINDOW(parent),     \
                          GTK_MESSAGE_QUESTION,    \
                          GTK_BUTTONS_OK_CANCEL,  \
                          (gchar *)message        \
                          )

#define bot_QUESTION_YES_NO_POPUP(parent, message)           \
    bot_utils_message_box(GTK_WINDOW(parent),     \
                          GTK_MESSAGE_QUESTION,    \
                          GTK_BUTTONS_YES_NO ,  \
                          (gchar *)message        \
                          )

#define bot_INFO_POPUP(parent, message)           \
    bot_utils_message_box(GTK_WINDOW(parent),     \
                          GTK_MESSAGE_INFO,       \
                          GTK_BUTTONS_OK,         \
                          (gchar *)message        \
                          )


#define bot_DIALOG_SHOW(widget)                   \
{                                                 \
    set_parent_widget_active(GTK_WIDGET(widget)); \
    set_sensitive_widget_topstack(FALSE);         \
    stack_widget_active_push(GTK_WIDGET(widget)); \
}

#define bot_DIALOG_HIDE(widget)             \
{                                           \
    gtk_widget_hide(GTK_WIDGET(widget));    \
    stack_widget_active_pop();              \
    set_sensitive_widget_topstack(TRUE);    \
}


extern std::map<gint, const gchar *> MessageResultMap;

gboolean bot_error_init(void);

void bot_error_finalize(void);

gboolean bot_error_check_message_result(GtkWidget *parentWidget,gchar *msg, gint result_code);

gboolean bot_error_notifice_run(GtkWidget *parentWidget, gchar *notifice_content);
#endif // BOT_ERROR_H_INCLUDED
