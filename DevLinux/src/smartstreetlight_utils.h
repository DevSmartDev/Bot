#ifndef SMARTSTREETLIGHT_UTILS_H_INCLUDED
#define SMARTSTREETLIGHT_UTILS_H_INCLUDED

#include "mapviewer.h"
#include "main.h"


/* We define these the same for all machines.
   Changes from this to the outside world should be done in `_exit'.  */
#define	EXIT_FAILURE	1	/* Failing exit status.  */
#define	EXIT_SUCCESS	0	/* Successful exit status.  */

#define ENTER_KEY_VALUE     65293
#define MAX_PATH_SPL        1024
#define MAX_PAGE_VIEW_NUM   50
#define CONFIG_FILE         "config"

enum SMARTLIGHT_DIALOG_RESPONSE
{
    DIALOG_CANCEL_RESPONSE          = 1,
    DIALOG_OK_RESPONSE              = 2,
    DIALOG_UPDATE_RESPONSE          = 2

};


typedef enum SPL_LISTSTORE_FILL_Enum
{
    LISTSTORE_PROGRAM_ALL_INFO = 0,
    LISTSTORE_PROGRAM_LCU_CONTROL
}SPL_LISTSTORE_FILL_Enum;


enum
{
    DCU_LOG_ID_COLUMN = 0,
    DCU_LOG_DCU_ID_COLUMN,
    DCU_LOG_CONTENT_COLUMN,
    DCU_LOG_TYPE_COLUMN,
    DCU_LOG_TIME_COLUMN,
    DCU_LOG_NUM_COLUMNS
};


typedef struct SmartStreetLight_Widgets
{
	GtkWidget	*login_dialog;
	GtkWidget	*main_window;
	GtkWidget	*main_notebook;

	GtkWidget	*create_schedule_dialog;
	GtkWidget   *starttime_choose_dialog;
	GtkWidget   *dcu_update_window;

	GtkWidget   *add_dcu_dialog;
	GtkWidget   *delete_element_dialog;
	GtkWidget   *notification_dialog;
	GtkWidget   *edit_dcu_dialog;

    GtkWidget   *lcu_info_box;
	GtkWidget   *add_lcu_dialog;
	GtkWidget   *lcu_control_dialog;

	GtkWidget   *new_schedule_dialog;

	GtkWidget   *program_choose_dialog;

    GtkWidget   *devices_log_dialog;

    GtkWidget   *day_schedule_dialog_new;

    GtkWidget   *schedule_item_new_dialog;

    GtkWidget   *dcu_custom_program_dialog;

    GtkWidget   *user_information_dialog;

    GtkWidget   *remember_login_checkbutton;

    GtkWidget   *lcu_chart_dialog;

    GtkWidget   *lcu_slope_datetime_dialog;


} SmartStreetLight_Widgets;

typedef struct _SplLogPaging
{
    gint                curPage;
	gint                totalItem;
	gint                minIndex;
	gint                maxIndex;
	gint                selected;
	gboolean            allowDel;
}SplLogPaging;

typedef struct _SplChartObject
{
    gboolean    isSave;
    gchar       *startTime;
    gchar       *endTime;
}SplChartObject;

typedef struct SPL_Object
{
    gchar           *configure_dir;
    gchar           *configure_full_path;
    gchar           *username;
    gchar           *password;
    gchar           *server_url;
    gchar           *server_port;
    SplChartObject  *chart;
} SPL_Object;

typedef struct _SplObjectMove
{
    OsmGpsMapImage  *image;
    gint            type;
    gchar           *name;
    gfloat          lat;
    gfloat          lon;
    gpointer        object;
    GtkWidget       *dialog;
    GtkBox          *map_box;
    GtkLabel        *lbname;
    GtkLabel        *lbdevice;
    GtkEntry        *lat_entry;
    GtkEntry        *lon_entry;
}SplObjectMove, *pSplObjectMove;


typedef struct _SplDataObject
{
    GtkTreeModelFilter  *filter;
    GtkListStore        *store;
    SplLogPaging        *paging;
    void                (*update_information_func)();
    gint                (*soap_delete_function)(gpointer, gint);
}SplDataObject;

extern SPL_Object *spl_object;

extern SmartStreetLight_Widgets	*main_widgets;
extern GtkBuilder               *smartstreetlight_builder;

extern GdkRGBA BG_COLOR_UNKNOWN;
extern GdkRGBA BG_COLOR_NORMAL;
extern GdkRGBA BG_COLOR_ACTIVE;
extern GdkRGBA BG_COLOR_ERROR;
extern GdkRGBA BG_COLOR_OFF;
extern GdkRGBA BG_COLOR_MANUAL;
extern pSplObjectMove ObjMove;

