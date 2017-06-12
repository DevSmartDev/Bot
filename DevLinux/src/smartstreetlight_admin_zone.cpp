#include "mapviewer.h"
#include <map>
#include <stdlib.h>
#include "smartstreetlight_admin_zone.h"
#include "smartstreetlight_admin_user.h"
#include "smartstreetlight_soap.h"
#include "smartstreetlight_login.h"
#include "gsoap/soapH.h"
#include "smartstreetlight_error.h"
static gint current_zone_id_show = -1;

struct SPL_ADMIN_ZONE_Widgets *spl_admin_zone_widgets;
struct ADMIN_ZONE_MANAGE_PopupMenu *admin_zone_manage_popupmenu;
struct SPL_ADMIN_ZONE_EDIT_Widgets *admin_zone_edit_widgets;

//static void spl_admin_zone_treestore_fill_information();

static void spl_admin_zone_manage_popup_menu_init();

static void spl_admin_zone_edit_dialog_init(void);

static void spl_admin_zone_manage_popup_menu_clicked(GtkWidget *popup_menu_item, gpointer userdata);

static void spl_admin_zone_manage_popup_menu_clicked_add();

static void spl_admin_zone_manage_popup_menu_clicked_edit();

static void spl_admin_zone_manage_popup_menu_clicked_remove();

static void spl_admin_zone_manage_popup_menu_clicked_move();

static gint spl_admin_zone_move_fill_list(gint curr_zone_id);

static void spl_admin_zone_move_dcu_run(pSplZone old_zone, GtkTreeModel *main_model, GtkTreeIter *main_iter, pSplDcu dcu_info);

static void spl_admin_zone_list_treestore_insert(ns1__ZONE_USCOREINFO_USCOREType *zone_info);

static void spl_admin_zone_list_treestore_update(GtkTreeIter *iter, GtkTreeModel *model, ns1__ZONE_USCOREINFO_USCOREType *zone_info);



/** ======================================================================================== **/

