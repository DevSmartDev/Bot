#include "smartstreetlight_dcu.h"
#include "smartstreetlight_soap.h"
#include "smartstreetlight_lcu.h"
#include "smartstreetlight_line.h"
#include "smartstreetlight_log.h"
#include "smartstreetlight_schedule.h"
#include "smartstreetlight_login.h"
#include "smartstreetlight_error.h"
#include "smartstreetlight_event_thread.h"
#include "smartstreetlight_soap_thread.h"
#include "smartstreetlight_error.h"
#include "mapviewer.h"
#include <map>
#include <stdlib.h>
#include <math.h>
#include <glib.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include <iostream>
#include <string>

/** ------------------------------------------------------------------------------ **/
/* ------------------------------------------------------------------------------ */
/*                             CONTROL AND SCHEDULE FOR DCU                       */
/** ------------------------------------------------------------------------------ **/
//////////// DATA ///////////////
struct _SplControlSchedule_Widgets *dcu_control_schedule_widgets;

////////// METHOD ///////////////
static void spl_dcu_control_init();

static void spl_dcu_control_finalize();

static void on_dcu_control_selection_changed_callback(GtkTreeSelection *treeselection,
        gpointer user_data);
static void on_dcu_control_on_off_callback (GtkCellRendererToggle *cell,
        gchar *path_str,
        gpointer data);
static void on_dcu_control_switch_activate_callback(GtkSwitch *widget,
        gboolean   state,
        gpointer   user_data);
static void on_dcu_schedule_interleaved_changed_callback(GtkComboBox *widget,
        gpointer user_data);
static void spl_dcu_control_dialog_as_manual_show(pSplDcu dcu);
static void spl_dcu_control_dialog_as_schedule_show(pSplDcu dcu);
static void dcu_control_manual_show_hide(gboolean is_show);
static void dcu_control_schedule_show_hide(gboolean is_show);
static GSList * dcu_schedule_interleaved_prepare(pSplDcu dcu);
static pSplLcu dcu_schedule_interleaved_scheck_incense(GSList *lcu_list);
static void spl_dcu_control_schedule_get_lcu_list_with_state(GString **lights_is_on,
        GString **lights_is_off);
/** ------------------------------------------------------------------------------ **/


static void on_dcu_control_switch_interleaved_callback(GtkSwitch *widget, gboolean   state, gpointer   user_data);
static void on_dcu_control_schedule_program_changed_callback(GtkComboBox *widget, gpointer user_data);
static void dcu_schedule_interleaved_show_hide(gboolean is_show);

static void spl_dcu_control_window_accelerator_pressed(GtkWidget *widget, GdkEventKey *event, gpointer data);
/** **************************************************************************************** **/

GSList *dculist = NULL;
GHashTable* dcumap = NULL;
GSList *closestUsingDculist = NULL;
GSList *zonelist = NULL;
GHashTable* zonemap = NULL;
gboolean showAllLightEnable = FALSE;
gboolean isControlShow = FALSE;

//GtkWidget *dcu_dialog_control = NULL;

pSplWidgets  main_view_widgets = NULL;

SplDcuMenuPopup *dcu_popup_menu = NULL;
pSplDcu dcuprev= NULL;

void map_image_remove_all()
{
    GSList  * item;
    LIST_ZONE_FOR_EACH_ENTRY(item)
    {
        SplZone  *zone = (SplZone*)  item->data;
        if (zone)
        {
            zone->isshowmap = FALSE;
        }
    }
    dcuprev= NULL;
    osm_gps_map_image_remove_all(map);
}
void osm_gps_map_show_lights_of_zone(pSplDcu dcu)
{
    SplZone * zone;
    pSplDcu dcuzone = NULL;
    GSList *itemDcu;
//    DEBUG("SHOW_ALL_DCU_IN_ZONE\n");
    if (dcu == NULL)
    {
        return;
    }
    if (LOCKUP_LIST_ZONE(&dcu->priv->zonecode, zone))
    {
//        DEBUG("SHOW_ALL_DCU_IN_ZONE 1 \n");
        if (zone != NULL)
        {
//            DEBUG("SHOW_ALL_DCU_IN_ZONE 2 \n");
//            DEBUG("\n zone->isshowmap: %d - FALSE: %d\n", zone->isshowmap, FALSE);
            if (zone->isshowmap == FALSE)
            {
//                DEBUG("SHOW_ALL_DCU_IN_ZONE 3 \n");

                map_image_remove_all();
                zone->isshowmap = TRUE;
                for(itemDcu = zone->dculistzone; itemDcu != NULL; itemDcu = itemDcu->next)
                {
                    dcuzone = (pSplDcu)itemDcu->data;
                    if (dcuzone != NULL)
                    {
                        gfloat lat = 0, lon = 0;
                        GSList *item;
                        if (SIZE_LIST_LCU(dcuzone) == 0)
                        {
                            create_new_light_instances(dcuzone);
                        }
                        LIST_LCU_FOR_EACH_ENTRY(dcuzone,item)
                        {
                            pSplLcu lcu = (pSplLcu)item->data;
                            spl_lcu_add_image(lcu, spl_get_light_icon(lcu, FALSE, dcu == dcuzone), &lat, &lon);
                        }

                    }
                }
                dcuprev= dcu;
            }
            else if (dcuprev != dcu)
            {
//                DEBUG("SHOW_ALL_DCU_IN_ZONE\n");
                /* un choise old dcu */
                GSList *item;
                LIST_LCU_FOR_EACH_ENTRY(dcuprev,item)
                {
                    pSplLcu lcu = (pSplLcu)item->data;
                    if (lcu->icon)
                    {
                        osm_gps_map_image_change_image(lcu->icon, spl_get_light_icon(lcu, FALSE, FALSE));
                    }
                }
                LIST_LCU_FOR_EACH_ENTRY(dcu,item)
                {
                    pSplLcu lcu = (pSplLcu)item->data;
                    if (lcu->icon)
                    {
                        osm_gps_map_image_change_image(lcu->icon, spl_get_light_icon(lcu, FALSE, TRUE));
                    }
                }
                dcuprev = dcu;
            }

        }

    }
    for(itemDcu = zone->dculistzone; itemDcu != NULL; itemDcu = itemDcu->next)
    {
        dcuzone = (pSplDcu)itemDcu->data;
        if(dcuzone!=NULL)
        {
            GSList *item;
            gboolean isFound=FALSE;
            LIST_LCU_FOR_EACH_ENTRY(dcuzone,item)
            {
                pSplLcu lcu = (pSplLcu)item->data;
                if (lcu /*&& (lcu->lat != 0 && lcu->lon!=0)*/)
                {
                    osm_gps_map_set_center(map, lcu->lat, lcu->lon);
                    isFound=TRUE;
                    break;
                }
            }
            if (isFound == TRUE)
                break;
        }
    }
}

void osm_gps_map_show_lights_of_dcu(pSplDcu dcu)
{
    gfloat lat = 0, lon = 0;
    g_return_if_fail(dcu);
    GSList *item;

    LIST_LCU_FOR_EACH_ENTRY(dcu, item)
    {
        pSplLcu lcu = (pSplLcu)item->data;

        DEBUG("LCU: %s", lcu->id);
        DEBUG("lcu->lat: %f - lcu->lon: %f", lcu->lat, lcu->lon);

        spl_lcu_add_image(lcu, spl_get_light_icon(lcu, FALSE,FALSE), &lat, &lon);

        DEBUG("lcu->lat 2: %f - lcu->lon 2: %f", lcu->lat, lcu->lon);
        DEBUG("lat: %f - lon: %f\n\n\n", lat, lon);
    }



    if(lat)
    {
        osm_gps_map_set_center(map, lat, lon);
    }
}
gboolean on_combo_box_display_changed(GtkWidget *cbb, gpointer p)
{
    //DEBUG_1();
    gint index =  gtk_combo_box_get_active(GTK_COMBO_BOX(cbb));
    osm_osm_gps_map_show_lights(index, lastSelectedDcu);
//    gtk_widget_hide(index == DISPLAY_FOLLOW_DCU
//                    ? GTK_WIDGET(main_view_widgets->lcu_all_view)
//                    : GTK_WIDGET(main_view_widgets->lcu_view));
//
//    gtk_widget_show_all(index == DISPLAY_FOLLOW_DCU
//                        ? GTK_WIDGET(main_view_widgets->lcu_view)
//                        : GTK_WIDGET(main_view_widgets->lcu_all_view));
    return TRUE;
}

void osm_osm_gps_map_remove_dcu( pSplDcu dcu)
{
    if (dcu != NULL)
    {
        GSList *item;
        LIST_LCU_FOR_EACH_ENTRY(dcu,item)
        {
            pSplLcu lcu = (pSplLcu)item->data;
            if (lcu->icon)
                osm_gps_map_image_remove (map,lcu->icon);
        }
    }
}
void osm_osm_gps_map_show_lights(gint index, pSplDcu dcu)
{
    DEBUG("osm_osm_gps_map_show_lights\n");
    if (dcu == NULL)
        return;
    switch (index)
    {
    case DISPLAY_FOLLOW_DCU:
        DEBUG("DISPLAY_FOLLOW_DCU\n");
        if(lastSelectedDcu!= NULL)
        {
            map_image_remove_all();
            osm_gps_map_show_lights_of_dcu(dcu);
        }
        break;
    case DISPLAY_FOLLOW_ZONE:
        DEBUG("DISPLAY_FOLLOW_ZONE\n");
        osm_gps_map_show_lights_of_zone(dcu);
        break;
    }
    if (SIZE_LIST_LCU(dcu) != 0)
    {
        pSplLcu lcu = (pSplLcu)lastSelectedDcu->priv->childlist->data;
        osm_gps_map_set_center(map, lcu->lat, lcu->lon);
    }
}
void spl_main_view_widgets_init()
{
    if(main_view_widgets == NULL)
        main_view_widgets = g_new0(SplWidgets, 1);
}

static void spl_dcu_priv_free(SplDcuPrivate *priv)
{
    if(priv)
    {
        g_char_free(priv->address);
        g_char_free(priv->gps);
        g_char_free(priv->id);
        g_char_free(priv->name);
        g_char_free(priv->note);
        g_char_free(priv->phonenum);
        g_char_free(priv->zonename);
        g_char_free(priv->programName);
        g_free(priv);
    }
}

void spl_dcu_free(pSplDcu pDcu)
{
    g_return_if_fail(pDcu);
    spl_dcu_priv_free(pDcu->priv);
    g_free(pDcu);
}

pSplDcu spl_dcu_init()
{
    pSplDcu dcu = g_new0(SplDcu, 1);
    SplDcuPrivate *priv = g_new0(SplDcuPrivate, 1);
    priv->address = NULL;
    priv->gps = NULL;
    priv->id = NULL;
    priv->name = NULL;
    priv->note = NULL;
    priv->phonenum = NULL;
    priv->zonename = NULL;
    priv->mode = 0;
    priv->status = 0;
    priv->programId= 0;
    priv->programIdPrev= 0;
    priv->programName= NULL;
    dcu->priv = priv;
    INIT_LIST_LCU(dcu);
    return dcu;
}

static void spl_dcu_view_init()
{
    static gboolean isInitDcuView = FALSE;
    GtkCellRenderer *render;
    GtkTreeViewColumn *column;
    GtkTreeSelection *selection;
    if(!isInitDcuView)
    {
        main_view_widgets = g_new0(SplWidgets, 1);
        main_view_widgets->dcu_view =
            GTK_TREE_VIEW(gtk_builder_get_object (smartstreetlight_builder, "dcu_info_tree_view"));
        g_object_set_data(G_OBJECT(main_view_widgets->dcu_view), "current_parent", (gpointer)"dcu_info_container");
        main_view_widgets->dcu_store =
            gtk_tree_store_new(OBJECT_NUM_COLUMNS, G_TYPE_STRING, G_TYPE_POINTER, G_TYPE_INT);
        render = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Khu vực", render, "text", OBJECT_NAME_COLUMN, NULL);
        gtk_tree_view_column_set_clickable(column, TRUE);
        gtk_tree_view_append_column(GTK_TREE_VIEW(main_view_widgets->dcu_view), column);
        gtk_tree_view_set_model(GTK_TREE_VIEW(main_view_widgets->dcu_view), GTK_TREE_MODEL(main_view_widgets->dcu_store));
        selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(main_view_widgets->dcu_view));
        gtk_tree_selection_set_mode(selection, GTK_SELECTION_SINGLE);
        //signal
        g_signal_connect(selection, "changed",  G_CALLBACK(on_dcu_selection_changed), GINT_TO_POINTER(FALSE));
        g_signal_connect(main_view_widgets->dcu_view, "button-press-event", G_CALLBACK(on_dcu_view_info_clicked), NULL);
        isInitDcuView = TRUE;
    }
}

