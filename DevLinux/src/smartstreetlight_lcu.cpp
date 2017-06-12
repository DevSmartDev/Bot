#include "main.h"
#include "smartstreetlight_lcu.h"
#include "smartstreetlight_sql.h"
#include "smartstreetlight_soap.h"
#include "smartstreetlight_ui_method.h"
#include "smartstreetlight_utils.h"
#include "smartstreetlight_login.h"
#include "smartstreetlight_error.h"
#include "smartstreetlight_soap_thread.h"
#include <gtk/gtk.h>
#include "gsoap/soapH.h"

GSList *LcuLogList = NULL;
pSplDcu lastSelectedDcu = NULL;
GtkComboBox *cbb_light_display = NULL;
pSplLcu lastSelectedLcu = NULL;

struct SPL_LCU_POPUP_MENU *lcu_info_popup_menu = NULL;

struct SPL_LCU_Widgets *lcu_widgets = NULL;

static void smartstreetlight_view_init();

static gboolean smartstreetlight_lcu_tree_view_init(void);

static gboolean smartstreetlight_lcu_list_store_init(void);

void smartstreetlight_lcu_dcu_list_combobox_fill(gchar *dcu_name);

static gboolean smartstreetlight_lcu_popup_menu_init(void);

static void smartstreetlight_lcu_popup_menu_widget_init(void);
static void smartstreetlight_lcu_popup_menu_callback_init(void);

static void smartstreetlight_lcu_popup_menu_clicked(GtkWidget *popup_menu_item, gpointer userdata);
static gboolean smartstreetlight_lcu_popup_menu_add_clicked(void);
static gboolean smartstreetlight_lcu_popup_menu_control_clicked(void);
static void smartstreetlight_lcu_popup_menu_remove_clicked(void);
static void smartstreetlight_lcu_popup_menu_remove_all_clicked(void);

/** ================================================================================================== **/
/** ================================================================================================== **/


static void  smartstreetlight_lcu_add_soap_execute(gpointer args);
static void* smartstreetlight_lcu_add_soap_receive(gpointer data);
static gboolean smartstreetlight_lcu_add_soap_receive_process(pSplLcu lcu);

static void  smartstreetlight_lcu_remove_soap_execute(gpointer args);
static void* smartstreetlight_lcu_remove_soap_receive(gpointer data);
static void smartstreetlight_lcu_remove_soap_receive_process(pSplLcu lcu);

static void spl_light_chart_show_execute(pSplLcu lcu, gchar *time_from, gchar *time_to);
static gboolean on_switch_button_press(GtkWidget *widget, GdkEvent *event, gpointer user_data);
static gboolean on_light_switch_light_button_press(GtkWidget *widget, GdkEvent *event, gpointer user_data);
/** ================================================================================================== **/
/** ================================================================================================== **/



static gboolean copy_light(pSplLcu pA, pSplLcu pB)
{
    pA->brightness  = pB->brightness;
    if(pA->icon)
    {
        osm_gps_map_image_remove(map, pA->icon);
    }
    pA->icon        = pB->icon;
    pA->isBroken    = pB->isBroken;
    pA->isOn        = pB->isOn;
    pA->mode        = pB->mode;
    pA->parent      = pB->parent;
    pA->status      = pB->status;
    pA->volt        = pB->volt;
    g_char_free(pA->gps);
    g_char_free(pA->note);
    g_char_free(pA->id);
    pA->id          = g_strdup(pB->id);
    pA->gps         = g_strdup(pB->gps);
    pA->note        = g_strdup(pB->note);
}

/** *********************************************************************************************** **/

/**
* Author: M-Hieu
* Begin developing for new interface
* I don't known what above code done and I don't have time to read all of them
*/

pSplLcuPopup lcuPopupMenu = NULL;
/**
*Callback functions
*
*
*/

#define append_menu(m, w) gtk_menu_shell_append(GTK_MENU_SHELL(m), GTK_WIDGET(w))
#define add_serparator(m, w) { w = gtk_separator_menu_item_new(); append_menu(m, w);}


static void popup_light_view_init()
{
    GtkWidget *separator_item;

    if(lcuPopupMenu == NULL)
    {
        lcuPopupMenu = g_new0(SplLcuPopup, 1);

        lcuPopupMenu->own = gtk_menu_new();

        lcuPopupMenu->menu_add = gtk_menu_item_new_with_label("Thêm mới");
        append_menu(lcuPopupMenu->own, lcuPopupMenu->menu_add);

        lcuPopupMenu->menu_add_from_file = gtk_menu_item_new_with_label("Thêm mới từ tập tin");
        append_menu(lcuPopupMenu->own, lcuPopupMenu->menu_add_from_file);
        gtk_widget_set_sensitive(lcuPopupMenu->menu_add_from_file, FALSE);

        add_serparator(lcuPopupMenu->own, separator_item);

        lcuPopupMenu->menu_edit = gtk_menu_item_new_with_label("Chỉnh sửa");
        append_menu(lcuPopupMenu->own, lcuPopupMenu->menu_edit);

        add_serparator(lcuPopupMenu->own, separator_item);

        lcuPopupMenu->menu_control = gtk_menu_item_new_with_label("Điều khiển đèn");
        append_menu(lcuPopupMenu->own, lcuPopupMenu->menu_control);

        add_serparator(lcuPopupMenu->own, separator_item);

        lcuPopupMenu->menu_location = gtk_menu_item_new_with_label("Định vị đèn");
        append_menu(lcuPopupMenu->own, lcuPopupMenu->menu_location);

        add_serparator(lcuPopupMenu->own, separator_item);

        lcuPopupMenu->menu_chart = gtk_menu_item_new_with_label("Biểu đồ");
        append_menu(lcuPopupMenu->own, lcuPopupMenu->menu_chart);

        add_serparator(lcuPopupMenu->own, separator_item);

        lcuPopupMenu->menu_remove = gtk_menu_item_new_with_label("Xóa");
        append_menu(lcuPopupMenu->own, lcuPopupMenu->menu_remove);

        lcuPopupMenu->menu_remove_all = gtk_menu_item_new_with_label("Xóa tất cả");
        append_menu(lcuPopupMenu->own, lcuPopupMenu->menu_remove_all);


        //signal

        g_signal_connect(lcuPopupMenu->menu_add, "activate",
                         (GCallback) spl_lcu_popup_menu_clicked, GINT_TO_POINTER(SPL_LCU_M_ADD));
        g_signal_connect(lcuPopupMenu->menu_add_from_file, "activate",
                         (GCallback) spl_lcu_popup_menu_clicked, GINT_TO_POINTER(SPL_LCU_M_ADD_FROM_FILE));
        g_signal_connect(lcuPopupMenu->menu_edit, "activate",
                         (GCallback) spl_lcu_popup_menu_clicked, GINT_TO_POINTER(SPL_LCU_M_EDIT));
        g_signal_connect(lcuPopupMenu->menu_remove, "activate",
                         (GCallback) spl_lcu_popup_menu_clicked, GINT_TO_POINTER(SPL_LCU_M_REMOVE));
        g_signal_connect(lcuPopupMenu->menu_remove_all, "activate",
                         (GCallback) spl_lcu_popup_menu_clicked, GINT_TO_POINTER(SPL_LCU_M_REMOVE_ALL));
        g_signal_connect(lcuPopupMenu->menu_control, "activate",
                         (GCallback) spl_lcu_popup_menu_clicked, GINT_TO_POINTER(SPL_LCU_M_CONTROL));
        g_signal_connect(lcuPopupMenu->menu_location, "activate",
                         (GCallback) spl_lcu_popup_menu_clicked, GINT_TO_POINTER(SPL_LCU_M_LOCATION));
        g_signal_connect(lcuPopupMenu->menu_chart, "activate",
                         (GCallback) spl_lcu_popup_menu_clicked, GINT_TO_POINTER(SPL_LCU_M_CHART));
    }
}