gboolean spl_admin_zone_manage_init(void)
{
#if 0
    GtkTreeViewColumn *column;
    GtkCellRenderer   *renderer;

    spl_admin_zone_widgets = g_slice_new(SPL_ADMIN_ZONE_Widgets);

    spl_admin_zone_widgets->list_zone_treeview = GTK_WIDGET(SPL_OBJECT("list_zone_treeview"));

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes ("Tên Khu Vực", renderer, "text", ADMIN_USER_ZONE_NAME_COLUMN, NULL);
    gtk_tree_view_column_set_resizable(column,TRUE);
    gtk_tree_view_column_set_reorderable(column, TRUE);
    gtk_tree_view_append_column (GTK_TREE_VIEW(spl_admin_zone_widgets->list_zone_treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes ("Ghi Chú", renderer, "text", ADMIN_USER_ZONE_NOTE_COLUMN, NULL);
    gtk_tree_view_column_set_resizable(column,TRUE);
    gtk_tree_view_column_set_reorderable(column, TRUE);
    gtk_tree_view_append_column (GTK_TREE_VIEW(spl_admin_zone_widgets->list_zone_treeview), column);

    // init for treestore //
/*
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
*/

    spl_admin_zone_widgets->list_zone_treestore = gtk_tree_store_new(ADMIN_USER_ZONE_NUNBER_COLUMN,
                                                                        G_TYPE_STRING,
                                                                        G_TYPE_STRING,
                                                                        G_TYPE_INT,
                                                                        G_TYPE_INT,
                                                                        GDK_TYPE_PIXBUF,
                                                                        GDK_TYPE_RGBA,
                                                                        G_TYPE_INT);

    gtk_tree_view_set_model(GTK_TREE_VIEW(spl_admin_zone_widgets->list_zone_treeview),
                            GTK_TREE_MODEL(spl_admin_zone_widgets->list_zone_treestore));

    g_object_unref(G_OBJECT(spl_admin_zone_widgets->list_zone_treestore));


#endif // 0
    spl_admin_zone_edit_dialog_init();

    spl_admin_zone_manage_popup_menu_init();

    gtk_paned_set_position(GTK_PANED(SPL_OBJECT("admin_zone_manage_paned")), 350);

    return TRUE;
}

static void spl_admin_zone_edit_dialog_init(void)
{
    admin_zone_edit_widgets = g_slice_new(SPL_ADMIN_ZONE_EDIT_Widgets);

    admin_zone_edit_widgets->dialog = GTK_WIDGET(SPL_OBJECT("admin_zone_edit_dialog"));
    admin_zone_edit_widgets->main_label = GTK_WIDGET(SPL_OBJECT("admin_zone_edit_main_label"));
    admin_zone_edit_widgets->error_label = GTK_WIDGET(SPL_OBJECT("admin_zone_edit_error_label"));
    admin_zone_edit_widgets->id_label = GTK_WIDGET(SPL_OBJECT("admin_zone_edit_id"));
    admin_zone_edit_widgets->name_entry = GTK_WIDGET(SPL_OBJECT("admin_zone_edit_name_entry"));
    admin_zone_edit_widgets->note_entry = GTK_WIDGET(SPL_OBJECT("admin_zone_edit_note_entry"));

    gtk_widget_set_visible(admin_zone_edit_widgets->error_label, FALSE);
    gtk_widget_set_visible(admin_zone_edit_widgets->id_label, FALSE);
}


static void spl_admin_zone_manage_popup_menu_init()
{
    admin_zone_manage_popupmenu = g_slice_new(ADMIN_ZONE_MANAGE_PopupMenu);

    admin_zone_manage_popupmenu->M_Popup = gtk_menu_new();
    SPL_MENU_CSS(admin_zone_manage_popupmenu->M_Popup);

    admin_zone_manage_popupmenu->M_Add = gtk_menu_item_new_with_label("Thêm mới");
    gtk_menu_shell_append(GTK_MENU_SHELL(admin_zone_manage_popupmenu->M_Popup),admin_zone_manage_popupmenu->M_Add);
    g_signal_connect(admin_zone_manage_popupmenu->M_Add, "activate",
                 (GCallback) spl_admin_zone_manage_popup_menu_clicked, GINT_TO_POINTER(ADMIN_ZONE_M_ADD));

    admin_zone_manage_popupmenu->M_Sep_1 = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(admin_zone_manage_popupmenu->M_Popup), admin_zone_manage_popupmenu->M_Sep_1);

    admin_zone_manage_popupmenu->M_Edit= gtk_menu_item_new_with_label("Chỉnh sửa");
    gtk_menu_shell_append(GTK_MENU_SHELL(admin_zone_manage_popupmenu->M_Popup),admin_zone_manage_popupmenu->M_Edit);
    g_signal_connect(admin_zone_manage_popupmenu->M_Edit, "activate",
                 (GCallback) spl_admin_zone_manage_popup_menu_clicked, GINT_TO_POINTER(ADMIN_ZONE_M_EDIT));

    admin_zone_manage_popupmenu->M_Sep_2 = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(admin_zone_manage_popupmenu->M_Popup), admin_zone_manage_popupmenu->M_Sep_2);

    admin_zone_manage_popupmenu->M_Remove= gtk_menu_item_new_with_label("Xóa");
    gtk_menu_shell_append(GTK_MENU_SHELL(admin_zone_manage_popupmenu->M_Popup),admin_zone_manage_popupmenu->M_Remove);
    g_signal_connect(admin_zone_manage_popupmenu->M_Remove, "activate",
                 (GCallback) spl_admin_zone_manage_popup_menu_clicked, GINT_TO_POINTER(ADMIN_ZONE_M_REMOVE));

    admin_zone_manage_popupmenu->M_Move= gtk_menu_item_new_with_label("Chuyển khu vực");
    gtk_menu_shell_append(GTK_MENU_SHELL(admin_zone_manage_popupmenu->M_Popup),admin_zone_manage_popupmenu->M_Move);
    g_signal_connect(admin_zone_manage_popupmenu->M_Move, "activate",
                 (GCallback) spl_admin_zone_manage_popup_menu_clicked, GINT_TO_POINTER(ADMIN_ZONE_M_MOVE));
}

void spl_admin_zone_manage_finalize(void)
{
    gtk_widget_destroy(GTK_WIDGET(admin_zone_manage_popupmenu->M_Popup));
    g_slice_free(ADMIN_ZONE_MANAGE_PopupMenu, admin_zone_manage_popupmenu);

    gtk_widget_destroy(GTK_WIDGET(admin_zone_edit_widgets->dialog));
    g_slice_free(SPL_ADMIN_ZONE_EDIT_Widgets, admin_zone_edit_widgets);

    g_slice_free(ADMIN_ZONE_OWN_Widgets, admin_zone_own_choose_widget);
#if 0
    gtk_widget_destroy(GTK_WIDGET(SPL_OBJECT("box93")));
    g_slice_free(SPL_ADMIN_ZONE_Widgets, spl_admin_zone_widgets);
#endif // 0
}