static void spl_dcu_popup_menu_init()
{
    static gboolean isInitDcuMenuPopup = FALSE;
    if(isInitDcuMenuPopup)
        return;
    dcu_popup_menu = g_new0(SplDcuMenuPopup, 1);
    GtkWidget *separator_item;
    dcu_popup_menu->parent = gtk_menu_new();
    SPL_MENU_CSS(dcu_popup_menu->parent);

    dcu_popup_menu->mAdd = gtk_menu_item_new_with_label("Thêm mới");
    gtk_menu_shell_append(GTK_MENU_SHELL(dcu_popup_menu->parent),dcu_popup_menu->mAdd);

    separator_item = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(dcu_popup_menu->parent), separator_item);

    dcu_popup_menu->mEdit = gtk_menu_item_new_with_label("Chỉnh sửa");
    gtk_menu_shell_append(GTK_MENU_SHELL(dcu_popup_menu->parent),dcu_popup_menu->mEdit);

    separator_item = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(dcu_popup_menu->parent), separator_item);

    dcu_popup_menu->mLog = gtk_menu_item_new_with_label("Nhật ký");
    gtk_menu_shell_append(GTK_MENU_SHELL(dcu_popup_menu->parent),dcu_popup_menu->mLog);

    separator_item = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(dcu_popup_menu->parent), separator_item);

    dcu_popup_menu->mSchedule = gtk_menu_item_new_with_label("Lập lịch");
    gtk_menu_shell_append(GTK_MENU_SHELL(dcu_popup_menu->parent),dcu_popup_menu->mSchedule);

    separator_item = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(dcu_popup_menu->parent), separator_item);

    dcu_popup_menu->mControl = gtk_menu_item_new_with_label("Điều khiển");
    gtk_menu_shell_append(GTK_MENU_SHELL(dcu_popup_menu->parent),dcu_popup_menu->mControl);

    separator_item = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(dcu_popup_menu->parent), separator_item);

    dcu_popup_menu->mRemove= gtk_menu_item_new_with_label("Xóa");
    gtk_menu_shell_append(GTK_MENU_SHELL(dcu_popup_menu->parent),dcu_popup_menu->mRemove);

    dcu_popup_menu->mRemove_all = gtk_menu_item_new_with_label("Xóa tất cả");
    gtk_menu_shell_append(GTK_MENU_SHELL(dcu_popup_menu->parent),dcu_popup_menu->mRemove_all);
    /**
        init signal
    */
    g_signal_connect(dcu_popup_menu->mAdd, "activate",
                     (GCallback) smartstreetlight_dcu_popup_menu_clicked, GINT_TO_POINTER(SPL_DCU_M_ADD));

    g_signal_connect(dcu_popup_menu->mEdit, "activate",
                     (GCallback) smartstreetlight_dcu_popup_menu_clicked, GINT_TO_POINTER(SPL_DCU_M_EDIT));

    g_signal_connect(dcu_popup_menu->mLog, "activate",
                     (GCallback) smartstreetlight_dcu_popup_menu_clicked, GINT_TO_POINTER(SPL_DCU_M_LOG));

    g_signal_connect(dcu_popup_menu->mSchedule, "activate",
                     (GCallback) smartstreetlight_dcu_popup_menu_clicked, GINT_TO_POINTER(SPL_DCU_M_SCHEDULE));

    g_signal_connect(dcu_popup_menu->mRemove, "activate",
                     (GCallback) smartstreetlight_dcu_popup_menu_clicked, GINT_TO_POINTER(SPL_DCU_M_REMOVE));

    g_signal_connect(dcu_popup_menu->mRemove_all, "activate",
                     (GCallback) smartstreetlight_dcu_popup_menu_clicked, GINT_TO_POINTER(SPL_DCU_M_REMOVE_ALL));

    g_signal_connect(dcu_popup_menu->mControl, "activate",
                     (GCallback) smartstreetlight_dcu_popup_menu_clicked, GINT_TO_POINTER(SPL_DCU_M_CONTROL));

    isInitDcuMenuPopup = TRUE;
}


static void spl_add_list_light_from_dcu(pSplDcu dcu)
{
    GtkTreeViewColumn *column;
    GSList *item;
    if(!main_view_widgets->lcu_view)
        return;
    smartstreetlight_tree_store_clean(SPL_LCU_STORE);
    gtk_widget_hide(GTK_WIDGET(main_view_widgets->lcu_all_view));
    gtk_widget_show_all(GTK_WIDGET(main_view_widgets->lcu_view));
    column = gtk_tree_view_get_column(main_view_widgets->lcu_view, LIGHT_ID);
    gtk_tree_view_column_set_title(column, dcu->priv->id);
    LIST_LCU_FOR_EACH_ENTRY(dcu,item)
    {
        GtkTreeIter iter;
        pSplLcu lcu = (pSplLcu)item->data;
        if(lcu->parent != dcu)
            break;
        gtk_tree_store_append(main_view_widgets->lcu_store, &iter, NULL);
        gtk_tree_store_set(main_view_widgets->lcu_store, &iter, LIGHT_ID, lcu->id, LIGHT_POINTER, lcu, -1);
    }

}

void spl_dcu_set_information(pSplDcu dcu)
{
    gchar *str;
    if(dcu == NULL)
        return;
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object (smartstreetlight_builder, "lb_dcu_id")),
                       dcu->priv->id);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object (smartstreetlight_builder, "lb_dcu_phone")),
                       dcu->priv->phonenum);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object (smartstreetlight_builder, "lb_dcu_location")),
                       dcu->priv->gps);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object (smartstreetlight_builder, "lb_dcu_note")),
                       dcu->priv->note);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object (smartstreetlight_builder, "lb_dcu_zone")),
                       dcu->priv->zonename);
    str = smartstreetlight_get_status_mode(dcu->priv->status);
    //DEBUG("mode_name: %s\n",str);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object (smartstreetlight_builder, "lb_dcu_mode")),
                       str);
    g_free(str);
    str = smartstreetlight_get_status_connect(dcu->priv->status);
    //DEBUG("connect_name: %s\n",str);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object (smartstreetlight_builder, "lb_dcu_connect")),
                       str);
    g_free(str);
    str = smartstreetlight_get_status_name(dcu->priv->status);
    // DEBUG("status_name: %s\n",str);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object (smartstreetlight_builder, "lb_dcu_status")),
                       str);
    g_free(str);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object (smartstreetlight_builder, "lb_dcu_address")),
                       dcu->priv->address);
    //cbb_program_name
    if(dcu->priv->programId == 0)
    {
        if (dcu->priv->programName != NULL)
            g_free(dcu->priv->programName);
        dcu->priv->programName= g_strdup("<Chưa thiết lập>");

    }
    else
    {
        //DEBUG ("dcu->priv->programId: %d,  dcu->priv->programIdPrev: %d\n", dcu->priv->programId,  dcu->priv->programIdPrev);
        if (dcu->priv->programId != dcu->priv->programIdPrev ||
                dcu->priv->programName == NULL)
        {
            ns1__PROGRAM_USCOREINFO_USCOREType ** program = NULL;
            SplSoap spl_soap;
            gint program_size;
            if (dcu->priv->programName != NULL)
            {
                g_free(dcu->priv->programName);
                dcu->priv->programName = NULL;
            }

            gint soap_err = smartstreetlight_get_program_list_nofree_execute(&spl_soap,dcu->priv->zonecode,dcu->priv->programId, &program, &program_size);
            if (soap_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)

            {
                if (program != NULL)
                {
                    dcu->priv->programName = g_strdup(program[0]->program_USCOREname);
                    dcu->priv->programIdPrev = dcu->priv->programId;
                }
            } else {
                 gchar * msg = g_strdup("Lỗi lấy danh sách chương trình từ server. ");
                GtkWidget *parent = stack_widget_active_top();
                smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
                g_char_free(msg);

            }
            smartstreetlight_free_soap_operation(&spl_soap);
            if(dcu->priv->programName == NULL)
            {
                dcu->priv->programName= g_strdup("<Chưa thiết lập>");
            }
        }
         //DEBUG ("dcu->priv->programId: %d,  dcu->priv->programIdPrev: %d, dcu->priv->programName: %s\n", dcu->priv->programId,  dcu->priv->programIdPrev,
          //      dcu->priv->programName);
    }

    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object (smartstreetlight_builder, "cbb_program_name")),
                       dcu->priv->programName);
    lastSelectedLcu = NULL;
    spl_add_list_light_from_dcu(dcu);

}
gchar * smartstreetlight_get_status_mode(gint status)
{
    gchar * msg;
    if (status & SPL_DCU_MANUAL_MODE)
    {
        msg = g_strdup ("Điều khiển bằng tay");
    }
    else
    {
        msg = g_strdup ("Điều khiển lập lịch");
    }
    return msg;
}
gchar * smartstreetlight_get_status_connect(gint status)
{
    gchar * msg;
    if (status & SPL_DCU_ONLINE)
    {
        msg = g_strdup ("Kết nối");
    }
    else
    {
        msg = g_strdup ("Chưa kết nối");
    }
    return msg;
}
gchar * smartstreetlight_get_status_name(gint status)
{
    gboolean is_err= FALSE;
    gchar * msg = (gchar *)"";
    if (status & SPL_DCU_ERROR_RF)
    {
        is_err= TRUE;
        msg = g_strconcat(msg, "Lỗi RF,",NULL);

    }
    if (status & SPL_DCU_ERROR_SYNC_MODE)
    {
        is_err= TRUE;
        msg = g_strconcat(msg, "Lỗi mất đồng bộ chế độ hoạt động,", NULL);
    }
    if (status & SPL_DCU_ERROR_SYNC_LCU)
    {
        is_err= TRUE;
        msg = g_strconcat(msg, "Lỗi mất đồng bộ đèn,", NULL);
    }
    if (status & SPL_DCU_ERROR_SYNC_LINE)
    {
        is_err= TRUE;
        msg = g_strconcat(msg, "Lỗi mất đồng bộ cổng điều khiển đèn,", NULL);
    }
    if (status & SPL_DCU_ERROR_SCHEDULE_LCU)
    {
        is_err= TRUE;
        msg = g_strconcat(msg, "Lỗi lập lịch đèn,", NULL);
    }
    if (status & SPL_DCU_ERROR_SCHEDULE_LINE)
    {
        is_err= TRUE;
        msg = g_strconcat(msg, "Lỗi lập lịch cổng điều khiển đèn,", NULL);
    }
    if (status & SPL_DCU_ERROR_LOCK_DCU)
    {
        is_err= TRUE;
        msg = g_strconcat(msg, "Lỗi hư thời gian thực,", NULL);
    }
    if (status & SPL_DCU_ERROR_MEM_DCU)
    {
        is_err= TRUE;
        msg = g_strconcat(msg, "Lỗi hư bộ nhớ,", NULL);
    }

    if (is_err == FALSE)
    {
        msg = g_strdup ("Đang hoạt động");
    }
    return msg;
}



