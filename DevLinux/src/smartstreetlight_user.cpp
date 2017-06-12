
#include "smartstreetlight_user.h"
#include "smartstreetlight_login.h"
#include "smartstreetlight_soap.h"
#include "smartstreetlight_ui_method.h"
#include "smartstreetlight_error.h"

struct SPL_USER_Widgets *user_widgets = NULL;
struct SPL_USER_LOG_POPUP_MENU *user_log_popup_menu = NULL;

static gboolean smartstreetlight_user_log_treeview_init(void);
static gboolean smartstreetlight_user_log_liststore_init(void);
static gboolean smartstreetlight_user_log_popup_menu_init(void);
static gboolean smartstreetlight_user_log_callback_init(void);
static void smartstreetlight_user_log_fill_infomation(gint event_id,
                                               gchar *event_content,
                                               gchar *event_time);
static void on_user_log_button_clicked (GtkButton *button, gpointer user_data);
static void spl_user_log_set_selection_all(gboolean is_select);
static gboolean on_spl_user_log_treeview_clicked (GtkTreeView *treeview,
                                                    GdkEventButton     *event,
                                                    gpointer           userdata);
static void spl_user_log_popupmenu_clicked(GtkWidget *popup_menu_item, gpointer userdata);
static void spl_user_log_popupmenu_show(GdkEventButton *event, gpointer userdata);
//static void spl_user_log_delete_one_item();
//static void spl_user_log_delete_mark_item();
//static void spl_user_log_delete_all_item();

#define USER_IMAGE_ID "image_checkbox"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static SplLogPaging paging  = {1, 1, 0, FALSE};

static SplDataObject ObjData = {
   NULL, NULL, &paging, NULL};

void checkbox_set_image(const gchar* imageId, gint selected)
{
    GtkImage *image = GTK_IMAGE(SPL_OBJECT(imageId));
    const gchar *file;
    //DEBUG("image icons: %d\n", selected);
    if(selected == 0)
        file = icon_name[ICON_DEF_CHECKBOX_UNCHECKED];
    else if(selected == MAX_PAGE_VIEW_NUM)
        file = icon_name[ICON_DEF_CHECKBOX_CHECKED];
    else
        file = icon_name[ICON_DEF_CHECKBOX_PARTIAL];
    gtk_image_set_from_file( image, g_strconcat(INSTALL_PATH, G_DIR_SEPARATOR_S, file, NULL));
}

static void spl_userlog_update_information()
{
    gchar *curStr = g_strdup_printf("%d-%d", paging.minIndex, paging.maxIndex);
    gtk_label_set_text(GTK_LABEL(SPL_OBJECT("lb_userlog_cur")),curStr);
    gchar *total = g_strdup_printf("%d", paging.totalItem);
    gtk_label_set_text(GTK_LABEL(SPL_OBJECT("lb_userlog_total")), (gchar*)total);
    checkbox_set_image(USER_IMAGE_ID, paging.selected);
    if(paging.maxIndex > paging.totalItem)
        paging.maxIndex = paging.totalItem;
    gboolean min = (paging.curPage != 1);
    gboolean max = (paging.curPage != ((paging.totalItem / MAX_PAGE_VIEW_NUM) + 1));
    gtk_widget_set_sensitive(GTK_WIDGET(SPL_OBJECT("btn_userlog_back")), min);
    gtk_widget_set_sensitive(GTK_WIDGET(SPL_OBJECT("btn_userlog_next")), max);

}