void popup_light_view_show(GdkEventButton *event)
{
    DEBUG_1();

    gtk_widget_show_all(lcuPopupMenu->own);
    gtk_menu_popup(GTK_MENU(lcuPopupMenu->own), NULL, NULL, NULL, NULL,
                   (event != NULL) ? event->button : 0, gdk_event_get_time((GdkEvent*)event));
}
void light_update_information(pSplLcu lcu, gboolean setmapcenter)
{
    g_return_if_fail(lcu);

    DEBUG("UPDATE INFORMATION : %s", lcu->id);

    gchar *str;
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object (smartstreetlight_builder, "lb_lcu_id")), lcu->id);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object (smartstreetlight_builder, "lb_lcd_note")), lcu->note ? lcu->note : "");
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object (smartstreetlight_builder, "lb_lcd_gps")), lcu->gps ?  lcu->gps : "");
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object (smartstreetlight_builder, "lb_lcd_lightname")),
                       lcu->lightname? lcu->lightname : "");
    str = g_strdup_printf("%.2f W", lcu->volt/100);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object (smartstreetlight_builder, "lb_lcd_vol")),
                       str);
    g_free(str);
    str = g_strdup_printf("%.0f", lcu->brightness/10);
    DEBUG(" lcu->brightness: %f; str: %s\n",  lcu->brightness, str);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object (smartstreetlight_builder, "lb_lcd_level")),
                       str);
    g_free(str);
    str = smartstreetlight_lcu_get_status_name(lcu->status);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object (smartstreetlight_builder, "lb_lcd_status")),
                       str);
    g_free(str);
    str = smartstreetlight_lcu_get_mode_name(lcu->mode);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object (smartstreetlight_builder, "lb_lcd_mode")),
                       str);
    g_free(str);
    str = g_strdup_printf("%d W", lcu->power);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object (smartstreetlight_builder, "lb_lcd_power")),
                       str);
    g_free(str);
    str = g_strdup_printf("%d %%", lcu->tolerance);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object (smartstreetlight_builder, "lb_lcd_tolerance")),
                       str);
    g_free(str);
    gtk_switch_set_active(GTK_SWITCH(gtk_builder_get_object (smartstreetlight_builder, "switch_light")), (lcu->isOn == TRUE));
    gtk_widget_set_sensitive(GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "switch_light")), (lcu->status == 0));
    if(lcu->icon)
    {
        const OsmGpsMapPoint *pt = osm_gps_map_image_get_point(lcu->icon);
        if(lcu != lastSelectedLcu)
        {
            osm_gps_map_image_change_image(lcu->icon, spl_get_light_icon(lcu, TRUE, FALSE));

            if(lastSelectedLcu)
            {
                osm_gps_map_image_change_image(lastSelectedLcu->icon,
                                               spl_get_light_icon(lastSelectedLcu, FALSE,
                                               gtk_combo_box_get_active(GTK_COMBO_BOX(cbb_light_display)) != DISPLAY_FOLLOW_DCU
                                               && dcuprev == lastSelectedLcu->parent));
            }
        }
        if(setmapcenter)
            osm_gps_map_set_center(map, rad2deg(pt->rlat), rad2deg(pt->rlon));
    }
    lastSelectedLcu = lcu;
}

gchar* smartstreetlight_lcu_get_mode_name(gint mode)
{
    gchar * msg;
    switch (mode)
    {
        case SPL_LCU_ScheduleMode:
        case SPL_LCU_OffMode:
            msg = g_strdup ("Lập lịch");
            break;
        case SPL_LCU_ManualMode:
            msg = g_strdup ("Điều khiển");
            break;
        default:
            msg = g_strdup ("Chưa thiết lập");
    }
    return msg;
}
static gboolean on_light_view_click_cb(GtkTreeView *treeview, GdkEventButton *event, gpointer userdata)
{

    DEBUG_1();
    GtkTreeIter iter;
    GtkTreeSelection *selection = gtk_tree_view_get_selection(treeview);
    gint select_rows = gtk_tree_selection_count_selected_rows(selection);
    GtkTreeModel *model;
    switch(event->button)
    {
    case GDK_BUTTON_PRIMARY: //left
        if(event->type == GDK_BUTTON_PRESS)
            return FALSE;
        if(select_rows != 1)
            return TRUE;
        DEBUG("Double click\n");
        //if(gtk_tree_selection_get_selected(light_selection, &model, &iter))
        //{
        //    light_update_information_from_model_iter(model, &iter);
        //}
        break;
    case GDK_BUTTON_MIDDLE: //middle
        DEBUG("Middle Button click ...\n");
        break;
    case GDK_BUTTON_SECONDARY: //right
        {
            DEBUG("Right Button click ...\n");
            gboolean popupShow = FALSE;
            /**Select row at where button were clicked on*/
            GtkTreePath *path;
            if (gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(treeview), (gint) event->x, (gint) event->y, &path, NULL, NULL, NULL))
            {
                gtk_tree_selection_unselect_all(selection);
                gtk_tree_selection_select_path(selection, path);
                gtk_tree_path_free(path);
                popupShow = TRUE;
            }
            /**Show popup menu for light view*/
            gtk_widget_set_sensitive(lcuPopupMenu->menu_add_from_file, FALSE);
            gtk_widget_set_sensitive(lcuPopupMenu->menu_remove_all, treeview == main_view_widgets->lcu_view);
            gtk_widget_set_sensitive(lcuPopupMenu->menu_remove, popupShow);
            gtk_widget_set_sensitive(lcuPopupMenu->menu_control, popupShow);
            gtk_widget_set_sensitive(lcuPopupMenu->menu_edit, popupShow);
            gtk_widget_set_sensitive(lcuPopupMenu->menu_location, popupShow);
            gtk_widget_set_sensitive(lcuPopupMenu->menu_remove_all, popupShow);
            popup_light_view_show(event);
        }
        break;
    default:
        DEBUG("Wrong button click\n");
        break;
    }
    return TRUE;
}

void on_lcu_selection_changed (GtkTreeSelection *selection, gpointer user_data)
{
    GtkTreeModel *model;
    GtkTreeIter iter;
    if(isLogining)
        return;
    if(gtk_tree_selection_get_selected(selection, &model, &iter))
    {
        pSplLcu lcu;
        gint type;
        gtk_tree_model_get(model, &iter, 1, &lcu, -1 );

        light_update_information(lcu, TRUE);
    }
}


/**
* End callback functions
*/

static void tree_view_init_with_model(GtkTreeView *view, GtkTreeModel *model)
{
    GtkTreeViewColumn   *column;
    GtkCellRenderer     *renderer;
    GtkTreeSelection    *selection;
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("", renderer, "text", LIGHT_ID, NULL);
    gtk_tree_view_append_column(view, column);
    gtk_tree_view_set_model(view, model);
    selection = gtk_tree_view_get_selection(view);
    gtk_tree_selection_set_mode(selection, GTK_SELECTION_SINGLE);
    g_signal_connect(GTK_TREE_VIEW(view),
                     "button-press-event",
                     G_CALLBACK(on_light_view_click_cb), NULL);
    g_signal_connect(selection,
                     "changed",
                     G_CALLBACK(on_lcu_selection_changed), NULL);
}

static gboolean
row_visible (GtkTreeModel *model,
             GtkTreeIter *iter,
             gpointer p)
{
    gboolean visible;
    gtk_tree_model_get (model, iter, LIGHT_VISIBLE, &visible, -1);
    //DEBUG("visible: %d\n", visible);
    return visible;
}

static void smartstreetlight_view_init()
{
    GtkTreeViewColumn   *column;
    GtkCellRenderer     *renderer;
    gboolean isInitView = FALSE;
    if(!isInitView)
    {
        DEBUG("Init ...\n");
        main_view_widgets->lcu_view
            = GTK_TREE_VIEW(gtk_builder_get_object (smartstreetlight_builder, "light_info_tree_view"));
        main_view_widgets->lcu_all_view
            = GTK_TREE_VIEW(gtk_builder_get_object (smartstreetlight_builder, "light_hidden_info_tree_view"));
        main_view_widgets->lcu_store = gtk_tree_store_new(LIGHT_COUNT, G_TYPE_STRING, G_TYPE_POINTER, G_TYPE_BOOLEAN);
        main_view_widgets->lcu_all_store = gtk_tree_store_new(LIGHT_COUNT, G_TYPE_STRING, G_TYPE_POINTER, G_TYPE_BOOLEAN);

        main_view_widgets->lcu_all_filter = GTK_TREE_MODEL_FILTER(gtk_tree_model_filter_new(
                                                GTK_TREE_MODEL(main_view_widgets->lcu_all_store), NULL));
        gtk_tree_model_filter_set_visible_func(main_view_widgets->lcu_all_filter,
                                               (GtkTreeModelFilterVisibleFunc) row_visible,
                                               NULL, NULL);

        tree_view_init_with_model(main_view_widgets->lcu_view, GTK_TREE_MODEL(main_view_widgets->lcu_store));
        tree_view_init_with_model(main_view_widgets->lcu_all_view, GTK_TREE_MODEL(main_view_widgets->lcu_all_filter));

        isInitView = TRUE;
    }
    popup_light_view_init();
}