void smartstreetlight_zone_fill_infomation(const gint zone_id,
        const gchar *zone_name,
        const gchar *zone_note)
{
    GtkTreeIter iter;
    GtkTreeIter child_iter;
    SplSoap spl_soap;
    SplZone *zone = g_new0(SplZone, 1);
    zone->zonecode = zone_id;
    zone->zonename = g_strdup(zone_name);
    zone->zonenote = g_strdup(zone_note);
    zone->isshowmap = FALSE;
    zone->dculistzone = NULL;
    ns1__DCU_USCOREINFO_USCOREType **dcu_list= NULL;
    gint dcu_list_size;
    gtk_tree_store_append (main_view_widgets->dcu_store, &zone->zoneIter, NULL);
    gtk_tree_store_set (main_view_widgets->dcu_store, &zone->zoneIter,
                        OBJECT_NAME_COLUMN, zone_name,
                        OBJECT_POINTER_COLUMN, (gpointer)zone,
                        OBJECT_TYPE_COLUMN, (gint)OBJECT_IS_ZONE_TYPE,
                        -1);
    gint soap_err = smartstreetlight_get_dcu_list_nofree_execute(&spl_soap,zone_id, 0, &dcu_list, &dcu_list_size);
    if (soap_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
    {
        if (dcu_list!=NULL)
        {
            gint i;
            for(i = 0; i<dcu_list_size; i++)
            {
                ns1__DCU_USCOREINFO_USCOREType *soapDCU = dcu_list[i];
                pSplDcu _dcu = spl_dcu_init();
                SplDcuPrivate *priv = _dcu->priv;
                priv->address = g_strdup(soapDCU->dcu_USCOREaddress);
                priv->gps = g_strdup(soapDCU->dcu_USCOREgps);
                priv->id = g_strdup(soapDCU->dcu_USCOREid);
                priv->note = g_strdup(soapDCU->dcu_USCOREnote);
                priv->phonenum = g_strdup(soapDCU->dcu_USCOREphone);
                priv->mode = soapDCU->dcu_USCOREmode;
                priv->status = soapDCU->dcu_USCOREstatus;
                priv->programId = soapDCU->dcu_USCOREprogram_USCOREid;
                priv->scheduleId= 0;
                priv->zonecode = soapDCU->dcu_USCOREzoneid;
                priv->zonename = g_strdup(zone->zonename);
                //add into treeview

                gtk_tree_store_append(main_view_widgets->dcu_store, &priv->iter, (GtkTreeIter *)&zone->zoneIter);
                gtk_tree_store_set(main_view_widgets->dcu_store, &priv->iter,
                                   0, priv->id,
                                   1, (gpointer)_dcu,
                                   2, OBJECT_IS_DCU_TYPE,
                                   -1);
                PREPEND_LIST_DCU(_dcu, zone);
            }
            if(i < MAX_DCU_MAYBE)
                showAllLightEnable = TRUE;
            else
                showAllLightEnable = FALSE;

        }
    }
    else
    {
        gchar * msg = g_strdup("Lỗi lấy danh sách trạm từ server. ");
        GtkWidget *parent = stack_widget_active_top();
        smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
        g_char_free(msg);
    }
    smartstreetlight_free_soap_operation(&spl_soap);
    APPEND_LIST_ZONE(zone);
}

void spl_zone_free(void *data)
{
    SplZone *zone = (SplZone *)data;
    if(zone)
    {
        g_char_free(zone->zonename);
        g_char_free(zone->zonenote);
        g_slist_free(zone->dculistzone);
        g_free(zone);
    }
}


void smartstreetlight_dcu_finalize(void)
{
    FREE_LIST_DCU_FINAL(spl_dcu_free);
    //g_slist_free_full(dculist, (GDestroyNotify)spl_dcu_free);
    if(!IS_EMPTY_LIST_ZONE)
        FREE_LIST_ZONE(spl_zone_free);

    spl_dcu_control_finalize();
}

gboolean smartstreetlight_dcu_info_init(void)
{
    spl_dcu_view_init();
    spl_dcu_popup_menu_init();
    spl_log_init();

    return TRUE;
}


void smartstreetlight_dcu_show_all()
{
    ns1__ZONE_USCOREINFO_USCOREType **zone_list = NULL;
    gint zone_list_size;
    smartstreetlight_tree_store_clean(SPL_DCU_STORE);
    SplSoap spl_soap;
    gint soap_err = smartstreetlight_get_all_zone_nofree_execute(&spl_soap,&zone_list, &zone_list_size);
    if (soap_err ==ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
    {
        if (zone_list != NULL)
        {
            gtk_tree_store_clear(main_view_widgets->dcu_store);

            for(gint i = 0; i<zone_list_size; i++)
            {
                ns1__ZONE_USCOREINFO_USCOREType *zone=zone_list[i];
                smartstreetlight_zone_fill_infomation(zone->zone_USCOREid,
                                                      zone->zone_USCOREname,
                                                      zone->zone_USCOREnote);
                /*GtkTreeIter iter;
                gint k = 1;
                if(gtk_tree_model_get_iter_first(GTK_TREE_MODEL(main_view_widgets->dcu_store), &iter))
                {
                    do
                    {
                        DEBUG("iter: %d has %d child\n", k++,
                              gtk_tree_model_iter_n_children(GTK_TREE_MODEL(main_view_widgets->dcu_store), &iter));
                    }
                    while(gtk_tree_model_iter_next(GTK_TREE_MODEL(main_view_widgets->dcu_store), &iter));
                }*/
            }
            if(SIZE_LIST_DCU() < MAX_DCU_MAYBE)
                showAllLightEnable = TRUE;
            else
                showAllLightEnable = FALSE;
        }
    }
    else
    {
        gchar * msg = g_strdup("Lỗi lấy danh sách khu vực từ server. ");
        GtkWidget *parent = stack_widget_active_top();
        smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
        g_char_free(msg);
    }
    smartstreetlight_free_soap_operation(&spl_soap);
}

gchar * smartstreetlight_get_mode_name(SPL_DCU_MODE_Enum index)
{
    switch(index)
    {
    case SPL_DCU_WirelessMode:
        return g_strdup(SPL_DCU_WIRELESS_MODE);
    case SPL_DCU_LineMode:
        return g_strdup(SPL_DCU_LINE_MODE);
    case SPL_DCU_UnknownMode:
        return g_strdup(SPL_DCU_UNKNOWN_MODE);
    default:
        return NULL;
    }
}



void smartstreetlight_tree_store_clean(gint storeIndex)
{
    GtkTreeStore *store = NULL;
    switch(storeIndex)
    {
    case SPL_DCU_STORE:
        store = main_view_widgets->dcu_store;
        break;
    case SPL_LCU_STORE:
        store = main_view_widgets->lcu_store;
        break;
    case SPL_LCU_ALL_STORE:
        store = main_view_widgets->lcu_all_store;
        break;
    case SPL_SCHEDULE_STORE:
        store = program_widgets->program_item_schedule_treestore;
        break;
    case SPL_PROGRAM_STORE:
        store = program_widgets->program_dcu_list_treestore;
        break;
    case SPL_DCU_PROGRAM_STORE:
        store = program_widgets->program_year_schedule_treestore;
        break;
    case SPL_MONTH_STORE:
        store = program_widgets->program_month_schedule_treestore;
        break;
    }
    if(store)
        gtk_tree_store_clear(store);
}

gboolean smartstreetlight_dcu_add_new(void)
{
    gboolean ret = TRUE;
    /**Init widget*/
    GtkWidget *add_dcu_entry_id = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "add_dcu_entry_id"));
    GtkWidget *add_dcu_entry_phone = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "add_dcu_entry_phone"));
    GtkWidget *add_dcu_entry_gps = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "add_dcu_entry_gps"));
    GtkWidget *add_dcu_combobox_mode = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "add_dcu_combobox_mode"));
    GtkWidget *add_dcu_combobox_zone = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "add_dcu_combobox_zone"));
    GtkWidget *add_dcu_entry_address = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "add_dcu_entry_address"));
    GtkWidget *add_dcu_entry_note = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "add_dcu_entry_note"));
    GtkWidget *add_dcu_label_error = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "add_dcu_label_error"));
    GtkWidget *btn_add = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "dcu_add_ok"));
    GtkWidget *lb_name = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "lb_dialog_name"));
    gtk_label_set_text(GTK_LABEL(lb_name), "Đăng kí trạm mới");
    gtk_widget_set_sensitive(GTK_WIDGET(add_dcu_entry_id), TRUE);
    static GtkTreeStore *zoneStore = NULL;
    if(zoneStore == NULL)
    {
        zoneStore = gtk_tree_store_new(2, G_TYPE_STRING, G_TYPE_POINTER);
        gtk_combo_box_set_model(GTK_COMBO_BOX(add_dcu_combobox_zone), GTK_TREE_MODEL(zoneStore));
    }
    gtk_widget_set_sensitive(btn_add, TRUE);
    gtk_combo_box_set_active(GTK_COMBO_BOX(add_dcu_combobox_mode), 1);
    gtk_widget_set_sensitive(add_dcu_combobox_mode, FALSE); //Only have one mode
    /**Get zone*/
    if(IS_EMPTY_LIST_ZONE)
    {
        gtk_label_set_text(GTK_LABEL(add_dcu_label_error), "Bạn không có quyền thêm trạm mới");
        gtk_widget_set_sensitive(btn_add, FALSE);
    }
    else
    {
        gtk_tree_store_clear(zoneStore);
        GSList *item;
        LIST_ZONE_FOR_EACH_ENTRY(item)
        {
            GtkTreeIter iter;
            SplZone *zone = (SplZone*) item->data;
            if(zone)
            {
                gtk_tree_store_append(zoneStore, &iter, NULL);
                gtk_tree_store_set(zoneStore, &iter, 0, zone->zonename, 1, zone, -1);
            }
        }
        gtk_combo_box_set_active(GTK_COMBO_BOX(add_dcu_combobox_zone), 0);
    }
    gtk_window_set_resizable(GTK_WINDOW(main_widgets->add_dcu_dialog), FALSE);

    SPL_DIALOG_SHOW(main_widgets->add_dcu_dialog);
    gint response_id;
    while(response_id = gtk_dialog_run(GTK_DIALOG(main_widgets->add_dcu_dialog)))
    {
        DEBUG(" *** response_id: %d", response_id);
        switch(response_id)
        {
        case GTK_RESPONSE_ACCEPT:
        {
            gchar *dcuId = (gchar *)gtk_entry_get_text(GTK_ENTRY(add_dcu_entry_id));
            gchar tmp[100];
            if(strlen(dcuId) != 10)
                gtk_label_set_text(GTK_LABEL(add_dcu_label_error), "Mã trạm không được để trống hoặc không đủ 10 kí tự");
            else if(sscanf(dcuId, "%[0-9a-zA-Z_]", &tmp) != 1 ||
                    strlen(tmp) != 10 || (tmp[0] >= '0' && tmp[0] <= '9'))
                gtk_label_set_text(GTK_LABEL(add_dcu_label_error), "Mã trạm theo chỉ sử dụng các kí tự [A-Za-z0-9_] và không được bắt đầu bằng số");
            else
            {
                gtk_label_set_text(GTK_LABEL(add_dcu_label_error), "");
                //All things are ok
                SplZone *zone1 = GET_ZONE_FROM_LIST_ZONE(gtk_combo_box_get_active(GTK_COMBO_BOX(add_dcu_combobox_zone)));
                pSplDcu dcu = spl_dcu_init();
                SplDcuPrivate *pri = dcu->priv;
                SplSoap spl_soap;
                pri->address    = g_strdup(gtk_entry_get_text(GTK_ENTRY(add_dcu_entry_address)));
                pri->gps        = g_strdup(gtk_entry_get_text(GTK_ENTRY(add_dcu_entry_gps)));
                pri->id         = g_strdup(dcuId);
                pri->phonenum   = g_strdup(gtk_entry_get_text(GTK_ENTRY(add_dcu_entry_phone)));
                pri->note       = g_strdup(gtk_entry_get_text(GTK_ENTRY(add_dcu_entry_note)));
                pri->mode       = 1;
                pri->zonecode   = zone1->zonecode;
                pri->zonename   = g_strdup(zone1->zonename);
                gint soap_err = smartstreetlight_add_dcu_execute(&spl_soap,dcu);
                if(soap_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
                {
                    //add into dcu treeview
                    gtk_tree_store_append(main_view_widgets->dcu_store, &dcu->priv->iter, &zone1->zoneIter);
                    gtk_tree_store_set(main_view_widgets->dcu_store, &dcu->priv->iter,
                                       OBJECT_NAME_COLUMN, dcu->priv->id,
                                       OBJECT_POINTER_COLUMN, dcu,
                                       OBJECT_TYPE_COLUMN, OBJECT_IS_DCU_TYPE, -1);
                    APPEND_LIST_DCU(dcu,zone1);
                }
                else
                {
                    gchar * msg = g_strconcat("Lỗi thêm trạm có id là ", dcu->priv->id,". ", NULL);
                    GtkWidget *parent = stack_widget_active_top();
                    smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
                    g_char_free(msg);
                    spl_dcu_free(dcu);
                    ret = FALSE;
                    break;
                }
                goto ___exit;
            }
        }
        break;
        case GTK_RESPONSE_CLOSE:
        case GTK_RESPONSE_CANCEL:
        case GTK_RESPONSE_DELETE_EVENT:
            goto ___exit;
        }
    }
___exit:
    SPL_DIALOG_HIDE(main_widgets->add_dcu_dialog);

    gtk_entry_set_text(GTK_ENTRY(add_dcu_entry_id), "");
    gtk_entry_set_text(GTK_ENTRY(add_dcu_entry_phone), "");
    gtk_entry_set_text(GTK_ENTRY(add_dcu_entry_gps), "");
    gtk_entry_set_text(GTK_ENTRY(add_dcu_entry_address), "");
    gtk_entry_set_text(GTK_ENTRY(add_dcu_entry_note), "");
    gtk_label_set_text(GTK_LABEL(add_dcu_label_error), "");

    return ret;
}



gboolean smartstreetlight_dcu_edit(pSplDcu dcu)
{
    gboolean ret = TRUE;
    /**Init widget*/
    GtkWidget *add_dcu_entry_id = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "add_dcu_entry_id"));
    GtkWidget *add_dcu_entry_phone = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "add_dcu_entry_phone"));
    GtkWidget *add_dcu_entry_gps = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "add_dcu_entry_gps"));
    GtkWidget *add_dcu_combobox_mode = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "add_dcu_combobox_mode"));
    GtkWidget *add_dcu_combobox_zone = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "add_dcu_combobox_zone"));
    GtkWidget *add_dcu_entry_address = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "add_dcu_entry_address"));
    GtkWidget *add_dcu_entry_note = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "add_dcu_entry_note"));
    GtkWidget *add_dcu_label_error = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "add_dcu_label_error"));
    GtkWidget *btn_add = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "dcu_add_ok"));
    GtkWidget *lb_name = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "lb_dialog_name"));
    gtk_label_set_text(GTK_LABEL(lb_name), "Chỉnh sửa thông tin trạm");

    static GtkTreeStore *zoneStore = NULL;
    if(zoneStore == NULL)
    {
        zoneStore = gtk_tree_store_new(2, G_TYPE_STRING, G_TYPE_POINTER);
        gtk_combo_box_set_model(GTK_COMBO_BOX(add_dcu_combobox_zone), GTK_TREE_MODEL(zoneStore));
    }
    gtk_widget_set_sensitive(btn_add, TRUE);
    gtk_combo_box_set_active(GTK_COMBO_BOX(add_dcu_combobox_mode), dcu->priv->mode);
    gtk_widget_set_sensitive(add_dcu_combobox_mode, FALSE); //Only have one mode
    /**Get zone*/
    if(IS_EMPTY_LIST_ZONE)
    {
        gtk_label_set_text(GTK_LABEL(add_dcu_label_error), "Bạn không có quyền chỉnh sửa thông tin trạm");
        gtk_widget_set_sensitive(btn_add, FALSE);
    }
    else
    {
        gtk_tree_store_clear(zoneStore);
        gint i = 0, index = 0;
        GSList *item;
        LIST_ZONE_FOR_EACH_ENTRY(item)
        {
            GtkTreeIter iter;
            SplZone *zone = (SplZone*) item->data;
            if(zone)
            {
                gtk_tree_store_append(zoneStore, &iter, NULL);
                gtk_tree_store_set(zoneStore, &iter, 0, zone->zonename, 1, zone, -1);
                if(dcu->priv->zonecode == zone->zonecode)
                    index = i;
                i++;
            }
        }
        gtk_combo_box_set_active(GTK_COMBO_BOX(add_dcu_combobox_zone), index);
    }

    gtk_entry_set_text(GTK_ENTRY(add_dcu_entry_id), dcu->priv->id);
    gtk_widget_set_sensitive(GTK_WIDGET(add_dcu_entry_id), FALSE);
    gtk_entry_set_text(GTK_ENTRY(add_dcu_entry_phone), dcu->priv->phonenum);
    gtk_entry_set_text(GTK_ENTRY(add_dcu_entry_gps), dcu->priv->gps);
    gtk_entry_set_text(GTK_ENTRY(add_dcu_entry_address), dcu->priv->address);
    gtk_entry_set_text(GTK_ENTRY(add_dcu_entry_note), dcu->priv->note);

    SPL_DIALOG_SHOW(main_widgets->add_dcu_dialog);
    gint response_id;
    while(response_id = gtk_dialog_run(GTK_DIALOG(main_widgets->add_dcu_dialog)))
    {
        switch(response_id)
        {
        case GTK_RESPONSE_ACCEPT:
        {
            //All things are ok
            SplZone *zone1 = GET_ZONE_FROM_LIST_ZONE(gtk_combo_box_get_active(GTK_COMBO_BOX(add_dcu_combobox_zone)));
            pSplDcu dcuEdit= spl_dcu_init();
            SplDcuPrivate *pri = dcuEdit->priv;
            SplSoap spl_soap;
            pri->address    = g_strdup(gtk_entry_get_text(GTK_ENTRY(add_dcu_entry_address)));
            pri->gps        = g_strdup(gtk_entry_get_text(GTK_ENTRY(add_dcu_entry_gps)));
            pri->phonenum   = g_strdup(gtk_entry_get_text(GTK_ENTRY(add_dcu_entry_phone)));
            pri->note       = g_strdup(gtk_entry_get_text(GTK_ENTRY(add_dcu_entry_note)));
            pri->mode       = dcu->priv->mode;
            pri->zonecode   = zone1->zonecode;
            pri->zonename   = g_strdup(zone1->zonename);
            pri->programId    = dcu->priv->programId;
            pri->scheduleId = dcu->priv->scheduleId;
            pri->id         = g_strdup(dcu->priv->id);
            gint soap_err = smartstreetlight_edit_dcu_execute(&spl_soap,dcuEdit);
            if(soap_err != ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
            {
                gchar * msg = g_strconcat("Lỗi thay đổi thông tịn trạm có id là ", dcuEdit->priv->id,". ", NULL);
                GtkWidget *parent = stack_widget_active_top();
                smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
                g_char_free(msg);
                spl_dcu_free(dcuEdit);
                ret = FALSE;
                break;
            }
            //If success, update dcu
            dcu->priv->mode = dcuEdit->priv->mode;
            g_char_free(dcu->priv->address);
            dcu->priv->address = g_strdup(dcuEdit->priv->address);
            g_char_free(dcu->priv->note);
            dcu->priv->note = g_strdup(dcuEdit->priv->note);
            g_char_free(dcu->priv->zonename);
            dcu->priv->zonename = g_strdup(dcuEdit->priv->zonename);
            g_char_free(dcu->priv->gps);
            dcu->priv->gps = g_strdup(dcuEdit->priv->gps);
            g_char_free(dcu->priv->phonenum);
            dcu->priv->phonenum = g_strdup(dcuEdit->priv->phonenum);
            dcu->priv->zonecode = dcuEdit->priv->zonecode;
            spl_dcu_set_information(dcu);
            spl_dcu_free(dcuEdit);

            goto ___exit;
        }
        break;
        case GTK_RESPONSE_CLOSE:
        case GTK_RESPONSE_CANCEL:
        case GTK_RESPONSE_DELETE_EVENT:
            goto ___exit;
        }
    }
___exit:

    SPL_DIALOG_HIDE(main_widgets->add_dcu_dialog);

    gtk_entry_set_text(GTK_ENTRY(add_dcu_entry_id), "");
    gtk_entry_set_text(GTK_ENTRY(add_dcu_entry_phone), "");
    gtk_entry_set_text(GTK_ENTRY(add_dcu_entry_gps), "");
    gtk_entry_set_text(GTK_ENTRY(add_dcu_entry_address), "");
    gtk_entry_set_text(GTK_ENTRY(add_dcu_entry_note), "");
    gtk_label_set_text(GTK_LABEL(add_dcu_label_error), "");

    return ret;
}