static gboolean smartstreetlight_user_log_treeview_init(void)
{
    user_widgets->user_log_treeview = GTK_TREE_VIEW(SPL_OBJECT("user_log_treeview"));

    GtkTreeViewColumn *user_log_column;
    GtkCellRenderer *user_log_renderer;

    user_log_renderer = gtk_cell_renderer_toggle_new();
    user_log_column = gtk_tree_view_column_new_with_attributes("", user_log_renderer, "active", EVENT_LOG_IS_SELECT_COLUMN, NULL);
    gtk_tree_view_column_set_resizable(user_log_column,TRUE);
    gtk_tree_view_column_set_reorderable(user_log_column, TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(user_widgets->user_log_treeview), user_log_column);
    g_signal_connect (user_log_renderer, "toggled", G_CALLBACK (on_event_log_renderer_toggled), &ObjData);

    user_log_renderer = gtk_cell_renderer_text_new();
    user_log_column = gtk_tree_view_column_new_with_attributes("Nội dung", user_log_renderer, "text", EVENT_LOG_IS_CONTENT_COLUMN, NULL);
    gtk_tree_view_column_set_resizable(user_log_column,TRUE);
    gtk_tree_view_column_set_reorderable(user_log_column, TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(user_widgets->user_log_treeview), user_log_column);

    user_log_renderer = gtk_cell_renderer_text_new();
    user_log_column = gtk_tree_view_column_new_with_attributes("Thời gian", user_log_renderer, "text", EVENT_LOG_IS_TIME_COLUMN, NULL);
    gtk_tree_view_column_set_resizable(user_log_column,TRUE);
    gtk_tree_view_column_set_reorderable(user_log_column, TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(user_widgets->user_log_treeview), user_log_column);

    gtk_tree_view_set_enable_search(GTK_TREE_VIEW(user_widgets->user_log_treeview), TRUE);
    gtk_tree_view_set_search_column(GTK_TREE_VIEW(user_widgets->user_log_treeview), EVENT_LOG_IS_CONTENT_COLUMN);
    gtk_tree_view_set_search_entry(GTK_TREE_VIEW(user_widgets->user_log_treeview),
                                   GTK_ENTRY(gtk_builder_get_object (smartstreetlight_builder, "user_log_search_entry")));
    paging.curPage = 1;
    paging.totalItem = 999;

    return TRUE;
}

gboolean log_row_visible (GtkTreeModel *model, GtkTreeIter *iter, gpointer p)
{
    gboolean visible = FALSE;
    //gboolean select = FALSE;
    gint min, max;
    SplLogPaging *page = (SplLogPaging*)p;
    GtkTreePath *path = gtk_tree_model_get_path(model, iter);
    if(!path)
        return FALSE;
    gchar *strpath = gtk_tree_path_to_string(path);
    gtk_tree_path_free(path);
    if(strpath == NULL)
        return FALSE;
    gint deep;
    if(sscanf(strpath, "%d", &deep) != 1)
        goto ____exit_here;

    min = page->minIndex - 1;
    max = page->maxIndex - 1;
    if(deep >= min && deep <= max)
        visible = TRUE;

____exit_here:
    g_char_free(strpath);
    return visible;
}

static gboolean smartstreetlight_user_log_liststore_init(void)
{
    user_widgets->user_log_liststore = gtk_list_store_new(EVENT_LOG_NUM_COLUMNS,
                                            G_TYPE_INT,
                                            G_TYPE_STRING,
                                            G_TYPE_STRING,
                                            G_TYPE_BOOLEAN,
                                            G_TYPE_BOOLEAN);
    user_widgets->user_log_filter   = GTK_TREE_MODEL_FILTER(gtk_tree_model_filter_new(GTK_TREE_MODEL(user_widgets->user_log_liststore), NULL));

    gtk_tree_model_filter_set_visible_func(user_widgets->user_log_filter, (GtkTreeModelFilterVisibleFunc) log_row_visible, &paging, NULL);

    gtk_tree_view_set_model(GTK_TREE_VIEW(user_widgets->user_log_treeview),
                            GTK_TREE_MODEL(user_widgets->user_log_filter));

    g_object_unref(user_widgets->user_log_liststore);

    return TRUE;
}
static gboolean smartstreetlight_user_log_popup_menu_init(void)
{
    user_log_popup_menu = g_new0(struct SPL_USER_LOG_POPUP_MENU, 1);

    GtkWidget *separator_item;
    user_log_popup_menu->M_POPUP = gtk_menu_new();
    SPL_MENU_CSS(user_log_popup_menu->M_POPUP);
    user_log_popup_menu->M_DELETE= gtk_menu_item_new_with_label("Xóa");
    gtk_menu_shell_append(GTK_MENU_SHELL(user_log_popup_menu->M_POPUP),user_log_popup_menu->M_DELETE);
    g_signal_connect(user_log_popup_menu->M_DELETE, "activate",
                 (GCallback) spl_user_log_popupmenu_clicked, GINT_TO_POINTER(SPL_USER_LOG_POPUP_MENU_DELETE));

    return TRUE;
}



