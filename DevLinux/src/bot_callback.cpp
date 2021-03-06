#include "bot_callback.h"
#include "bot_dcu.h"
#include "bot_schedule.h"
#include "bot_line.h"
#include "bot_lcu.h"
#include "bot_soap.h"
#include "bot_log.h"
#include "bot_login.h"
#include "bot_server.h"
#include "bot_user.h"
#include "bot_admin_zone.h"
#include "bot_error.h"


static gboolean is_changed_map_parent_by_admin_zone = FALSE;

void on_dcu_selection_changed (GtkTreeSelection *selection, gpointer user_data)
{
    GtkWidget * dcu_treeview = GTK_WIDGET(bot_OBJECT("dcu_info_tree_view"));
    if(g_strcmp0((gchar *)g_object_get_data(G_OBJECT(dcu_treeview), "current_parent"), "admin_zone_container")==0)
        return;

    DEBUG("start ..\n");

    GtkTreeModel *model;
    GtkTreeIter iter;
    GtkTreePath *path;
    if(isLogining)
        return;

    gboolean is_reload = FALSE;
    if(user_data!=NULL)
        is_reload = (gboolean)GPOINTER_TO_INT(user_data);

    if(gtk_tree_selection_get_selected(selection, &model, &iter))
    {
        gint type;
        pbotDcu dcu;
        gtk_tree_model_get(model, &iter, OBJECT_POINTER_COLUMN, &dcu, OBJECT_TYPE_COLUMN, &type, -1 );
        if(type != OBJECT_IS_DCU_TYPE)
        {
            GtkTreeIter childIter;
            lastSelectedDcu = NULL;
            if(gtk_tree_model_iter_has_child(model, &iter))
            {
                path = gtk_tree_model_get_path(model, &iter);
                gtk_tree_view_expand_row(GTK_TREE_VIEW(main_view_widgets->dcu_view), path, TRUE);
                if(gtk_tree_model_iter_children(model, &childIter, &iter))
                {
                    gtk_tree_selection_select_iter(selection, &childIter);
                }
                gtk_tree_path_free(path);
            }
            return;
        }

        DEBUG("show dcu: %s", dcu->priv->id);

        if(dcu && is_reload ? TRUE : (dcu != lastSelectedDcu))
        {
            lastSelectedDcu = dcu;
            if(!showAllLightEnable)
            {
                //looking it on closest using list
                gboolean looked = FALSE;
                //DEBUG("closest dcu length: %d\n", g_slist_length(closestUsingDculist));
                for(GSList *item = closestUsingDculist; item != NULL; item = item->next)
                {
                    pbotDcuClosestUsing closest = (pbotDcuClosestUsing)item->data;
                    //DEBUG("id closest: %s id: %s\n", closest->dcu->priv->id, dcu->priv->id);
                    if(closest->dcu == dcu)
                    {
                        //DEBUG("found DCU with ID: %s\n", dcu->priv->id);
                        g_get_current_time(&closest->last_edit_time);
                        looked = TRUE;
                        break;
                    }
                }
                if(!looked)
                {
                    //DEBUG("Not found DCU with ID: %s\n", dcu->priv->id);
                    bot_add_new_dcu_into_closest_list(dcu);
                    //get all light of this dcu on mysql
                    if (SIZE_LIST_LCU(dcu) == 0)
                    {
                        create_new_light_instances(dcu);
                    }
                }
                bot_closeset_list_sort();
            }
            bot_dcu_set_information(lastSelectedDcu);
            DEBUG_1();
            osm_osm_gps_map_show_lights(gtk_combo_box_get_active(GTK_COMBO_BOX(cbb_light_spl)),lastSelectedDcu);
        }
    }
}

gboolean
on_dcu_view_info_clicked                    (GtkTreeView        *treeview,
                                             GdkEventButton     *event,
                                             gpointer           userdata)
{
    GtkTreeIter iter;
    GtkTreePath *path;
    GtkTreeModel *model = gtk_tree_view_get_model(main_view_widgets->dcu_view);
    gint btnType = event->type;
    GtkTreeSelection *selection = gtk_tree_view_get_selection(main_view_widgets->dcu_view);

    if (gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(treeview), (gint) event->x, (gint) event->y, &path, NULL, NULL, NULL))
    {
        if(gtk_tree_model_get_iter(model, &iter, path))
        {
            gboolean is_admin_zone_parent = (g_strcmp0((gchar *)g_object_get_data(G_OBJECT(treeview), "current_parent"), "admin_zone_container")==0)?TRUE:FALSE;

            switch(event->button)
            {
            case GDK_BUTTON_MIDDLE:
                return FALSE;
            case GDK_BUTTON_PRIMARY:
                {
                    if(event->type == GDK_2BUTTON_PRESS)
                    {
                        gint type;
                        gtk_tree_model_get(model, &iter, OBJECT_TYPE_COLUMN, &type, -1);
                        if(is_admin_zone_parent && type == OBJECT_IS_ZONE_TYPE)
                        {
                            pbotZone _zone;
                            gtk_tree_model_get(model, &iter, OBJECT_POINTER_COLUMN, &_zone, -1);
                            if(bot_admin_zone_manage_specific_show(_zone))
                            {
                                _zone->isshowmap = TRUE;
                            }
                        }
                        else if(is_admin_zone_parent && type == OBJECT_IS_DCU_TYPE)
                        {
                            pbotDcu _dcu;
                            gtk_tree_model_get(model, &iter, OBJECT_POINTER_COLUMN, &_dcu, -1);
                            gtk_notebook_set_current_page(GTK_NOTEBOOK(main_widgets->main_notebook), bot_NOTEBOOK_DCU_PAGE);
                            on_bot_main_notebook_switch_page (GTK_NOTEBOOK(main_widgets->main_notebook), NULL,
                                                   gtk_notebook_get_current_page(GTK_NOTEBOOK(main_widgets->main_notebook)),
                                                   NULL);
                            gtk_notebook_set_current_page(GTK_NOTEBOOK(bot_OBJECT("notebook_manager_dcu")), bot_DCU_NOTEBOOK_DCU_PAGE);
                            lastSelectedDcu = _dcu;
                            osm_osm_gps_map_show_lights(gtk_combo_box_get_active(GTK_COMBO_BOX(bot_OBJECT("cbb_light_spl"))), lastSelectedDcu);
                            gtk_tree_selection_select_iter(gtk_tree_view_get_selection(GTK_TREE_VIEW(main_view_widgets->dcu_view)), &iter);

                        }
                        else if(!is_admin_zone_parent && type == OBJECT_IS_DCU_TYPE)
                        {
                            gtk_tree_selection_unselect_all(gtk_tree_view_get_selection(GTK_TREE_VIEW(bot_OBJECT("light_info_tree_view"))));
                            gtk_notebook_set_current_page(GTK_NOTEBOOK(bot_OBJECT("notebook_manager_dcu")), bot_DCU_NOTEBOOK_LCU_PAGE);

                        }
                    }
                    return FALSE;
                }
                break;
            case GDK_BUTTON_SECONDARY:
                {
                    gint type;
                    pbotDcu dcu;
                    gtk_tree_model_get(model, &iter, OBJECT_POINTER_COLUMN, &dcu, OBJECT_TYPE_COLUMN, &type, -1);

                    if(is_admin_zone_parent)
                    {
                        gboolean is_zone_type = (type == OBJECT_IS_ZONE_TYPE)?TRUE:FALSE;
                        bot_admin_zone_manage_popup_menu_show(treeview, event, GINT_TO_POINTER(is_zone_type));
                    }

                    if(!is_admin_zone_parent && type == OBJECT_IS_DCU_TYPE)
                    {
                        bot_popup_menu_show(dcu_popup_menu->parent, event);
                    }
                    return FALSE;
                }
                break;
            }
        }
        if(!gtk_tree_selection_path_is_selected(selection, path))
        {
            gtk_tree_selection_select_path(selection, path);
        }
        gtk_tree_path_free(path);

    }
    return TRUE;
}