void spl_delete_all_lcu_on_dcu(pSplDcu dcu)
{
    GtkTreeIter child;
    g_return_if_fail(dcu && dcu->priv);

    //clear all iter light
    if(gtk_tree_store_iter_is_valid(main_view_widgets->lcu_all_store, &dcu->controlIter))
    {
        if(gtk_tree_model_iter_children(GTK_TREE_MODEL(main_view_widgets->lcu_all_store), &dcu->controlIter, &child))
        {
            while(gtk_tree_store_remove(main_view_widgets->lcu_all_store, &child)) {};
        }
        gtk_tree_store_remove(main_view_widgets->lcu_all_store, &dcu->controlIter);
    }
    FREE_LIST_LCU(dcu, spl_lcu_free);
}

/**
* This function only use when showAllLightEnable = FALSE
*
*/

void spl_add_new_dcu_into_closest_list(pSplDcu dcu)
{
    while(g_slist_length(closestUsingDculist) >= (MAX_DCU_MAYBE -1))
    {
        pSplDcuClosestUsing lastDcu = (pSplDcuClosestUsing)g_slist_last(closestUsingDculist)->data;
        //clear all light of this dcu
        /* nghi ---> */
        //if(lastDcu && lastDcu->dcu)
        //    FREE_LIST_LCU(lastDcu->dcu, spl_lcu_free);
        /*-------------- */
        //spl_dcu_free(lastDcu->dcu);
        closestUsingDculist = g_slist_remove(closestUsingDculist, lastDcu); //??????? g_slist_remove(closestUsingDculist, lastDcu)
    }
    pSplDcuClosestUsing newElement = g_new0(SplDcuClosestUsing, 1);
    newElement->dcu = dcu;
    g_get_current_time(&newElement->last_edit_time);
    closestUsingDculist = g_slist_append(closestUsingDculist, newElement);
}




static int closest_time_compare (const pSplDcuClosestUsing a, const pSplDcuClosestUsing b)
{
    return b->last_edit_time.tv_sec - a->last_edit_time.tv_sec;
}


void spl_closeset_list_sort()
{
    closestUsingDculist = g_slist_sort(closestUsingDculist, (GCompareFunc)closest_time_compare);
}


void * spl_lcu_runtime_data_update(gpointer data)
{
    spl_lcu_runtime_data *event_data = (spl_lcu_runtime_data *)data;
    g_return_if_fail(dcumap);

    pSplDcu _dcu = NULL;
    pSplLcu _lcu = NULL;
    gchar *buffer = NULL;

    if(! ( LOCKUP_LIST_DCU(event_data->lcu_dcuid, _dcu) && _dcu && _dcu->priv))
        goto __free;
/**ADD ACTION*/
    if((event_data->lcu_status & ADD_STATUS) != 0)
    {
        buffer = g_strdup_printf("Đèn mã '%s' được thêm vào trạm '%s'.",
                                        event_data->lcu_id, _dcu->priv->id);
        //smartstreetlight_error_notifice_run(main_widgets->main_window, buffer);
//                    SPL_WARNING_POPUP(NULL, buffer);
        if(_dcu->priv->childlist != NULL)
        {
            pSplLcu new_lcu     = spl_lcu_init();
            new_lcu->gps        = g_strdup(event_data->lcu_gps);
            new_lcu->id         = g_strdup(event_data->lcu_id);
            new_lcu->note       = g_strdup(event_data->lcu_note);
            new_lcu->lightname  = g_strdup(event_data->lightname);
            new_lcu->icon       = NULL;
            new_lcu->brightness = (gfloat)event_data->lcu_level;
            new_lcu->isBroken   = FALSE;
            new_lcu->isOn       = event_data->lcu_ison;
            new_lcu->mode       = event_data->lcu_mode;
            new_lcu->parent     = _dcu;
            new_lcu->status     = event_data->lcu_status;
            new_lcu->volt       = (gfloat)event_data->lcu_current;
            new_lcu->power      = event_data->power;
            new_lcu->tolerance  = event_data->tolerance;
            GtkTreeIter     iter;
            GtkTreeIter     *iter_parent = NULL;
            GtkTreeStore    *store;

            if(lastSelectedDcu == _dcu)
            {
                PREPEND_LIST_LCU(_dcu, new_lcu);
                store = main_view_widgets->lcu_store;
                gtk_tree_store_append(store, &iter, iter_parent);
                gtk_tree_store_set(store, &iter, LIGHT_ID, new_lcu->id, LIGHT_POINTER, new_lcu, -1);
                spl_lcu_add_image(new_lcu, spl_get_light_icon(new_lcu, FALSE, FALSE),
                                  &new_lcu->lat, &new_lcu->lon);
            }
            else
            {
                if(!IS_EMPTY_LIST_LCU(_dcu))
                {
                    PREPEND_LIST_LCU(_dcu, new_lcu);

                    if(gtk_combo_box_get_active(GTK_COMBO_BOX(cbb_light_display))==DISPLAY_FOLLOW_ZONE)
                    {
#if 0
                        store = main_view_widgets->lcu_all_store;
                        iter_parent = &new_lcu->parent->controlIter;
#else
                        //store = main_view_widgets->lcu_store;
                        gtk_tree_store_append(store, &iter, iter_parent);
                        gtk_tree_store_set(store, &iter, LIGHT_ID, new_lcu->id, LIGHT_POINTER, new_lcu, -1);
                        spl_lcu_add_image(new_lcu, spl_get_light_icon(new_lcu, FALSE, TRUE),
                                          &new_lcu->lat, &new_lcu->lon);
#endif
                    }
                }
            }
        }
        goto __exit;
    }

    if((event_data->lcu_status & DELETE_STATUS) != 0)
    {
        buffer = g_strdup_printf("Đèn mã '%s' bị xóa khỏi trạm '%s'.",
                                        event_data->lcu_id, _dcu->priv->id);
    }
    if(!(LOCKUP_LIST_LCU(_dcu, event_data->lcu_id, _lcu) && _lcu))
        goto __exit;
/**DELETE ACTION FOR EXISTED LCU*/
    if((event_data->lcu_status & DELETE_STATUS) != 0)
    {
        // remove on Struct
        REMOVE_LIST_LCU(_dcu, _lcu);

        GtkTreeIter     iter;
        GtkTreeIter     *iter_parent = NULL;
        GtkTreeStore    *store;

        gint index =  gtk_combo_box_get_active(GTK_COMBO_BOX(cbb_light_display));
        switch(index)
        {
        case DISPLAY_FOLLOW_ZONE:
#if 0
            store = GTK_TREE_STORE(main_view_widgets->lcu_all_store);
            iter_parent = &_dcu->controlIter;
            /* do while to get iter of LCU on treestore. */
            if(_lcu->icon)
                osm_gps_map_image_remove (map, _lcu->icon);
            break;
#endif
        case DISPLAY_FOLLOW_DCU:
            if(lastSelectedDcu == _dcu)
            {
                //delete on treeview
                store = GTK_TREE_STORE(main_view_widgets->lcu_store);
                if(gtk_tree_model_get_iter_first(GTK_TREE_MODEL(store), &iter))
                {
                    do
                    {
                        pSplLcu tmp;
                        gtk_tree_model_get(GTK_TREE_MODEL(store), &iter,
                                           LIGHT_POINTER, &tmp,  -1 );
                        if(tmp == _lcu)
                        {
                            gtk_tree_store_remove(store, &iter);
                            break;
                        }
                    }
                    while(gtk_tree_model_iter_next(GTK_TREE_MODEL(store), &iter));
                }
                //delete on map
                if(_lcu->icon)
                    osm_gps_map_image_remove (map, _lcu->icon);
            }
            break;
        };
    }
/**UPDATE ACTION FOR EXISTED LCU*/
    else // update infomation and status
    {
//                        gchar *buffer = g_strdup_printf("Thông tin đèn mã '%s' của trạm '%s' đã được cập nhật.",
//                                                        _lcu->id, _dcu->priv->id);

        g_free(_lcu->gps);
        _lcu->gps = g_strdup(event_data->lcu_gps);

        g_free(_lcu->note);
        _lcu->note = g_strdup(event_data->lcu_note);
        g_free(_lcu->lightname);
        _lcu->lightname = g_strdup(event_data->lightname);
        _lcu->isOn = event_data->lcu_ison;
        _lcu->status = event_data->lcu_status;
        _lcu->volt = event_data->lcu_current;
        _lcu->brightness = event_data->lcu_level;
        _lcu->power = event_data->power;
        _lcu->tolerance = event_data->tolerance;
        if (lastSelectedLcu == _lcu)
        {
//                            smartstreetlight_error_notifice_run(buffer);
//                            g_free(buffer);
            GtkTreeSelection *selection;
            selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(main_view_widgets->lcu_view));
            on_lcu_selection_changed(selection, NULL);
            if (_lcu->icon)
                    osm_gps_map_image_remove (map,_lcu->icon);
            if(gtk_combo_box_get_active(GTK_COMBO_BOX(cbb_light_display))!=DISPLAY_FOLLOW_DCU)
                spl_lcu_add_image(_lcu, spl_get_light_icon(_lcu, TRUE, TRUE), &_lcu->lat, &_lcu->lon);
            else
                spl_lcu_add_image(_lcu, spl_get_light_icon(_lcu, TRUE, FALSE), &_lcu->lat, &_lcu->lon);
        }
        else
        {
            if(gtk_combo_box_get_active(GTK_COMBO_BOX(cbb_light_display))!=DISPLAY_FOLLOW_DCU)
            {
                if (_lcu->icon)
                    osm_gps_map_image_remove (map,_lcu->icon);
                if (_lcu->parent == lastSelectedDcu) {
                    spl_lcu_add_image(_lcu, spl_get_light_icon(_lcu, FALSE, TRUE), &_lcu->lat, &_lcu->lon);
                }else
                    spl_lcu_add_image(_lcu, spl_get_light_icon(_lcu, FALSE, FALSE), &_lcu->lat, &_lcu->lon);
            } else if (_lcu->parent == lastSelectedDcu) {

                if (_lcu->icon)
                    osm_gps_map_image_remove (map,_lcu->icon);
                spl_lcu_add_image(_lcu, spl_get_light_icon(_lcu, FALSE, FALSE), &_lcu->lat, &_lcu->lon);
            }
        }
    }
__exit:
    if(buffer)
    {
        spl_event_notify_add(2, buffer);
        g_char_free(buffer);
    }
__free:
    g_free(event_data->lcu_id);
    g_free(event_data->lcu_dcuid);
    g_free(event_data->lcu_gps);
    g_free(event_data->lcu_note);
    g_free(event_data->lightname);
    g_slice_free(spl_lcu_runtime_data, event_data);

    return NULL;
}

