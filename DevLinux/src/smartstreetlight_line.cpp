#include "smartstreetlight_line.h"
#include "smartstreetlight_ui_method.h"
#include "smartstreetlight_soap.h"
#include "smartstreetlight_login.h"
#include "smartstreetlight_error.h"



GtkTreeView *line_info_tree_view;
GtkListStore *line_info_list_store;

struct SPL_LINE_POPUP_MENU *line_info_popup_menu = NULL;

static gboolean smartstreetlight_line_tree_view_init(void);

static gboolean smartstreetlight_line_list_store_init(void);

static gboolean smartstreetlight_line_callback_init(void);

static gboolean smartstreetlight_lcu_popup_menu_init(void);

static void smartstreetlight_line_popup_menu_widget_init(void);

static void smartstreetlight_line_popup_menu_callback_init(void);

static void smartstreetlight_line_popup_menu_clicked(GtkWidget *popup_menu_item, gpointer userdata);

static gboolean smartstreetlight_line_popup_menu_add_clicked(void);

static void smartstreetlight_line_popup_menu_remove_clicked(void);

static void smartstreetlight_line_popup_menu_remove_all_clicked(void);
/** *********************************************************************************************** **/

static gboolean smartstreetlight_line_popup_menu_add_clicked(void)
{
    DEBUG_1();
    DEBUG("===== ENTER ADD LINE =====");

    gboolean exit_here = FALSE;

    GtkWidget *add_line_combobox_id = GTK_WIDGET(SPL_OBJECT("add_line_combobox_id"));
    GtkWidget *add_line_entry_note = GTK_WIDGET(SPL_OBJECT("add_line_entry_note"));
    GtkWidget *add_line_combobox_mode = GTK_WIDGET(SPL_OBJECT("add_line_combobox_mode"));

    GtkWidget *add_line_label_error = GTK_WIDGET(SPL_OBJECT("add_line_label_error"));

    gtk_widget_set_sensitive(GTK_WIDGET(main_widgets->main_window), FALSE);
    gint response_id;

    const gchar *line_dcuid = gtk_label_get_text(GTK_LABEL(SPL_OBJECT("lb_dcu_id")));
    gint line_id = gtk_combo_box_get_active(GTK_COMBO_BOX(add_line_combobox_id)) + 1;


    switch(response_id)
    {

        case DIALOG_OK_RESPONSE:
            gint line_mode;
            if(line_id==0)
            {
                gtk_label_set_text(GTK_LABEL(add_line_label_error), "Thông tin mã LINE không được để trống!");
            }
            else
            {
                line_mode = gtk_combo_box_get_active(GTK_COMBO_BOX(add_line_combobox_mode));
                if(line_mode == -1)
                {
                    gtk_label_set_text(GTK_LABEL(add_line_label_error), "Xin chọn mode hoạt động cho LCU.");
                }
                else
                {
                    struct ns1__LINE_USCOREINFO_USCOREType line_info;
                    SplSoap spl_soap;
                    line_info.line_USCOREid = line_id;
                    line_info.line_USCOREdcuid = g_strdup(line_dcuid);
                    line_info.line_USCOREnote = g_strdup(gtk_entry_get_text(GTK_ENTRY(add_line_entry_note)));
                    line_info.line_USCOREmode = line_mode;
                    gint soap_err = smartstreetlight_add_line_execute(&spl_soap,&line_info);
                    if (soap_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
                    {
                        DEBUG_1();
                        smartstreetlight_line_fill_infomation(line_info.line_USCOREid,
                                          line_info.line_USCOREdcuid,
                                          g_strdup_printf("%d", line_info.line_USCOREstatus),
                                          line_info.line_USCOREnote,
                                          g_strdup_printf("%d", line_info.line_USCOREmode),
                                          g_strdup_printf("%d", line_info.line_USCOREison),
                                          g_strdup_printf("%d", line_info.line_USCOREcurrent)
                                          );
                        DEBUG("\n Add LCU is OK !!\n");
                    } else {
                        gchar * line_id_str = g_strdup_printf("%i", line_info.line_USCOREid);
                        gchar * msg = g_strconcat("Lỗi thêm cổng điều khiển đèn có id là ", line_id_str," vào trạm có id là ", line_info.line_USCOREdcuid, ". ", NULL);
                        GtkWidget *parent = stack_widget_active_top();
                        smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
                        g_char_free(msg);
                        g_char_free(line_id_str);
                    }
                    g_char_free(line_info.line_USCOREdcuid);
                    g_char_free(line_info.line_USCOREnote);
                    exit_here = TRUE;
                }


            }
            break;
        case DIALOG_CANCEL_RESPONSE:
            exit_here = TRUE;
            break;
        default:
            break;
	}

    if(exit_here)
    {
        gtk_entry_set_text(GTK_ENTRY(add_line_entry_note), "");
        gtk_label_set_text(GTK_LABEL(add_line_label_error), "");

        gtk_combo_box_set_active(GTK_COMBO_BOX(add_line_combobox_id), -1);
        gtk_combo_box_set_active(GTK_COMBO_BOX(add_line_combobox_mode), -1);

    }
//    gtk_widget_hide(main_widgets->add_line_dialog);
    gtk_widget_set_sensitive(GTK_WIDGET(main_widgets->main_window), TRUE);
    return exit_here;
}

static void smartstreetlight_line_popup_menu_remove_clicked(void)
{
    DEBUG_1();
    DEBUG("===== ENTER REMOVE LINE =====");

    GtkTreeIter      iter;
    GtkTreeModel     *model;
    GtkTreeSelection *selection;

    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(line_info_tree_view));

    if (gtk_tree_selection_count_selected_rows(selection)  == 1)
    {
        if(gtk_tree_selection_get_selected(selection, &model, &iter))
        {
            gint line_id;
            gchar *line_dcuid;
            SplSoap spl_soap;
            gtk_tree_model_get(GTK_TREE_MODEL(model), &iter, LINE_ID_COLUMN   , &line_id,
                                                             LINE_DCUID_COLUMN, &line_dcuid,
                                                             -1);

            gtk_label_set_text(GTK_LABEL(SPL_OBJECT("delete_dialog_label")), "Xóa LINE với mã sau:");
            gtk_label_set_text(GTK_LABEL(SPL_OBJECT("delete_element_id")), g_strdup_printf("%d", line_id));

            SPL_DIALOG_SHOW(main_widgets->delete_element_dialog);
            gint response_id = gtk_dialog_run((GtkDialog *)main_widgets->delete_element_dialog);
            switch(response_id)
            {
                case DIALOG_OK_RESPONSE:
                {
                   gint soap_err = smartstreetlight_remove_line_execute(&spl_soap,
                                                           line_id,
                                                           line_dcuid);
                   if(soap_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
                    {
                        gtk_list_store_remove(GTK_LIST_STORE(model), &iter);
                    } else {
                        gchar * line_id_str = g_strdup_printf("%i", line_id);
                        gchar * msg = g_strconcat("Lỗi xoá cổng điều khiển có id là ", line_id_str," của trạm có id là ", line_dcuid, ". ", NULL);
                        GtkWidget *parent = stack_widget_active_top();
                        smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
                        g_char_free(msg);
                        g_char_free(line_id_str);
                    }

                }
                     break;
                case DIALOG_CANCEL_RESPONSE:

                    break;
                default:
                    break;
            }
            SPL_DIALOG_HIDE(main_widgets->delete_element_dialog);
            g_free(line_dcuid);
        }
    }
}

static void smartstreetlight_line_popup_menu_remove_all_clicked(void)
{
    DEBUG_1();
    DEBUG("===== ENTER REMOVE ALL LINE =====");
}

static void smartstreetlight_line_popup_menu_clicked(GtkWidget *popup_menu_item, gpointer userdata)
{
    SPL_LINE_POPUP_MENU_Enum type = (SPL_LINE_POPUP_MENU_Enum)GPOINTER_TO_INT(userdata);
    switch(type)
    {
    case SPL_LINE_M_ADD:
        smartstreetlight_line_popup_menu_add_clicked();
        break;
    case SPL_LINE_M_REMOVE:
        smartstreetlight_line_popup_menu_remove_clicked();
        break;
    case SPL_LINE_M_REMOVE_ALL:
        smartstreetlight_line_popup_menu_remove_all_clicked();
        break;
    default:
        break;
    }
}
static void smartstreetlight_line_popup_menu_widget_init(void)
{
    GtkWidget *separator_item;
    line_info_popup_menu->M_Popup = gtk_menu_new();
    SPL_MENU_CSS(line_info_popup_menu->M_Popup);

    line_info_popup_menu->M_Add = gtk_menu_item_new_with_label("Thêm mới");
    gtk_menu_shell_append(GTK_MENU_SHELL(line_info_popup_menu->M_Popup),line_info_popup_menu->M_Add);

    separator_item = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(line_info_popup_menu->M_Popup), separator_item);

    line_info_popup_menu->M_Remove= gtk_menu_item_new_with_label("Xóa");
    gtk_menu_shell_append(GTK_MENU_SHELL(line_info_popup_menu->M_Popup),line_info_popup_menu->M_Remove);

    line_info_popup_menu->M_Remove_all = gtk_menu_item_new_with_label("Xóa tất cả");
    gtk_menu_shell_append(GTK_MENU_SHELL(line_info_popup_menu->M_Popup),line_info_popup_menu->M_Remove_all);
}