void smartstreetlight_get_all_light()
{
    GtkTreeView *view = GTK_TREE_VIEW(gtk_builder_get_object (smartstreetlight_builder, "dcu_info_tree_view"));
    GtkTreeModel *model = gtk_tree_view_get_model(view);
    GtkTreeIter diter;
    GtkTreeIter iter;
    GSList *item;
    smartstreetlight_tree_store_clean(SPL_LCU_ALL_STORE);
    smartstreetlight_tree_store_clean(SPL_LCU_STORE);
    if(showAllLightEnable)
    {
        LIST_DCU_FOR_EACH_ENTRY(item)
        {
            pSplDcu dcu = (pSplDcu)item->data;
            if(!dcu || !dcu->priv || !dcu->priv->id)
                continue;
            gtk_tree_store_append(main_view_widgets->lcu_all_store, &dcu->controlIter, NULL);
            gtk_tree_store_set(main_view_widgets->lcu_all_store, &dcu->controlIter,
                               LIGHT_ID, dcu->priv->id,
                               LIGHT_POINTER, NULL,
                               LIGHT_VISIBLE, FALSE, -1);
            create_new_light_instances(dcu);
        }
        gtk_widget_set_sensitive(GTK_WIDGET(cbb_light_display), TRUE);
    }
    else
    {
        gtk_widget_set_sensitive(GTK_WIDGET(cbb_light_display), TRUE);
    }
    gtk_combo_box_set_active(GTK_COMBO_BOX(cbb_light_display), DISPLAY_FOLLOW_DCU);
    gtk_tree_model_filter_refilter(main_view_widgets->lcu_all_filter);
}

void spl_lcu_free(pSplLcu lcu)
{
    if(lcu)
    {
        g_char_free(lcu->gps);
        g_char_free(lcu->id);
        g_char_free(lcu->note);
        g_char_free(lcu->lightname);
        if(lcu->icon)
            osm_gps_map_image_remove(map, lcu->icon);
        g_free(lcu);
    }
}

pSplLcu spl_lcu_init()
{
    pSplLcu lcu = g_new0(SplLcu, 1);
    lcu->gps = NULL;
    lcu->id = NULL;
    lcu->note = NULL;
    lcu->icon = NULL;
    lcu->parent = NULL;
    lcu->lightname = NULL;
    return lcu;
}

/*
typedef struct _SplLcuLog
{
    gchar           *id;
    gchar           *lcuId;
    gdouble         power_consum; // cong suat tieu thu 10mW -> bieu do
    gdouble         power_ctrl; // cong suat dieu khien 10mW -> bieu do
    gdouble         power; // cong suat den 10mW
    gint            tolerance;
    gchar*          date_time; // time
    gchar*          lightname;
    gint            status;
    gint            mode;
    }
    SplLcuLog, *pSplLcuLog;
*/

pSplLcuLog spl_lcu_log_init()
{
    pSplLcuLog lcu_log = g_new0(SplLcuLog, 1);
    lcu_log->lcuId = NULL;
    lcu_log->date_time = NULL;
    lcu_log->lightname = NULL;
    return lcu_log;
}

void spl_lcu_log_free(pSplLcuLog lcu_log)
{
    g_return_if_fail(lcu_log);
    g_free(lcu_log->lcuId);
    g_free(lcu_log->date_time);
    g_free(lcu_log->lightname);
    g_free(lcu_log);
}

void smartstreetlight_lcu_finalize(void)
{
    /*
    if(main_view_widgets->lcu_all_store)
        gtk_widget_destroy(GTK_WIDGET(main_view_widgets->lcu_all_store));
    if(main_view_widgets->lcu_all_view)
        gtk_widget_destroy(GTK_WIDGET(main_view_widgets->lcu_all_view));
    if(main_view_widgets->lcu_store)
        gtk_widget_destroy(GTK_WIDGET(main_view_widgets->lcu_store));
    if(main_view_widgets->lcu_view)
        gtk_widget_destroy(GTK_WIDGET(main_view_widgets->lcu_view));
    */
}


gboolean smartstreetlight_lcu_info_init(void)
{
    smartstreetlight_view_init();
    if(cbb_light_display == NULL)
    {
        cbb_light_display = GTK_COMBO_BOX(gtk_builder_get_object (smartstreetlight_builder, "cbb_light_display"));

        //signal
        DEBUG("combobox signal init\n");
        g_signal_connect(gtk_builder_get_object (smartstreetlight_builder, "cbb_light_display"), "changed",
                         G_CALLBACK (on_combo_box_display_changed), (gpointer) NULL);
        gtk_combo_box_set_active(GTK_COMBO_BOX(cbb_light_display), DISPLAY_FOLLOW_DCU);
    }

    g_signal_connect(GTK_WIDGET(SPL_OBJECT("switch_light")), "button-press-event", G_CALLBACK(on_light_switch_light_button_press), NULL);

    return TRUE;
}


gchar * smartstreetlight_lcu_get_status_name(gint status)
{
    gboolean is_err= FALSE;
    gchar * msg = (gchar *)"";
    if (status & ERROR_RF_LCU_STATUS){
        is_err= TRUE;
        msg = g_strconcat(msg, "Lỗi RF,",NULL);

    }

    if (status & ERROR_LIGHT_STATUS){
        is_err= TRUE;
        msg = g_strconcat(msg, "Lỗi điều khiển đèn,", NULL);
    }
    if (status & ERROR_CLOCK_LCU_STATUS){
        is_err= TRUE;
        msg = g_strconcat(msg, "Lỗi hư thời gian thực,", NULL);
    }
    if (status & ERROR_CURRENT_STATUS){
        is_err= TRUE;
        msg = g_strconcat(msg, "Lỗi quá tải,", NULL);
    }

    if (is_err == FALSE)
    {
        msg = g_strdup ("Đang hoạt động");
    }
    return msg;
}

void spl_lcu_add_image(pSplLcu lcu, GdkPixbuf *buf, gfloat *lat, gfloat *lon)
{
    if(lcu != NULL)
    {
        gchar delimiter;
        DEBUG("Gps: %s", lcu->gps);
        if(sscanf(lcu->gps, "%f-%f", lat,  lon) != 2)
        {
#ifdef SET_LOCATION_ROOT
            ROOT_GPS(*lat, *lon);
#else
            HOME_GPS(*lat, *lon);
#endif
        }
        //DEBUG("Show lights\n");
        lcu->lat = *lat;
        lcu->lon = *lon;
        //OsmGpsMapImage *image = osm_gps_map_image_add(map, *lat, *lon, buf);
        OsmGpsMapImage *image = osm_gps_map_image_add_with_alignment_z(map, *lat, *lon, buf,0,0,0);
        image->handler = (gpointer)lcu;
        lcu->icon   = image;
    }
}

//lcu is selected
#define OFFSET_C        3
//lcu's parent is selected
#define OFFSET_P        6

GdkPixbuf *spl_get_light_icon(pSplLcu lcu, gboolean selected, gboolean parentSelected)
{
    g_return_val_if_fail(lcu,  NULL);
    GdkPixbuf *ret;
    gint status = ICON_LIGHT_OFF;

    if(lcu->status & (ERROR_RF_LCU_STATUS | ERROR_LIGHT_STATUS| ERROR_CLOCK_LCU_STATUS | ERROR_CURRENT_STATUS | DELETE_STATUS))
        status = ICON_LIGHT_BROKEN;
    else if(lcu->isOn)
        status = ICON_LIGHT_ON;
    if(selected)
        status += OFFSET_C;
    else if(parentSelected)
        status += OFFSET_P;
    ret = light_image[status];
    return ret;
}