void * spl_dcu_runtime_data_update(gpointer data)
{
    DEBUG_1();
    spl_dcu_runtime_data *event_data = (spl_dcu_runtime_data *)data;
    g_return_if_fail(dcumap && event_data);

    pSplDcu _dcu = NULL;
    gboolean is_found_dcu = LOCKUP_LIST_DCU(event_data->dcu_id, _dcu);
    gchar *buffer = NULL;
    /* delete dcu */
    if((event_data->dcu_status & DELETE_STATUS) != 0)
    {
        if (is_found_dcu == TRUE)
        {
            /* delete dcu on GUI */
            buffer = g_strdup_printf("Trạm '%s' thuộc khu vực '%s' bị xóa.",
                                                _dcu->priv->id, _dcu->priv->zonename);
            //smartstreetlight_error_notifice_run(main_widgets->main_window, buffer);
            //SPL_WARNING_POPUP(NULL, buffer)
            //g_free(buffer);

            if(gtk_tree_store_remove(main_view_widgets->dcu_store, &_dcu->priv->iter))
            {
                GtkTreeSelection *selection;
                GtkTreeModel *model;
                GtkTreeIter iter;
                selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(main_view_widgets->dcu_view));
                spl_delete_all_lcu_on_dcu(_dcu);
                if(gtk_tree_selection_get_selected(selection, &model, &iter))
                {
                    on_dcu_selection_changed(selection, GINT_TO_POINTER(TRUE));
                }
                REMOVE_LIST_DCU(_dcu);
            }
        }
    }
    /* add dcu */
    else if (is_found_dcu == FALSE)
    {
        SplZone * _zone = NULL;
        if(LOCKUP_LIST_ZONE(&event_data->dcu_zone_id, _zone) && _zone)
        {
            pSplDcu new_dcu = spl_dcu_init();
            new_dcu->priv->id           = g_strdup(event_data->dcu_id);
            new_dcu->priv->zonecode     = event_data->dcu_zone_id;
            new_dcu->priv->zonename     = _zone->zonename;
            new_dcu->priv->mode         = event_data->dcu_mode;
            new_dcu->priv->status       = event_data->dcu_status;
            new_dcu->priv->programId    = event_data->dcu_program_id;
            new_dcu->priv->address      = g_strdup(event_data->dcu_address);
            new_dcu->priv->phonenum     = g_strdup(event_data->dcu_phone);
            new_dcu->priv->gps          = g_strdup(event_data->dcu_gps);
            new_dcu->priv->note         = g_strdup(event_data->dcu_note);

            buffer = g_strdup_printf("Trạm mới mã '%s' được thêm vào khu vực: '%s'.",
                                                    new_dcu->priv->id, new_dcu->priv->zonename);
            //smartstreetlight_error_notifice_run(main_widgets->main_window, buffer);
            //SPL_WARNING_POPUP(NULL, buffer);
            //g_free(buffer);
            /* add in treeview */
            gtk_tree_store_append(main_view_widgets->dcu_store, &new_dcu->priv->iter, &_zone->zoneIter);
            gtk_tree_store_set (main_view_widgets->dcu_store, &new_dcu->priv->iter,
                                OBJECT_NAME_COLUMN, new_dcu->priv->id,
                                OBJECT_POINTER_COLUMN, (gpointer)new_dcu,
                                OBJECT_TYPE_COLUMN, (gint)OBJECT_IS_DCU_TYPE,
                                -1);
            APPEND_LIST_DCU(new_dcu, _zone);
        }
    }
    /* DCU is exsit => check zoneid is changed ?*/
    else if (is_found_dcu == TRUE)
    {
        _dcu->priv->mode            = event_data->dcu_mode;
        _dcu->priv->status          = event_data->dcu_status;
        _dcu->priv->programId       = event_data->dcu_program_id;
        g_free(_dcu->priv->address);
        _dcu->priv->address         = g_strdup(event_data->dcu_address);
        g_free(_dcu->priv->phonenum);
        _dcu->priv->phonenum        = g_strdup(event_data->dcu_phone);
        g_free(_dcu->priv->gps);
        _dcu->priv->gps             = g_strdup(event_data->dcu_gps);
        g_free(_dcu->priv->note);
        _dcu->priv->note            = g_strdup(event_data->dcu_note);

        SplZone * _zone = NULL;
        /* Find zoneid */
        if( LOCKUP_LIST_ZONE(&event_data->dcu_zone_id, _zone) && _zone)
        {
            /* dcu not change zoneid => only update information */
            if(_dcu->priv->zonecode == event_data->dcu_zone_id)
            {
//                gchar *buffer = g_strdup_printf("Trạm '%s' thuộc khu vực '%s' được cập nhật thông tin.",
//                                                            _dcu->priv->id, _dcu->priv->zonename);
//                smartstreetlight_error_notifice_run(buffer);
//                g_free(buffer);

                gtk_tree_store_set(main_view_widgets->dcu_store, &_dcu->priv->iter,
                                   OBJECT_POINTER_COLUMN, _dcu, -1);

            }
            /* dcu change zoneid => process */
            else
            {
                GtkTreeModel *model = GTK_TREE_MODEL(main_view_widgets->dcu_store);

                buffer = g_strdup_printf("Trạm '%s' bị chuyển từ khu vực '%s' sang khu vực '%s'.",
                                                _dcu->priv->id, _dcu->priv->zonename, _zone->zonename);
                //smartstreetlight_error_notifice_run(main_widgets->main_window, buffer);
                //SPL_WARNING_POPUP(NULL, buffer);
                //g_free(buffer);

                // remove old row
                gtk_tree_store_remove(GTK_TREE_STORE(model), &_dcu->priv->iter);

                pSplZone old_zone = NULL;
                if(LOCKUP_LIST_ZONE(&_dcu->priv->zonecode, old_zone) && old_zone)
                {
                    old_zone->dculistzone =  g_slist_remove(old_zone->dculistzone, _dcu);
                }

                // append on new zone
                /* update struct */
                _dcu->priv->zonecode = event_data->dcu_zone_id;
                pSplZone new_zone = NULL;
                if(LOCKUP_LIST_ZONE(&event_data->dcu_zone_id, new_zone) && new_zone)
                {
                    /* update treestore */
                    gtk_tree_store_append(GTK_TREE_STORE(main_view_widgets->dcu_store), &_dcu->priv->iter, &_zone->zoneIter);
                    gtk_tree_store_set(GTK_TREE_STORE(main_view_widgets->dcu_store), &_dcu->priv->iter,
                                       OBJECT_NAME_COLUMN, _dcu->priv->name,
                                       OBJECT_POINTER_COLUMN, (gpointer)_dcu,
                                       OBJECT_TYPE_COLUMN, (gint)OBJECT_IS_DCU_TYPE, -1);

                    /* update struct */
                    new_zone->dculistzone = g_slist_append(new_zone->dculistzone, _dcu);
                }

            }

            // update on GUI
            if(_dcu == lastSelectedDcu)
            {
                GtkTreeSelection *dcu_list_selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(main_view_widgets->dcu_view));
                on_dcu_selection_changed(dcu_list_selection, GINT_TO_POINTER(TRUE));
            }
        }
        /* zone id is not belong to current user */
        else
        {
            buffer = g_strdup_printf("Trạm '%s' bị chuyển từ khu vực %s sang khu vực khác không có quyền quản lý.",
                                             _dcu->priv->id, _dcu->priv->zonename);
            //smartstreetlight_error_notifice_run(main_widgets->main_window, buffer);
            //SPL_WARNING_POPUP(NULL, buffer);
            //g_free(buffer);
            if(gtk_tree_store_remove(main_view_widgets->dcu_store, &_dcu->priv->iter))
            {
                GtkTreeSelection *selection;
                GtkTreeModel *model;
                GtkTreeIter iter;
                selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(main_view_widgets->dcu_view));
                spl_delete_all_lcu_on_dcu(_dcu);
                if(gtk_tree_selection_get_selected(selection, &model, &iter))
                {
                    on_dcu_selection_changed(selection, GINT_TO_POINTER(TRUE));
                }
                REMOVE_LIST_DCU(_dcu);
            }
        }
    }
    if(buffer)
    {
        spl_event_notify_add(2, buffer);
        g_char_free(buffer);
    }
    g_free(event_data->dcu_id);
    g_free(event_data->dcu_address);
    g_free(event_data->dcu_gps);
    g_free(event_data->dcu_phone);
    g_free(event_data->dcu_note);
    g_slice_free(spl_dcu_runtime_data, event_data);

    return NULL;
}


static void on_dcu_control_switch_interleaved_callback(GtkSwitch *widget,
        gboolean state,
        gpointer user_data)
{
    DEBUG_1();
}




/** ------------------------------------------------------------------------------ **/
/* ------------------------------------------------------------------------------ */
/*                             CONTROL AND SCHEDULE FOR DCU                       */
/** ------------------------------------------------------------------------------ **/
static void spl_dcu_control_finalize()
{
    g_return_if_fail(dcu_control_schedule_widgets && dcu_control_schedule_widgets->dcu_schedule_lcu_sorted_list);

    if(dcu_control_schedule_widgets->dcu_schedule_lcu_sorted_list)
    {
        g_slist_free_full(dcu_control_schedule_widgets->dcu_schedule_lcu_sorted_list, GDestroyNotify(spl_lcu_free));
        //dcu_control_schedule_widgets->dcu_schedule_lcu_sorted_list = NULL;
    }

    gtk_widget_destroy(dcu_control_schedule_widgets->dcu_control_window);
    g_slice_free(_SplControlSchedule_Widgets, dcu_control_schedule_widgets);
}

static void spl_dcu_control_window_accelerator_pressed(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
    if (event->keyval == GDK_KEY_Escape)
    {
        on_dcu_control_btn_clicked(NULL, GINT_TO_POINTER(DIALOG_CONTROL_BTN_QUIT));
    }
}

static void spl_dcu_control_init()
{
    if(dcu_control_schedule_widgets)
        return;

    dcu_control_schedule_widgets = g_slice_new(_SplControlSchedule_Widgets);
//    _SplControlSchedule_Widgets *p = dcu_control_schedule_widgets;
    dcu_control_schedule_widgets->dcu_schedule_lcu_sorted_list = NULL;

    // common widgets //
    dcu_control_schedule_widgets->dcu_control_window               = GTK_WIDGET(SPL_OBJECT("dcu_control_window"));
    dcu_control_schedule_widgets->dcu_control_core_frame_label     = GTK_WIDGET(SPL_OBJECT("dcu_control_core_frame_label"));
    dcu_control_schedule_widgets->dcu_control_treeview             = GTK_WIDGET(SPL_OBJECT("dcu_control_treeview"));
    dcu_control_schedule_widgets->dcu_control_select_button_box    = GTK_WIDGET(SPL_OBJECT("dcu_control_select_button_box"));
    dcu_control_schedule_widgets->dcu_control_is_temp              = GTK_WIDGET(SPL_OBJECT("dcu_control_is_temp"));

    // schedule setting widgets //
    dcu_control_schedule_widgets->dcu_schedule_program_box                 = GTK_WIDGET(SPL_OBJECT("dcu_schedule_program_box"));
    dcu_control_schedule_widgets->dcu_schedule_program_comboboxtext        = GTK_WIDGET(SPL_OBJECT("dcu_schedule_program_comboboxtext"));
    dcu_control_schedule_widgets->dcu_schedule_interleaved_comboboxtext    = GTK_WIDGET(SPL_OBJECT("dcu_schedule_interleaved_comboboxtext"));
    dcu_control_schedule_widgets->dcu_schedule_summit_button               = GTK_WIDGET(SPL_OBJECT("dcu_schedule_summit_button"));

    // control maunal widgets //
    dcu_control_schedule_widgets->dcu_manual_level_grid            = GTK_WIDGET(SPL_OBJECT("dcu_manual_level_grid"));
    dcu_control_schedule_widgets->dcu_manual_summit_button         = GTK_WIDGET(SPL_OBJECT("dcu_manual_summit_button"));

    // init for list dcu_schedule_interleaved_liststore //
    dcu_control_schedule_widgets->dcu_schedule_interleaved_liststore = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_INT);
    gtk_combo_box_set_model(GTK_COMBO_BOX(dcu_control_schedule_widgets->dcu_schedule_interleaved_comboboxtext),
                            GTK_TREE_MODEL(dcu_control_schedule_widgets->dcu_schedule_interleaved_liststore));

    GtkTreeIter iter;
    GtkListStore *store = GTK_LIST_STORE(dcu_control_schedule_widgets->dcu_schedule_interleaved_liststore);
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, 0, "<none>", 1, DCU_SCHEDULE_INTERLEAVED_0, -1);
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, 0, "Xen kẽ 1 sáng 1 tắt", 1, DCU_SCHEDULE_INTERLEAVED_1_1, -1);
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, 0, "Xen kẽ 2 sáng 2 tắt", 1, DCU_SCHEDULE_INTERLEAVED_2_2, -1);
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, 0, "Xen kẽ 1 sáng 2 tắt", 1, DCU_SCHEDULE_INTERLEAVED_1_2, -1);

    // init for list lcu on tree view //
    GtkTreeViewColumn *column;
    GtkCellRenderer *render;

    dcu_control_schedule_widgets->dcu_control_lcu_list = gtk_tree_store_new(4, G_TYPE_STRING,
            G_TYPE_BOOLEAN,
            G_TYPE_POINTER,
            G_TYPE_BOOLEAN);

    GtkTreeSelection *selection = gtk_tree_view_get_selection(
                                      GTK_TREE_VIEW(dcu_control_schedule_widgets->dcu_control_treeview));
    g_signal_connect (selection, "changed", G_CALLBACK(on_dcu_control_selection_changed_callback), NULL);


    render              = gtk_cell_renderer_text_new();
    column              = gtk_tree_view_column_new_with_attributes("Mã đèn", render, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(dcu_control_schedule_widgets->dcu_control_treeview), column);

    render              = gtk_cell_renderer_toggle_new();
    column              = gtk_tree_view_column_new_with_attributes("Mở/tắt", render, "active", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(dcu_control_schedule_widgets->dcu_control_treeview), column);
    g_signal_connect (render, "toggled", G_CALLBACK (on_dcu_control_on_off_callback), NULL);

    gtk_tree_view_set_model(GTK_TREE_VIEW(dcu_control_schedule_widgets->dcu_control_treeview), GTK_TREE_MODEL(dcu_control_schedule_widgets->dcu_control_lcu_list));

    // init for list lcu on tree view //
    dcu_control_schedule_widgets->dcu_schedule_program_store = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_INT);
    gtk_combo_box_set_model(GTK_COMBO_BOX(dcu_control_schedule_widgets->dcu_schedule_program_comboboxtext),
                            GTK_TREE_MODEL(dcu_control_schedule_widgets->dcu_schedule_program_store));
    gtk_combo_box_set_entry_text_column(GTK_COMBO_BOX(dcu_control_schedule_widgets->dcu_schedule_program_comboboxtext), 0);
    g_object_unref(dcu_control_schedule_widgets->dcu_schedule_program_store);
    // set dialge as fullscreen
    gtk_window_maximize(GTK_WINDOW(dcu_control_schedule_widgets->dcu_control_window));

    // accel for dcu_control_window