static void smartstreetlight_line_popup_menu_callback_init(void)
{
    g_signal_connect(line_info_popup_menu->M_Add, "activate",
                     (GCallback) smartstreetlight_line_popup_menu_clicked, GINT_TO_POINTER(SPL_LINE_M_ADD));

    g_signal_connect(line_info_popup_menu->M_Remove, "activate",
                     (GCallback) smartstreetlight_line_popup_menu_clicked, GINT_TO_POINTER(SPL_LINE_M_REMOVE));

    g_signal_connect(line_info_popup_menu->M_Remove_all, "activate",
                     (GCallback) smartstreetlight_line_popup_menu_clicked, GINT_TO_POINTER(SPL_LINE_M_REMOVE_ALL));
}

static gboolean smartstreetlight_lcu_popup_menu_init(void)
{
    line_info_popup_menu = g_new0(struct SPL_LINE_POPUP_MENU, 1);

    smartstreetlight_line_popup_menu_widget_init();
    smartstreetlight_line_popup_menu_callback_init();

    return TRUE;
}

static gboolean smartstreetlight_line_tree_view_init(void)
{
    GtkTreeViewColumn   *line_list_column;
    GtkCellRenderer     *line_list_renderer;

    line_info_tree_view = GTK_TREE_VIEW(gtk_builder_get_object (smartstreetlight_builder, "line_info_tree_view"));

    line_list_renderer = gtk_cell_renderer_toggle_new();
    line_list_column = gtk_tree_view_column_new_with_attributes ("", line_list_renderer, "active", LINE_CHECKBOX_COLUMN, NULL);
    gtk_tree_view_append_column (GTK_TREE_VIEW(line_info_tree_view), line_list_column);

    line_list_renderer = gtk_cell_renderer_text_new();
    line_list_column = gtk_tree_view_column_new_with_attributes("Mã:", line_list_renderer, "text", LINE_ID_COLUMN, NULL);
    gtk_tree_view_column_set_resizable(line_list_column,TRUE);
    gtk_tree_view_column_set_reorderable(line_list_column, TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(line_info_tree_view), line_list_column);

    line_list_renderer = gtk_cell_renderer_text_new();
    line_list_column = gtk_tree_view_column_new_with_attributes("Mã DCU Quản Lý:", line_list_renderer, "text", LINE_DCUID_COLUMN, NULL);
    gtk_tree_view_column_set_resizable(line_list_column,TRUE);
    gtk_tree_view_column_set_reorderable(line_list_column, TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(line_info_tree_view), line_list_column);

    line_list_renderer = gtk_cell_renderer_text_new();
    line_list_column = gtk_tree_view_column_new_with_attributes("Trạng Thái:", line_list_renderer, "text", LINE_STATUS_COLUMN, NULL);
    gtk_tree_view_column_set_resizable(line_list_column,TRUE);
    gtk_tree_view_column_set_reorderable(line_list_column, TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(line_info_tree_view), line_list_column);

    line_list_renderer = gtk_cell_renderer_text_new();
    line_list_column = gtk_tree_view_column_new_with_attributes("Ghi Chú:", line_list_renderer, "text", LINE_NOTE_COLUMN, NULL);
    gtk_tree_view_column_set_resizable(line_list_column,TRUE);
    gtk_tree_view_column_set_reorderable(line_list_column, TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(line_info_tree_view), line_list_column);

    line_list_renderer = gtk_cell_renderer_text_new();
    line_list_column = gtk_tree_view_column_new_with_attributes("Chế Độ Hoạt Động", line_list_renderer, "text", LINE_MODE_COLUMN, NULL);
    gtk_tree_view_column_set_resizable(line_list_column,TRUE);
    gtk_tree_view_column_set_reorderable(line_list_column, TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(line_info_tree_view), line_list_column);

    line_list_renderer = gtk_cell_renderer_text_new();
    line_list_column = gtk_tree_view_column_new_with_attributes("Online", line_list_renderer, "text", LINE_ISON_COLUMN, NULL);
    gtk_tree_view_column_set_resizable(line_list_column,TRUE);
    gtk_tree_view_column_set_reorderable(line_list_column, TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(line_info_tree_view), line_list_column);

    line_list_renderer = gtk_cell_renderer_text_new();
    line_list_column = gtk_tree_view_column_new_with_attributes("Dòng Điện", line_list_renderer, "text", LINE_CURRENT_COLUMN, NULL);
    gtk_tree_view_column_set_resizable(line_list_column,TRUE);
    gtk_tree_view_column_set_reorderable(line_list_column, TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(line_info_tree_view), line_list_column);

    return TRUE;
}