static gboolean smartstreetlight_lcu_add_soap_receive_process(pSplLcu lcu)
{
    GtkTreeIter     iter;
    GtkTreeIter     *parent = NULL;
    GtkTreeStore    *store;
    GtkTreeSelection *selection;


    if(gtk_combo_box_get_active(GTK_COMBO_BOX(cbb_light_display)) == DISPLAY_FOLLOW_DCU)
    {
        store = main_view_widgets->lcu_store;
        selection = gtk_tree_view_get_selection(main_view_widgets->lcu_view);
    }
    else
    {
        store = main_view_widgets->lcu_all_store;
        parent = &lcu->parent->controlIter;
        selection = gtk_tree_view_get_selection(main_view_widgets->lcu_all_view);
    }

    gtk_tree_store_append(store, &iter, parent);
    gtk_tree_store_set(store, &iter, LIGHT_ID, lcu->id, LIGHT_POINTER, lcu, -1);
    gtk_tree_selection_select_iter(selection, &iter);

    PREPEND_LIST_LCU(lcu->parent, lcu);
}

static void smartstreetlight_lcu_add_soap_execute(gpointer args)
{
    SoapResponse *soap_response = (SoapResponse *)args;
    pSplLcu lcu = (pSplLcu)soap_response->data;
    soap_response->result_value =  smartstreetlight_add_lcu_execute(&soap_thread.spl_soap, lcu);
}

static void* smartstreetlight_lcu_add_soap_receive(gpointer data)
{
    DEBUG_1();
    SoapResponse *soap_response = (SoapResponse *)data;
    pSplLcu lcu = (pSplLcu)soap_response->data;
    if(soap_response->result_value == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
    {
        // not free for lcu data //
        smartstreetlight_lcu_add_soap_receive_process((pSplLcu)soap_response->data);
    }
    else
    {
        gchar *msg = g_strdup_printf("Lỗi thêm đèn '%s' vào trạm '%s'.", lcu->id, lcu->parent->priv->id);
        GtkWidget *parent = stack_widget_active_top();
        smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_response->result_value);
        spl_lcu_free((pSplLcu)soap_response->data);
        g_free(msg);
    }
    g_free(soap_response);
    return NULL;
}
gboolean spl_light_add_new_request()
{
    gboolean ret = FALSE;
    GtkWidget *add_lcu_entry_id = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "add_lcu_entry_id"));
    GtkWidget *add_lcu_entry_gps = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "add_lcu_entry_gps"));
    GtkWidget *add_lcu_entry_note = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "add_lcu_entry_note"));
    GtkWidget *add_lcu_entry_lightname = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "add_lcu_entry_lightname"));
    GtkWidget *add_lcu_entry_power = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "add_lcu_entry_power"));
    GtkWidget *add_lcu_entry_tolerance = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "add_lcu_entry_tolerance"));
    GtkWidget *add_lcu_combobox_dcu = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "add_lcu_combobox_dcu"));
    GtkWidget *add_lcu_label_error = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "add_lcu_label_error"));
    GtkWidget *lb_name = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "lb_dialog_lcu_name"));
    GtkWidget *btn_add = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "lcu_add_ok"));
    gtk_label_set_text(GTK_LABEL(lb_name), "Khai báo đèn mới");
    static GtkTreeStore *dcuStore = NULL;
    // static GtkTextBuffer *buff;
    if(dcuStore == NULL)
    {
        dcuStore = gtk_tree_store_new(2, G_TYPE_STRING, G_TYPE_POINTER);
        gtk_combo_box_set_model(GTK_COMBO_BOX(add_lcu_combobox_dcu), GTK_TREE_MODEL(dcuStore));
        //buff = gtk_text_buffer_new()
    }
    gtk_widget_set_sensitive(btn_add, TRUE);
    if(IS_EMPTY_LIST_DCU)
    {
        gtk_label_set_text(GTK_LABEL(add_lcu_label_error), "Không có trạm nào đang tồn tại");
        gtk_widget_set_sensitive(btn_add, FALSE);
    }
    else
    {
        gtk_tree_store_clear(dcuStore);
        GSList *item;
        LIST_DCU_FOR_EACH_ENTRY(item)
        {
            GtkTreeIter iter;
            pSplDcu dcu = (pSplDcu)item->data;
            if(dcu)
            {
                gtk_tree_store_append(dcuStore, &iter, NULL);
                gtk_tree_store_set(dcuStore, &iter, 0, dcu->priv->id, 1, dcu, -1);
                // set default dcu that will be father of the new light
                // the first condition is the last selected lcu, after that we just choose last selected dcu
                if((lastSelectedLcu && lastSelectedLcu->parent && lastSelectedLcu->parent == dcu)
                   || (lastSelectedDcu && lastSelectedDcu == dcu))
                {
                    gtk_combo_box_set_active_iter(GTK_COMBO_BOX(add_lcu_combobox_dcu), &iter);
                }

            }
        }
    }

    SPL_DIALOG_SHOW(main_widgets->add_lcu_dialog);
    gint response_id;
    while(response_id = gtk_dialog_run(GTK_DIALOG(main_widgets->add_lcu_dialog)))
    {
        switch(response_id)
        {
        case GTK_RESPONSE_ACCEPT:
            DEBUG("\n accept click\n");
            {
                gchar *lcuId = (gchar *)gtk_entry_get_text(GTK_ENTRY(add_lcu_entry_id));
                gchar tmp[100];
                if(strlen(lcuId) != 10)
                    gtk_label_set_text(GTK_LABEL(add_lcu_label_error), "Mã đèn không được để trống hoặc không đủ 10 kí tự");
                else if(sscanf(lcuId, "%[0-9a-zA-Z_]", &tmp) != 1 ||
                        strlen(tmp) != 10 || (tmp[0] >= '0' && tmp[0] <= '9'))
                    gtk_label_set_text(GTK_LABEL(add_lcu_label_error), "Mã đèn theo chỉ sử dụng các kí tự [A-Za-z0-9_] và không được bắt đầu bằng số");
                else
                {
                    gtk_label_set_text(GTK_LABEL(add_lcu_label_error), "");
                    //All things are ok
                    pSplDcu dcu     = GET_DCU_FROM_LIST_DCU(gtk_combo_box_get_active(GTK_COMBO_BOX(add_lcu_combobox_dcu)));
                    pSplLcu lcu     = spl_lcu_init();
                    SplSoap spl_soap;
                    lcu->gps        = g_strdup(gtk_entry_get_text(GTK_ENTRY(add_lcu_entry_gps)));
                    lcu->id         = g_strdup(gtk_entry_get_text(GTK_ENTRY(add_lcu_entry_id)));
                    lcu->note       = g_strdup(gtk_entry_get_text(GTK_ENTRY(add_lcu_entry_note)));
                    lcu->lightname  = g_strdup(gtk_entry_get_text(GTK_ENTRY(add_lcu_entry_lightname)));
                    lcu->power      = (gint )g_ascii_strtoll (gtk_entry_get_text(GTK_ENTRY(add_lcu_entry_power)),
                                                              NULL,
                                                              10);
                    lcu->tolerance  = (gint )g_ascii_strtoll (gtk_entry_get_text(GTK_ENTRY(add_lcu_entry_tolerance)),
                                                              NULL,
                                                              10);
                    lcu->icon       = NULL;
                    lcu->brightness = 0;
                    lcu->isBroken   = FALSE;
                    lcu->isOn       = FALSE;
                    lcu->mode       = 0;
                    lcu->parent     = dcu;
                    lcu->status     = 0;
                    lcu->volt       = 0;

                    if(soap_thread.init_thread(lcu, smartstreetlight_lcu_add_soap_execute,
                                                    smartstreetlight_lcu_add_soap_receive ) == FALSE)
                    {
                        gchar * str_error = g_strdup("Không thể tạo thread xử lý cho thao tác thêm mới LCU.");
                        DEBUG ("Internal error: %s", str_error);
                        GtkWidget *parent = stack_widget_active_top();
                        smartstreetlight_error_check_message_result(GTK_WIDGET(parent), str_error, ns1__MESSAGE_USCORERESULT_USCOREEnum__INTERNAL_USCOREERR);
                        g_free(str_error);
                        ret = FALSE;
                    }
                    goto ___exit;
                }
            }
            break;
        case GTK_RESPONSE_CLOSE:
        case GTK_RESPONSE_CANCEL:
        case GTK_RESPONSE_DELETE_EVENT:
            ret = TRUE;
            goto ___exit;
        }
    }
___exit:

    SPL_DIALOG_HIDE(main_widgets->add_lcu_dialog);

    gtk_entry_set_text(GTK_ENTRY(add_lcu_entry_id), "");
    gtk_entry_set_text(GTK_ENTRY(add_lcu_entry_gps), "");
    gtk_entry_set_text(GTK_ENTRY(add_lcu_entry_note), "");
    gtk_label_set_text(GTK_LABEL(add_lcu_label_error), "");

    return ret;
}