//    GClosure* closure = g_cclosure_new(spl_dcu_control_window_accelerator_pressed, 0, 0);
//    GtkAccelGroup* accel_group = gtk_accel_group_new();
//    gtk_accel_group_connect(accel_group, GDK_KEY_Escape, GDK_MODIFIER_MASK, (GtkAccelFlags)0, closure);
//    gtk_window_add_accel_group(GTK_WINDOW(dcu_control_schedule_widgets->dcu_control_window), accel_group);
    g_signal_connect(GTK_WIDGET(dcu_control_schedule_widgets->dcu_control_window),
                     "key_press_event", G_CALLBACK(spl_dcu_control_window_accelerator_pressed), NULL);
    //signal
//    g_signal_connect(GTK_WIDGET(dcu_control_schedule_widgets->dcu_control_window),
//                        "delete-event", G_CALLBACK(on_dcu_control_btn_clicked), GINT_TO_POINTER(DIALOG_CONTROL_BTN_QUIT));
    g_signal_connect (GTK_WIDGET(dcu_control_schedule_widgets->dcu_manual_summit_button),
                      "clicked", G_CALLBACK(on_dcu_control_btn_clicked), GINT_TO_POINTER(DIALOG_MANUAL_SUBMIT_SET));
    g_signal_connect (GTK_WIDGET(dcu_control_schedule_widgets->dcu_schedule_summit_button),
                      "clicked", G_CALLBACK(on_dcu_control_btn_clicked), GINT_TO_POINTER(DIALOG_SCHEDULE_SUBMIT_SET));
    g_signal_connect (GTK_WIDGET(SPL_OBJECT("btn_dcu_control_select_all")),
                      "clicked", G_CALLBACK(on_dcu_control_btn_clicked), GINT_TO_POINTER(DIALOG_CONTROL_BTN_SELECT_ALL));
    g_signal_connect (GTK_WIDGET(SPL_OBJECT("btn_dcu_control_deselect_all")),
                      "clicked", G_CALLBACK(on_dcu_control_btn_clicked), GINT_TO_POINTER(DIALOG_CONTROL_BTN_DESELECT_ALL));
    g_signal_connect (GTK_WIDGET(SPL_OBJECT("dcu_control_btn_quit")),
                      "clicked", G_CALLBACK(on_dcu_control_btn_clicked), GINT_TO_POINTER(DIALOG_CONTROL_BTN_QUIT));

    g_signal_connect (GTK_COMBO_BOX(dcu_control_schedule_widgets->dcu_schedule_program_comboboxtext), "changed",
                      G_CALLBACK(on_dcu_control_schedule_program_changed_callback),
                      NULL);

    g_signal_connect (GTK_COMBO_BOX(dcu_control_schedule_widgets->dcu_schedule_interleaved_comboboxtext), "changed",
                      G_CALLBACK(on_dcu_schedule_interleaved_changed_callback),
                      NULL);


    /*g_signal_connect (treeview, "clicked", G_CALLBACK(on_dcu_control_treeview_clicked_callback), store);
    g_signal_connect (switch_on_off, "activate", G_CALLBACK(on_dcu_control_switch_activate_callback), NULL);
    g_signal_connect (btn_set, "clicked", G_CALLBACK(on_dcu_control_btn_clicked), GINT_TO_POINTER(DIALOG_CONTROL_BTN_SET));
    g_signal_connect (btn_select, "clicked", G_CALLBACK(on_dcu_control_btn_clicked), GINT_TO_POINTER(DIALOG_CONTROL_BTN_SELECT_ALL));
    g_signal_connect (btn_deselect, "clicked", G_CALLBACK(on_dcu_control_btn_clicked), GINT_TO_POINTER(DIALOG_CONTROL_BTN_DESELECT_ALL));
    */
}

static void on_dcu_control_selection_changed_callback(GtkTreeSelection *treeselection, gpointer user_data)
{
    spl_dcu_control_display_light_on_map();
}

static void on_dcu_control_schedule_program_changed_callback(GtkComboBox *widget, gpointer user_data)
{
    gboolean is_choosed = (gtk_combo_box_get_active(widget) == -1)?FALSE:TRUE;

    gtk_widget_set_sensitive(dcu_control_schedule_widgets->dcu_control_treeview, is_choosed);
    gtk_widget_set_sensitive(dcu_control_schedule_widgets->dcu_control_select_button_box, is_choosed);
    gtk_widget_set_sensitive(dcu_control_schedule_widgets->dcu_control_is_temp, is_choosed);

    gtk_combo_box_set_active(GTK_COMBO_BOX(dcu_control_schedule_widgets->dcu_schedule_interleaved_comboboxtext), 0);
    on_dcu_schedule_interleaved_changed_callback(GTK_COMBO_BOX(dcu_control_schedule_widgets->dcu_schedule_interleaved_comboboxtext), NULL);
}

static void on_dcu_schedule_interleaved_changed_callback(GtkComboBox *widget, gpointer user_data)
{
    GtkTreeIter iter;
    GtkTreeModel *model = gtk_combo_box_get_model(widget);
    gint mode_schedule = -1;
    if(gtk_combo_box_get_active_iter(widget, &iter))
    {
        gtk_tree_model_get(model, &iter, 1, &mode_schedule, -1);
    }
    if(mode_schedule == -1)
        return;

    GtkTreeIter lcu_iter;
    GtkTreeStore *lcu_list_treestore = dcu_control_schedule_widgets->dcu_control_lcu_list;

    switch(mode_schedule)
    {
    case DCU_SCHEDULE_INTERLEAVED_0:
        if(gtk_tree_model_get_iter_first(GTK_TREE_MODEL(lcu_list_treestore), &lcu_iter))
        {
            do
            {
                gboolean is_on = FALSE;
                gtk_tree_model_get(GTK_TREE_MODEL(lcu_list_treestore), &lcu_iter, 3, &is_on, -1);
                gtk_tree_store_set(lcu_list_treestore, &lcu_iter, 1, is_on, -1);
            }
            while(gtk_tree_model_iter_next(GTK_TREE_MODEL(lcu_list_treestore), &lcu_iter));
        }
        break;
    case DCU_SCHEDULE_INTERLEAVED_1_1:
    {
        if(gtk_tree_model_get_iter_first(GTK_TREE_MODEL(lcu_list_treestore), &lcu_iter))
        {
            do
            {
                gtk_tree_store_set(lcu_list_treestore, &lcu_iter, 1, TRUE, -1);
                if(gtk_tree_model_iter_next(GTK_TREE_MODEL(lcu_list_treestore), &lcu_iter))
                    gtk_tree_store_set(lcu_list_treestore, &lcu_iter, 1, FALSE, -1);
                else
                    break;
            }
            while(gtk_tree_model_iter_next(GTK_TREE_MODEL(lcu_list_treestore), &lcu_iter));
        }
        break;
    }
    case DCU_SCHEDULE_INTERLEAVED_2_2:
    {
        if(gtk_tree_model_get_iter_first(GTK_TREE_MODEL(lcu_list_treestore), &lcu_iter))
        {
            gint count_iter = 0;
            do
            {
                gtk_tree_store_set(lcu_list_treestore, &lcu_iter, 1, TRUE, -1);
                if(gtk_tree_model_iter_next(GTK_TREE_MODEL(lcu_list_treestore), &lcu_iter))
                    gtk_tree_store_set(lcu_list_treestore, &lcu_iter, 1, TRUE, -1);
                else
                    break;
                if(gtk_tree_model_iter_next(GTK_TREE_MODEL(lcu_list_treestore), &lcu_iter))
                    gtk_tree_store_set(lcu_list_treestore, &lcu_iter, 1, FALSE, -1);
                else
                    break;
                if(gtk_tree_model_iter_next(GTK_TREE_MODEL(lcu_list_treestore), &lcu_iter))
                    gtk_tree_store_set(lcu_list_treestore, &lcu_iter, 1, FALSE, -1);
                else
                    break;
            }
            while(gtk_tree_model_iter_next(GTK_TREE_MODEL(lcu_list_treestore), &lcu_iter));
        }
        break;
    }
    case DCU_SCHEDULE_INTERLEAVED_1_2:
    {
        if(gtk_tree_model_get_iter_first(GTK_TREE_MODEL(lcu_list_treestore), &lcu_iter))
        {
            do
            {
                gtk_tree_store_set(lcu_list_treestore, &lcu_iter, 1, TRUE, -1);
                if(gtk_tree_model_iter_next(GTK_TREE_MODEL(lcu_list_treestore), &lcu_iter))
                    gtk_tree_store_set(lcu_list_treestore, &lcu_iter, 1, FALSE, -1);
                else
                    break;
                if(gtk_tree_model_iter_next(GTK_TREE_MODEL(lcu_list_treestore), &lcu_iter))
                    gtk_tree_store_set(lcu_list_treestore, &lcu_iter, 1, FALSE, -1);
                else
                    break;
            }
            while(gtk_tree_model_iter_next(GTK_TREE_MODEL(lcu_list_treestore), &lcu_iter));
        }
        break;
    }
    };

    spl_dcu_control_display_light_on_map();
}

void spl_dcu_control_dialog_show(gint type, pSplDcu dcu)
{
    g_return_if_fail(!IS_EMPTY_LIST_LCU(dcu));

    spl_dcu_control_init();

    map_image_remove_all();
//    DEBUG("TYPE: %d", type);
//    DEBUG("DIALOG_CONTROL_IS_ON_OFF: %d", DIALOG_CONTROL_IS_ON_OFF);
//    DEBUG("DIALOG_CONTROL_IS_SCHEDULE: %d", DIALOG_CONTROL_IS_SCHEDULE);
    switch(type)
    {
    case DIALOG_CONTROL_IS_ON_OFF:
        spl_dcu_control_dialog_as_manual_show(dcu);
        break;
    case DIALOG_CONTROL_IS_SCHEDULE:
        spl_dcu_control_dialog_as_schedule_show(dcu);
        break;
    }

    if(!osm_gps_map_change_parent("map_box", "dcu_control_osm_map_box"))
        return;

#if 1//def WIN32
    GdkScreen *screen = gdk_screen_get_default();
    if(screen)
        gtk_widget_set_size_request(dcu_control_schedule_widgets->dcu_control_window,
                                gdk_screen_get_width(screen), gdk_screen_get_height(screen));

#else
    gtk_window_maximize(GTK_WINDOW(dcu_control_schedule_widgets->dcu_control_window));
#endif

    SPL_DIALOG_SHOW(dcu_control_schedule_widgets->dcu_control_window);
    gtk_widget_show(dcu_control_schedule_widgets->dcu_control_window);
}