static void on_btn_log_select_click (SplDataObject *obj, gint btn)
{
    g_return_if_fail(obj && obj->paging);
    spl_event_log_selection_config(obj, TRUE, FALSE);
    switch(btn)
    {
    default:
        return;
    case 0:
        if(obj->paging->curPage > 1)
            obj->paging->curPage--;
        else
        {
            obj->paging->curPage = 1;
        }
        break;
    case 1:
        {
            gint maxpage = obj->paging->totalItem / MAX_PAGE_VIEW_NUM + 1;
            if(obj->paging->curPage  <  maxpage)
                obj->paging->curPage++;
            else
            {
                obj->paging->curPage = maxpage;
            }
        }
        break;
    }
    obj->paging->maxIndex = obj->paging->curPage * MAX_PAGE_VIEW_NUM;
    obj->paging->minIndex = obj->paging->maxIndex - MAX_PAGE_VIEW_NUM + 1;
    if(obj->paging->maxIndex > obj->paging->totalItem)
        obj->paging->maxIndex = obj->paging->totalItem;
    obj->update_information_func();
    gtk_tree_model_filter_refilter(obj->filter);
}


void on_event_log_btn_next_clicked(GtkButton *button, gpointer   user_data)
{
    on_btn_log_select_click((SplDataObject*) user_data, 1);
}

void on_event_log_btn_back_clicked(GtkButton *button, gpointer   user_data)
{
    on_btn_log_select_click((SplDataObject*) user_data, 0);
}

gboolean on_image_selection_click(GtkImage *image, gpointer   user_data)
{
    SplDataObject *obj = (SplDataObject*)user_data;
    g_return_val_if_fail(obj, FALSE);
    g_return_val_if_fail(obj->paging, FALSE);
    DEBUG("selected: %d\n", obj->paging->selected);
    switch(obj->paging->selected)
    {
    case 0:
        spl_event_log_selection_config(obj, TRUE, TRUE);
        break;
    case MAX_PAGE_VIEW_NUM:
    default:
        spl_event_log_selection_config(obj, TRUE, FALSE);
        break;
    }
    gboolean TRUE;
}

static gboolean smartstreetlight_user_log_callback_init(void)
{
    g_signal_connect(GTK_TREE_VIEW(user_widgets->user_log_treeview),
                     "button-press-event",
                     G_CALLBACK(on_spl_user_log_treeview_clicked), NULL);
    g_signal_connect(SPL_OBJECT("btn_userlog_back"), "clicked",
                     G_CALLBACK(on_event_log_btn_back_clicked), &ObjData);
    g_signal_connect(SPL_OBJECT("btn_userlog_next"), "clicked",
                     G_CALLBACK(on_event_log_btn_next_clicked), &ObjData);
    g_signal_connect(SPL_OBJECT("userlog_btn_selection_click"), "clicked",
                     G_CALLBACK(on_image_selection_click), &ObjData);
    return TRUE;
}