gboolean on_bot_dcu_active_info_reload_clicked(GtkButton *button, gpointer userdata)
{
    DEBUG_1();
    return TRUE;
}

gboolean on_bot_dcu_info_hide_clicked(GtkButton *button, gpointer userdata)
{
    DEBUG_1();
//    gtk_widget_set_visible(GTK_WIDGET(bot_OBJECT("dcu_info_paned")), FALSE);
    gtk_paned_set_position (GTK_PANED(bot_OBJECT("paned3")), 0);
    return TRUE;
}



gboolean bot_callback_init(void)
{
//    g_signal_connect(GTK_LABEL(gtk_builder_get_object (bot_builder, "notebook_user_manager")),
//                     "activate-link",
//                     G_CALLBACK(on_bot_main_notebook_dcu_active), NULL);
//
//    g_signal_connect(GTK_LABEL(gtk_builder_get_object (bot_builder, "notebook_program_manager")),
//                     "activate-link",
//                     G_CALLBACK(on_bot_main_notebook_dcu_active), NULL);
//
//    g_signal_connect(GTK_LABEL(gtk_builder_get_object (bot_builder, "notebook_dcu_manager")),
//                     "activate-link",
//                     G_CALLBACK(on_bot_main_notebook_dcu_active), NULL);
    g_signal_connect(GTK_NOTEBOOK(gtk_builder_get_object (bot_builder, "main_notebook")),
                     "switch-page",
                     G_CALLBACK(on_bot_main_notebook_switch_page), NULL);

//    g_signal_connect(GTK_BUTTON(gtk_builder_get_object (bot_builder, "dcu_zone_program_update_btn")),
//                     "clicked",
//                     G_CALLBACK(on_bot_dcu_program_modified_clicked), NULL);
//
//    g_signal_connect(GTK_BUTTON(gtk_builder_get_object (bot_builder, "dcu_line_program_update_btn")),
//                     "clicked",
//                     G_CALLBACK(on_bot_dcu_program_modified_clicked), NULL);

    g_signal_connect(GTK_BUTTON(gtk_builder_get_object (bot_builder, "dcu_program_edit_btn")),
                     "clicked",
                     G_CALLBACK(on_bot_dcu_program_modified_clicked), NULL);

    g_signal_connect(GTK_BUTTON(gtk_builder_get_object (bot_builder, "dcu_program_reload_btn")),
                     "clicked",
                     G_CALLBACK(on_bot_dcu_active_info_reload_clicked), NULL);

//    g_signal_connect(GTK_BUTTON(gtk_builder_get_object (bot_builder, "dcu_program_update_btn")),
//                     "clicked",
//                     G_CALLBACK(on_bot_dcu_active_info_update_clicked), NULL);

    g_signal_connect(GTK_BUTTON(gtk_builder_get_object (bot_builder, "dcu_info_hide_btn")),
                     "clicked",
                     G_CALLBACK(on_bot_dcu_info_hide_clicked), NULL);


    g_signal_connect(GTK_COMBO_BOX(gtk_builder_get_object (bot_builder, "dcu_info_mode_combobox")),
                     "changed",
                     G_CALLBACK(on_bot_dcu_combobox_modified_clicked), NULL);

    g_signal_connect(GTK_COMBO_BOX(gtk_builder_get_object (bot_builder, "dcu_info_program_combobox")),
                     "changed",
                     G_CALLBACK(on_bot_dcu_combobox_modified_clicked), NULL);

    g_signal_connect(GTK_COMBO_BOX(gtk_builder_get_object (bot_builder, "lcu_control_combobox_mode")),
                     "changed",
                     G_CALLBACK(on_bot_lcu_control_mode_combobox_modified_clicked), NULL);

  /*  g_signal_connect(GTK_WIDGET(bot_OBJECT("login_custom_expander")),
                     "button-press-event",
                     G_CALLBACK(on_bot_login_custom_expander), NULL);
*/

    g_signal_connect(GTK_LINK_BUTTON(bot_OBJECT("current_username_login")),
                     "activate-link",
                     G_CALLBACK(on_bot_current_username_login_activate), NULL);


    g_signal_connect(GTK_WIDGET(bot_OBJECT("grid4")), "key-release-event", G_CALLBACK(bot_login_key_event), NULL);

    return TRUE;


//    g_signal_connect(GTK_BUTTON(gtk_builder_get_object (bot_builder, "dcu_program_update_btn")),
//                     "clicked",
//                     G_CALLBACK(on_bot_dcu_program_modified_clicked), NULL);
//
//    g_signal_connect(GTK_BUTTON(gtk_builder_get_object (bot_builder, "dcu_program_reload_btn")),
//                     "clicked",
//                     G_CALLBACK(on_bot_dcu_program_modified_clicked), NULL);

}
//gboolean
//on_login_dialog_response            (GtkDialog      *dialog,
//                                     gint           response_id,
//                                     gpointer       custom_data)
//{
//    switch(response_id)
//    {
//        case DIALOG_OK_RESPONSE:
//            gtk_widget_hide(main_widgets->login_dialog);
//            return TRUE;
//            break;
//
//        case DIALOG_CANCEL_RESPONSE:
//        default:
//            gtk_widget_hide(main_widgets->login_dialog);
//            return FALSE;
//            break;
//	}
//}

