#ifndef SMARTSTREETLIGHT_ADMIN_ZONE_H_INCLUDED
#define SMARTSTREETLIGHT_ADMIN_ZONE_H_INCLUDED

#include "main.h"
#include "smartstreetlight_utils.h"
#include "smartstreetlight_callback.h"
#include "smartstreetlight_ui_method.h"
#include "smartstreetlight_dcu.h"

enum
{
    ADMIN_USER_ZONE_NAME_COLUMN = 0,
    ADMIN_USER_ZONE_NOTE_COLUMN,

    ADMIN_USER_ZONE_ID_COLUMN,
    ADMIN_USER_DCU_ID_COLUMN,

    ADMIN_USER_ZONE_PIXBUF_COLUMN,
    ADMIN_USER_ZONE_RGBA_COLUMN,

    ADMIN_USER_ZONE_TYPE_COLUMN,

    ADMIN_USER_ZONE_NUNBER_COLUMN
};

typedef enum ADMIN_ZONE_MANAGE_POPUP_Enum
{
    ADMIN_ZONE_M_ADD = 0,
    ADMIN_ZONE_M_EDIT,
    ADMIN_ZONE_M_REMOVE,

    ADMIN_ZONE_M_MOVE,

    ADMIN_ZONE_M_NUMBER

}ADMIN_ZONE_MANAGE_POPUP_Enum;

typedef struct ADMIN_ZONE_MANAGE_PopupMenu
{
    GtkWidget *M_Popup;
    GtkWidget *M_Add;
    GtkWidget *M_Edit;
    GtkWidget *M_Remove;
    GtkWidget *M_Move;

    GtkWidget *M_Sep_1;
    GtkWidget *M_Sep_2;

}ADMIN_ZONE_MANAGE_PopupMenu;


typedef struct SPL_ADMIN_ZONE_Widgets
{
    GtkWidget       *list_zone_treeview;
    GtkTreeStore    *list_zone_treestore;
    GtkWidget       *admin_zone_map_box;

} SPL_ADMIN_ZONE_Widgets;

typedef struct SPL_ADMIN_ZONE_EDIT_Widgets
{
    GtkWidget       *dialog;
    GtkWidget       *main_label;
    GtkWidget       *error_label;
    GtkWidget       *id_label;

    GtkWidget       *name_entry;
    GtkWidget       *note_entry;

} SPL_ADMIN_ZONE_EDIT_Widgets;

gboolean spl_admin_zone_manage_init(void);

void spl_admin_zone_manage_finalize(void);

//void spl_admin_zone_show_specific(GtkTreePath *path);

gboolean spl_admin_zone_show_tab_on_notebook(void);

//void spl_admin_zone_run(void);

gboolean spl_admin_zone_manage_specific_show(pSplZone zone_data);

void spl_admin_zone_manage_popup_menu_show(GtkTreeView *treeview, GdkEventButton *event, gpointer userdata);
#endif // SMARTSTREETLIGHT_ADMIN_ZONE_H_INCLUDED