//void spl_admin_zone_show_specific(GtkTreePath *path)
//{
//    g_return_if_fail(main_widgets && main_widgets->main_notebook);
//
//    gtk_notebook_set_current_page(GTK_NOTEBOOK(main_widgets->main_notebook), SPL_NOTEBOOK_ZONE_MANAGE_PAGE);
//
//    if(spl_admin_zone_show_tab_on_notebook())
//    {
//        spl_admin_zone_run();
//    }
//}

gboolean spl_admin_zone_show_tab_on_notebook(void)
{
    GtkTreeView * dcu_treeview = main_view_widgets->dcu_view;

    if(osm_gps_map_change_parent("map_box", "admin_zone_map_box") &&
       spl_widget_change_parent(GTK_WIDGET(dcu_treeview), GTK_WIDGET(SPL_OBJECT("scrolledwindow19")),
                                              GTK_WIDGET(SPL_OBJECT("scrolledwindow23")))
      )
    {
        g_object_set_data(G_OBJECT(dcu_treeview), "current_parent", (gpointer)"admin_zone_container");
        osm_gps_map_image_remove_all(map);
        spl_zone_clear_is_show();
//        lastSelectedZone = NULL;
        GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(dcu_treeview));
        gtk_tree_selection_unselect_all(selection);
        gtk_tree_view_collapse_all(GTK_TREE_VIEW(dcu_treeview));
        return TRUE;
    }
    return FALSE;
}

//static void spl_admin_zone_treestore_fill_information()
//{
//}

////void spl_admin_zone_run(void)
//{
//    GtkTreeStore *store = GTK_TREE_STORE(spl_admin_zone_widgets->list_zone_treestore);
//    gtk_tree_store_clear(store);
//    g_return_if_fail(zonelist);
//    /*
//        enum
//        {
//            ADMIN_USER_ZONE_NAME_COLUMN = 0,
//            ADMIN_USER_ZONE_NOTE_COLUMN,
//
//            ADMIN_USER_ZONE_ID_COLUMN,
//            ADMIN_USER_DCU_ID_COLUMN,
//
//            ADMIN_USER_ZONE_PIXBUF_COLUMN,
//            ADMIN_USER_ZONE_RGBA_COLUMN,
//
//            ADMIN_USER_ZONE_TYPE_COLUMN,
//
//            ADMIN_USER_ZONE_NUNBER_COLUMN
//        };
//    */
//    for(GSList *item  = zonelist; item != NULL; item = item->next)
//    {
//        GtkTreeIter iter;
//        SplZone *zone = (SplZone*) item->data;
//        if(zone)
//        {
//            gtk_tree_store_append(store, &iter, NULL);
//            gtk_tree_store_set(store, &iter, ADMIN_USER_ZONE_NAME_COLUMN, zone->zonename,
//                                             ADMIN_USER_ZONE_NOTE_COLUMN, zone->zonenote,
//                                             ADMIN_USER_ZONE_ID_COLUMN, zone->zonecode, -1);
//        }
//    }
//}

//static gboolean on_admin_zone_list_treeview_clicked (GtkTreeView *treeview, GdkEventButton *event, gpointer userdata)
//{
//    if (event->type == GDK_2BUTTON_PRESS || event->type == GDK_BUTTON_PRESS)
//    {
//        GtkTreeIter      iter;
//        GtkTreeModel     *model;
//        GtkTreeSelection *selection;
//
//        selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
//
//        gboolean is_selected = gtk_tree_selection_count_selected_rows(selection)>0?TRUE:FALSE;
//        gtk_widget_set_sensitive(admin_zone_manage_popupmenu->M_Edit, is_selected);
//        gtk_widget_set_sensitive(admin_zone_manage_popupmenu->M_Remove, is_selected);
//
//        if(event->type == GDK_2BUTTON_PRESS)
//        {
//            switch(event->button)
//            {
//                case GDK_BUTTON_PRIMARY:
//                {
//                    if(gtk_tree_selection_get_selected(selection, &model, &iter))
//                    {
//                        gint zone_id;
//                        gtk_tree_model_get(GTK_TREE_MODEL(model), &iter,ADMIN_USER_ZONE_ID_COLUMN, &zone_id, -1);
//                        if(current_zone_id_show != zone_id)
//                        {
////                            spl_admin_zone_manage_specific_show(zone_id);
//                            current_zone_id_show = zone_id;
//                        }
//                        else
//                        {
//                            DEBUG("This zone is current zone => not query database! ");
//                        }
//                    }
//                }
//                break;
//            }
//        }
//        else if(event->type == GDK_BUTTON_PRESS)
//        {
//            switch(event->button)
//            {
//                case GDK_BUTTON_SECONDARY:
//                spl_admin_zone_manage_popup_menu_show(treeview, event, userdata);
//                break;
//            }
//        }
//    }
//    return FALSE;
//}