static void on_chart_remember_active (GtkToggleButton *togglebutton, gpointer user_data)
{
    spl_object->chart->isSave = gtk_toggle_button_get_active(togglebutton);
}

#define STR_DATETIME_FORMAT "%04d:%02d:%02d %02d:%02d:%02d"
#define EPOCH 1900

static gboolean on_time_btn_click(GtkButton *button, gpointer userdata)
{
    gchar *strTime = (gchar *)gtk_button_get_label(button);
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    if(sscanf(strTime, STR_DATETIME_FORMAT,
              &tm->tm_year,
              &tm->tm_mon,
              &tm->tm_mday,
              &tm->tm_hour,
              &tm->tm_min,
              &tm->tm_sec) == 6)
    {
        tm->tm_mon -= 1;
        GtkCalendar *calendar = GTK_CALENDAR(SPL_OBJECT("calendar_select"));
        GtkWidget *dlg = GTK_WIDGET(SPL_OBJECT("dialog_date_n_time"));
        if(calendar)
        {
            gtk_calendar_select_day(calendar, (guint)tm->tm_mday);
            gtk_calendar_select_month(calendar, (guint)tm->tm_mon, (guint)tm->tm_year);
            gtk_spin_button_set_value(GTK_SPIN_BUTTON(SPL_OBJECT("spinbutton_hour")), (gdouble)tm->tm_hour);
            gtk_spin_button_set_value(GTK_SPIN_BUTTON(SPL_OBJECT("spinbutton_minute")), (gdouble)tm->tm_min);
            gtk_spin_button_set_value(GTK_SPIN_BUTTON(SPL_OBJECT("spinbutton_second")), (gdouble)tm->tm_sec);
        }

        SPL_DIALOG_SHOW(dlg);
        gtk_widget_show_all(dlg);
___LOOP1:
        if(gtk_dialog_run(GTK_DIALOG(dlg)))
        {
            gtk_calendar_get_date(calendar, (guint*)&tm->tm_year, (guint*)&tm->tm_mon, (guint*)&tm->tm_mday);
            tm->tm_hour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(SPL_OBJECT("spinbutton_hour")));
            tm->tm_min  = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(SPL_OBJECT("spinbutton_minute")));
            tm->tm_sec  = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(SPL_OBJECT("spinbutton_second")));
            time_t now = time(NULL);
            tm->tm_year -= EPOCH;
            if(now < mktime(tm))
            {
                GtkWidget *parent = stack_widget_active_top();
                SPL_ERROR_POPUP(parent, "Thời gian không được lớn hơn thời gian hện tại!");
                goto ___LOOP1;
            }
        }
        SPL_DIALOG_HIDE(dlg);
        gtk_widget_hide_on_delete(dlg);
        strTime = g_strdup_printf(STR_DATETIME_FORMAT,
                                  tm->tm_year + EPOCH,
                                  tm->tm_mon + 1,
                                  tm->tm_mday,
                                  tm->tm_hour,
                                  tm->tm_min,
                                  tm->tm_sec);
        gtk_button_set_label(button, (const gchar*)strTime);
        if(!GPOINTER_TO_INT(userdata))
        {
            spl_object->chart->startTime = strTime;
        }
        else
        {
            spl_object->chart->endTime = strTime;
        }

    }
    return FALSE;
}

#define TIME_FORM_HERE 7 * 24 * 60 * 60

gboolean spl_light_chart_show(pSplLcu lcu)
{
    static gboolean isInitChart = FALSE;
    g_return_if_fail(lcu);
    if(!isInitChart)
    {
        g_signal_connect(SPL_OBJECT("autoload_time"), "toggled", G_CALLBACK(on_chart_remember_active), NULL);
        g_signal_connect(SPL_OBJECT("slope_btn_start_time"), "clicked", G_CALLBACK(on_time_btn_click), GINT_TO_POINTER(0));
        g_signal_connect(SPL_OBJECT("slope_btn_end_time"), "clicked", G_CALLBACK(on_time_btn_click), GINT_TO_POINTER(1));
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(SPL_OBJECT("autoload_time")), spl_object->chart->isSave);
        isInitChart = TRUE;
    }
    if(spl_object->chart->isSave)
    {
        gtk_button_set_label(GTK_BUTTON(SPL_OBJECT("slope_btn_start_time")), spl_object->chart->startTime);
        gtk_button_set_label(GTK_BUTTON(SPL_OBJECT("slope_btn_end_time")), spl_object->chart->endTime);
    }
    else
    {
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        gtk_button_set_label(GTK_BUTTON(SPL_OBJECT("slope_btn_end_time")), g_strdup_printf(STR_DATETIME_FORMAT,
                                  tm->tm_year + EPOCH,
                                  tm->tm_mon + 1,
                                  tm->tm_mday,
                                  tm->tm_hour,
                                  tm->tm_min,
                                  tm->tm_sec));
        t -= TIME_FORM_HERE;
        tm = localtime(&t);
        gtk_button_set_label(GTK_BUTTON(SPL_OBJECT("slope_btn_start_time")), g_strdup_printf(STR_DATETIME_FORMAT,
                                  tm->tm_year + EPOCH,
                                  tm->tm_mon + 1,
                                  tm->tm_mday,
                                  tm->tm_hour,
                                  tm->tm_min,
                                  tm->tm_sec));
    }

    gint response_id;
    SPL_DIALOG_SHOW(main_widgets->lcu_slope_datetime_dialog);
___LOOP:
    response_id = gtk_dialog_run(GTK_DIALOG(main_widgets->lcu_slope_datetime_dialog));
    switch(response_id)
    {
        case GTK_RESPONSE_OK:
        {
            gchar *startTime    = (gchar*) gtk_button_get_label(GTK_BUTTON(SPL_OBJECT("slope_btn_start_time")));
            gchar *endTime      = (gchar*) gtk_button_get_label(GTK_BUTTON(SPL_OBJECT("slope_btn_end_time")));
            struct tm _start, _end;
            if(sscanf(startTime, STR_DATETIME_FORMAT, &_start.tm_year,&_start.tm_mon, &_start.tm_mday,
                      &_start.tm_hour, &_start.tm_min,&_start.tm_sec) == 6
               &&
               sscanf(endTime, STR_DATETIME_FORMAT, &_end.tm_year,&_end.tm_mon, &_end.tm_mday,
                      &_end.tm_hour, &_end.tm_min,&_end.tm_sec) == 6
               )

            {
                _start.tm_year -= EPOCH;
                _start.tm_mon -=1;
                _end.tm_year -= EPOCH;
                _end.tm_mon -=1;
                DEBUG("startTime: %s(%ld),endTime: %s(%ld)",startTime,mktime(&_start), endTime,mktime(&_end));
                if(mktime(&_end) <= mktime(&_start))
                {
                    GtkWidget *parent = stack_widget_active_top();
                    SPL_ERROR_POPUP(parent, "Thời gian kết thúc lớn hơn thời gian bắt đầu!");
                    goto ___LOOP;
                }
                SPL_DIALOG_HIDE(main_widgets->lcu_slope_datetime_dialog);
                spl_light_chart_show_execute(lcu, startTime, endTime);
            }
        }
            break;
        default:
        case GTK_RESPONSE_CANCEL:
        {
            SPL_DIALOG_HIDE(main_widgets->lcu_slope_datetime_dialog);
        }
            break;
    }
}

static void spl_light_chart_show_execute(pSplLcu lcu, gchar *time_from, gchar *time_to)
{

#ifdef WIN32
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );
    TCHAR * cmd = g_strdup_printf("%s\\bin\\splchart -a \"%s\" -d %d -u \"%s\" -l \"%s\" -b \"%s\" -e \"%s\"",
                                                g_win32_get_package_installation_directory_of_module(NULL),
                                                smartstreetlight_username,
                                                smartstreetlight_session_id,
                                                smartstreetlight_server_url,
                                                lcu->id,
                                                time_from,
                                                time_to);
    DEBUG("cmd: %s", cmd);
    BOOL fSuccess = CreateProcess(NULL,
                        cmd,     // command line
                        NULL,          // process security attributes
                      NULL,          // primary thread security attributes
                      FALSE,          // handles are inherited
                      0,             // creation flags
                      NULL,          // use parent's environment
                      NULL,          // use parent's current directory
                      &si,            // Pointer to STARTUPINFO structure
                      &pi);  // receives PROCESS_INFORMATION
	if (! fSuccess)
	{
		DEBUG("win32_spawn: Create process failed");
	}