static void spl_dcu_control_dialog_as_manual_show(pSplDcu dcu)
{
    g_return_if_fail(dcu_control_schedule_widgets);

    dcu_control_manual_show_hide(TRUE);
    dcu_control_schedule_show_hide(FALSE);
    gtk_label_set_text(GTK_LABEL(SPL_OBJECT("dcu_control_lb_title")), (gchar *)"Điều khiển trạm");
    gtk_label_set_text(GTK_LABEL(dcu_control_schedule_widgets->dcu_control_core_frame_label ),
                       (gchar *)"Điều khiển bằng tay");
    gtk_label_set_text(GTK_LABEL(SPL_OBJECT("dcu_control_lb_id")), dcu->priv->id);

    //clear store
    isControlShow = TRUE;
    GtkTreeIter iter;
    GtkTreeStore *model = GTK_TREE_STORE(dcu_control_schedule_widgets->dcu_control_lcu_list);
    gtk_tree_store_clear(model);

    GSList *temp;
    GSList *list_lcu_sorted = g_slist_copy(dcu->priv->childlist);
    for(temp = list_lcu_sorted; temp != NULL; temp = temp->next)
    {
        if(temp)
        {
            pSplLcu lcu = (pSplLcu)temp->data;
            if(lcu)
            {

                gtk_tree_store_append(model, &iter, NULL);
                gtk_tree_store_set(model, &iter,
                                   0, lcu->id,
                                   1, lcu->isOn,
                                   2, lcu,
                                   3, lcu->isOn, -1);
            }
        }
    }
    //show light on map base on
    spl_dcu_control_display_light_on_map();
}
static void spl_dcu_control_dialog_as_schedule_show(pSplDcu dcu)
{
    g_return_if_fail(dcu_control_schedule_widgets);

    dcu_control_schedule_show_hide(TRUE);
    dcu_control_manual_show_hide(FALSE);
    gtk_label_set_text(GTK_LABEL(SPL_OBJECT("dcu_control_lb_title")), (gchar *)"Lập lịch hoạt động");
    gtk_label_set_text(GTK_LABEL(dcu_control_schedule_widgets->dcu_control_core_frame_label ),
                       (gchar *)"Thiết lập tự động");
    gtk_label_set_text(GTK_LABEL(SPL_OBJECT("dcu_control_lb_id")), dcu->priv->id);

    gtk_combo_box_set_active(GTK_COMBO_BOX(dcu_control_schedule_widgets->dcu_schedule_interleaved_comboboxtext), 0);
    on_dcu_schedule_interleaved_changed_callback(GTK_COMBO_BOX(dcu_control_schedule_widgets->dcu_schedule_interleaved_comboboxtext), NULL);

    // Sorted LCU of DCU follow GPS address //
    dcu_control_schedule_widgets->dcu_schedule_lcu_sorted_list = dcu_schedule_interleaved_prepare(dcu);

    gint zone_id = dcu->priv->zonecode;
    ns1__PROGRAM_USCOREINFO_USCOREType ** program = NULL;
    gint program_size;
    gint current_program = -1;
    if(zone_id!=0)
    {
        GtkTreeIter iter;
        GtkListStore *store = dcu_control_schedule_widgets->dcu_schedule_program_store;
        smartstreetlight_clear_list_store(GTK_TREE_MODEL(store));
        SplSoap spl_soap;
        gint soap_err= smartstreetlight_get_program_list_nofree_execute(&spl_soap,zone_id, 0,&program, &program_size);
        if (soap_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
        {
            if (program != NULL)
            {
                for(gint i = 0; i<program_size; i++)
                {
                    gtk_list_store_append(store, &iter);
                    gtk_list_store_set(store, &iter,
                                       0, program[i]->program_USCOREname,
                                       1, program[i]->program_USCOREid,   -1);
                    if(program[i]->program_USCOREid == dcu->priv->programId)
                    {
                        current_program = i;
                    }
                }
                gtk_combo_box_set_active(GTK_COMBO_BOX(dcu_control_schedule_widgets->dcu_schedule_program_comboboxtext), current_program);
                on_dcu_control_schedule_program_changed_callback(GTK_COMBO_BOX(dcu_control_schedule_widgets->dcu_schedule_program_comboboxtext), NULL);
            }
        } else {
            gchar * msg = g_strdup("Lỗi lấy danh sách chương trình từ server. ");
            GtkWidget *parent = stack_widget_active_top();
            smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
            g_char_free(msg);

        }

        smartstreetlight_free_soap_operation(&spl_soap);
    }

    //clear store
    isControlShow = TRUE;
    GtkTreeIter iter;
    GtkTreeStore *model = GTK_TREE_STORE(dcu_control_schedule_widgets->dcu_control_lcu_list);
    gtk_tree_store_clear(model);

    GSList *temp;
    GSList *list_lcu_sorted = dcu_control_schedule_widgets->dcu_schedule_lcu_sorted_list;

    if(!list_lcu_sorted)
        list_lcu_sorted = g_slist_copy(dcu->priv->childlist);

    for(temp = list_lcu_sorted; temp != NULL; temp = temp->next)
    {
        if(temp && temp->data)
        {
            pSplLcu lcu = (pSplLcu)temp->data;
            if(lcu)
            {
                gboolean is_active = FALSE;
                if(lcu->mode == SPL_LCU_ScheduleMode && (current_program != -1))
                    is_active = TRUE;

                gtk_tree_store_append(model, &iter, NULL);
                gtk_tree_store_set(model, &iter,
                                   0, lcu->id,
                                   1, is_active,
                                   2, lcu,
                                   3, is_active, -1);
            }
        }
    }
    //show light on map base on
    spl_dcu_control_display_light_on_map();
}

static void dcu_control_manual_show_hide(gboolean is_show)
{
    gtk_widget_set_visible(dcu_control_schedule_widgets->dcu_manual_level_grid, is_show);
    gtk_widget_set_visible(dcu_control_schedule_widgets->dcu_manual_summit_button, is_show);
    gtk_widget_set_visible(dcu_control_schedule_widgets->dcu_control_is_temp, is_show);
}
static void dcu_control_schedule_show_hide(gboolean is_show)
{
    gtk_widget_set_visible(dcu_control_schedule_widgets->dcu_schedule_program_box, is_show);
    gtk_widget_set_visible(dcu_control_schedule_widgets->dcu_schedule_interleaved_comboboxtext, is_show);
    gtk_widget_set_visible(dcu_control_schedule_widgets->dcu_schedule_summit_button, is_show);
}
static void on_dcu_control_on_off_callback (GtkCellRendererToggle *cell,
        gchar *path_str,
        gpointer data)
{
    GtkTreeIter iter;
    GtkTreePath *path = gtk_tree_path_new_from_string (path_str);
    gboolean toggle;
    pSplLcu lcu;
    /* get toggled iter */
    gtk_tree_model_get_iter (GTK_TREE_MODEL(dcu_control_schedule_widgets->dcu_control_lcu_list), &iter, path);
    gtk_tree_model_get (GTK_TREE_MODEL(dcu_control_schedule_widgets->dcu_control_lcu_list), &iter, 1, &toggle, 2, &lcu, -1);

    /* set new value */
    gtk_tree_store_set (dcu_control_schedule_widgets->dcu_control_lcu_list, &iter, 1, !toggle, -1);

    gtk_tree_path_free (path);
    spl_dcu_control_display_light_on_map();
    osm_gps_map_set_lcu_center(lcu);
}
void spl_dcu_control_set_all_selected(gboolean select)
{
    GtkTreeIter iter;
    GtkTreeModel *model = GTK_TREE_MODEL(dcu_control_schedule_widgets->dcu_control_lcu_list);
    if(gtk_tree_model_get_iter_first(model, &iter))
    {
        do
        {
            gtk_tree_store_set(dcu_control_schedule_widgets->dcu_control_lcu_list, &iter, 1, select, -1);
        }
        while(gtk_tree_model_iter_next(model, &iter));
    }
}
void spl_dcu_control_display_light_on_map()
{
    GtkTreeIter iter;
    GtkTreeModel *model = GTK_TREE_MODEL(dcu_control_schedule_widgets->dcu_control_lcu_list);
    gboolean toggled;
    gfloat lat = 0, lon;
    map_image_remove_all();
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(dcu_control_schedule_widgets->dcu_control_treeview));
    if(gtk_tree_model_get_iter_first(model, &iter))
    {
        do
        {
            pSplLcu lcu;
            gint offset = 0;
            gtk_tree_model_get(model, &iter, 1, &toggled, 2, &lcu, -1);
            if(gtk_tree_selection_iter_is_selected(selection, &iter))
            {
                offset = 3;
                osm_gps_map_set_lcu_center(lcu);
            }
            spl_lcu_add_image(lcu, light_image[ offset + (toggled ? ICON_LIGHT_ON : ICON_LIGHT_OFF )], &lat, &lon);
        }
        while(gtk_tree_model_iter_next(model, &iter));
    }
    /*if(lat)
        osm_gps_map_set_center(map, lat, lon);*/
}

void spl_dcu_select_iter_of_light(OsmGpsMapImage *im)
{
    GtkTreeIter iter;
    GtkTreeModel *model = GTK_TREE_MODEL(dcu_control_schedule_widgets->dcu_control_lcu_list);
    GtkTreeView *view = GTK_TREE_VIEW(dcu_control_schedule_widgets->dcu_control_treeview);
    GtkTreeSelection *selection = gtk_tree_view_get_selection(view);
    if(gtk_tree_model_get_iter_first(model, &iter))
    {
        do
        {
            pSplLcu lcu;
            gtk_tree_model_get(model, &iter, 2, &lcu, -1);
            if(lcu  && lcu == (pSplLcu)im->handler)
            {
                GtkTreePath *path = gtk_tree_model_get_path(model, &iter);
                gtk_tree_selection_select_iter(selection, &iter);
                gtk_tree_view_scroll_to_cell(view, path, NULL, FALSE, 0, 0);
                gtk_tree_path_free(path);
                break;
            }
        }
        while(gtk_tree_model_iter_next(model, &iter));
    }
}

static GSList * dcu_schedule_interleaved_prepare(pSplDcu dcu)
{
    GSList *list_lcu_sorted = g_slist_alloc();
    GSList *item;
    GString *strErr = g_string_new(NULL);
    gfloat lat_x, lat_y, lon_x, lon_y;
    pSplLcu lcu_closest;

    g_return_if_fail(dcu && dcu->priv && dcu->priv->childlist);

    GSList *lcu_list = g_slist_copy(dcu->priv->childlist);

    pSplLcu root_position_lcu =  dcu_schedule_interleaved_scheck_incense(lcu_list);

    g_return_if_fail(root_position_lcu);

    lat_x = root_position_lcu->lat;
    lon_x = root_position_lcu->lon;

//    DEBUG("\n\n\n");
//    DEBUG_0("\n ROOT : %s", root_position_lcu->id);

    do
    {
        gfloat min_distance = -1;
        gfloat new_distance = -1;

        for(item = lcu_list; item != NULL; item = item->next)
        {
            if(item && item->data)
            {
                pSplLcu lcu = (pSplLcu)item->data;
                if(lcu)
                {
    //                DEBUG_0("\n NEXT LCU: %s - x:%f; y:%f", lcu->id, lcu->lat, lcu->lon);

                    lat_y = lcu->lat;
                    lon_y = lcu->lon;

                    new_distance = distance_lat_lon(lat_x, lon_x, lat_y, lon_y, 'm');

    //                DEBUG_0("\n new_distance: %f", new_distance);
                    if(new_distance < min_distance | min_distance == -1)
                    {
                        lcu_closest = lcu;
                        min_distance = new_distance;

                    }
                }
            }
        }
        lat_x = lcu_closest->lat;
        lon_y = lcu_closest->lon;
        list_lcu_sorted = g_slist_append(list_lcu_sorted, lcu_closest);
        lcu_list = g_slist_remove(lcu_list, lcu_closest);

    }
    while(lcu_list);

//    DEBUG_0("\n\n\n");
//    GSList *temp;
//    for(temp = list_lcu_sorted; temp != NULL; temp = temp->next)
//    {
//        if(temp)
//        {
//            pSplLcu lcu = (pSplLcu)temp->data;
//            if(lcu)
//            {
//                DEBUG_0("%s ", lcu->id);
//            }
//        }
//    }

    return list_lcu_sorted;
}

static pSplLcu dcu_schedule_interleaved_scheck_incense(GSList *lcu_list)
{
    GSList *temp;
    gfloat distance_lat = 0, distance_lon = 0;
    pSplLcu lcu_min_lat = NULL, lcu_max_lat = NULL, lcu_min_lon = NULL, lcu_max_lon = NULL;
    for(temp = lcu_list; temp != NULL; temp = temp->next)
    {
        if(temp)
        {
            pSplLcu lcu = (pSplLcu)temp->data;
            if(lcu)
            {
                if(sscanf(lcu->gps, "%f-%f", &lcu->lat,  &lcu->lon) != 2)
                    return NULL;

                if(lcu_min_lat == NULL || lcu->lat < lcu_min_lat->lat)
                {
                    lcu_min_lat = lcu;
                }
                if(lcu_max_lat == NULL || lcu->lat > lcu_max_lat->lat)
                {
                    lcu_max_lat = lcu;
                }
                if(lcu_min_lon == NULL || lcu->lon < lcu_min_lon->lon)
                {
                    lcu_min_lon = lcu;
                }
                if(lcu_max_lon == NULL || lcu->lon < lcu_max_lon->lon)
                {
                    lcu_max_lon = lcu;
                }
            }
        }
    }

    if(lcu_max_lat != NULL && lcu_min_lat != NULL)
        distance_lat = lcu_max_lat - lcu_min_lat;
    if(lcu_max_lon != NULL && lcu_min_lon != NULL)
        distance_lon = lcu_max_lon - lcu_min_lon;

    if(distance_lat>distance_lon)
    {
        return lcu_min_lat;
    }
    else
    {
        return lcu_min_lon;
    }
}

struct ScheduleDcuThread{
    gchar* dcu_id;
    gint program_id;
};

static void smartstreetlight_schedule_dcu_execute(gpointer args)
{
    SoapResponse *soap_response = (SoapResponse *)args;
    struct ScheduleDcuThread* schedule_dcu = (struct ScheduleDcuThread *)soap_response->data;
    soap_response->result_value = smartstreetlight_set_program_for_dcu_execute(&soap_thread.spl_soap,
                                                                               schedule_dcu->dcu_id,
                                                                               SPL_DCU_WirelessMode,
                                                                               schedule_dcu->program_id);
}
static void* smartstreetlight_schedule_dcu_receive(gpointer data)
{
//    DEBUG_1();
    SoapResponse *soap_response = (SoapResponse *)data;
    gboolean is_fail_ctrl = FALSE;
    struct ScheduleDcuThread *schedule_dcu = (struct ScheduleDcuThread*)soap_response->data;
    if(soap_response->result_value == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
    {
        GtkWidget *parent = stack_widget_active_top();
        SPL_INFO_POPUP(parent, "Yêu cầu lập lịch cho trạm thành công.");

        pSplDcu _dcu = NULL;
        GString *msgError = g_string_new (NULL);
        if(LOCKUP_LIST_DCU(schedule_dcu->dcu_id, _dcu))
        {
            if(_dcu && _dcu->priv)
            {
                _dcu->priv->programId = schedule_dcu->program_id;
                _dcu->priv->status = _dcu->priv->status &(~(SPL_DCU_MANUAL_MODE));
                spl_dcu_set_information(_dcu);
            }
        }
        on_dcu_control_btn_clicked(NULL, GINT_TO_POINTER(DIALOG_CONTROL_BTN_QUIT));
    }
    else
    {
        DEBUG("Set program %d for dcu %s is FAIL !!", schedule_dcu->program_id, schedule_dcu->dcu_id);
        gchar * msg = g_strconcat("Lỗi thiết lập lập lịch cho trạm có id là ", schedule_dcu->dcu_id,". ", NULL);
        GtkWidget *parent = stack_widget_active_top();
        smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_response->result_value);
        g_char_free(msg);
    }
    g_char_free(schedule_dcu->dcu_id);
    g_free((pSplLcu)soap_response->data);
    g_free(soap_response);
    return NULL;
}
static void smartstreetlight_dcu_schedule_thread(const char *dcu_id,gboolean is_fail_ctrl)
{
    gint responseId;
    gboolean is_continue = FALSE;
    if(is_fail_ctrl==TRUE)
    {
        gchar *warning_str = g_strdup("Tiếp tục gửi yêu cầu lập lịch cho trạm này?");
        GtkWidget *parent = stack_widget_active_top();
        switch(responseId = SPL_QUESTION_YES_NO_POPUP(parent, warning_str))
        {
        case GTK_RESPONSE_YES:
            is_continue = TRUE;
            break;
        case GTK_RESPONSE_NO:
            break;
        }
        g_free(warning_str);
    }
    DEBUG("is_continue: %d, is_fail_ctrl: %d,responseId: %d\n", is_continue, is_fail_ctrl,responseId);
    if (is_fail_ctrl==FALSE || is_continue==TRUE)
    {
        GtkComboBox *program_combobox = GTK_COMBO_BOX(dcu_control_schedule_widgets->dcu_schedule_program_comboboxtext);
        GtkTreeIter program_iter;
        if(gtk_combo_box_get_active_iter(program_combobox, &program_iter))
        {
            ScheduleDcuThread * schedule_dcu= g_new0(ScheduleDcuThread, 1);

            GtkTreeModel *program_model = gtk_combo_box_get_model(program_combobox);
            gtk_tree_model_get(program_model, &program_iter, 1, &schedule_dcu->program_id, -1);
            schedule_dcu->dcu_id = g_strdup(dcu_id);
            //DEBUG("schedule_dcu->dcu_id: %s,schedule_dcu->program_id: %d\n",schedule_dcu->dcu_id,schedule_dcu->program_id);
            if(soap_thread.init_thread(schedule_dcu, smartstreetlight_schedule_dcu_execute,
                                                smartstreetlight_schedule_dcu_receive ) == FALSE)
            {
                gchar * str_error = g_strdup("Không thể tạo thread xử lý cho thao tác điều khiển LCU.");
                GtkWidget *parent = stack_widget_active_top();
                smartstreetlight_error_check_message_result(GTK_WIDGET(parent), str_error, ns1__MESSAGE_USCORERESULT_USCOREEnum__INTERNAL_USCOREERR);
                g_free(str_error);
            }
        }
    }
}