/*gboolean on_bot_dcu_specical_clicked(GtkTreeView *treeview, GdkEventButton *event, gpointer userdata)
{
    if (event->type == GDK_2BUTTON_PRESS || event->type == GDK_BUTTON_PRESS)
    {
        GtkTreeIter      iter;
        GtkTreeModel     *model;
        GtkTreeSelection *selection;


        selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));

        if (gtk_tree_selection_count_selected_rows(selection)  <= 1)
        {
            GtkTreePath *path;
            if (gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(treeview), (gint) event->x, (gint) event->y, &path, NULL, NULL, NULL))
            {
                gtk_tree_selection_unselect_all(selection);
                gtk_tree_selection_select_path(selection, path);
                gtk_tree_path_free(path);
            }
        }
        else
        {
            return FALSE;
        }

        if(gtk_tree_selection_get_selected(selection, &model, &iter))
        {
            if(event->type == GDK_2BUTTON_PRESS)
            {
                switch(event->button)
                {
                case 1:
                    DEBUG("\n ******** 2 event->button: %d\n", event->button);

                    gint row_type;
                    gtk_tree_model_get(GTK_TREE_MODEL(model), &iter, TYPE_ROW_COMLUMN, &row_type, -1);

                    DEBUG("\n\n - Type of row is: %d", row_type);

                    if(row_type==(gint)DCU_TREE_STORE_DCU_TYPE)
                    {
                        gchar * dcu_id;
                        gchar * dcu_phone;
                        gchar * dcu_gps;
                        gchar * dcu_address;
                        gchar * dcu_note;
                        gchar * dcu_mode;
                        gchar * dcu_status;
                        gchar * dcu_lcu_program;
                        gchar * dcu_line_program;
                        gchar * dcu_zone_name;
                        gint dcu_zone_id;

                        GtkTreeIter      zone_iter;


                        gtk_tree_model_get(GTK_TREE_MODEL(model), &iter, DCU_ZONE_NAME_COLUMN, &dcu_id,
                                                                         DCU_PHONE_COLUMN, &dcu_phone,
                                                                         DCU_GPS_COLUMN, &dcu_gps,
                                                                         DCU_ADDRESS_COLUMN, &dcu_address,
                                                                         DCU_NOTE_COLUMN, &dcu_note,
                                                                         DCU_MODE_COLUMN, &dcu_mode,
                                                                         DCU_STATUS_COLUMN, &dcu_status,
                                                                         -1);

                        if(gtk_tree_model_iter_parent(GTK_TREE_MODEL(model), &zone_iter, &iter))
                        {
                            gtk_tree_model_get(GTK_TREE_MODEL(model), &zone_iter, ZONE_ID_COLUMN, &dcu_zone_id,
                                                                             ZONE_NAME_COLUMN, &dcu_zone_name, -1);

                            bot_dcu_show_specific_info(dcu_id, dcu_phone, dcu_gps, dcu_address, dcu_note,
                                                                dcu_mode, dcu_status, dcu_lcu_program, dcu_line_program,
                                                                dcu_zone_id, dcu_zone_name);

                            g_free(dcu_zone_name);
                        }


                        g_free(dcu_id);
                        g_free(dcu_phone);
                        g_free(dcu_gps);
                        g_free(dcu_address);
                        g_free(dcu_note);
                        g_free(dcu_mode);
                        g_free(dcu_status);
                        g_free(dcu_lcu_program);
                        g_free(dcu_line_program);
                    }
                    break;
                case 2:
                    DEBUG("\n ******** 2 event->button: %d\n", event->button);
                    break;
                case 3:
                    DEBUG("\n ******** 2 event->button: %d\n", event->button);
                    break;
                default:
                    DEBUG("\n ******** 2 event->button is invalid\n");
                    break;
                }
            }
            else if(event->type == GDK_BUTTON_PRESS)
            {
                switch(event->button)
                {
                case 1:
                    DEBUG("\n ******** 1 event->button: %d\n", event->button);
                    break;
                case 2:
                    DEBUG("\n ******** 1 event->button: %d\n", event->button);
                    break;
                case 3:

                    DEBUG("\n ******** 1 event->button: %d\n", event->button);
                    gint row_type;
                    gtk_tree_model_get(GTK_TREE_MODEL(model), &iter, TYPE_ROW_COMLUMN, &row_type, -1);
                    DEBUG("\n\n - Type of row is: %d", row_type);
                    if(row_type==(gint)DCU_TREE_STORE_DCU_TYPE)
                    {
                        bot_dcu_popup_menu_show(treeview, event, userdata);
                    }

                    break;
                default:
                    DEBUG("\n ******** 1 event->button is invalid\n");
                    break;
                }
            }
        }
    }
    return FALSE;
}
*/
gboolean on_bot_line_specical_clicked (GtkTreeView *treeview, GdkEventButton *event, gpointer userdata)
{
    if (event->type == GDK_2BUTTON_PRESS || event->type == GDK_BUTTON_PRESS)
    {
        GtkTreeIter      iter;
        GtkTreeModel     *model;
        GtkTreeSelection *selection;


        selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));

        if (gtk_tree_selection_count_selected_rows(selection)  <= 1)
        {
            GtkTreePath *path;
            if (gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(treeview), (gint) event->x, (gint) event->y, &path, NULL, NULL, NULL))
            {
                gtk_tree_selection_unselect_all(selection);
                gtk_tree_selection_select_path(selection, path);
                gtk_tree_path_free(path);
            }
        }
        else
        {
            return FALSE;
        }

        if(gtk_tree_selection_get_selected(selection, &model, &iter))
        {
            if(event->type == GDK_2BUTTON_PRESS)
            {
                switch(event->button)
                {
                case 1:
                    DEBUG("\n ******** event->button: %d\n", event->button);
                    break;
                case 2:
                    DEBUG("\n ******** event->button: %d\n", event->button);
                    break;
                case 3:
                    DEBUG("\n ******** event->button: %d\n", event->button);
                    break;
                default:
                    DEBUG("\n ******** event->button is invalid\n");
                    break;
                }
            }
            else if(event->type == GDK_BUTTON_PRESS)
            {
                switch(event->button)
                {
                case 1:
                    DEBUG("\n ******** event->button: %d\n", event->button);
                    break;
                case 2:
                    DEBUG("\n ******** event->button: %d\n", event->button);
                    break;
                case 3:
                    DEBUG("\n ******** event->button: %d\n", event->button);
                    bot_line_popup_menu_show(treeview, event, userdata);
                    break;
                default:
                    DEBUG("\n ******** event->button is invalid\n");
                    break;
                }
            }
        }
    }
    return FALSE;
}