static gboolean smartstreetlight_line_list_store_init(void)
{
    line_info_list_store = gtk_list_store_new(LINE_NUM_COLUMNS,
                                            G_TYPE_BOOLEAN,
                                            G_TYPE_INT,
                                            G_TYPE_STRING,
                                            G_TYPE_STRING,
                                            G_TYPE_STRING,
                                            G_TYPE_STRING,
                                            G_TYPE_STRING,
                                            G_TYPE_STRING);

    gtk_tree_view_set_model(GTK_TREE_VIEW(line_info_tree_view), GTK_TREE_MODEL(line_info_list_store));
    g_object_unref(line_info_list_store);

    return TRUE;
}

gboolean smartstreetlight_line_info_init(void)
{
    DEBUG("\n\n*************************** ENTER smartstreetlight_lcu_info_init!! *******************\n\n");
    DEBUG_1();


    if(smartstreetlight_line_tree_view_init())
    {
        if (smartstreetlight_line_list_store_init())
        {
            if(smartstreetlight_line_callback_init())
            {
                if(smartstreetlight_lcu_popup_menu_init())
                {
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

void smartstreetlight_line_show_list(gchar *dcu_id)
{
    ns1__LINE_USCOREINFO_USCOREType **line_list=NULL;
    SplSoap spl_soap;
    gint line_list_size;
    DEBUG_1();
    gint soap_err = smartstreetlight_get_line_list_nofree_execute(&spl_soap,dcu_id, &line_list, &line_list_size);
    if (soap_err==ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
    {


        smartstreetlight_line_liststore_clean();
        if (line_list==NULL)
        {
            for(gint i = 0; i<line_list_size; i++)
            {
                ns1__LINE_USCOREINFO_USCOREType *line = line_list[i];
                smartstreetlight_line_fill_infomation(line->line_USCOREid,
                                              line->line_USCOREdcuid,
                                              g_strdup_printf("%d", line->line_USCOREstatus),
                                              line->line_USCOREnote,
                                              g_strdup_printf("%d", line->line_USCOREmode),
                                              g_strdup_printf("%d", line->line_USCOREison),
                                              g_strdup_printf("%d", line->line_USCOREcurrent)
                                              );
            }
        }

    }
    else
    {
        gchar * msg = g_strdup("Lỗi lấy danh sách cổng điều khiển đèn từ server. ");
        GtkWidget *parent = stack_widget_active_top();
        smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
        g_char_free(msg);
    }
    smartstreetlight_free_soap_operation(&spl_soap);
}


void smartstreetlight_line_liststore_clean(void)
{
    smartstreetlight_clear_list_store(GTK_TREE_MODEL(line_info_list_store));
}


void smartstreetlight_line_fill_infomation(gint line_name,
                                           gchar *line_dcuid,
                                           gchar *line_status,
                                           gchar *line_note,
                                           gchar *line_mode,
                                           gchar *line_ison,
                                           gchar *line_current
                                           )
{
    GtkTreeIter iter;
    gtk_list_store_append(line_info_list_store, &iter);
    gtk_list_store_set(line_info_list_store, &iter, LINE_CHECKBOX_COLUMN,  FALSE,
                                                   LINE_ID_COLUMN,         line_name,
                                                   LINE_DCUID_COLUMN,      line_dcuid,
                                                   LINE_STATUS_COLUMN,     line_status,
                                                   LINE_NOTE_COLUMN,       line_note,
                                                   LINE_MODE_COLUMN,       line_mode,
                                                   LINE_ISON_COLUMN,       line_ison,
                                                   LINE_CURRENT_COLUMN,    line_current,
                                                   -1);
}

static gboolean smartstreetlight_line_callback_init(void)
{
    g_signal_connect(GTK_TREE_VIEW(line_info_tree_view),
                     "button-press-event",
                     G_CALLBACK(on_smartstreetlight_line_specical_clicked), NULL);
    return TRUE;
}


void smartstreetlight_line_popup_menu_show(GtkTreeView *treeview, GdkEventButton *event, gpointer userdata)
{
    gtk_widget_show_all(GTK_WIDGET(line_info_popup_menu->M_Popup));
    gtk_menu_popup(GTK_MENU(line_info_popup_menu->M_Popup), NULL, NULL, NULL, NULL,
                   (event != NULL) ? event->button : 0, gdk_event_get_time((GdkEvent*)event));
}