gboolean smartstreetlight_user_log_init(void)
{
    user_widgets = g_slice_new(SPL_USER_Widgets);

    user_widgets->spl_user_log_box = GTK_WIDGET(SPL_OBJECT("spl_user_log_box"));

    if(smartstreetlight_user_log_treeview_init())
    {
        if (smartstreetlight_user_log_liststore_init())
        {
            if (smartstreetlight_user_log_popup_menu_init())
            {
                if (smartstreetlight_user_log_callback_init())
                {
                    ObjData.filter = user_widgets->user_log_filter;
                    ObjData.store = user_widgets->user_log_liststore;
                    ObjData.update_information_func =   &spl_userlog_update_information;
                    ObjData.soap_delete_function =      &smartstreetlight_delete_user_log_execute;
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

void smartstreetlight_user_log_finalize(void)
{
    user_log_popup_menu = g_new0(struct SPL_USER_LOG_POPUP_MENU, 1);
    if(user_log_popup_menu && user_log_popup_menu->M_POPUP)
        gtk_widget_destroy(GTK_WIDGET(user_log_popup_menu->M_POPUP));
    if(user_widgets->spl_user_log_box)
        gtk_widget_destroy(user_widgets->spl_user_log_box);
    g_slice_free(SPL_USER_Widgets, user_widgets);
}


static void smartstreetlight_user_log_fill_infomation(gint event_id,
                                               gchar *event_content,
                                               gchar *event_time)
{
    GtkTreeIter iter;
    gtk_list_store_append(user_widgets->user_log_liststore, &iter);
    gtk_list_store_set(user_widgets->user_log_liststore, &iter,
                       EVENT_LOG_IS_ID_COLUMN,      event_id,
                       EVENT_LOG_IS_CONTENT_COLUMN, event_content,
                       EVENT_LOG_IS_TIME_COLUMN,    event_time,
                       EVENT_LOG_IS_SELECT_COLUMN, FALSE,
                       EVENT_LOG_IS_DELETE_COLUMN, FALSE,
                       -1);
}



void smartstreetlight_user_log_show_all(void)
{
    g_return_if_fail(user_widgets);
    ns1__USER_USCORELOG_USCOREINFO_USCOREType ** userlog_List;
    gint userlog_List_size;
    SplSoap spl_soap;
    paging.curPage      = 1;
    paging.minIndex     = 1;
    paging.maxIndex     =  MAX_PAGE_VIEW_NUM;
    smartstreetlight_clear_list_store(GTK_TREE_MODEL(user_widgets->user_log_liststore));
    checkbox_set_image(USER_IMAGE_ID, 0);
    gint soap_err = smartstreetlight_get_user_log_nofree_execute(&spl_soap,current_account->spl_current_id, &userlog_List, &userlog_List_size);
    if(soap_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
    {
        for(gint i=0; i< userlog_List_size; i++)
        {
            smartstreetlight_user_log_fill_infomation(userlog_List[i]->userlog_USCOREid,
                                                      userlog_List[i]->eventlog_USCOREcontent,
                                                      userlog_List[i]->eventlog_USCOREtime);
        }
    } else {
        gchar * msg = g_strdup("Lỗi lấy thông tin nhật ký của tài khoản");
        GtkWidget *parent = stack_widget_active_top();
        smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
        g_char_free(msg);

    }
    paging.totalItem    = userlog_List_size;
    paging.selected     = 0;
    if(paging.totalItem < paging.maxIndex)
        paging.maxIndex = paging.totalItem;
    spl_userlog_update_information();
    smartstreetlight_free_soap_operation(&spl_soap);
}


static void on_user_log_button_clicked (GtkButton *button, gpointer user_data)
{
    gboolean is_select = FALSE;
    switch(GPOINTER_TO_INT(user_data))
    {
    case USER_LOG_SELECT_ALL:
        is_select = TRUE;
    case USER_LOG_DISSELECT_ALL:
        spl_user_log_set_selection_all(is_select);
        break;
    }
}

static void spl_user_log_set_selection_all(gboolean is_select)
{
    g_return_if_fail(user_widgets);
    GtkTreeIter iter;
    GtkTreeModel *model = GTK_TREE_MODEL(user_widgets->user_log_liststore);
    if(gtk_tree_model_get_iter_first(model, &iter))
    {
        do
        {
            gtk_list_store_set(GTK_LIST_STORE(model), &iter, EVENT_LOG_IS_SELECT_COLUMN, is_select, -1);
        }
        while(gtk_tree_model_iter_next(model, &iter));
    }
}

void on_event_log_renderer_toggled (GtkCellRendererToggle *cell_renderer,
                                            gchar *path,
                                            gpointer user_data)
{
    SplDataObject *obj = (SplDataObject*)user_data;
	GtkTreeIter iter, storeIter;
	GtkTreeModel *model = GTK_TREE_MODEL(obj->filter);
	GtkTreePath *toggle_path = gtk_tree_path_new_from_string (path);
	gboolean is_toggle;
	gtk_tree_model_get_iter (model, &iter, toggle_path);
	gtk_tree_model_get (model, &iter, EVENT_LOG_IS_SELECT_COLUMN, &is_toggle, -1);

    gtk_tree_model_filter_convert_iter_to_child_iter(obj->filter, &storeIter, &iter);
    if(gtk_list_store_iter_is_valid(obj->store, &storeIter))
    {
        gtk_list_store_set (GTK_LIST_STORE(obj->store), &storeIter,
                            EVENT_LOG_IS_SELECT_COLUMN, !is_toggle, -1);
    }
	gtk_tree_path_free (toggle_path);
	spl_event_log_selection_config(obj, FALSE, FALSE);
}


static void spl_user_log_popupmenu_clicked(GtkWidget *popup_menu_item, gpointer userdata)
{
    switch(GPOINTER_TO_INT(userdata))
    {
    case SPL_USER_LOG_POPUP_MENU_SELECT_ALL:
        //on_user_log_button_clicked(NULL, GINT_TO_POINTER(USER_LOG_SELECT_ALL));
        break;
    case SPL_USER_LOG_POPUP_MENU_DISSELECT_ALL:
        //on_user_log_button_clicked(NULL, GINT_TO_POINTER(USER_LOG_DISSELECT_ALL));
        break;
    case SPL_USER_LOG_POPUP_MENU_DELETE:
        spl_event_log_delete_marked_iter(&ObjData);
        break;
    case SPL_USER_LOG_POPUP_MENU_DELETE_MARK:
        //spl_user_log_delete_marked_iter();
        break;
    case SPL_USER_LOG_POPUP_MENU_DELETE_ALL:
        //spl_user_log_delete_all_item();
        //spl_user_log_delete_marked_iter();
        break;
    };
}

static gboolean on_spl_user_log_treeview_clicked (GtkTreeView *treeview,
                                                    GdkEventButton     *event,
                                                    gpointer           userdata)
{
    if(event->type == GDK_BUTTON_PRESS && event->button == GDK_BUTTON_SECONDARY)
    {
        spl_user_log_popupmenu_show(event, NULL);
    }
    return FALSE;
}

static void spl_user_log_popupmenu_show(GdkEventButton *event, gpointer userdata)
{
    gtk_widget_show_all(GTK_WIDGET(user_log_popup_menu->M_POPUP));
    gtk_menu_popup(GTK_MENU(user_log_popup_menu->M_POPUP), NULL, NULL, NULL, NULL,
                   (event != NULL) ? event->button : 0, gdk_event_get_time((GdkEvent*)event));
}

void spl_log_delete_row_marked(GtkListStore *store, SplLogPaging *_paging)
{
    GtkTreeModel *model = GTK_TREE_MODEL(store);
    GtkTreeIter iter;
    if(gtk_tree_model_get_iter_first(model, &iter))
    {
       gboolean pass = FALSE;
       do
       {
            pass = FALSE;
            gboolean _delete;
            gtk_tree_model_get(model, &iter, EVENT_LOG_IS_DELETE_COLUMN, &_delete, -1);
            if(_delete)
            {
                if(gtk_list_store_remove(store, &iter))
                    pass = TRUE;
            }
       }while(pass || gtk_tree_model_iter_next(model, &iter));
    }
    _paging->totalItem = gtk_tree_model_iter_n_children(model, NULL);
}

void spl_event_log_selection_config(SplDataObject *obj, gboolean setSelection, gboolean selectAll)
{
    GtkTreeIter sIter; //selected Iter
    GtkTreeModel *model = GTK_TREE_MODEL(obj->filter);
    gint selectNums = 0;
    if(gtk_tree_model_get_iter_first(model, &sIter))
    {
        do
        {
            if(setSelection)
            {
                GtkTreeIter storeIter;
                gtk_tree_model_filter_convert_iter_to_child_iter(obj->filter, &storeIter, &sIter );
                if(gtk_list_store_iter_is_valid(obj->store, &storeIter))
                {
                    gtk_list_store_set(obj->store, &storeIter,
                                       EVENT_LOG_IS_SELECT_COLUMN, selectAll, -1);
                }
                if(selectAll)
                    selectNums = MAX_PAGE_VIEW_NUM;
            }
            else
            {
                gboolean selected;
                gtk_tree_model_get(model, &sIter,
                               EVENT_LOG_IS_SELECT_COLUMN, &selected, -1);
                if(selected)
                    selectNums++;
            }
        }while(gtk_tree_model_iter_next(model, &sIter));
    }
    obj->paging->selected = selectNums;
    obj->update_information_func();
}


void spl_event_log_delete_marked_iter(SplDataObject *obj)
{
    GtkTreeIter sIter; //selected Iter
    GtkTreeModel *model = GTK_TREE_MODEL(obj->filter);
    GString *msgError = NULL;
    gint index = 0;
    if(gtk_tree_model_get_iter_first(model, &sIter))
    {
        do
        {

            gint event_log_id = -1;
            gboolean selected;
            gchar *content;
            gtk_tree_model_get(model, &sIter,
                               EVENT_LOG_IS_ID_COLUMN, &event_log_id,
                               EVENT_LOG_IS_SELECT_COLUMN, &selected,
                               EVENT_LOG_IS_CONTENT_COLUMN, &content, -1);
            if(selected)
            {
                SplSoap spl_soap;
                gint soap_err = obj->soap_delete_function(&spl_soap, event_log_id);
                if(soap_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
                {
                    GtkTreeIter storeIter;
                    gtk_tree_model_filter_convert_iter_to_child_iter(obj->filter, &storeIter, &sIter);
                    if(gtk_list_store_iter_is_valid(obj->store, &storeIter))
                        gtk_list_store_set(obj->store, &storeIter,
                                            EVENT_LOG_IS_DELETE_COLUMN, TRUE, -1);
                }else
                {
                    msgError = g_string_new("");
                    g_string_append_printf(msgError, "Xóa sự kiện '%s' bị lỗi", content);
                    GtkWidget *parent = stack_widget_active_top();
                    smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msgError->str, soap_err);
                    g_string_free(msgError, TRUE);
                    g_free(content);
                    break;
                }
            }
            g_free(content);
        }while(gtk_tree_model_iter_next(model, &sIter));
    }
    spl_log_delete_row_marked(obj->store, obj->paging);
    gint maxPage = obj->paging->totalItem / MAX_PAGE_VIEW_NUM + 1;
    if( maxPage < obj->paging->curPage)
    {
        obj->paging->curPage = maxPage;
    }
    if(obj->paging->curPage < 1)
        obj->paging->curPage = 1;
    obj->paging->maxIndex = obj->paging->curPage * MAX_PAGE_VIEW_NUM;
    obj->paging->minIndex = obj->paging->maxIndex - MAX_PAGE_VIEW_NUM + 1;

    gtk_tree_model_filter_refilter(obj->filter);
    spl_event_log_selection_config(obj, FALSE, FALSE);
    obj->update_information_func();
}