gboolean on_bot_lcu_specical_clicked(GtkTreeView *treeview, GdkEventButton *event, gpointer userdata)
{
#if 0
    if (event->type == GDK_2BUTTON_PRESS || event->type == GDK_BUTTON_PRESS)
    {
        GtkTreeIter      iter;
        GtkTreeModel     *model;
        GtkTreeSelection *selection;


        selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));

        if (gtk_tree_selection_count_selected_rows(selection)  <= 1)
        {
            GtkTreePath *path;
            if (gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(treeview), (gint) event->x, (gint) event->y, &path, NULL, NULL, NULL))
            {
                gtk_tree_selection_unselect_all(selection);
                gtk_tree_selection_select_path(selection, path);
                gtk_tree_path_free(path);
            }
        }
        else
        {
            return FALSE;
        }

        if(gtk_tree_selection_get_selected(selection, &model, &iter))
        {
            if(event->type == GDK_2BUTTON_PRESS)
            {
                switch(event->button)
                {
                case 1:
                    DEBUG("\n ******** event->button: %d\n", event->button);
                    break;
                case 2:
                    DEBUG("\n ******** event->button: %d\n", event->button);
                    break;
                case 3:
                    DEBUG("\n ******** event->button: %d\n", event->button);
                    break;
                default:
                    DEBUG("\n ******** event->button is invalid\n");
                    break;
                }
            }
            else if(event->type == GDK_BUTTON_PRESS)
            {
                switch(event->button)
                {
                case 1:
                    DEBUG("\n ******** event->button: %d\n", event->button);
                    break;
                case 2:
                    DEBUG("\n ******** event->button: %d\n", event->button);
                    break;
                case 3:
                    DEBUG("\n ******** event->button: %d\n", event->button);
                    bot_lcu_popup_menu_show(treeview, event, userdata);
                    break;
                default:
                    DEBUG("\n ******** event->button is invalid\n");
                    break;
                }
            }
        }
    }
#else
    if (event->type == GDK_BUTTON_PRESS && event->button == 3)
    {
        DEBUG("\n event->button: %d", event->button);
       // bot_lcu_popup_menu_show(treeview, event, userdata);
    }
#endif // 0
    return FALSE;
}

gboolean on_bot_dcu_choose_start_time(GtkButton *button, gpointer userdata)
{
//    bot_dcu_choose_time();
}

gboolean on_bot_dcu_update(GtkButton *button, gpointer userdata)
{
    //bot_dcu_update();
}


