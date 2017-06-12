#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <gtk/gtk.h>
#include <glib/gstdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SET_LOCATION_ROOT 1
#define LAT_HOME    10.868658
#define LON_HOME    106.795967
#define LAT_ROOT    0
#define LON_ROOT    0

#define ROOT_GPS(lat, lon) {lat = LAT_ROOT; lon = LON_ROOT;}
#define HOME_GPS(lat, lon) {lat = LAT_HOME; lon = LON_HOME;}
typedef enum CSSTYPE
{
    CSS_TYPE_NONE   = -1,
    CSS_FRAME,
    CSS_TREEVIEW,
    CSS_WIDGET,
    CSS_MENU,
    CSS_MENU_BAR,
    CSS_MENU_ITEM,
    CSS_MENU_SEARCH,
    CSS_MENU_NOTEBOOK
}CSSTYPE;


enum SPL_NOTEBOOK_PAGE_Enum
{
    SPL_NOTEBOOK_DCU_PAGE           = 0,
    SPL_NOTEBOOK_PROGRAM_PAGE       = 1,
    SPL_NOTEBOOK_USER_LOG_PAGE      = 2,
    SPL_NOTEBOOK_SERVER_LOG_PAGE    = 3,
    SPL_NOTEBOOK_USER_MANAGE_PAGE   = 4,
    SPL_NOTEBOOK_ZONE_MANAGE_PAGE   = 5,
    SPL_NOTEBOOK_PAGE_NUMBER
};

enum SPL_DCU_NOTEBOOK_PAGE_Enum
{
    SPL_DCU_NOTEBOOK_DCU_PAGE           = 0,
    SPL_DCU_NOTEBOOK_LCU_PAGE           = 1,
    SPL_DCU_NOTEBOOK_PAGE_NUMBER
};

extern char * smartstreetlight_server_url;

extern GtkTextBuffer *notification_text_buffer;
extern gboolean show_debug;

#define SPL_MENU_CSS(widget)         smartstreetlight_set_private_css_provide(CSS_MENU, widget)

#define SPL_OBJECT(name_widget)      gtk_builder_get_object (smartstreetlight_builder, name_widget)


#define SPL_DCU_UNKNOWN_MODE    "<none>"
#define SPL_DCU_WIRELESS_MODE   "Wireless Mode"
#define SPL_DCU_LINE_MODE       "Line Mode"

#define SPL_LCU_UNKNOWN_MODE    "<none>"
#define SPL_LCU_SCHEDULE_MODE   "Schedule Mode"
#define SPL_LCU_MANUAL_MODE     "Manual Mode"

#define SPL_STATUS_ACTIVE       "Active"
#define SPL_STATUS_INACTIVE     "Inactive"

#if 1
    #define SPL_SERVER_URL_DEFAULT "http://14.161.7.19"
    #define SPL_SERVER_PORT_DEFAULT "8447"
#else
    #define SPL_SERVER_URL_DEFAULT "http://localhost"
    #define SPL_SERVER_PORT_DEFAULT "8447"
#endif // 0

#define SPL_SERVER_SIDE_DEFAULT "axis2/services/smartstreetlightService"

/**
Common define
*/


enum
{
    ICON_LIGHT_ON = 0,
    ICON_LIGHT_OFF,
    ICON_LIGHT_BROKEN ,
    ICON_LIGHT_ON_SELECTED,
    ICON_LIGHT_OFF_SELECTED,
    ICON_LIGHT_BROKEN_SELECTED,
    ICON_LIGHT_ON_P_SELECTED, //parent selected
    ICON_LIGHT_OFF_P_SELECTED,
    ICON_LIGHT_BROKEN_P_SELECTED,
    ICON_LIGHT_NUM_COUNT,
};

enum
{
    ICON_DEF_ADD = ICON_LIGHT_NUM_COUNT,
    ICON_DEF_BACK,
    ICON_DEF_NEXT,
    ICON_DEF_EDIT,
    ICON_DEF_TICK,
    ICON_DEF_REMOVE,
    ICON_DEF_DOWN,
    ICON_DEF_FIND,
    ICON_DEF_HOME,
    ICON_DEF_ZOOM_OUT,
    ICON_DEF_ZOOM_IN,
    ICON_DEF_CHECKBOX_UNCHECKED,
    ICON_DEF_CHECKBOX_CHECKED,
    ICON_DEF_CHECKBOX_PARTIAL,
    ICON_DEF_NOTICATION,
    ICON_DEF_ICON_NAME_COUNT,
};

extern const gchar* icon_name[ICON_DEF_ICON_NAME_COUNT];
extern gchar* INSTALL_PATH;

void smartstreetlight_main_server_info_update(const gchar *server_url, const gchar *server_port);

gboolean smartstreetlight_application_init(void);

void smartstreetlight_application_run(void);

void smartstreetlight_finalize (GtkWidget *object, gpointer user_data);
#endif // MAIN_H_INCLUDED