struct CtrlAllLcuInDcuThread{
    gchar* dcu_id;
    gboolean is_temp;
    gint scale;
    gint mode;
    GString *lights_is_on;
    GString *lights_is_off;
    gint rsp_lcu_list_size;
    gboolean is_program;
    ns1__LCU_USCOREINFO_USCOREType **rsp_lcu_list;
};
static void smartstreetlight_control_lcu_list_execute(gpointer args)
{
    SoapResponse *soap_response = (SoapResponse *)args;
    struct CtrlAllLcuInDcuThread* ctrl_list_lcu = (struct CtrlAllLcuInDcuThread *)soap_response->data;
    soap_response->result_value = smartstreetlight_control_lcu_nofree(&soap_thread.spl_soap,ctrl_list_lcu->dcu_id,
                                                                      ctrl_list_lcu->lights_is_on, ctrl_list_lcu->lights_is_off,
                                                                      ctrl_list_lcu->scale,
                                                                      ctrl_list_lcu->mode,
                                                                      ctrl_list_lcu->is_temp,
                                                                      &ctrl_list_lcu->rsp_lcu_list,
                                                                      &ctrl_list_lcu->rsp_lcu_list_size,
                                                                      ctrl_list_lcu->is_program);
}


static void* smartstreetlight_control_lcu_list_receive(gpointer data)
{
    SoapResponse *soap_response = (SoapResponse *)data;
    gboolean is_fail_ctrl = TRUE;

    struct CtrlAllLcuInDcuThread *ctrl_list_lcu = (struct CtrlAllLcuInDcuThread*)soap_response->data;
    DEBUG("ctrl_list_lcu->dcu_id: %s\n",ctrl_list_lcu->dcu_id);
    if(soap_response->result_value == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
    {
        pSplDcu _dcu = NULL;
        GString *msgError = g_string_new (NULL);
        if(LOCKUP_LIST_DCU(ctrl_list_lcu->dcu_id, _dcu))
        {

            if(_dcu && _dcu->priv)
            {
                for(gint i=0; i<ctrl_list_lcu->rsp_lcu_list_size; i++)
                {
                    pSplLcu _lcu = NULL;

                    if( LOCKUP_LIST_LCU(_dcu, ctrl_list_lcu->rsp_lcu_list[i]->lcu_USCOREid, _lcu))
                    {
                        if(_lcu)
                        {
                            _lcu->mode = ctrl_list_lcu->rsp_lcu_list[i]->lcu_USCOREmode;
                            _lcu->isOn = ctrl_list_lcu->rsp_lcu_list[i]->lcu_USCOREison;
                            _lcu->status = ctrl_list_lcu->rsp_lcu_list[i]->lcu_USCOREstatus;
                            _lcu->brightness = (gfloat)ctrl_list_lcu->rsp_lcu_list[i]->lcu_USCORElevel;
                            _lcu->volt = (gfloat)ctrl_list_lcu->rsp_lcu_list[i]->lcu_USCOREcurrent;
                            if (IS_ERROR_LCU(_lcu->status))
                            {
                                g_string_append_printf(msgError, "Điều khiển %s bị lỗi\n", _lcu->id);
                            }
                        }
                    }
                }
                if (ctrl_list_lcu->is_program == FALSE)
                {
                    // update info dcu
                        _dcu->priv->status = _dcu->priv->status | (SPL_DCU_MANUAL_MODE);
                        spl_dcu_set_information(_dcu);
                }

            }


        }
        if (msgError->len == 0)
        {
            is_fail_ctrl = FALSE;
            if (ctrl_list_lcu->is_program == FALSE)
            {
                GtkWidget *parent = stack_widget_active_top();
                SPL_INFO_POPUP(parent, "Yêu cầu điều khiển các đèn của DCU thành công.");

                on_dcu_control_btn_clicked(NULL, GINT_TO_POINTER(DIALOG_CONTROL_BTN_QUIT));
            }
        }
        else
        {
            GtkWidget *parent = stack_widget_active_top();
            SPL_ERROR_POPUP(parent, msgError->str);
        }
    }
    else
    {
        gchar * msg = g_strconcat("Lỗi điền khiển các đèn của trạm có id là ", ctrl_list_lcu->dcu_id,". ", NULL);
        GtkWidget *parent = stack_widget_active_top();
        smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_response->result_value);
        g_char_free(msg);
    }
    smartstreetlight_free_soap_operation(&soap_thread.spl_soap);
    if (ctrl_list_lcu->is_program == TRUE && soap_response->result_value == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
    {
        smartstreetlight_dcu_schedule_thread(ctrl_list_lcu->dcu_id,is_fail_ctrl);
    }
    g_string_free(ctrl_list_lcu->lights_is_on, TRUE);
    g_string_free(ctrl_list_lcu->lights_is_off, TRUE);
    g_char_free(ctrl_list_lcu->dcu_id);
    g_free((pSplLcu)soap_response->data);
    g_free(soap_response);

    return NULL;
}

void smartstreetlight_dcu_schedule_setting(void)
{
    GtkWidget * dcu_id_label = GTK_WIDGET(SPL_OBJECT("dcu_control_lb_id"));
    GtkWidget * dcu_control_is_temp = GTK_WIDGET(SPL_OBJECT("dcu_control_is_temp"));
    g_return_if_fail(dcu_id_label && dcu_control_is_temp);

    gboolean is_temp = (gboolean)gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(dcu_control_is_temp));
    const gchar *dcu_id = gtk_label_get_text(GTK_LABEL(dcu_id_label));

    GtkTreeIter program_iter;

    GtkComboBox *program_combobox = GTK_COMBO_BOX(dcu_control_schedule_widgets->dcu_schedule_program_comboboxtext);
    GtkTreeModel *program_model = gtk_combo_box_get_model(program_combobox);
    GString *lights_is_on = NULL;
    GString *lights_is_off = NULL;

    // SET OFF MODE FOR SOME LCU //
    GtkComboBox *schedule_mode_combo_box = GTK_COMBO_BOX(dcu_control_schedule_widgets->dcu_schedule_interleaved_comboboxtext);
    GtkTreeModel *interleaved_model = gtk_combo_box_get_model(schedule_mode_combo_box);
    GtkTreeIter interleaved_iter;
    gint mode_schedule = -1;
    if(gtk_combo_box_get_active_iter(schedule_mode_combo_box, &interleaved_iter))
    {
        gtk_tree_model_get(interleaved_model, &interleaved_iter, 1, &mode_schedule, -1);
    }
    //DEBUG("===================================>mode_schedule: %d\n",mode_schedule);




    if(mode_schedule != -1 && gtk_combo_box_get_active_iter(program_combobox, &program_iter))
    {

        struct CtrlAllLcuInDcuThread *ctrl_list_lcu = g_new0(CtrlAllLcuInDcuThread,1);
        spl_dcu_control_schedule_get_lcu_list_with_state(&lights_is_on, &lights_is_off);
        ctrl_list_lcu->dcu_id = g_strdup(dcu_id);
        ctrl_list_lcu->is_temp = is_temp;
        ctrl_list_lcu->scale = -1;
        ctrl_list_lcu->mode = SPL_LCU_ScheduleMode; // set cho vui, khong tac dung
        ctrl_list_lcu->lights_is_on = lights_is_on;
        ctrl_list_lcu->lights_is_off = lights_is_off;
        ctrl_list_lcu->is_program = TRUE;
        //DEBUG("ctrl_list_lcu->dcu_id: %s, dcu_id: %s\n",ctrl_list_lcu->dcu_id,dcu_id);
        if(soap_thread.init_thread(ctrl_list_lcu, smartstreetlight_control_lcu_list_execute,
                                            smartstreetlight_control_lcu_list_receive ) == FALSE)
        {
            gchar * str_error = g_strdup("Không thể tạo thread xử lý cho thao tác thiết lập lập lịch.");
            GtkWidget *parent = stack_widget_active_top();
            smartstreetlight_error_check_message_result(GTK_WIDGET(parent), str_error, ns1__MESSAGE_USCORERESULT_USCOREEnum__INTERNAL_USCOREERR);
            g_free(str_error);
        }
    }

}



void spl_dcu_control_execute()
{
    gboolean exit = FALSE;

    GtkWidget * dcu_id_label = GTK_WIDGET(SPL_OBJECT("dcu_control_lb_id"));
    GtkWidget * lcu_brightness_adjustment = GTK_WIDGET(SPL_OBJECT("lcu_brightness_adjustment"));
    GtkWidget * dcu_control_is_temp = GTK_WIDGET(SPL_OBJECT("dcu_control_is_temp"));

    g_return_if_fail(dcu_id_label && lcu_brightness_adjustment && dcu_control_is_temp);

    const gchar *dcu_id = gtk_label_get_text(GTK_LABEL(dcu_id_label));
    gint light_level = (gint)gtk_adjustment_get_value(GTK_ADJUSTMENT(lcu_brightness_adjustment))*10;
    gboolean is_temp = (gboolean)gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(dcu_control_is_temp));

    GString *lights_is_on = NULL;
    GString *lights_is_off = NULL;

//    DEBUG("light_level: %d", light_level);
    spl_dcu_control_schedule_get_lcu_list_with_state(&lights_is_on, &lights_is_off);
    struct CtrlAllLcuInDcuThread *ctrl_list_lcu = g_new0(CtrlAllLcuInDcuThread,1);
    ctrl_list_lcu->dcu_id = g_strdup(dcu_id);
    ctrl_list_lcu->is_temp = is_temp;
    ctrl_list_lcu->scale = light_level;
    ctrl_list_lcu->mode = SPL_LCU_ManualMode;
    ctrl_list_lcu->lights_is_on = lights_is_on;
    ctrl_list_lcu->lights_is_off = lights_is_off;
    ctrl_list_lcu->is_program = FALSE;
    if(soap_thread.init_thread(ctrl_list_lcu, smartstreetlight_control_lcu_list_execute,
                                        smartstreetlight_control_lcu_list_receive ) == FALSE)
    {
        gchar * str_error = g_strdup("Không thể tạo thread xử lý cho thao tác điều khiển LCU.");
        GtkWidget *parent = stack_widget_active_top();
        smartstreetlight_error_check_message_result(GTK_WIDGET(parent), str_error, ns1__MESSAGE_USCORERESULT_USCOREEnum__INTERNAL_USCOREERR);
        g_free(str_error);
    }
}


static void spl_dcu_control_schedule_get_lcu_list_with_state(GString **lights_is_on, GString **lights_is_off)
{
    GtkTreeIter iter;
    GtkTreeModel *model = GTK_TREE_MODEL(dcu_control_schedule_widgets->dcu_control_lcu_list);
    gchar *lcu_id;
    gboolean lcu_is_on;

    if(gtk_tree_model_get_iter_first(model, &iter))
    {
        do
        {
            gtk_tree_model_get(model, &iter, 0, &lcu_id,
                               1, &lcu_is_on, -1);
            if(lcu_is_on)
            {
                if(!*lights_is_on)
                    *lights_is_on = g_string_new(lcu_id);
                else
                    g_string_append_printf(*lights_is_on, "-%s", lcu_id);
            }
            else
            {
                if(!*lights_is_off)
                    *lights_is_off = g_string_new(lcu_id);
                else
                    g_string_append_printf(*lights_is_off, "-%s", lcu_id);
            }
        }
        while(gtk_tree_model_iter_next(model, &iter));
    }
}

gboolean spl_dcu_info_show_tab_on_notebook()
{
    GtkWidget * dcu_treeview = GTK_WIDGET(main_view_widgets->dcu_view);

    if(osm_gps_map_change_parent("admin_zone_map_box", "map_box"))
    {
        if(spl_widget_change_parent(dcu_treeview, GTK_WIDGET(SPL_OBJECT("scrolledwindow23")),
                                              GTK_WIDGET(SPL_OBJECT("scrolledwindow19"))))
        {
//            DEBUG("\n\n ************** SET CURRENT_PARENT IS ADMIN_ZONE\n\n");
            g_object_set_data(G_OBJECT(dcu_treeview), "current_parent", (gpointer)"dcu_info_container");
            osm_gps_map_image_remove_all(map);

            osm_osm_gps_map_show_lights(gtk_combo_box_get_active(GTK_COMBO_BOX(cbb_light_display)),
                                                         lastSelectedDcu);
            GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(dcu_treeview));
            gtk_tree_selection_unselect_all(selection);
            gtk_tree_view_collapse_all(GTK_TREE_VIEW(dcu_treeview));
        }
        return TRUE;
    }
    return FALSE;
}

void spl_zone_clear_is_show()
{
    GSList *item;
    LIST_ZONE_FOR_EACH_ENTRY(item)
    {
        pSplZone _zone = (pSplZone)item->data;
        _zone->isshowmap = FALSE;
    }
}


/** ------------------------------------------------------------------------------ **/