gboolean
on_bot_schedule_specical_clicked (GtkTreeView        *treeview,
                                             GdkEventButton     *event,
                                             gpointer           userdata)
{
    if (event->type == GDK_2BUTTON_PRESS || event->type == GDK_BUTTON_PRESS)
    {
        GtkTreeIter      iter;
        GtkTreeModel     *model;
        GtkTreeSelection *selection;


        selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));

        if (gtk_tree_selection_count_selected_rows(selection)  <= 1)
        {
            GtkTreePath *path;
            if (gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(treeview), (gint) event->x, (gint) event->y, &path, NULL, NULL, NULL))
            {
                gtk_tree_selection_unselect_all(selection);
                gtk_tree_selection_select_path(selection, path);
                gtk_tree_path_free(path);
            }
        }
        else
        {
            return FALSE;
        }

        if(gtk_tree_selection_get_selected(selection, &model, &iter))
        {
            if(event->type == GDK_2BUTTON_PRESS)
            {
                switch(event->button)
                {
                case 1:
                    DEBUG("\n ******** event->button: %d\n", event->button);
                    break;
                case 2:
                    DEBUG("\n ******** event->button: %d\n", event->button);
                    break;
                case 3:
                    DEBUG("\n ******** event->button: %d\n", event->button);
                    break;
                default:
                    DEBUG("\n ******** event->button is invalid\n");
                    break;
                }
            }
            else if(event->type == GDK_BUTTON_PRESS)
            {
                switch(event->button)
                {
                case 1:
                    DEBUG("\n ******** event->button: %d\n", event->button);
                    break;
                case 2:
                    DEBUG("\n ******** event->button: %d\n", event->button);
                    break;
                case 3:
                    DEBUG("\n ******** event->button: %d\n", event->button);

                    gint row_type;
                    gtk_tree_model_get(GTK_TREE_MODEL(model), &iter, SCHEDULE_TYPE_COLUMN, &row_type, -1);

                    DEBUG("\n\n - Type of row is: %d", row_type);

                    switch(row_type)
                    {
                    case SCHEDULE_MONTH_COL_INDEX:
                        //bot_schedule_day_popup_menu_show(treeview, event, NULL);
                        break;
                    case SCHEDULE_NAME_COL_INDEX:
                        //bot_schedule_list_popup_menu_show(treeview, event, NULL);
                        break;
                    case SCHEDULE_CONTENT_COL_INDEX:
//                        bot_schedule_item_popup_menu_show(treeview, event, NULL);
                        break;
                    default:
                        break;
                    };

                    break;
                default:
                    DEBUG("\n ******** event->button is invalid\n");
                    break;
                }
            }
        }
    }
    return FALSE;
}


gboolean
on_bot_schedule_item_specical_clicked(GtkTreeView        *treeview,
                                                    GdkEventButton     *event,
                                                    gpointer           userdata)
{
    if (event->type == GDK_2BUTTON_PRESS || event->type == GDK_BUTTON_PRESS)
    {
        GtkTreeIter      iter;
        GtkTreeModel     *model;
        GtkTreeSelection *selection;


        selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));

        if (gtk_tree_selection_count_selected_rows(selection)  <= 1)
        {
            GtkTreePath *path;
            if (gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(treeview), (gint) event->x, (gint) event->y, &path, NULL, NULL, NULL))
            {
                gtk_tree_selection_unselect_all(selection);
                gtk_tree_selection_select_path(selection, path);
                gtk_tree_path_free(path);
            }
        }
        else
        {
            return FALSE;
        }

        if(gtk_tree_selection_get_selected(selection, &model, &iter))
        {
            if(event->type == GDK_2BUTTON_PRESS)
            {
                switch(event->button)
                {
                case 1:
                    DEBUG("\n ******** event->button: %d\n", event->button);
                    break;
                case 2:
                    DEBUG("\n ******** event->button: %d\n", event->button);
                    break;
                case 3:
                    DEBUG("\n ******** event->button: %d\n", event->button);
                    break;
                default:
                    DEBUG("\n ******** event->button is invalid\n");
                    break;
                }
            }
            else if(event->type == GDK_BUTTON_PRESS)
            {
                switch(event->button)
                {
                case 1:
                    DEBUG("\n ******** event->button: %d\n", event->button);
                    break;
                case 2:
                    DEBUG("\n ******** event->button: %d\n", event->button);
                    break;
                case 3:
                    DEBUG("\n ******** event->button: %d\n", event->button);

                    gint row_type;
                    gtk_tree_model_get(GTK_TREE_MODEL(model), &iter, ITEM_SCHEDULE_TYPE_COLUMN, &row_type, -1);

                    DEBUG("\n\n - Type of row is: %d", row_type);

                    switch(row_type)
                    {
                    case SCHEDULE_MONTH_COL_INDEX:
                        break;
                    case SCHEDULE_NAME_COL_INDEX:
                        //bot_schedule_item_name_popup_menu_show(treeview, event, NULL);
                        break;
                    case SCHEDULE_CONTENT_COL_INDEX:
                        //bot_schedule_item_content_popup_menu_show(treeview, event, NULL);
                        break;
                    default:
                        break;
                    };

                    break;
                default:
                    DEBUG("\n ******** event->button is invalid\n");
                    break;
                }
            }
        }
    }
    return FALSE;
}

#if 0
gboolean on_bot_program_year_treeview_clicked(GtkTreeView *treeview, GdkEventButton *event, gpointer userdata)
{
    if (event->type == GDK_2BUTTON_PRESS || event->type == GDK_BUTTON_PRESS)
    {
        GtkTreeIter      iter;
        GtkTreeModel     *model;
        GtkTreeSelection *selection;
        selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
        if (gtk_tree_selection_count_selected_rows(selection)  <= 1)
        {
            GtkTreePath *path;
            if (gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(treeview), (gint) event->x, (gint) event->y, &path, NULL, NULL, NULL))
            {
                gtk_tree_selection_unselect_all(selection);
                gtk_tree_selection_select_path(selection, path);
                gtk_tree_path_free(path);
            }
        }
        else
        {
            return FALSE;
        }
        if(gtk_tree_selection_get_selected(selection, &model, &iter))
        {
            if(event->type == GDK_2BUTTON_PRESS)
            {
                switch(event->button)
                {
                case 1:
                    DEBUG("\n ******** 2 event->button: %d\n", event->button);
                    gint program_id;
                    gint type_column;

                    gtk_tree_model_get(GTK_TREE_MODEL(model), &iter, PROGRAM_TYPE_COLUMN, &type_column, -1);

                    DEBUG("type_column: %d", type_column);
                    if(type_column!=PROGRAM_NAME_COL_INDEX)
                    {
                        gtk_tree_model_get(GTK_TREE_MODEL(model), &iter, PROGRAM_ID_COLUMN, &program_id, -1);
                        bot_program_year_show_specific(program_id);
                    }
                    break;
                case 2:
                    DEBUG("\n ******** 2 event->button: %d\n", event->button);
                    break;
                case 3:
                    DEBUG("\n ******** 2 event->button: %d\n", event->button);
                    break;
                default:
                    DEBUG("\n ******** 2 event->button is invalid\n");
                    break;
                }
            }
            else if(event->type == GDK_BUTTON_PRESS)
            {
                switch(event->button)
                {
                case 1:
                    DEBUG("\n ******** 1 event->button: %d\n", event->button);
                    break;
                case 2:
                    DEBUG("\n ******** 1 event->button: %d\n", event->button);
                    break;
                case 3:
                    DEBUG("\n ******** 1 event->button: %d\n", event->button);
                    gint program_id;
                    gint type_column;

                    gtk_tree_model_get(GTK_TREE_MODEL(model), &iter, PROGRAM_TYPE_COLUMN, &type_column, -1);

                    DEBUG("type_column: %d", type_column);
                    if(type_column!=PROGRAM_NAME_COL_INDEX)
                    {
                        bot_program_popup_menu_show(treeview, event, userdata);
                        /** Tai sao lai roi ham nay o vi tri nay ??? **/
//                        bot_program_year_show_specific(program_id);
                    }
                    else
                    {
                        bot_program_year_show_specific(program_id);
                    }
                    break;
                default:
                    DEBUG("\n ******** 1 event->button is invalid\n");
                    break;
                }
            }
        }
    }
    return FALSE;
}