#define X_NOTIFICE "Thiếu xót từ ứng dụng"

//extern MYSQL                    *smartlight_sql_connection;
/* Macro print debug (alvinnguyen) */

#ifdef __RELEASE__
	#define __DEBUG__(format, ...) { };
#else
    #ifdef WIN32
        #include "winsock2.h"
        #include "windows.h"
        BOOL WINAPI AttachConsole(DWORD);
        #define __DEBUG__(format, ...)\
            if (show_debug) {\
                if( !AttachConsole(-1))\
                {\
                    gchar* _tmp_1 = g_strdup_printf("%s\n",format);\
                    gchar* _tmp_ = g_strdup_printf(_tmp_1,## __VA_ARGS__);\
                    DWORD count;\
                    WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), _tmp_, strlen(_tmp_), &count, NULL);\
                    g_free(_tmp_1);\
                    g_free(_tmp_);\
                }\
            }
    #else
         #define __DEBUG__(format, ...) fprintf (stderr, format, ## __VA_ARGS__)
    #endif
#endif

#define DEBUG(fmt, args...) __DEBUG__("%s||%s():%d:: " fmt "\n",__FILE__,__FUNCTION__, __LINE__, ##args)
#define DEBUG_0(format, ...) __DEBUG__(format, ## __VA_ARGS__)
#define DEBUG_1() DEBUG("\n")

#define g_char_free(str ) if(str != NULL) g_free(str);
#define radtodeg(rad) (rad / 180 * M_PI)

#ifdef WIN32

/* On Win32, the canonical directory separator is the backslash, and
 * the search path separator is the semicolon. Note that also the
 * (forward) slash works as directory separator.
 */
#define G_DIR_SEPARATOR '\\'
#define G_DIR_SEPARATOR_S "\\"
#define G_IS_DIR_SEPARATOR(c) ((c) == G_DIR_SEPARATOR || (c) == '/')
#define G_SEARCHPATH_SEPARATOR ';'
#define G_SEARCHPATH_SEPARATOR_S ";"
#define CONFIG_DIR	        "\\.smartstreetlight\\"

#else  /* !WIN32 */

#define G_DIR_SEPARATOR '/'
#define G_DIR_SEPARATOR_S "/"
#define G_IS_DIR_SEPARATOR(c) ((c) == G_DIR_SEPARATOR)
#define G_SEARCHPATH_SEPARATOR ':'
#define G_SEARCHPATH_SEPARATOR_S ":"
#define CONFIG_DIR	        "/.smartstreetlight/"
#endif /* !WIN32 */


void spl_gtk_parent_set_sensitive(GtkWidget *widget);

gint spl_utils_message_box(GtkWindow *parent, GtkMessageType type, GtkButtonsType btn, const gchar* msg);

gboolean spl_widget_change_parent(GtkWidget *object, GtkWidget *old_parent, GtkWidget *new_parent);

gboolean spl_utils_mkdir(const gchar *path, gboolean create_parent_dirs);

void spl_utils_widgets_hide_all(void);

void spl_utils_free_slist(GSList **list, GDestroyNotify free_func);

gint utils_get_setting_integer(GKeyFile *config, const gchar *section, const gchar *key,
							   const gint default_value);

gboolean utils_get_setting_boolean(GKeyFile *config, const gchar *section, const gchar *key,
								   const gboolean default_value);

gchar *utils_get_setting_string(GKeyFile *config, const gchar *section, const gchar *key,
								const gchar *default_value);

gchar *utils_get_locale_from_utf8(const gchar *utf8_text);

gboolean utils_write_file(const gchar *filename, const gchar *text);

gchar *get_homedir(void);

gboolean osm_gps_map_change_parent(const gchar* oldparent, const gchar* newparent);

gboolean osm_gps_map_set_lcu_center(gpointer lcu);

void osm_gps_map_move_object();

void osm_gps_map_redraw_object();

void osm_gps_map_image_change_image(OsmGpsMapImage *image, GdkPixbuf *buf);

GDateTime * spl_gdatetime_from_str(gchar *data);

void set_parent_widget_active(GtkWidget *child);

void stack_widget_active_push(GtkWidget *item);

void stack_widget_active_pop();

void set_sensitive_widget_topstack(gboolean is_sensitive);

GtkWidget * stack_widget_active_top(void);
#endif // SMARTSTREETLIGHT_UTILS_H_INCLUDED