#else
    gchar * cmd = g_strdup_printf("splchart -a \"%s\" -d %d -u \"%s\" -l \"%s\" -b \"%s\" -e \"%s\"",
                                                smartstreetlight_username,
                                                smartstreetlight_session_id,
                                                smartstreetlight_server_url,
                                                lcu->id,
                                                time_from,
                                                time_to);
    DEBUG("cmd: %s", cmd);
    g_spawn_command_line_async	(	cmd,NULL);
#endif
}


gboolean spl_light_edit(pSplLcu lcu)
{
    gboolean ret = FALSE;
    gchar * str;
    GtkWidget *add_lcu_entry_id = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "add_lcu_entry_id"));
    GtkWidget *add_lcu_entry_lightname = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "add_lcu_entry_lightname"));
    GtkWidget *add_lcu_entry_gps = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "add_lcu_entry_gps"));
    GtkWidget *add_lcu_entry_note = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "add_lcu_entry_note"));
    GtkWidget *add_lcu_entry_power = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "add_lcu_entry_power"));
    GtkWidget *add_lcu_entry_tolerance = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "add_lcu_entry_tolerance"));
    GtkWidget *add_lcu_combobox_dcu = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "add_lcu_combobox_dcu"));
    GtkWidget *add_lcu_label_error = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "add_lcu_label_error"));
    GtkWidget *lb_name = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "lb_dialog_lcu_name"));
    GtkWidget *btn_add = GTK_WIDGET(gtk_builder_get_object (smartstreetlight_builder, "lcu_add_ok"));
    gtk_label_set_text(GTK_LABEL(lb_name), "Chỉnh sửa thông tin đèn");
    g_return_if_fail(lcu);
    static GtkTreeStore *dcuStore = NULL;
    if(dcuStore == NULL)
    {
        dcuStore = gtk_tree_store_new(2, G_TYPE_STRING, G_TYPE_POINTER);
    }
    gtk_widget_set_sensitive(btn_add, TRUE);
    if(IS_EMPTY_LIST_DCU)
    {
        gtk_label_set_text(GTK_LABEL(add_lcu_label_error), "Không có trạm nào đang tồn tại");
        gtk_widget_set_sensitive(btn_add, FALSE);
    }
    else
    {
        gtk_combo_box_set_model(GTK_COMBO_BOX(add_lcu_combobox_dcu), GTK_TREE_MODEL(dcuStore));
        gtk_tree_store_clear(dcuStore);
        GSList *item;
        LIST_DCU_FOR_EACH_ENTRY(item)
        {
            GtkTreeIter iter;
            pSplDcu dcu = (pSplDcu)item->data;
            if(dcu)
            {
                gtk_tree_store_append(dcuStore, &iter, NULL);
                gtk_tree_store_set(dcuStore, &iter, 0, dcu->priv->id, 1, dcu, -1);
                if(lastSelectedLcu && lastSelectedLcu->parent && lastSelectedLcu->parent == dcu)
                {
                    gtk_combo_box_set_active_iter(GTK_COMBO_BOX(add_lcu_combobox_dcu), &iter);
                }
            }
            gtk_widget_set_sensitive(GTK_WIDGET(add_lcu_combobox_dcu), FALSE);
        }
    }
    gtk_entry_set_text(GTK_ENTRY(add_lcu_entry_id), lcu->id);
    gtk_entry_set_text(GTK_ENTRY(add_lcu_entry_lightname), lcu->lightname);
    gtk_entry_set_text(GTK_ENTRY(add_lcu_entry_gps), lcu->gps);
    gtk_entry_set_text(GTK_ENTRY(add_lcu_entry_note), lcu->note);
    str = g_strdup_printf("%d", lcu->power);
    gtk_entry_set_text(GTK_ENTRY(add_lcu_entry_power), str);
    g_char_free(str);
    str = g_strdup_printf("%d", lcu->tolerance);
    gtk_entry_set_text(GTK_ENTRY(add_lcu_entry_tolerance), str);
    g_char_free(str);
    gtk_widget_set_sensitive(add_lcu_entry_id, FALSE);


    SPL_DIALOG_SHOW(main_widgets->add_lcu_dialog);
    gint response_id;
    while(response_id = gtk_dialog_run((GtkDialog *)main_widgets->add_lcu_dialog))
    {
        switch(response_id)
        {
        case GTK_RESPONSE_ACCEPT:
            DEBUG("accept click\n");
            {
                //All things are ok
                DEBUG("gtk_combo_box_get_active: %d", gtk_combo_box_get_active(GTK_COMBO_BOX(add_lcu_combobox_dcu)));
                pSplDcu dcu     = GET_DCU_FROM_LIST_DCU(gtk_combo_box_get_active(GTK_COMBO_BOX(add_lcu_combobox_dcu)));
                pSplLcu lcuEdit = spl_lcu_init();
                SplSoap spl_soap;
                copy_light(lcuEdit, lcu);
                g_char_free(lcuEdit->gps);
                g_char_free(lcuEdit->note);
                g_char_free(lcuEdit->lightname);
                lcuEdit->gps        = g_strdup(gtk_entry_get_text(GTK_ENTRY(add_lcu_entry_gps)));
                lcuEdit->note       = g_strdup(gtk_entry_get_text(GTK_ENTRY(add_lcu_entry_note)));
                lcuEdit->lightname  = g_strdup(gtk_entry_get_text(GTK_ENTRY(add_lcu_entry_lightname)));
                lcuEdit->power      = (gint )g_ascii_strtoll (gtk_entry_get_text(GTK_ENTRY(add_lcu_entry_power)),
                                                              NULL,
                                                              10);
                lcuEdit->tolerance  = (gint )g_ascii_strtoll (gtk_entry_get_text(GTK_ENTRY(add_lcu_entry_tolerance)),
                                                              NULL,
                                                              10);
                // add code edit to here
                DEBUG("lcuEdit->gps: '%s', lcuEdit->note: '%s'\n", lcuEdit->gps,lcuEdit->note);
                gint soap_err = smartstreetlight_edit_lcu_execute(&spl_soap,lcuEdit);
                if (soap_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
                {

                    g_char_free(lcu->gps);
                    g_char_free(lcu->note);
                    g_char_free(lcu->lightname);
                    lcu->gps        = g_strdup(gtk_entry_get_text(GTK_ENTRY(add_lcu_entry_gps)));
                    lcu->note       = g_strdup(gtk_entry_get_text(GTK_ENTRY(add_lcu_entry_note)));
                    lcu->lightname  = g_strdup(gtk_entry_get_text(GTK_ENTRY(add_lcu_entry_lightname)));
                    lcu->power      = (gint )g_ascii_strtoll (gtk_entry_get_text(GTK_ENTRY(add_lcu_entry_power)),
                                                              NULL,
                                                              10);
                    lcu->tolerance  = (gint )g_ascii_strtoll (gtk_entry_get_text(GTK_ENTRY(add_lcu_entry_tolerance)),
                                                              NULL,
                                                              10);
                    light_update_information(lcu,TRUE);
                    ret = TRUE;
                } else {
                    gchar * msg = g_strdup_printf("Lỗi lấy danh sách trạm %s từ server. ", lcu->parent->priv->id);
                    GtkWidget *parent = stack_widget_active_top();
                    smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
                    g_char_free(msg);
                }
                spl_lcu_free(lcuEdit);
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
    SPL_DIALOG_HIDE(main_widgets->add_lcu_dialog);

    gtk_entry_set_text(GTK_ENTRY(add_lcu_entry_id), "");
    gtk_widget_set_sensitive(add_lcu_entry_id, TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(add_lcu_combobox_dcu), TRUE);
    gtk_entry_set_text(GTK_ENTRY(add_lcu_entry_gps), "");
    gtk_entry_set_text(GTK_ENTRY(add_lcu_entry_note), "");
    gtk_label_set_text(GTK_LABEL(add_lcu_label_error), "");

    return ret;
}

static void on_light_mode_changed (GtkComboBox *widget, gpointer user_data)
{
    GtkWidget *manual_frame = GTK_WIDGET(SPL_OBJECT("lcu_control_manual_mode_frame"));
    GtkWidget *schedule_frame = GTK_WIDGET(SPL_OBJECT("lcu_control_schedule_mode_frame"));

    gint lcu_mode = gtk_combo_box_get_active(widget)+1;

    switch(lcu_mode)
    {
    case SPL_LCU_ScheduleMode:
        gtk_widget_set_sensitive(manual_frame, FALSE);
        gtk_widget_set_sensitive(schedule_frame, TRUE);
        break;
    case SPL_LCU_ManualMode:
        gtk_widget_set_sensitive(manual_frame, TRUE);
        gtk_widget_set_sensitive(schedule_frame, FALSE);
        break;
//    case SPL_LCU_OffMode:
//        gtk_widget_set_sensitive(manual_frame, FALSE);
//        gtk_widget_set_sensitive(schedule_frame, FALSE);
//        break;
    }
}
static gboolean on_switch_button_press(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
    DEBUG_1();
    gboolean is_active = gtk_switch_get_active(GTK_SWITCH(widget));
    gtk_widget_set_sensitive(GTK_WIDGET(SPL_OBJECT("lcu_control_scale_level")), !is_active);
    return FALSE;
}

static gboolean on_light_switch_light_button_press(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
    return TRUE;
}
static void smartstreetlight_control_lcu_soap_execute(gpointer args)
{
    SoapResponse *soap_response = (SoapResponse *)args;
    struct CtrlLcuThread* ctrl_lcu = (struct CtrlLcuThread *)soap_response->data;
    GString *id = g_string_new(ctrl_lcu->lcu->id);
    soap_response->result_value = smartstreetlight_control_lcu_nofree(&soap_thread.spl_soap,ctrl_lcu->lcu->parent->priv->id,
                                           (ctrl_lcu->isOn == TRUE? (GString *)id:NULL),(ctrl_lcu->isOn == FALSE?(GString *)id:NULL),
                                           (const gint)ctrl_lcu->scale,
                                           ctrl_lcu->mode,
                                           ctrl_lcu->istemp,
                                           &ctrl_lcu->rsp_lcu_list, &ctrl_lcu->rsp_lcu_list_size,false);
    g_string_free(id, TRUE);
}

static void* smartstreetlight_control_lcu_soap_receive(gpointer data)
{
    DEBUG_1();
    SoapResponse *soap_response = (SoapResponse *)data;
    struct CtrlLcuThread *ctrl_lcu = (struct CtrlLcuThread*)soap_response->data;
    if(soap_response->result_value == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
    {
        GString *msgError = g_string_new (NULL);
        if (ctrl_lcu->rsp_lcu_list_size == 1)
        {

            ctrl_lcu->lcu->mode = ctrl_lcu->rsp_lcu_list[0]->lcu_USCOREmode;
            ctrl_lcu->lcu->isOn = ctrl_lcu->rsp_lcu_list[0]->lcu_USCOREison;
            ctrl_lcu->lcu->status = ctrl_lcu->rsp_lcu_list[0]->lcu_USCOREstatus;
            ctrl_lcu->lcu->brightness = (gfloat)ctrl_lcu->rsp_lcu_list[0]->lcu_USCORElevel;
            ctrl_lcu->lcu->volt = (gfloat)ctrl_lcu->rsp_lcu_list[0]->lcu_USCOREcurrent;
            if (IS_ERROR_LCU(ctrl_lcu->lcu->status))
            {
                g_string_append_printf(msgError, "Điều khiển %s bị lỗi\n", ctrl_lcu->lcu->id);
            }

            light_update_information(ctrl_lcu->lcu, TRUE);
            // inoder to test,will modify feature
//            if (ctrl_lcu->lcu->icon)
//                osm_gps_map_image_remove(map, ctrl_lcu->lcu->icon);
//            gfloat lat = 0, lon;
//            spl_lcu_add_image(ctrl_lcu->lcu, light_image[ctrl_lcu->lcu->isOn ? ICON_LIGHT_ON : ICON_LIGHT_OFF], &lat, &lon);
        }
        if (msgError->len != 0)
        {
            GtkWidget *parent = stack_widget_active_top();
            SPL_ERROR_POPUP(parent, msgError->str);
        }
        else
        {
            GtkWidget *parent = stack_widget_active_top();
            SPL_INFO_POPUP(parent, "Yêu cầu điều khiển các đèn của DCU thành công.");
        }
    }
    else
    {
        gchar * msg = g_strconcat("Lỗi điền khiển đèn id ",  ctrl_lcu->lcu->id, " của trạm có id là ", ctrl_lcu->lcu->parent->priv->id,". ", NULL);
        GtkWidget *parent = stack_widget_active_top();
        smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_response->result_value);
        g_char_free(msg);
    }
    smartstreetlight_free_soap_operation(&soap_thread.spl_soap);
    g_free((pSplLcu)soap_response->data);
    g_free(soap_response);
    return NULL;
}
gboolean spl_lcu_popup_menu_control(pSplLcu lcu)
{
    gboolean ret = FALSE;
    gint responseId ;
    static gboolean isSignalInit = FALSE;

    g_return_val_if_fail(lcu, FALSE);
    gtk_label_set_text(GTK_LABEL(SPL_OBJECT("lcu_control_label_id")), lcu->id);
    gtk_label_set_text(GTK_LABEL(SPL_OBJECT("lcu_control_label_lightname")), lcu->lightname);

    /* Will fix here later @alvinnguyen */
    DEBUG("lcu->mode %d", lcu->mode);
    gtk_combo_box_set_active(GTK_COMBO_BOX(SPL_OBJECT("lcu_control_combobox_mode")), (lcu->mode-1));
    on_light_mode_changed(GTK_COMBO_BOX(SPL_OBJECT("lcu_control_combobox_mode")), NULL);
    gtk_switch_set_active(GTK_SWITCH(SPL_OBJECT("lcu_control_switch_on_off")), lcu->isOn);
    gtk_widget_set_sensitive(GTK_WIDGET(SPL_OBJECT("lcu_control_scale_level")), lcu->isOn);
    gtk_adjustment_set_value(GTK_ADJUSTMENT(SPL_OBJECT("lcu_brightness_adjustment")), (gdouble)lcu->brightness/10);
    if(!isSignalInit)
    {
        g_signal_connect(GTK_COMBO_BOX(SPL_OBJECT("lcu_control_combobox_mode")), "changed",
                         G_CALLBACK(on_light_mode_changed), NULL);
        g_signal_connect(GTK_WIDGET(SPL_OBJECT("lcu_control_switch_on_off")), "button-press-event",
                         G_CALLBACK(on_switch_button_press), NULL);
        isSignalInit = TRUE;
    }

    SPL_DIALOG_SHOW(main_widgets->lcu_control_dialog);
    gtk_widget_show_all(main_widgets->lcu_control_dialog);
    while(responseId = gtk_dialog_run(GTK_DIALOG(main_widgets->lcu_control_dialog)))
    {
        gboolean exit = TRUE;
        switch(responseId)
        {
        case GTK_RESPONSE_OK:
        {
            gboolean isOn = gtk_switch_get_active(GTK_SWITCH(SPL_OBJECT("lcu_control_switch_on_off")));
            gint mode = gtk_combo_box_get_active(GTK_COMBO_BOX(SPL_OBJECT("lcu_control_combobox_mode"))) + 1;
            gdouble  scale = gtk_adjustment_get_value(GTK_ADJUSTMENT(SPL_OBJECT("lcu_brightness_adjustment")))*10;
            gboolean istemp = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(SPL_OBJECT("lcu_control_istemp_checkbutton")));
            gboolean hasChange = FALSE;
            if(mode == lcu->mode)//truong hop ko thay doi mode
            {
                if(mode == SPL_LCU_ManualMode)
                {
                    DEBUG("In manual mode %d\n", lcu->isOn != isOn);
                    if(lcu->isOn != isOn || (lcu->isOn && ((gint)scale != (gint)(lcu->brightness / LCU_BRIGHTNESS_MAX_LEVEL *10))))
                        hasChange = TRUE;
                }
            }
            else
                hasChange = TRUE;
            if(!hasChange)
            {
                GtkWidget *parent = stack_widget_active_top();
                if(SPL_QUESTION_POPUP(parent, "Chưa có thông số nào được thay đổi, bạn muốn thoát chứ?") == GTK_RESPONSE_CANCEL)
                    exit = FALSE;
            }
            else //cap nhat trang thai xuong device and sql
            {
//                if(mode == SPL_LCU_ScheduleMode)
//                {
//                    isOn = lcu->isOn;
//                    scale = (gdouble)lcu->brightness;
//                }
//                else
//                {
//                    if(!isOn)
//                        scale = (gdouble)lcu->brightness;
//                    else
//                        scale = scale / 10 * LCU_BRIGHTNESS_MAX_LEVEL;
//                }

                DEBUG("scale level of light: %d", (gint)scale);
                struct CtrlLcuThread *ctrl_lcu = g_new0(CtrlLcuThread, 1);
                ctrl_lcu->lcu = lcu;
                ctrl_lcu->mode = mode;
                ctrl_lcu->isOn = isOn;
                ctrl_lcu->scale = scale;
                ctrl_lcu->istemp = istemp;
                if(soap_thread.init_thread(ctrl_lcu, smartstreetlight_control_lcu_soap_execute,
                                                    smartstreetlight_control_lcu_soap_receive ) == FALSE)
                {
                    gchar * str_error = g_strdup("Không thể tạo thread xử lý cho thao tác điều khiển LCU.");
                    DEBUG ("Internal error: %s", str_error);
                    GtkWidget *parent = stack_widget_active_top();
                    smartstreetlight_error_check_message_result(GTK_WIDGET(parent), str_error, ns1__MESSAGE_USCORERESULT_USCOREEnum__INTERNAL_USCOREERR);
                    g_free(str_error);
                    ret = FALSE;
                }
            }
        }
        break;
        case GTK_RESPONSE_CLOSE:
        case GTK_RESPONSE_CANCEL:
        case GTK_RESPONSE_DELETE_EVENT:
            break;
        }
        if(exit)
            break;
    }
    SPL_DIALOG_HIDE(main_widgets->lcu_control_dialog);
    return TRUE;
}

static void  smartstreetlight_lcu_remove_soap_execute(gpointer args)
{
    SoapResponse *soap_response = (SoapResponse *)args;
    pSplLcu lcu = (pSplLcu)soap_response->data;
    g_return_if_fail(lcu && lcu->parent && lcu->parent->priv);
    soap_response->result_value =  smartstreetlight_remove_lcu_execute(&soap_thread.spl_soap, lcu->id, lcu->parent->priv->id);
}

static void* smartstreetlight_lcu_remove_soap_receive(gpointer data)
{
    SoapResponse *soap_response = (SoapResponse *)data;
    pSplLcu lcu = (pSplLcu)soap_response->data;
    if(soap_response->result_value == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
    {
        // not free for lcu data //
        smartstreetlight_lcu_remove_soap_receive_process((pSplLcu)soap_response->data);
        spl_lcu_free((pSplLcu)soap_response->data);
    }
    else
    {
        gchar *msg = g_strdup_printf("Lỗi xóa đèn '%s' từ trạm '%s'.", lcu->id, lcu->parent->priv->id);
        GtkWidget *parent = stack_widget_active_top();
        smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_response->result_value);
        g_free(msg);
    }
    g_free(soap_response);

    return NULL;  // must return NULL here
}

static void smartstreetlight_lcu_remove_soap_receive_process(pSplLcu lcu)
{
    GtkTreeIter iter;
    GtkTreeStore *store;
    GtkTreeIter *parentIter;
    pSplDcu dcu = lcu->parent;

    DEBUG("Remove Ok, update interface\n");

    if(!IS_EMPTY_LIST_LCU(dcu))
    {
        REMOVE_LIST_LCU(dcu, lcu)
        //remove on all list
        store = main_view_widgets->lcu_all_store;
        if(gtk_tree_store_iter_is_valid(GTK_TREE_STORE(store), &dcu->controlIter))
        {
            if(gtk_tree_model_iter_children(GTK_TREE_MODEL(store), &iter, &dcu->controlIter))
            {
                parentIter = &dcu->controlIter;
                do
                {
                    pSplLcu tmp;
                    gtk_tree_model_get(GTK_TREE_MODEL(store), &iter,
                                       LIGHT_POINTER, &tmp,  -1 );
                    if(tmp == lcu)
                    {
                        gtk_tree_store_remove(store, &iter);
                        break;
                    }

                }
                while(gtk_tree_model_iter_next(GTK_TREE_MODEL(store), &iter));
                gtk_tree_model_filter_refilter(main_view_widgets->lcu_all_filter);
            }
        }
        DEBUG("Clear on ALL Light OK\n");
        if(gtk_combo_box_get_active(GTK_COMBO_BOX(cbb_light_display)) == DISPLAY_FOLLOW_DCU)
        {
            GtkTreeModel *model;
            parentIter = NULL;
            store = main_view_widgets->lcu_store;
            DEBUG("Get selected\n");
            if(gtk_tree_selection_get_selected(
                        GTK_TREE_SELECTION(gtk_tree_view_get_selection(GTK_TREE_VIEW(main_view_widgets->lcu_view))),
                        &model, &iter))
            {
                DEBUG("remove iter\n");
                gtk_tree_store_remove(store, &iter);
            }
        }
        lastSelectedLcu = NULL;
    }
}

void spl_light_remove_request(pSplLcu lcu)
{
    g_return_val_if_fail(lcu && lcu->parent && lcu->parent->priv && lcu->parent->priv->id, FALSE);

    if(soap_thread.init_thread(lcu, smartstreetlight_lcu_remove_soap_execute,
                                    smartstreetlight_lcu_remove_soap_receive) == FALSE)
    {
        gchar * str_error = g_strdup_printf("Không thể tạo thread xử lý cho thao tác xóa đèn '%s'", lcu->id);
        DEBUG ("Internal error: %s", str_error);
        GtkWidget *parent = stack_widget_active_top();
        smartstreetlight_error_check_message_result(GTK_WIDGET(parent), str_error, ns1__MESSAGE_USCORERESULT_USCOREEnum__INTERNAL_USCOREERR);
        g_free(str_error);
    }
}

void create_new_light_instances(pSplDcu dcu)
{
    ns1__LCU_USCOREINFO_USCOREType **lcu_list;
    gint lcu_list_size;
    SplSoap spl_soap;
    gint soap_err = smartstreetlight_get_lcu_list_nofree_execute(&spl_soap,dcu->priv->id, &lcu_list, &lcu_list_size);
    if (soap_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
    {
        if (lcu_list!= NULL)
        {
            GtkTreeIter iter;
            for(gint i=0; i<lcu_list_size; i++)
            {
                ns1__LCU_USCOREINFO_USCOREType *lcuWsdl = lcu_list[i];
                pSplLcu lcuInstance    = g_new0(SplLcu, 1);
                //lcuInstance->isBroken   = (lcu->lcu_USCOREisbroken != 0);
                lcuInstance->isOn       = (lcuWsdl->lcu_USCOREison != 0);
                lcuInstance->id         = g_strdup(lcuWsdl->lcu_USCOREid);
                lcuInstance->gps        = g_strdup(lcuWsdl->lcu_USCOREgps);
                lcuInstance->brightness = (gfloat)lcuWsdl->lcu_USCORElevel;
                lcuInstance->icon       = NULL;
                lcuInstance->mode       = lcuWsdl->lcu_USCOREmode;
                lcuInstance->note       = g_strdup(lcuWsdl->lcu_USCOREnote);
                lcuInstance->parent     = dcu;
                lcuInstance->status     = lcuWsdl->lcu_USCOREstatus;
                lcuInstance->volt       = lcuWsdl->lcu_USCOREcurrent;
                lcuInstance->power      = lcuWsdl->lcu_USCOREpower;
                lcuInstance->lightname  = g_strdup(lcuWsdl->lcu_USCORElightname);
                lcuInstance->tolerance  = lcuWsdl->lcu_USCOREtolerance;
                PREPEND_LIST_LCU(dcu,lcuInstance);
                if(showAllLightEnable)
                {
                    gtk_tree_store_append(main_view_widgets->lcu_all_store, &iter, NULL);
                    gtk_tree_store_set(main_view_widgets->lcu_all_store, &iter,
                                       LIGHT_ID, lcuInstance->id, LIGHT_POINTER, lcuInstance, LIGHT_VISIBLE, TRUE, -1);
                }
            }
        }
    }
    else
    {
        gchar * msg = g_strdup("Lỗi lấy danh sách đèn từ server. ");
        GtkWidget *parent = stack_widget_active_top();
        smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
        g_char_free(msg);
    }
    smartstreetlight_free_soap_operation(&spl_soap);
}