gboolean
on_bot_program_year_treeview_clicked (GtkTreeView        *treeview,
                                                    GdkEventButton     *event,
                                                    gpointer           userdata)
{
    if (event->type == GDK_2BUTTON_PRESS || event->type == GDK_BUTTON_PRESS)
    {
        GtkTreeIter      iter;
        GtkTreeModel     *model;
        GtkTreeSelection *selection;

        selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));

        if (gtk_tree_selection_count_selected_rows(selection)  <= 1)
        {
            GtkTreePath *path;
            if (gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(treeview), (gint) event->x, (gint) event->y, &path, NULL, NULL, NULL))
            {
                gtk_tree_selection_unselect_all(selection);
                gtk_tree_selection_select_path(selection, path);
                gtk_tree_path_free(path);
            }
        }
        else
        {
            return FALSE;
        }

        if(gtk_tree_selection_get_selected(selection, &model, &iter))
        {
            if(event->type == GDK_2BUTTON_PRESS)
            {
                switch(event->button)
                {
                case 1:
                    DEBUG("\n ******** 2 event->button: %d\n", event->button);
                    gint program_id;
                    gint type_column;

                    gtk_tree_model_get(GTK_TREE_MODEL(model), &iter, PROGRAM_TYPE_COLUMN, &type_column, -1);

                    DEBUG("type_column: %d", type_column);
                    if(type_column!=PROGRAM_NAME_COL_INDEX)
                    {
                        gtk_tree_model_get(GTK_TREE_MODEL(model), &iter, PROGRAM_ID_COLUMN, &program_id, -1);
                        bot_program_year_show_specific(program_id);
                    }

                    break;
                case 2:
                    DEBUG("\n ******** 2 event->button: %d\n", event->button);
                    break;
                case 3:
                    DEBUG("\n ******** 2 event->button: %d\n", event->button);
                    break;
                default:
                    DEBUG("\n ******** 2 event->button is invalid\n");
                    break;
                }
                return TRUE;
            }
            else if(event->type == GDK_BUTTON_PRESS)
            {
                switch(event->button)
                {
                case 1:
                    DEBUG("\n ******** 1 event->button: %d\n", event->button);
                    break;
                case 2:
                    DEBUG("\n ******** 1 event->button: %d\n", event->button);
                    break;
                case 3:
                    DEBUG("\n ******** 1 event->button: %d\n", event->button);
                    gint program_id;
                    gint type_column;

                    gtk_tree_model_get(GTK_TREE_MODEL(model), &iter, PROGRAM_TYPE_COLUMN, &type_column, -1);

                    DEBUG("type_column: %d", type_column);
                    if(type_column!=PROGRAM_NAME_COL_INDEX)
                    {
                        bot_program_popup_menu_show(treeview, event, userdata);
                        /** Tai sao lai roi ham nay o vi tri nay ??? **/
//                        bot_program_year_show_specific(program_id);
                    }
                    else
                    {
                        bot_program_year_show_specific(program_id);
                    }
                    break;
                default:
                    DEBUG("\n ******** 1 event->button is invalid\n");
                    break;
                }
            }
        }
    }
    return FALSE;
}
#endif // 0

gboolean on_bot_main_notebook_switch_page (GtkNotebook *notebook,
                                               GtkWidget   *page,
                                               guint        page_num,
                                               gpointer     user_data)
{
    DEBUG("=============== page_num: %d", page_num);

    bot_NOTEBOOK_PAGE_Enum page_index = (bot_NOTEBOOK_PAGE_Enum) page_num;

    switch(page_index)
    {
    case bot_NOTEBOOK_DCU_PAGE:
        if(is_changed_map_parent_by_admin_zone)
        {
            if(bot_dcu_info_show_tab_on_notebook())
                is_changed_map_parent_by_admin_zone = FALSE;
        }
        break;
    case bot_NOTEBOOK_PROGRAM_PAGE:
        break;
    case bot_NOTEBOOK_USER_LOG_PAGE:
        bot_user_log_show_all();
        break;
    case bot_NOTEBOOK_SERVER_LOG_PAGE:
        bot_server_log_show_all();
        break;
    case bot_NOTEBOOK_USER_MANAGE_PAGE:
        break;
    case bot_NOTEBOOK_ZONE_MANAGE_PAGE:
        if(bot_admin_zone_show_tab_on_notebook())
            is_changed_map_parent_by_admin_zone = TRUE;
        break;
    default:
        break;
    };
    if(!page)
        return FALSE;
    gchar *newTitle = g_strdup_printf("bot-%s", gtk_notebook_get_tab_label_text(notebook, page));
    gtk_window_set_title(GTK_WINDOW(main_widgets->main_window), newTitle);
    return FALSE;
}