void spl_admin_zone_manage_popup_menu_show(GtkTreeView *treeview, GdkEventButton *event, gpointer userdata)
{
    gboolean is_zone_type = GPOINTER_TO_INT(userdata);

    gtk_widget_set_visible(GTK_WIDGET(admin_zone_manage_popupmenu->M_Move), !is_zone_type);
    gtk_widget_set_visible(GTK_WIDGET(admin_zone_manage_popupmenu->M_Add), is_zone_type);
    gtk_widget_set_visible(GTK_WIDGET(admin_zone_manage_popupmenu->M_Edit), is_zone_type);
    gtk_widget_set_visible(GTK_WIDGET(admin_zone_manage_popupmenu->M_Remove), is_zone_type);
    gtk_widget_set_visible(GTK_WIDGET(admin_zone_manage_popupmenu->M_Sep_1), is_zone_type);
    gtk_widget_set_visible(GTK_WIDGET(admin_zone_manage_popupmenu->M_Sep_2), is_zone_type);


//    gtk_widget_show_all(GTK_WIDGET(admin_zone_manage_popupmenu->M_Popup));
    gtk_menu_popup(GTK_MENU(admin_zone_manage_popupmenu->M_Popup), NULL, NULL, NULL, NULL,
                   (event != NULL) ? event->button : 0, gdk_event_get_time((GdkEvent*)event));
}

static void spl_admin_zone_manage_popup_menu_clicked(GtkWidget *popup_menu_item, gpointer userdata)
{
    ADMIN_USER_MANAGE_POPUP_Enum type = (ADMIN_USER_MANAGE_POPUP_Enum)GPOINTER_TO_INT(userdata);
    switch(type)
    {
    case ADMIN_ZONE_M_ADD:
        spl_admin_zone_manage_popup_menu_clicked_add();
        break;
    case ADMIN_ZONE_M_EDIT:
        spl_admin_zone_manage_popup_menu_clicked_edit();
        break;
    case ADMIN_ZONE_M_REMOVE:
        spl_admin_zone_manage_popup_menu_clicked_remove();
        break;
    case ADMIN_ZONE_M_MOVE:
        spl_admin_zone_manage_popup_menu_clicked_move();
        break;
    default:
        break;
    }
}

gboolean spl_admin_zone_manage_specific_show(pSplZone zone_data)
{
    g_return_if_fail(zone_data);
    GSList *last_dcu = g_slist_last(zone_data->dculistzone);
    osm_gps_map_show_lights_of_zone((pSplDcu)last_dcu->data);

    return TRUE;
}