gboolean on_bot_dcu_program_modified_clicked(GtkButton *button, gpointer userdata)
{
    gtk_widget_set_sensitive(GTK_WIDGET(bot_OBJECT("dcu_info_mode_combobox")), TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(bot_OBJECT("dcu_info_program_combobox")), TRUE);

    gtk_widget_set_visible(GTK_WIDGET(bot_OBJECT("dcu_program_reload_btn")), TRUE);
    gtk_widget_set_visible(GTK_WIDGET(bot_OBJECT("dcu_program_update_btn")), TRUE);

    const gchar *current_dcu_id = gtk_label_get_text(GTK_LABEL(gtk_builder_get_object (bot_builder, "lb_dcu_id")));
//    bot_program_change(current_dcu_id);
}

gboolean on_bot_dcu_info_modified_clicked(GtkButton *button, gpointer userdata)
{
   // bot_dcu_info_edit();
}

void on_bot_dcu_combobox_modified_clicked (GtkComboBox *widget, gpointer user_data)
{
    gtk_widget_set_sensitive(GTK_WIDGET(bot_OBJECT("dcu_program_update_btn")), TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(bot_OBJECT("dcu_program_reload_btn")), TRUE);
}

void on_bot_lcu_control_mode_combobox_modified_clicked (GtkComboBox *widget, gpointer user_data)
{
//    bot_lcu_control_mode_combobox_change();
}

void
on_bot_schedule_timeon_on_change (GtkAdjustment *adjustment,
                                                  gpointer       user_data)
{
    DEBUG("\n === change value is: %d", gtk_adjustment_get_value(adjustment));
}

gboolean
on_bot_login_custom_expander  (GtkWidget *widget,
                                            GdkEvent  *event,
                                            gpointer   user_data)
{
    /*
    if(gtk_expander_get_expanded(GTK_EXPANDER(bot_OBJECT("login_custom_expander"))))
    {
        DEBUG_1();
    }
    else
    {
        DEBUG_1();
    }
    */
    return TRUE;
}
void bot_dcu_popup_menu_clicked(GtkWidget *popup_menu_item, gpointer userdata)
{
    bot_DCU_POPUP_MENU_Enum type = (bot_DCU_POPUP_MENU_Enum)GPOINTER_TO_INT(userdata);
    switch(type)
    {
    case bot_DCU_M_ADD:
        gboolean add_result;
        do
        {
            add_result = bot_dcu_add_new();
            add_result = TRUE;
        }
        while(!add_result);
        break;
    case bot_DCU_M_EDIT:
        bot_dcu_edit(lastSelectedDcu);
        break;
    case bot_DCU_M_LOG:
        bot_dcu_view_log(lastSelectedDcu);
        //bot_dcu_popup_menu_log_clicked();
        break;
    case bot_DCU_M_SCHEDULE:
        bot_dcu_control_dialog_show(DIALOG_CONTROL_IS_SCHEDULE, lastSelectedDcu);
        break;
    case bot_DCU_M_REMOVE:
        {
            GtkWidget *parent = stack_widget_active_top();
            switch(bot_QUESTION_POPUP(parent, "Bạn có chắc muốn xóa trạm này, tất cả các đèn thuộc trạm này sẽ bị xóa"))
            {
                case GTK_RESPONSE_OK:
                {
                    if(lastSelectedDcu)
                    {
                        pbotDcu dcuRemove = lastSelectedDcu;
                        botSoap bot_soap;
                        gint soap_err = bot_remove_dcu_execute(&bot_soap,dcuRemove->priv->id);
                        if(soap_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
                        {
                            //clear this dcu on treeview
                            if(gtk_tree_store_remove(main_view_widgets->dcu_store, &dcuRemove->priv->iter))
                            {
                                bot_delete_all_lcu_on_dcu(dcuRemove); //delete all his child
                                REMOVE_LIST_DCU(dcuRemove);
                            }
                        } else
                        {
                            gchar * msg = g_strconcat("Lỗi xoá trạm có id là ", dcuRemove->priv->id,". ", NULL);
                            GtkWidget *parent = stack_widget_active_top();
                            bot_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
                            g_char_free(msg);
                        }
                    }
                    DEBUG("OK\n");
                }
                break;
                case GTK_RESPONSE_CANCEL:
                    DEBUG("CANCEL\n");
                default:
                    break;
            }
        }
        //bot_dcu_popup_menu_remove_clicked();
        break;
    case bot_DCU_M_REMOVE_ALL:
        //bot_dcu_popup_menu_remove_all_clicked();
        break;
    case bot_DCU_M_CONTROL:
        bot_dcu_control_dialog_show(DIALOG_CONTROL_IS_ON_OFF, lastSelectedDcu);
        //bot_dcu_control_dialog_show(DIALOG_CONTROL_IS_SETTING);
        break;
    default:
        break;
    }
}

void bot_lcu_popup_menu_clicked(GtkWidget *w, gpointer usr_data)
{
    gint type = GPOINTER_TO_INT(usr_data);
    switch(type)
    {
        case bot_LCU_M_ADD:
            bot_light_add_new_request();
            break;
        case bot_LCU_M_ADD_FROM_FILE:
            //bot_light_add_new_from_file();
            break;
        case bot_LCU_M_EDIT:
            bot_light_edit(lastSelectedLcu);
            break;
        case bot_LCU_M_REMOVE:
            bot_light_remove_request(lastSelectedLcu);
            break;
        case bot_LCU_M_REMOVE_ALL:
            //if(xoa all lcu on dcuID)
            {
                lastSelectedLcu = NULL;
                osm_osm_gps_map_remove_dcu(lastSelectedDcu);
                bot_delete_all_lcu_on_dcu(lastSelectedDcu);
            }
            break;
        case bot_LCU_M_CONTROL:
            bot_lcu_popup_menu_control(lastSelectedLcu);
            break;
        case bot_LCU_M_LOCATION:
            g_return_if_fail(lastSelectedLcu);
            ObjMove->object = lastSelectedLcu;
            ObjMove->image = lastSelectedLcu->icon;
            ObjMove->type = OBJECT_IS_LCU_TYPE;
            osm_gps_map_move_object();
            break;
        case bot_LCU_M_CHART:
            bot_light_chart_show(lastSelectedLcu);
            break;
        default:
            break;
    }
}

void bot_popup_menu_show(GtkWidget *w, GdkEventButton *ev)
{
    gtk_widget_show_all(w);
    gtk_menu_popup(GTK_MENU(w), NULL, NULL, NULL, NULL,
                   (ev != NULL) ? ev->button : 0, gdk_event_get_time((GdkEvent*)ev));

}


gboolean
on_bot_current_username_login_activate(GtkLabel *label,
                                                    gchar    *uri,
                                                    gpointer  user_data)
{
    DEBUG_1();
    bot_current_account_show();
}

gboolean bot_login_key_event(GtkWidget    *widget,
                             GdkEventKey  *event,
                             gpointer     user_data)
{
//    if(event->keyval == ENTER_KEY_VALUE)
//    {
//        DEBUG_1();
//        gtk_dialog_response(GTK_DIALOG(main_widgets->login_dialog), (gint)DIALOG_OK_RESPONSE);
//        DEBUG_1();
//    }
    return FALSE;
}

void on_dcu_control_btn_clicked (GtkButton *button, gpointer user_data)
{
    gboolean select = TRUE;
    switch(GPOINTER_TO_INT(user_data))
    {
    case DIALOG_CONTROL_BTN_DESELECT_ALL:
        select = FALSE;
    case DIALOG_CONTROL_BTN_SELECT_ALL:
        bot_dcu_control_set_all_selected(select);
        bot_dcu_control_spl_light_on_map();
        break;
    case DIALOG_MANUAL_SUBMIT_SET:
        /* get information on form control then send to server */
        bot_dcu_control_execute();
        break;
    case DIALOG_CONTROL_BTN_QUIT:
        osm_gps_map_change_parent("dcu_control_osm_map_box", "map_box");
        osm_osm_gps_map_show_lights(gtk_combo_box_get_active(GTK_COMBO_BOX(cbb_light_spl)),lastSelectedDcu);
        bot_DIALOG_HIDE(dcu_control_schedule_widgets->dcu_control_window);
        gtk_widget_hide_on_delete(dcu_control_schedule_widgets->dcu_control_window);
        isControlShow = FALSE;
        //set treeview into container box
        {
            GtkWidget *boxtreeview = GTK_WIDGET(bot_OBJECT("dcu_control_box_treeview"));
            GtkWidget *boxsetlight = GTK_WIDGET(bot_OBJECT("dcu_control_box_set_light"));
            GtkWidget *parent = gtk_widget_get_parent(boxtreeview);
            GtkWidget *boxcontaintreeview = GTK_WIDGET(bot_OBJECT("dcu_control_box_contain_tree_view"));
            if(parent == boxsetlight)
            {
                GtkWidget *p = GTK_WIDGET(g_object_ref((gpointer)boxtreeview));
                gtk_container_remove(GTK_CONTAINER(boxsetlight), boxtreeview);
                gtk_box_pack_start(GTK_BOX(boxcontaintreeview), p, TRUE, TRUE, 0);
            }
        }
        break;
    case DIALOG_SCHEDULE_SUBMIT_SET:
        bot_dcu_schedule_setting();
        break;
    }
}


gboolean mouse_moved(GtkWidget *widget,GdkEvent *event, gpointer user_data)
{
    OsmGpsMapPoint coord;
    float lat, lon;
    OsmGpsMapImage *im;
    if (event->type==GDK_MOTION_NOTIFY) {
        //printf("Coordinates: (%u,%u)\n", (guint)e->x,(guint)e->y);
        GdkEventMotion* e=(GdkEventMotion*)event;
        //DEBUG("e->type: %d e->state: %d\n", e->type, e->state);
        if(e->state == GDK_BUTTON1_MASK)
        {
            gchar *latStr, *lonStr;
            osm_gps_map_convert_screen_to_geographic(map, e->x, e->y, &coord);
            osm_gps_map_point_get_degrees(&coord, &ObjMove->lat, &ObjMove->lon);
            latStr = g_strdup_printf("%f", ObjMove->lat);
            lonStr = g_strdup_printf("%f", ObjMove->lon);
            gtk_entry_set_text(ObjMove->lat_entry, latStr);
            gtk_entry_set_text(ObjMove->lon_entry, lonStr);

            osm_gps_map_redraw_object();
            printf("Coordinates: (%u,%u)\n", (guint)e->x,(guint)e->y);
        }
    }
}


gboolean on_gps_entry_changed_text(GtkEntry *entry, GdkEventKey *event, gpointer userdata)
{
    switch(event->keyval)
    {
    case GDK_KEY_Return:
        {
            gint    i = 0;
            gfloat  partOfPoint;
            gchar   *text = (gchar*)gtk_entry_get_text(entry);
            for( ; i < strlen(text); i++)
            {
                gchar c = text[i];
                if( !g_ascii_isdigit(c) && c != '.')
                {
                    goto __wrong_format;
                }
            }
            if(sscanf(text, "%f", &partOfPoint) != 1)
            {
__wrong_format:
                bot_WARNING_POPUP(GTK_WINDOW(ObjMove->dialog), "Tọa độ không đúng định dạng");
                return FALSE;
            }
            switch(GPOINTER_TO_INT(userdata))
            {
            case 0:
                ObjMove->lat = partOfPoint;
                break;
            case 1:
                ObjMove->lon = partOfPoint;
                break;
            }
            osm_gps_map_redraw_object();
            osm_gps_map_set_center(map, ObjMove->lat, ObjMove->lon);
        }
        break;
    default:
        return FALSE;
    }
    return FALSE;
}