static void spl_admin_zone_manage_popup_menu_clicked_add()
{
    gboolean is_ok = TRUE;
    gchar *main_label = g_strdup("TẠO MỚI KHU VỰC");
    struct SPL_ADMIN_ZONE_EDIT_Widgets *p = admin_zone_edit_widgets;

    gtk_label_set_text(GTK_LABEL(p->main_label), main_label);
    gtk_entry_set_text(GTK_ENTRY(p->name_entry), "");
    gtk_entry_set_text(GTK_ENTRY(p->note_entry), "");
    gtk_widget_set_visible(p->error_label, FALSE);

    do
    {
        SPL_DIALOG_SHOW(p->dialog);
        gint response_id = gtk_dialog_run(GTK_DIALOG(p->dialog));
        switch(response_id)
        {
            case DIALOG_OK_RESPONSE:
            {
                ns1__ZONE_USCOREINFO_USCOREType zone_info;
                zone_info.zone_USCOREname = (gchar *)gtk_entry_get_text(GTK_ENTRY(p->name_entry));
                zone_info.zone_USCOREnote = (gchar *)gtk_entry_get_text(GTK_ENTRY(p->note_entry));
                gint new_zone_id;

                if(g_strcmp0(zone_info.zone_USCOREname, "")==0)
                {
                    gtk_label_set_text(GTK_LABEL(p->error_label), (const gchar *)"Tên khu vực không thể để trống");
                    gtk_widget_set_visible(p->error_label, TRUE);
                    is_ok = FALSE;
                }
                else
                {
                    SplSoap spl_soap;
                    gint soap_err = smartstreetlight_add_zone_execute(&spl_soap,&zone_info, &new_zone_id);
                    if(soap_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
                    {
                        zone_info.zone_USCOREid = new_zone_id;
                        spl_admin_zone_list_treestore_insert(&zone_info);
                    }
                    else
                    {
                        gchar * msg = g_strdup("Lỗi thêm mới khu vực.");
                        GtkWidget *parent = stack_widget_active_top();
                        smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
                        g_char_free(msg);
                    }
                }
            }
            break;
            case DIALOG_CANCEL_RESPONSE:
                is_ok = TRUE;
                break;
        };
    }
    while(!is_ok);
    SPL_DIALOG_HIDE(p->dialog);
    g_free(main_label);
}

static void spl_admin_zone_manage_popup_menu_clicked_edit()
{
    gboolean is_ok = TRUE;
    struct SPL_ADMIN_ZONE_EDIT_Widgets *p = admin_zone_edit_widgets;
    gchar *main_label = g_strdup("CHỈNH SỬA THÔNG TIN KHU VỰC");

    gtk_label_set_text(GTK_LABEL(p->main_label), main_label);
    gtk_widget_set_visible(p->error_label, FALSE);
    gtk_widget_set_visible(p->error_label, FALSE);

    GtkTreeIter iter;
    GtkTreeModel     *model;
    GtkTreeView      *treeview = main_view_widgets->dcu_view;

    pSplZone _zone;
    /*

        enum
        {
            OBJECT_NAME_COLUMN = 0,
            OBJECT_POINTER_COLUMN,
            OBJECT_TYPE_COLUMN,
            OBJECT_NUM_COLUMNS,
        };

    */

    if(spl_get_current_select_iter(treeview, &model, &iter))
    {
        gtk_tree_model_get(model, &iter, OBJECT_POINTER_COLUMN, &_zone, -1);
        gtk_entry_set_text(GTK_ENTRY(p->name_entry), _zone->zonename);
        gtk_entry_set_text(GTK_ENTRY(p->note_entry), _zone->zonenote);

        gtk_label_set_text(GTK_LABEL(p->main_label), main_label);

        do
        {
            SPL_DIALOG_SHOW(p->dialog);
            gint response_id = gtk_dialog_run(GTK_DIALOG(p->dialog));
            switch(response_id)
            {
                case DIALOG_OK_RESPONSE:
                {
                    ns1__ZONE_USCOREINFO_USCOREType zone_info;
                    zone_info.zone_USCOREname = (gchar *)gtk_entry_get_text(GTK_ENTRY(p->name_entry));
                    zone_info.zone_USCOREnote = (gchar *)gtk_entry_get_text(GTK_ENTRY(p->note_entry));
                    zone_info.zone_USCOREid   = _zone->zonecode;

                    if(g_strcmp0(zone_info.zone_USCOREname, "")==0)
                    {
                        gtk_label_set_text(GTK_LABEL(p->error_label), (const gchar *)"Tên khu vực không thể để trống");
                        gtk_widget_set_visible(p->error_label, TRUE);
                        is_ok = FALSE;
                    }
                    else
                    {
                        SplSoap spl_soap;
                        gint soap_err = smartstreetlight_edit_zone_execute(&spl_soap, &zone_info);
                        if(soap_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
                        {
                            spl_admin_zone_list_treestore_update(&iter, model, &zone_info);
                        }
                        else
                        {
                            gchar * msg = g_strdup("Lỗi chỉnh sửa thông tin khu vực.");
                            GtkWidget *parent = stack_widget_active_top();
                            smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
                            g_char_free(msg);
                        }
                    }
                }
                break;
                case DIALOG_CANCEL_RESPONSE:
                    is_ok = TRUE;
                    break;
            };
        }
        while(!is_ok);
        SPL_DIALOG_HIDE(p->dialog);
        g_free(main_label);
    }
}

static void spl_admin_zone_manage_popup_menu_clicked_remove()
{
    GtkTreeView *treeview = GTK_TREE_VIEW(main_view_widgets->dcu_view);
    GtkTreeModel *model;
    GtkTreeIter iter;
    pSplZone _zone;

    if(spl_get_current_select_iter(treeview, &model, &iter))
    {
        gtk_tree_model_get(model, &iter, OBJECT_POINTER_COLUMN, &_zone, -1);
        g_return_if_fail(_zone);

        gchar *buffer = g_strdup_printf("Bạn chắc chắn muốn xóa khu vực '%s' ?", _zone->zonename);

        GtkWidget *parent = stack_widget_active_top();
        switch(SPL_QUESTION_POPUP(parent, buffer))
        {
            case GTK_RESPONSE_OK:
            {
                SplSoap spl_soap;
                gint soap_err = smartstreetlight_remove_zone_execute(&spl_soap, _zone->zonecode);
                if(soap_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
                {
                    gtk_tree_store_remove(GTK_TREE_STORE(model), &iter);
                    REMOVE_LIST_ZONE(_zone);
                    if(_zone->zonecode == current_zone_id_show)
                    {
                        osm_gps_map_image_remove_all(map);
                        spl_zone_clear_is_show();
                        current_zone_id_show = -1;
                    }
                }
                else
                {
                    gchar * msg = g_strdup("Lỗi xóa khu vực.");
                    GtkWidget *parent = stack_widget_active_top();
                    smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
                    g_char_free(msg);
                }
            }
            break;
            case GTK_RESPONSE_CANCEL:
                break;
            default:
                break;
        }
    }
}

static void spl_admin_zone_manage_popup_menu_clicked_move()
{
    spl_admin_zone_own_choose_init();

    GtkTreeIter iter;
    GtkTreeIter zone_iter;
    GtkTreeView *treeview = GTK_TREE_VIEW(main_view_widgets->dcu_view);
    GtkTreeModel *model;

    pSplZone _zone;
    pSplDcu  _dcu;
    gint count_all_zone;

    if(spl_get_current_select_iter(treeview, &model, &iter))
    {
        gtk_tree_model_get(model, &iter, OBJECT_POINTER_COLUMN, &_dcu, -1);
        if(gtk_tree_model_iter_parent(model, &zone_iter, &iter))
            gtk_tree_model_get(model, &zone_iter, OBJECT_POINTER_COLUMN, &_zone, -1);
        g_return_if_fail(_zone && _dcu);
        smartstreetlight_clear_tree_store(GTK_TREE_MODEL(admin_zone_own_choose_widget->treestore));
        count_all_zone = spl_admin_zone_move_fill_list(_zone->zonecode);
        g_object_set_data(G_OBJECT(admin_zone_own_choose_widget->dialog), "is_radio", GINT_TO_POINTER(TRUE));

        SPL_DIALOG_SHOW(admin_zone_own_choose_widget->dialog);
        gint response_id = gtk_dialog_run(GTK_DIALOG(admin_zone_own_choose_widget->dialog));
        switch(response_id)
        {
        case DIALOG_OK_RESPONSE:
            {
                spl_admin_zone_move_dcu_run(_zone, model, &iter, _dcu);
            }
            break;
        case DIALOG_CANCEL_RESPONSE:
            break;
        }
        SPL_DIALOG_HIDE(admin_zone_own_choose_widget->dialog);
    }
}

static void spl_admin_zone_move_dcu_run(pSplZone old_zone, GtkTreeModel *main_model, GtkTreeIter *main_iter, pSplDcu dcu_info)
{
    gint zone_id = -1;
    gboolean is_toggle = FALSE;
    GtkTreeModel *model = GTK_TREE_MODEL(admin_zone_own_choose_widget->treestore);
    GtkTreeIter iter;
    if(gtk_tree_model_get_iter_first(model, &iter))
    {
        do
        {
            gtk_tree_model_get(model, &iter, 0, &is_toggle, 2, &zone_id, -1);
            if(is_toggle)
                break;
        }
        while(gtk_tree_model_iter_next(model, &iter));

        if(zone_id != -1)
        {
            if(zone_id == dcu_info->priv->zonecode)
                return;

            dcu_info->priv->zonecode = zone_id;
            SplSoap spl_soap;
            gint soap_err = smartstreetlight_edit_dcu_execute(&spl_soap, dcu_info);
            if(soap_err != ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
            {
                gchar * msg = g_strconcat("Lỗi chuyển khu vực cho trạm '%s'", dcu_info->priv->id);
                GtkWidget *parent = stack_widget_active_top();
                smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
                g_char_free(msg);
            }
            else
            {
                /* remove dcu from old zone */
                gtk_tree_store_remove(GTK_TREE_STORE(main_model), main_iter);
                GSList *listzone = old_zone->dculistzone;
                listzone = g_slist_remove(listzone, dcu_info);

                /* append dcu to new zone */
                pSplZone _zone = NULL;
                if( LOCKUP_LIST_ZONE(&zone_id, _zone) && _zone)
                {
                    gtk_tree_store_append(main_view_widgets->dcu_store, &dcu_info->priv->iter, &_zone->zoneIter);
                    gtk_tree_store_set (main_view_widgets->dcu_store, &dcu_info->priv->iter,
                                        OBJECT_NAME_COLUMN, dcu_info->priv->id,
                                        OBJECT_POINTER_COLUMN, (gpointer)dcu_info,
                                        OBJECT_TYPE_COLUMN, (gint)OBJECT_IS_DCU_TYPE,
                                        -1);
                    _zone->dculistzone = g_slist_append(_zone->dculistzone, dcu_info);
                    //gtk_tree_selection_select_iter(gtk_tree_view_get_selection(GTK_TREE_VIEW(main_view_widgets->dcu_view)),
                    //                                                             &dcu_info->priv->iter);
                }
                else
                {
                    GtkWidget *parent = stack_widget_active_top();
                    SPL_ERROR_POPUP(parent, "Lỗi từ ứng dụng");
                }
            }
        }
    }

}


static gint spl_admin_zone_move_fill_list(gint curr_zone_id)
{
    GtkTreeIter iter;
    gboolean is_own;
    GtkTreeStore *store = admin_zone_own_choose_widget->treestore;
    GSList *zonelist_iter = NULL;
    gint zone_count = 0;
    LIST_ZONE_FOR_EACH_ENTRY(zonelist_iter)
    {
        pSplZone _zone = (pSplZone)zonelist_iter->data;
        is_own = _zone->zonecode==curr_zone_id?TRUE:FALSE;
        gtk_tree_store_append(store, &iter, NULL);
        gtk_tree_store_set(store, &iter, 0, is_own, 1, _zone->zonename, 2, _zone->zonecode, -1);
        zone_count++;
    }
    return zone_count;
}


static void spl_admin_zone_list_treestore_insert(ns1__ZONE_USCOREINFO_USCOREType *zone_info)
{
    g_return_if_fail(zone_info);
    smartstreetlight_zone_fill_infomation(zone_info->zone_USCOREid, zone_info->zone_USCOREname, zone_info->zone_USCOREnote);
}


static void spl_admin_zone_list_treestore_update(GtkTreeIter *iter, GtkTreeModel *model,
                                                 ns1__ZONE_USCOREINFO_USCOREType *zone_info)
{
    g_return_if_fail(iter && model && zone_info);

    SplZone * _zone = NULL;

    if( LOCKUP_LIST_ZONE(&zone_info->zone_USCOREid, _zone) && _zone)
    {
        g_free(_zone->zonename);
        _zone->zonename = g_strdup(zone_info->zone_USCOREname);
        g_free(_zone->zonenote);
        _zone->zonenote = g_strdup(zone_info->zone_USCOREnote);
        /*
            enum
            {
                OBJECT_NAME_COLUMN = 0,
                OBJECT_POINTER_COLUMN,
                OBJECT_TYPE_COLUMN,
                OBJECT_NUM_COLUMNS,
            };
        */
        gtk_tree_store_set(GTK_TREE_STORE(model), iter, OBJECT_NAME_COLUMN,     _zone->zonename,
                                                        OBJECT_POINTER_COLUMN,  &_zone,
                                                        OBJECT_TYPE_COLUMN,     OBJECT_IS_ZONE_TYPE, -1);
    }
}

