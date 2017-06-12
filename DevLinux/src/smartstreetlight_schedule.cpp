#include "smartstreetlight_schedule.h"
#include "smartstreetlight_soap.h"
#include "smartstreetlight_ui_method.h"
#include "smartstreetlight_callback.h"
#include "smartstreetlight_utils.h"
#include "smartstreetlight_dcu.h"
#include "smartstreetlight_login.h"
#include "smartstreetlight_error.h"


#define FULL_MINUTE_OF_DAY  24 * 60
GtkImage  *image_remove;
GtkImage  *image_edit;
static SplDaySchedule *dayTmp = NULL;
static SplDayScheduleItem *itemTmp = NULL;

static gint startTime, endTime, lastTime, countTime;
static gboolean isDoubleClickOnTreeView = FALSE;
static gint zoneID = -1, programID = -1;
static gboolean passSignal = FALSE;

const gchar MONTH_FMT[]     = "Tháng %d      ";
const gchar MONTH_UNKNOWN[] = "<Chưa được thiết lập>";

struct SPL_PROGRAM_Widgets      	*program_widgets;
struct SPL_SCHEDULE_ITEM_Widgets	*schedule_item_widgets;

struct SplMonthItem
{
    gint    month;
    gint    dayScheduleId;
    gint    Id;
};

struct SplYearSchedule
{
    gint        programId;
    struct SplMonthItem month[12];
};

static GSList *programChildListDay = NULL;

static SplDaySchedule * spl_day_schedule_init()
{
    SplDaySchedule *day = g_new0(SplDaySchedule, 1);
    day->name           = NULL;
    return day;
}

static void spl_day_schedule_free(SplDaySchedule *day)
{
    g_return_if_fail(day);
    g_char_free(day->name);
    if(day->itemlist)
        spl_utils_free_slist(&day->itemlist, g_free);
    g_free(day);
}

enum
{
    BTN_ITEM_EDIT,
    BTN_ITEM_REMOVE,
    BTN_ITEM_ADD,
    BTN_ITEM_ACCEPT,
};

struct SPL_PROGRAM_POPUP_MENU *program_info_popup_menu = NULL;
struct SPL_SCHEDULE_DAY_POPUP_MENU *schedule_day_popup_menu = NULL;
struct SPL_SCHEDULE_LIST_POPUP_MENU *schedule_list_popup_menu = NULL;
struct SPL_SCHEDULE_ITEM_POPUP_MENU *schedule_item_popup_menu = NULL;

struct SPL_SCHEDULE_LIST_NAME_POPUP_MENU *schedule_list_name_popup_menu = NULL;
struct SPL_SCHEDULE_LIST_CONTENT_POPUP_MENU *schedule_list_content_popup_menu = NULL;

static gboolean smartstreetlight_schedule_item_element_init(void);

static void smartstreetlight_schedule_list_name_popup_menu_init();
static void smartstreetlight_schedule_list_name_popup_menu_widget_init();
static void smartstreetlight_schedule_list_name_popup_menu_callback_init();
static void smartstreetlight_schedule_list_name_popup_menu_clicked(GtkWidget *popup_menu_item, gpointer userdata);
static void smartstreetlight_schedule_create_new_schedule_item_process(void);
static void smartstreetlight_schedule_list_name_popup_menu_add_clicked(void);
static void smartstreetlight_schedule_list_name_popup_menu_remove_clicked(void);
static void smartstreetlight_schedule_list_starttime_adjustment_changed (GtkAdjustment *adjustment, gpointer user_data);
static void smartstreetlight_schedule_list_timeon_adjustment_changed (GtkAdjustment *adjustment, gpointer user_data);
static void smartstreetlight_schedule_list_level_adjustment_changed(GtkAdjustment *adjustment, gpointer user_data);
static gboolean smartstreetlight_schedule_list_commit_btn_clicked(GtkButton *button, gpointer userdata);
static void smartstreetlight_schedule_list_append_data(gint starttime, gint timeon, gint level);

static void smartstreetlight_schedule_list_content_popup_menu_init();
static void smartstreetlight_schedule_list_content_popup_menu_widget_init();
static void smartstreetlight_schedule_list_content_popup_menu_callback_init();
static void smartstreetlight_schedule_list_content_popup_menu_clicked(GtkWidget *popup_menu_item, gpointer userdata);
static void smartstreetlight_schedule_list_content_popup_menu_add_clicked(void);
static void smartstreetlight_schedule_list_content_popup_menu_remove_clicked(void);

static gboolean smartstreetlight_schedule_tree_view_init(void);
static gboolean smartstreetlight_schedule_store_init(void);
static gboolean smartstreetlight_schedule_callback_init();
static const gchar * smartstreetlight_schedule_int2time(const gint value);

static gboolean smartstreetlight_program_popup_menu_init(void);
static void smartstreetlight_program_popup_menu_widget_init(void);
static void smartstreetlight_program_popup_menu_callback_init(void);
static gboolean smartstreetlight_program_popup_menu_add_clicked(void);
static void smartstreetlight_program_popup_menu_schedule_clicked(void);
static void smartstreetlight_program_popup_menu_remove_clicked(void);
static void smartstreetlight_program_popup_menu_clicked(GtkWidget *popup_menu_item, gpointer userdata);


static gboolean smartstreetlight_schedule_day_popup_menu_init(void);
static void smartstreetlight_schedule_day_popup_menu_widget_init(void);
static void smartstreetlight_schedule_day_popup_menu_callback_init(void);
static void smartstreetlight_schedule_day_popup_menu_add_clicked(gint program_id);
static void smartstreetlight_schedule_day_popup_menu_remove_clicked(void);
static void smartstreetlight_schedule_day_popup_menu_schedule_clicked(void);
static void smartstreetlight_schedule_day_popup_menu_clicked(GtkWidget *popup_menu_item, gpointer userdata);


static gboolean smartstreetlight_schedule_list_popup_menu_init(void);
static void smartstreetlight_schedule_list_popup_menu_widget_init(void);
static void smartstreetlight_schedule_list_popup_menu_callback_init(void);
static void smartstreetlight_schedule_list_popup_menu_add_clicked(void);
static void smartstreetlight_schedule_list_popup_menu_remove_clicked(void);
static void smartstreetlight_schedule_list_popup_menu_clicked(GtkWidget *popup_menu_item, gpointer userdata);


static gboolean smartstreetlight_schedule_item_popup_menu_init(void);
static void smartstreetlight_schedule_item_popup_menu_widget_init(void);
static void smartstreetlight_schedule_item_popup_menu_callback_init(void);
static void smartstreetlight_schedule_item_popup_menu_add_clicked(void);
static void smartstreetlight_schedule_item_popup_menu_remove_clicked(void);
static void smartstreetlight_schedule_item_popup_menu_clicked(GtkWidget *popup_menu_item, gpointer userdata);




static gboolean check_exist_int(gint *list_value, gint value, gint list_size);
static void smartstreetlight_schedule_choose_liststore_fill_information(gchar *listschedule_name, gint listschedule_id);

static void smartstreetlight_schedule_day_create_process(void);
static void smartstreetlight_schedule_day_change_process(GtkTreeIter *iter);
static void on_combo_box_time_activated(GtkComboBoxText *cbbt, gpointer data);
static void on_btn_item_clicked(GtkButton *btn, gpointer data);

/** ********************************************************************************************************************** **/
/** ********************************************************************************************************************** **/
/** ********************************************************************************************************************** **/


/**
* Please free the return of this function
*
*/
static gchar *convert_time_tick_to_string(guint timetick)
{
    return g_strdup_printf("%02d:%02d", timetick  / 60, timetick % 60);
}


static int item_compare (const SplDayScheduleItem *a, const SplDayScheduleItem *b)
{
    return a->timeBegin - b->timeBegin;
}


static void spl_item_dialog_fill_tree(SplDayScheduleItem *selectItem)
{
    g_return_if_fail(dayTmp);
    dayTmp->itemlistTmp = g_slist_sort(dayTmp->itemlistTmp, (GCompareFunc)item_compare);
    GSList *list = dayTmp->itemlistTmp;
    GtkTreeIter iter;
    GtkListStore *store =  schedule_item_widgets->schedule_item_content_liststore;
    gtk_list_store_clear(store);
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(schedule_item_widgets->schedule_item_content_treeview));
    for( ; list != NULL; list = list->next)
    {
        SplDayScheduleItem  *it = (SplDayScheduleItem*)list->data;
        //DEBUG("ID: %d Start: %d On: %d Level: %d\n", it->Id, it->timeBegin, it->timeOn, it->level);
        gchar *sTime = convert_time_tick_to_string(it->timeBegin);
        gchar *eTime = convert_time_tick_to_string(it->timeBegin + it->timeOn);
        gchar *level = g_strdup_printf("%d", it->level / DIV_BRIGHTNESS);
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           NEW_ITEM_SCHEDULE_STARTTIME_COLUMN, sTime,
                           NEW_ITEM_SCHEDULE_TIMEON_COLUMN, eTime,
                           NEW_ITEM_SCHEDULE_LEVEL_COLUMN, level,
                           NEW_ITEM_SCHEDULE_POINTER_COLUMN, it, -1);
        if(selectItem && selectItem->Id == it->Id)
            gtk_tree_selection_select_iter(selection, &iter);

        g_char_free(sTime);
        g_char_free(eTime);
        g_char_free(level);
    }
}

void smartstreetlight_program_schedule_finalize(void)
{
    g_slice_free(SPL_PROGRAM_Widgets, program_widgets);
    g_slice_free(SPL_SCHEDULE_ITEM_Widgets, schedule_item_widgets);

    g_slice_free(SPL_PROGRAM_POPUP_MENU, program_info_popup_menu);
    g_slice_free(SPL_SCHEDULE_DAY_POPUP_MENU, schedule_day_popup_menu);
    g_slice_free(SPL_SCHEDULE_LIST_POPUP_MENU, schedule_list_popup_menu);
    g_slice_free(SPL_SCHEDULE_ITEM_POPUP_MENU, schedule_item_popup_menu);
}


static void on_toggle_radio_toggled (GtkCellRendererToggle *cell,
                                     gchar *path_str,
                                     gpointer data)
{
    GtkTreeIter iter, iter1;
    GtkTreeStore *store = (GtkTreeStore*)data;
    GtkTreePath *path = gtk_tree_path_new_from_string (path_str);
    gboolean toggle;
    /* get toggled iter */
    gtk_tree_model_get_iter (GTK_TREE_MODEL(store), &iter, path);
    if(gtk_tree_model_get_iter_first(GTK_TREE_MODEL(store), &iter1))
    {
        do
        {
            gtk_tree_store_set (store, &iter1, 0, FALSE, -1);
        }
        while(gtk_tree_model_iter_next(GTK_TREE_MODEL(store), &iter1));
    }
    /* set new value */
    gtk_tree_store_set (store, &iter, 0, TRUE, -1);
    gtk_tree_path_free (path);
}


enum
{
    SELECT_PROGRAM_CHECK_COLUMN = 0,
    SELECT_PROGRAM_SHOW_COLUMN,
    SELECT_PROGRAM_ID_COLUMN,
    SELECT_PROGRAM_HIDE_COLUMN,
    SELECT_PROGRAM_COUNT_COLUMNS
};
static void
on_editable_cell_clicked(GtkCellRenderer *cell,
                         GtkCellEditable *editable,
                         const gchar     *path_str,
                         gpointer         data)
{
    DEBUG("\n");
    static gboolean isInitEditableCell = FALSE;
    static GtkWidget    *dlg = NULL;
    static GtkTreeStore *store;
    GtkTreeModel *monthModel = GTK_TREE_MODEL(data);
    GtkTreeIter iter;
    gint responseId;
    GtkTreePath *path;
    GtkTreeIter editableIter;
    gchar *month, *title;
    GSList *item;
    gint imonth, Id, scheduleId;
    if(!isInitEditableCell)
    {
        dlg = GTK_WIDGET(SPL_OBJECT("dlg_select_program_day"));
        GtkTreeView *view = GTK_TREE_VIEW(SPL_OBJECT("dlg_select_treeview"));
        GtkTreeViewColumn *column;
        GtkCellRenderer *render;
        store = gtk_tree_store_new(SELECT_PROGRAM_COUNT_COLUMNS, G_TYPE_BOOLEAN, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING);
        render = gtk_cell_renderer_toggle_new();
        g_object_set(render, "radio", TRUE, NULL);
        column = gtk_tree_view_column_new_with_attributes("", render, "active", 0, NULL);
        g_signal_connect (render, "toggled", G_CALLBACK (on_toggle_radio_toggled), store);
        gtk_tree_view_append_column(view, column);

        render = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("", render, "text", 1, NULL);
        gtk_tree_view_append_column(view, column);

        gtk_tree_view_set_model(view, GTK_TREE_MODEL(store));

        isInitEditableCell = TRUE;
    }
    //fill inforation to store
    //show
    path = gtk_tree_path_new_from_string (path_str);
    gtk_tree_model_get_iter (monthModel, &editableIter, path);
    gtk_tree_path_free(path);
    gtk_tree_model_get(monthModel, &editableIter,
                       SCHEDULE_MONTH_STORE_MONTH_COLUMN, &month,
                       SCHEDULE_MONTH_STORE_MONTH_INT_COLUMN, &imonth,
                       SCHEDULE_MONTH_STORE_ID_COLUMN, &Id, -1);
    if(!month)
        return;
    title = g_strdup_printf("Chọn chương trình cho %s", month);
    gtk_window_set_title(GTK_WINDOW(dlg), title);
    g_char_free(month);
    g_char_free(title);

    if(programChildListDay == NULL || g_slist_length(programChildListDay)== 0)
    {
        GtkWidget *parent = stack_widget_active_top();
        SPL_WARNING_POPUP(parent, "Không có cấu hình chương trình theo ngày nào tồn tại");
        return;
    }
    gtk_tree_store_clear(store);
    gtk_tree_store_append(store, &iter, NULL);
    gtk_tree_store_set(store, &iter, SELECT_PROGRAM_CHECK_COLUMN, TRUE,
                       SELECT_PROGRAM_SHOW_COLUMN, "none",
                       SELECT_PROGRAM_ID_COLUMN, 0,
                       SELECT_PROGRAM_HIDE_COLUMN, MONTH_UNKNOWN, -1);
    item = programChildListDay;
    for( ; item != NULL; item = item->next)
    {
        SplDaySchedule *daySchedule = (SplDaySchedule*)item->data;
        gtk_tree_store_append(store, &iter, NULL);
        gtk_tree_store_set(store, &iter, SELECT_PROGRAM_CHECK_COLUMN, FALSE,
                           SELECT_PROGRAM_SHOW_COLUMN, daySchedule->name,
                           SELECT_PROGRAM_ID_COLUMN, daySchedule->Id,
                           SELECT_PROGRAM_HIDE_COLUMN, daySchedule->name, -1);
    }
    SPL_DIALOG_SHOW(dlg);
    while(responseId = gtk_dialog_run(GTK_DIALOG(dlg)))
    {
        switch(responseId)
        {
        case GTK_RESPONSE_CLOSE:
        case GTK_RESPONSE_CANCEL:
        case GTK_RESPONSE_DELETE_EVENT:
            goto _____exit;
            break;
        case GTK_RESPONSE_OK:
            if(gtk_tree_model_get_iter_first(GTK_TREE_MODEL(store), &iter))
            {
                do
                {
                    gboolean check;
                    gchar *name;
                    gint id;
                    gtk_tree_model_get(GTK_TREE_MODEL(store), &iter,
                                       SELECT_PROGRAM_CHECK_COLUMN, &check,
                                       SELECT_PROGRAM_HIDE_COLUMN, &name,
                                       SELECT_PROGRAM_ID_COLUMN, &scheduleId,
                                       -1);
                    if(check)
                    {
                        SplSoap spl_soap;
                        if(Id == 0) //this data be not in database. create new here
                        {
                            //DEBUG("Id is 0\n");
                            gint soap_err = smartstreetlight_add_day_schedule_execute(&spl_soap,programID, imonth, &Id);
                            DEBUG("%d: %d: error: %d\n", programID, imonth, soap_err);
                            if(soap_err != ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
                            {
                                gchar * msg = g_strdup_printf("Lỗi thêm mới lập lịch tháng %d." , imonth);
                                GtkWidget *parent = stack_widget_active_top();
                                smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
                                g_char_free(msg);
                                g_char_free(name);
                                break;
                            }
                        } else {
                            //set name to cell editable
                            //DEBUG("get name: %s\n", name);
                            //change on database
                            //DEBUG("[[[smartstreetlight_edit_day_schedule_execute(%d, %d, %d, %d)]]]\n",Id, scheduleId, programID, imonth);
                            gint soap_err = smartstreetlight_edit_day_schedule_execute(&spl_soap, Id, scheduleId, programID, imonth);
                            if(soap_err != ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
                            {
                                gchar * msg = g_strdup("Lỗi thay đổi thông tin lập lịch tháng. ");
                                GtkWidget *parent = stack_widget_active_top();
                                smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
                                g_char_free(msg);
                            }

                        }
                        gtk_tree_store_set (GTK_TREE_STORE(data), &editableIter,
                                                    SCHEDULE_MONTH_STORE_NAME_COLUMN, name,
                                                    SCHEDULE_MONTH_STORE_SCHEDULE_ID_COLUMN, scheduleId,
                                                    SCHEDULE_MONTH_STORE_ID_COLUMN, Id,
                                                    -1);
                        g_char_free(name);
                        break;
                    }
                    g_char_free(name);
                }
                while(gtk_tree_model_iter_next(GTK_TREE_MODEL(store), &iter));
            }
            goto _____exit;
            break;
        }
    }
_____exit:
    gtk_cell_editable_editing_done(editable);
    SPL_DIALOG_HIDE(dlg);
    gtk_widget_hide_on_delete(dlg);
}

static void spl_month_schedule_init_view()
{
    static gboolean isInitMonthView = FALSE;
    GtkTreeViewColumn *column;
    GtkCellRenderer *renderer;
    if(isInitMonthView)
        return;
    program_widgets->program_month_schedule_treestore =
        gtk_tree_store_new(
            SCHEDULE_MONTH_STORE_COUNT_COLUMNS,
            G_TYPE_STRING,
            G_TYPE_STRING,
            G_TYPE_INT,
            G_TYPE_INT,
            G_TYPE_INT);

    program_widgets->program_month_schedule_treeview = GTK_TREE_VIEW(SPL_OBJECT("program_month_schedule_treeview"));

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes ("Tháng", renderer, "text", 0, NULL);
    gtk_tree_view_column_set_resizable(column,TRUE);
    gtk_tree_view_column_set_reorderable(column, TRUE);
    gtk_tree_view_append_column (GTK_TREE_VIEW(program_widgets->program_month_schedule_treeview), column);

    renderer = gtk_cell_renderer_text_new();
    g_object_set(renderer, "editable", TRUE, NULL);
    column = gtk_tree_view_column_new_with_attributes ("Chương trình hoạt động", renderer, "text", 1, NULL);
    gtk_tree_view_column_set_resizable(column,TRUE);
    gtk_tree_view_column_set_reorderable(column, TRUE);
    gtk_tree_view_append_column (GTK_TREE_VIEW(program_widgets->program_month_schedule_treeview), column);

    gtk_tree_view_set_model(program_widgets->program_month_schedule_treeview,
                            GTK_TREE_MODEL(program_widgets->program_month_schedule_treestore));

    //signal connect
    /*
    g_signal_connect(GTK_TREE_VIEW(program_widgets->program_month_schedule_treeview),
                     "button-press-event",
                     G_CALLBACK(on_smartstreetlight_schedule_specical_clicked), NULL);
    */
    DEBUG("Init signel editable\n");
    g_signal_connect(renderer, "editing-started", G_CALLBACK(on_editable_cell_clicked),
                     program_widgets->program_month_schedule_treestore);
    isInitMonthView = TRUE;
}

static void spl_fill_day_schedule_configuration(SplDaySchedule *day, GtkTreeStore *store)
{
    g_return_if_fail(day);
    GSList *list;
    GtkTreeIter iter;
    gtk_tree_store_append(store, &day->iter, NULL);
    gtk_tree_store_set(store, &day->iter,
                       OBJECT_NAME_COLUMN, day->name,
                       OBJECT_POINTER_COLUMN, day,
                       OBJECT_TYPE_COLUMN, OBJECT_IS_DAY_SCHEDULE_TYPE,
                       ITEM_ID_COLUMN, day->Id,
                       -1);
    //fill it's child
    if(day->itemlist)
    {
        for(list = day->itemlist; list != NULL; list = list->next)
        {
            SplDayScheduleItem *item = (SplDayScheduleItem*)list->data;
            if(item)
            {
                gchar *startStr = convert_time_tick_to_string(item->timeBegin);
                gchar *endStr   = convert_time_tick_to_string(item->timeBegin + item->timeOn);
                //DEBUG("ID ...... : %d\n", item->Id);
                gchar *levelStr = g_strdup_printf("%d", item->level / DIV_BRIGHTNESS);
                gtk_tree_store_append(store, &iter, &day->iter);
                gtk_tree_store_set(store, &iter,
                                   OBJECT_TYPE_COLUMN, OBJECT_IS_ITEM_SCHEDULE_TYPE,
                                   ITEM_START_TIME_COLUMN, startStr,
                                   ITEM_END_TIME_COLUMN, endStr,
                                   ITEM_BRIGHTNESS_COLUMN, levelStr,
                                   ITEM_ID_COLUMN, item->Id,
                                   OBJECT_POINTER_COLUMN, item, -1);
                g_char_free(startStr);
                g_char_free(endStr);
                g_char_free(levelStr);
            }
        }
    }
}

static void spl_program_schedule_fill_belong_information(gint progamId)
{
    ns1__DAYSCHEDULE_USCOREINFO_USCOREType  **dayschedule_list  = NULL;
    ns1__LISTSCHEDULE_USCOREINFO_USCOREType **listschedule_list = NULL;
    ns1__SCHEDULE_USCOREINFO_USCOREType     **schedule_list     = NULL;
    gint list_size;
    gint i;
    GSList *list;
    GtkTreeIter iter;
    GtkTreeStore *store;
    static struct SplYearSchedule *year = NULL;
    if(year == NULL)
    {
        year = g_new0(SplYearSchedule, 1);
        for(i = 0; i < 12; i++)
        {
            year->month[i].month = i + 1;
            year->month[i].Id = 0;
        }
    }
    //reset month of year id
    for(i = 0; i < 12; i++)
    {
        year->month[i].Id = 0;
        year->month[i].dayScheduleId = 0;
    }

    year->programId = progamId;

    gtk_tree_store_clear(program_widgets->program_item_schedule_treestore);
    gtk_tree_store_clear(program_widgets->program_month_schedule_treestore);
    /**get list configuration schedule of this program*/
    spl_utils_free_slist(&programChildListDay, (GDestroyNotify)spl_day_schedule_free);
    SplSoap spl_soap;
    gint soap_err = smartstreetlight_get_list_schedule_nofree_execute(&spl_soap,0, progamId, &listschedule_list, &list_size);
    if (soap_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
    {
        if (listschedule_list!= NULL)
        {
            for (i = 0 ; i < list_size; i++)
            {
                SplDaySchedule *day = spl_day_schedule_init();
                day->name       = g_strdup(listschedule_list[i]->listscheduleName);
                day->Id         = listschedule_list[i]->listscheduleId;
                day->programId  = listschedule_list[i]->listscheduleProgramId;

                DEBUG("Configuration name: %s have %d element\n", day->name, listschedule_list[i]->__sizesheduleList);
                if (listschedule_list[i]->sheduleList!= NULL)
                {
                    ns1__SCHEDULE_USCOREINFO_USCOREType **schedule_list = listschedule_list[i]->sheduleList;
                    spl_utils_free_slist(&day->itemlist, (GDestroyNotify)g_free); //well-equipment, it will not happen
                    for(int index = 0; index < listschedule_list[i]->__sizesheduleList; index++)
                    {
                        SplDayScheduleItem *item = g_new0(SplDayScheduleItem, 1);
                        item->Id = schedule_list[index]->scheduleId;
                        item->level = schedule_list[index]->scheduleLevel;
                        item->timeBegin = schedule_list[index]->scheduleStarttime;
                        item->timeOn = schedule_list[index]->scheduleOntime;
                        item->parent = day;
                        day->itemlist = g_slist_append(day->itemlist, item);
                        // DEBUG("id: %d\n", item->Id);
                    }
                }
                programChildListDay = g_slist_append(programChildListDay, day);

            }
        }
    }
    else
    {
        gchar * msg = g_strdup("Lỗi danh sách lập lịch ngày. ");
        GtkWidget *parent = stack_widget_active_top();
        smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
        g_char_free(msg);
        smartstreetlight_free_soap_operation(&spl_soap);
        return;
    }
    DEBUG("Program id %d have %d element\n", progamId, list_size);
    smartstreetlight_free_soap_operation(&spl_soap);

    /**get year schedule*/
    soap_err = smartstreetlight_get_day_schedule_list_nofree_execute(&spl_soap,progamId, 0, &dayschedule_list, &list_size);
    if(soap_err ==ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
    {
        if (dayschedule_list!=NULL)
        {
            for(gint i=0; i < list_size; i++)
            {
                gint month = dayschedule_list[i]->dayschedule_USCOREmonth;
                if(month > 12 || month < 1)
                    continue;
                year->month[month - 1].Id = dayschedule_list[i]->dayschedule_USCOREid;
                year->month[month - 1].dayScheduleId = dayschedule_list[i]->dayschedule_USCORElistScheduel_USCOREid;
            }
            DEBUG("Year get %d element\n",list_size);
        }
    } else {
        gchar * msg = g_strdup("Lỗi lấy danh sách lập lịch tháng. ");
        GtkWidget *parent = stack_widget_active_top();
        smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
        g_char_free(msg);
    }
    smartstreetlight_free_soap_operation(&spl_soap);

    /** NOW we will update the interface with which we got above*/
    //update year schedule tree view
    store = program_widgets->program_month_schedule_treestore;
    for(i = 0; i < 12; i++)
    {
        gchar *monthStr = g_strdup_printf(MONTH_FMT, i + 1);
        gchar *nameStr = (gchar*)MONTH_UNKNOWN;
        gint dayScheduleId = year->month[i].dayScheduleId;
        if( dayScheduleId > 0)
        {
            for(list = programChildListDay; list != NULL; list = list->next)
            {
                SplDaySchedule *day = (SplDaySchedule*)list->data;
                if(day && day->Id == dayScheduleId)
                {
                    nameStr = day->name;
                    break;
                }
            }
        }
        gtk_tree_store_append(store, &iter, NULL);
        gtk_tree_store_set(store, &iter,
                           SCHEDULE_MONTH_STORE_MONTH_COLUMN, monthStr,
                           SCHEDULE_MONTH_STORE_NAME_COLUMN, nameStr,
                           SCHEDULE_MONTH_STORE_ID_COLUMN, year->month[i].Id,
                           SCHEDULE_MONTH_STORE_SCHEDULE_ID_COLUMN, year->month[i].dayScheduleId,
                           SCHEDULE_MONTH_STORE_MONTH_INT_COLUMN, i + 1,
                           -1);
    }
    //update day schedule configuration
    store = program_widgets->program_item_schedule_treestore;
    if(programChildListDay)
    {
        for(list = programChildListDay; list != NULL; list = list->next)
        {
            spl_fill_day_schedule_configuration((SplDaySchedule*)list->data, store);
        }
    }

}

static void on_program_view_selection_changed(GtkTreeSelection *treeselection, gpointer user_data)
{
    GtkTreeModel *model;
    GtkTreeIter iter;
    if(!isLogining && gtk_tree_selection_get_selected(treeselection, &model, &iter))
    {
        SplZone *zone;
        gint type, progamId;
        gtk_tree_model_get(model, &iter,
                           OBJECT_POINTER_COLUMN, &zone,
                           OBJECT_TYPE_COLUMN, &type,
                           PROGRAM_ID_COLUMN, &progamId, -1);
        zoneID = -1;
        programID = -1;
        if(type == OBJECT_IS_PROGRAM_TYPE && zone)
        {
            zoneID = zone->zonecode;
            programID = progamId;
            //get database with this programId
            spl_program_schedule_fill_belong_information(progamId);

        }
        else
        {
            if(type == OBJECT_IS_ZONE_TYPE && zone)
                zoneID = zone->zonecode;
            gtk_tree_store_clear(program_widgets->program_item_schedule_treestore);
            gtk_tree_store_clear(program_widgets->program_month_schedule_treestore);
        }
        gtk_tree_model_filter_refilter(program_widgets->program_dcu_list_filter);
    }
}


static gboolean on_program_view_press_callback(GtkTreeView *treeview, GdkEventButton *event, gpointer userdata)
{
    GtkTreeIter iter;
    GtkTreePath *path;
    GtkTreeModel *model = gtk_tree_view_get_model(treeview);
    gint btnType = event->type;
    GtkTreeSelection *selection = gtk_tree_view_get_selection(treeview);
    switch(event->button)
    {
    case GDK_BUTTON_SECONDARY:
        if (gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(treeview), (gint) event->x, (gint) event->y, &path, NULL, NULL, NULL))
        {
            if(gtk_tree_model_get_iter(model, &iter, path))
            {
                gint type;
                gtk_tree_model_get(model, &iter, OBJECT_TYPE_COLUMN, &type, -1);
                gtk_widget_set_sensitive(program_info_popup_menu->M_Remove, type == OBJECT_IS_PROGRAM_TYPE);
                gtk_widget_show_all(GTK_WIDGET(program_info_popup_menu->M_Popup));
                gtk_menu_popup(GTK_MENU(program_info_popup_menu->M_Popup), NULL, NULL, NULL, NULL,
                               event ? event->button: 0, gdk_event_get_time((GdkEvent*)event));

            }
            if(!gtk_tree_selection_path_is_selected(selection, path))
            {
                gtk_tree_selection_select_path(selection, path);
            }
            gtk_tree_path_free(path);
            return TRUE;
        }
        break;
    default:
        break;
    }
    return FALSE;
}
static void spl_program_schedule_init_view()
{
    static gboolean isInitProgramView = FALSE;
    if(isInitProgramView)
        return;
    GtkTreeView *view;// = program_widgets->program_year_schedule_treeview;
    GtkTreeStore *store;// = program_widgets->program_year_schedule_treestore;
    GtkTreeViewColumn *column;
    GtkCellRenderer *render;
    GtkTreeSelection *selection;
    GtkWidget *separator_item;

    view = GTK_TREE_VIEW(SPL_OBJECT("program_year_schedule_treeview"));
    store = gtk_tree_store_new( (PROGRAM_ID_COLUMN + 1), G_TYPE_STRING, G_TYPE_POINTER, G_TYPE_INT, G_TYPE_INT);
    gtk_tree_view_set_model(view, GTK_TREE_MODEL(store));

    render = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Khu vực", render, "text", OBJECT_NAME_COLUMN, NULL);
    gtk_tree_view_append_column(view, column);

    gtk_tree_view_set_enable_search(view, TRUE);
    gtk_tree_view_set_search_column(view, OBJECT_NAME_COLUMN);
    gtk_tree_view_set_search_entry(view, GTK_ENTRY(SPL_OBJECT("program_list_search_entry")));

    selection = gtk_tree_view_get_selection(view);
    gtk_tree_selection_set_mode(selection, GTK_SELECTION_SINGLE);

    program_info_popup_menu = g_new0(struct SPL_PROGRAM_POPUP_MENU, 1);
    program_info_popup_menu->M_Popup = gtk_menu_new();
    SPL_MENU_CSS(program_info_popup_menu->M_Popup);

    program_info_popup_menu->M_Add = gtk_menu_item_new_with_label("Thêm mới");
    gtk_menu_shell_append(GTK_MENU_SHELL(program_info_popup_menu->M_Popup),program_info_popup_menu->M_Add);

    separator_item = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(program_info_popup_menu->M_Popup), separator_item);

    program_info_popup_menu->M_Remove= gtk_menu_item_new_with_label("Xóa");
    gtk_menu_shell_append(GTK_MENU_SHELL(program_info_popup_menu->M_Popup),program_info_popup_menu->M_Remove);


    //signal connect
    g_signal_connect(view, "button-press-event", G_CALLBACK(on_program_view_press_callback), NULL);
    g_signal_connect(selection, "changed", G_CALLBACK(on_program_view_selection_changed), NULL);
    g_signal_connect(program_info_popup_menu->M_Add, "activate",
                     (GCallback) smartstreetlight_program_popup_menu_clicked, GINT_TO_POINTER(SPL_PROGRAM_M_ADD));
    g_signal_connect(program_info_popup_menu->M_Remove, "activate",
                     (GCallback) smartstreetlight_program_popup_menu_clicked, GINT_TO_POINTER(SPL_PROGRAM_M_REMOVE));

    program_widgets->program_year_schedule_treeview = view;
    program_widgets->program_year_schedule_treestore = store;
    isInitProgramView = TRUE;
}

static gboolean  on_dcu_list_function_visible(GtkTreeModel *model, GtkTreeIter *iter, gpointer data)
{
    if(programID <= 0 || zoneID <= 0)
        return FALSE;
    pSplDcu dcu;
    gtk_tree_model_get(model, iter, OBJECT_POINTER_COLUMN, &dcu, -1);
    if(dcu && dcu->priv && dcu->priv->programId > 0)
    {
        /*DEBUG("zoneCode: %d programID: %d ==>RESULT: %d\n", dcu->priv->zonecode, dcu->priv->program,
              dcu->priv->program == programID && dcu->priv->zonecode == zoneID);
        */

        if(dcu->priv->programId == programID && dcu->priv->zonecode == zoneID)
        {
            /**if will autoupdate if status of dcu would be changed*/

            return TRUE;
        }
    }
    return FALSE;
}

static void spl_dcu_list_schedule_view_init()
{
    static gboolean isInitDcuListView = FALSE;
    if(isInitDcuListView)
        return;
    GtkTreeView         *view;
    GtkTreeStore        *store;
    GtkTreeModelFilter  *filter;
    GtkTreeIter         iter;
    GtkTreeViewColumn   *column;
    GtkCellRenderer     *render;

    view                = GTK_TREE_VIEW(SPL_OBJECT("program_dcu_list_treeview"));
    store               = gtk_tree_store_new(OBJECT_NUM_COLUMNS  + 2,
                          G_TYPE_STRING,
                          G_TYPE_POINTER,
                          G_TYPE_INT,
                          GDK_TYPE_PIXBUF,
                          GDK_TYPE_RGBA);


    render = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes ("Mã Trạm", render,
             "text", OBJECT_NAME_COLUMN,
             "foreground-rgba", OBJECT_NUM_COLUMNS  + 1,
             NULL);
    gtk_tree_view_column_set_resizable(column,TRUE);
    gtk_tree_view_column_set_reorderable(column, TRUE);
    gtk_tree_view_append_column (view, column);

    render = gtk_cell_renderer_pixbuf_new();
    column = gtk_tree_view_column_new_with_attributes ("Trạng thái", render,
             "pixbuf", OBJECT_NUM_COLUMNS, NULL);
    gtk_tree_view_column_set_resizable(column,TRUE);
    gtk_tree_view_column_set_reorderable(column, TRUE);
    gtk_tree_view_append_column (view, column);

    filter = GTK_TREE_MODEL_FILTER(gtk_tree_model_filter_new(GTK_TREE_MODEL(store), NULL));
    gtk_tree_model_filter_set_visible_func(filter, (GtkTreeModelFilterVisibleFunc)on_dcu_list_function_visible, NULL, NULL);
    gtk_tree_view_set_model(view, GTK_TREE_MODEL(filter));


    program_widgets->program_dcu_list_treeview  = view;
    program_widgets->program_dcu_list_treestore = store;
    program_widgets->program_dcu_list_filter    = filter;
    isInitDcuListView = TRUE;
}

static void spl_schedule_item_modify(SplDayScheduleItem *item)
{
    gint hStart, hEnd, mStart, mEnd;
    hStart = hEnd = mStart = mEnd = 0;
    gint level = 0;
    if(item)
    {
        hStart = item->timeBegin / 60;
        hEnd   =  (item->timeBegin + item->timeOn ) / 60;
        mStart = item->timeBegin % 60;
        mEnd = (item->timeBegin + item->timeOn) % 60;
        level = item->level / DIV_BRIGHTNESS;
    }
    passSignal = TRUE;
    gtk_combo_box_set_active(GTK_COMBO_BOX(SPL_OBJECT("cbb_startHour")), hStart);
    gtk_combo_box_set_active(GTK_COMBO_BOX(SPL_OBJECT("cbb_endHour")), hEnd);
    gtk_combo_box_set_active(GTK_COMBO_BOX(SPL_OBJECT("cbb_startMinute")), mStart);
    gtk_combo_box_set_active(GTK_COMBO_BOX(SPL_OBJECT("cbb_endMinute")), mEnd);
    gtk_adjustment_set_value(GTK_ADJUSTMENT(SPL_OBJECT("lcu_brightness_adjustment")), (gdouble)level);
    passSignal = FALSE;
    on_combo_box_time_activated(NULL, NULL);
}


static void copy_item_child_list(GSList *src, GSList **dest)
{
    GSList *item = src;
    spl_utils_free_slist(dest, (GDestroyNotify)g_free);
    for( ; item != NULL; item = item->next)
    {
        SplDayScheduleItem *itSrc = (SplDayScheduleItem*)item->data;
        SplDayScheduleItem *itDest = g_new0(SplDayScheduleItem, 1);
        itDest->Id          = itSrc->Id;
        itDest->level       = itSrc->level;
        itDest->parent      = itSrc->parent;
        itDest->timeBegin   = itSrc->timeBegin;
        itDest->timeOn      = itSrc->timeOn;
        *dest = g_slist_append(*dest, itDest);
        //DEBUG("SRC Start: %d On: %d Level: %d\n", itSrc->timeBegin, itSrc->timeOn, itSrc->level);
        //DEBUG("DEST Start: %d On: %d Level: %d\n", itDest->timeBegin, itDest->timeOn, itDest->level);
    }
}

static void spl_schedule_item_dialog_show(gint type, SplDaySchedule *day, SplDayScheduleItem *item)
{
    gint responseId;

    gboolean nameEnable = FALSE;
    dayTmp = NULL;
    GtkListStore *store = schedule_item_widgets->schedule_item_content_liststore;
    gtk_widget_set_sensitive(GTK_WIDGET(SPL_OBJECT("frame_config_schedule")), FALSE);
    switch(type)
    {
    case BTN_ITEM_ADD:
        gtk_label_set_text(GTK_LABEL(SPL_OBJECT("lb_schedule_tittle")), "Tạo mới");
        gtk_entry_set_text(GTK_ENTRY(SPL_OBJECT("schedule_item_name_entry")), "");
        nameEnable = TRUE;
        dayTmp = g_new0(SplDaySchedule, 1);
        dayTmp->name = NULL;
        gtk_list_store_clear(store);
        break;
    case BTN_ITEM_EDIT:
        gtk_label_set_text(GTK_LABEL(SPL_OBJECT("lb_schedule_tittle")), "Chỉnh sửa");
        if(!day || !day->name)
            return;
        //DEBUG("id: %s\n", day->name);
        dayTmp = day;
        gtk_list_store_clear(store);
        gtk_entry_set_text(GTK_ENTRY(SPL_OBJECT("schedule_item_name_entry")), day->name);
        if(day->itemlist)
        {
            copy_item_child_list(day->itemlist, &day->itemlistTmp);
            spl_item_dialog_fill_tree(item);
            if(item)
                on_btn_item_clicked(NULL, GINT_TO_POINTER(BTN_ITEM_EDIT));
        }
        break;
    }
    gtk_widget_set_sensitive(GTK_WIDGET(SPL_OBJECT("schedule_item_name_entry")), nameEnable);

    SPL_DIALOG_SHOW(main_widgets->schedule_item_new_dialog);
    while(responseId = gtk_dialog_run(GTK_DIALOG(main_widgets->schedule_item_new_dialog)))
    {
        switch(responseId)
        {
        case GTK_RESPONSE_OK:
            switch (type)
            {
                case BTN_ITEM_ADD:
                {
                    g_char_free(dayTmp->name);
                    gchar *name = (gchar*)gtk_entry_get_text(GTK_ENTRY(SPL_OBJECT("schedule_item_name_entry")));
                    if(!name  ||strlen(name) == 0)
                    {
                        GtkWidget *parent = stack_widget_active_top();
                        SPL_WARNING_POPUP(parent, "Tên không được để trống");
                        goto ___loop;
                    }
                    GSList *list = programChildListDay;
                    for( ; list!= NULL; list = list->next)
                    {
                        SplDaySchedule *cday = (SplDaySchedule*)list->data;
                        if(cday)
                        {
                            if(g_strcmp0(cday->name, name) == 0)
                            {
                                GtkWidget *parent = stack_widget_active_top();
                                SPL_WARNING_POPUP(parent, "Tên đã được sử dụng");
                                goto ___loop;
                            }
                        }
                    }
                    dayTmp->name        = g_strdup(name);
                    dayTmp->programId   = programID;
                }
                case BTN_ITEM_EDIT:
                {
                    SplSoap spl_soap;
                    gint soap_err = smartstreetlight_edit_list_schedule_execute(&spl_soap,dayTmp);
                    if(soap_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
                    {
                        DEBUG("update interface\n");
                        /**update interface*/
                        spl_program_schedule_fill_belong_information(dayTmp->programId);
                        goto ___exit;
                    }
                    else {
                        gchar * msg = g_strdup("Lỗi thêm mới danh sách lập lịch ngày. ");
                        GtkWidget *parent = stack_widget_active_top();
                        smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
                        g_char_free(msg);
                    }
                    DEBUG("update interface\n");
                }
                break;
            }
            break;
        default:
            switch (type)
            {
            case BTN_ITEM_EDIT:
                break;
            case BTN_ITEM_ADD:
                if(dayTmp)
                {
                    spl_day_schedule_free(dayTmp);
                    dayTmp = NULL;
                }
                break;
            }
            goto ___exit;
            break;
        }
___loop:
        continue;
    }
___exit:
    SPL_DIALOG_HIDE(main_widgets->schedule_item_new_dialog);
    gtk_widget_hide_on_delete(main_widgets->schedule_item_new_dialog);
}

static void on_schedule_item_btn_clicked(GtkButton *button,  gpointer userdata)
{
    GtkTreeView         *view = program_widgets->program_item_schedule_treeview;
    GtkTreeSelection    *selection = gtk_tree_view_get_selection(view);
    GtkTreeStore        *store =  program_widgets->program_item_schedule_treestore;
    GtkTreeModel        *model;
    GtkTreeIter         iter;
    gint hasSelected    = gtk_tree_selection_get_selected(selection, &model, &iter);
    gint type;
    gpointer            pObject;
    gchar *msg = NULL;
    SplDaySchedule      *day;
    SplDayScheduleItem  *item;
    SplSoap spl_soap;
    gint btn = GPOINTER_TO_INT(userdata);
    item = NULL;
    day = NULL;
    switch(btn)
    {
    case BTN_ITEM_EDIT:
        if(!hasSelected)
            return;
        gtk_tree_model_get(model, &iter, OBJECT_TYPE_COLUMN, &type, OBJECT_POINTER_COLUMN, &pObject, -1);
        if(type == OBJECT_IS_DAY_SCHEDULE_TYPE)
        {
            day  = (SplDaySchedule*)pObject;
            item = NULL;
        }
        else if(type == OBJECT_IS_ITEM_SCHEDULE_TYPE)
        {
            item = (SplDayScheduleItem*)pObject;
            day = item->parent;
        }
    case BTN_ITEM_ADD:
        if(programID <= 0)
            break;
        spl_schedule_item_dialog_show(btn, day, item);
        break;
    case BTN_ITEM_REMOVE:
        if(hasSelected)
        {
            gtk_tree_model_get(model, &iter, OBJECT_TYPE_COLUMN, &type, OBJECT_POINTER_COLUMN, &pObject, -1);
            if(type == OBJECT_IS_DAY_SCHEDULE_TYPE)
            {
                if(pObject)
                {
                    day = (SplDaySchedule*)pObject;
                    msg = g_strdup_printf("Bạn muốn xóa cấu hình \"%s\"?", day->name);
                    DEBUG("Xoa lap lich ngay voi id: %d\n", day->Id);
                    GtkWidget *parent = stack_widget_active_top();
                    if(SPL_QUESTION_POPUP(parent, msg) == GTK_RESPONSE_OK)
                    {
                        gint soap_err = smartstreetlight_remove_list_schedule_execute(&spl_soap,day->Id);
                        if(soap_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
                        {
                            gtk_tree_store_remove(program_widgets->program_item_schedule_treestore, &iter);
                        }
                        else
                        {
                            /*
                            spl_utils_message_box(GTK_WINDOW(main_widgets->main_window),
                                                  GTK_MESSAGE_WARNING,
                                                  GTK_BUTTONS_OK,
                                                  "Thao tác không thực hiện được");
                            */
                            gchar * msg = g_strdup("Lỗi xoá danh sách lập lịch ngày. ");
                            GtkWidget *parent = stack_widget_active_top();
                            smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
                            g_char_free(msg);
                        }

                    }
                }

            }
            else if(type == OBJECT_IS_ITEM_SCHEDULE_TYPE)
            {
                if(pObject)
                {
                    item = (SplDayScheduleItem*)pObject;
                    gchar *startime = convert_time_tick_to_string(item->timeBegin);
                    msg = g_strdup_printf("Bạn muốn xóa lịch lúc %s của cấu hình \"%s\"?",startime, item->parent->name);
                    DEBUG("Remove schedule Id: %d\n", item->Id);
                    GtkWidget *parent = stack_widget_active_top();
                    if(SPL_QUESTION_POPUP(parent, msg) == GTK_RESPONSE_OK)
                    {
                        gint soap_err = smartstreetlight_remove_schedule_execute(&spl_soap,item->Id);
                        if(soap_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
                        {
                            gtk_tree_store_remove(program_widgets->program_item_schedule_treestore, &iter);
                            if(item->parent)
                            {
                                SplDaySchedule *parent = item->parent;
                                parent->itemlist = g_slist_remove(parent->itemlist, item);
                            }
                        }
                        else
                        {
                            /*
                            spl_utils_message_box(GTK_WINDOW(main_widgets->main_window),
                                                  GTK_MESSAGE_WARNING,
                                                  GTK_BUTTONS_OK,
                                                  "Thao tác không thực hiện được");
                            */
                            gchar * msg = g_strdup("Lỗi xóa lập lịch. ");
                            GtkWidget *parent = stack_widget_active_top();
                            smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
                            g_char_free(msg);
                        }
                    }
                    g_char_free(startime);
                }
            }
        }
        break;
    }
    g_char_free(msg);
}

static void spl_day_schedule_init_view()
{
    static gboolean isInitDayview = FALSE;
    if(isInitDayview)
        return;
    GtkTreeIter         iter;
    GtkTreeViewColumn   *column;
    GtkCellRenderer     *render;
    GtkTreeView         *view;
    GtkTreeStore        *store;
    GtkTreeSelection    *selection;

    image_edit = GTK_IMAGE(SPL_OBJECT("image_edit"));
    image_remove = GTK_IMAGE(SPL_OBJECT("image_remove"));

    view    = GTK_TREE_VIEW(SPL_OBJECT("program_item_schedule_treeview"));
    store   = gtk_tree_store_new(ITEM_COUNT_COLUMNS,
                                 G_TYPE_STRING,
                                 G_TYPE_POINTER,
                                 G_TYPE_INT,
                                 G_TYPE_STRING,
                                 G_TYPE_STRING,
                                 G_TYPE_STRING,
                                 G_TYPE_INT);

    render = gtk_cell_renderer_text_new();
    g_object_set(render, "is-expanded", TRUE, NULL);
    column = gtk_tree_view_column_new_with_attributes("Tên cấu hình", render, "text", OBJECT_NAME_COLUMN, NULL);
    gtk_tree_view_append_column(view, column);

    render = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Tg bắt đầu", render, "text", ITEM_START_TIME_COLUMN, NULL);
    gtk_tree_view_append_column(view, column);

    render = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Tg kết thúc", render, "text", ITEM_END_TIME_COLUMN, NULL);
    gtk_tree_view_append_column(view, column);

    render = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Độ sáng", render, "text", ITEM_BRIGHTNESS_COLUMN, NULL);
    gtk_tree_view_append_column(view, column);
    /** Could not using this method, because it will raise so many things which could not be control
        render = gtk_cell_renderer_pixbuf_new();
        column = gtk_tree_view_column_new_with_attributes("", render, "pixbuf", ITEM_EDIT_COLUMN, "stock-size", 16,  NULL);
        gtk_tree_view_append_column(view, column);
        g_signal_connect(render, "button-press-event",
                         G_CALLBACK(on_schedule_item_icon_clicked), GINT_TO_POINTER(ITEM_EDIT_COLUMN));


        render = gtk_cell_renderer_pixbuf_new();
        g_object_set(render, "width", 16, NULL);
        column = gtk_tree_view_column_new_with_attributes("", render, "pixbuf", ITEM_REMOVE_COLUMN, "stock-size", 16, NULL);
        g_object_set(column, "sizing", GTK_TREE_VIEW_COLUMN_FIXED, "fixed-width", 16,  "max-width", 16, NULL);
        gtk_tree_view_append_column(view, column);
        g_signal_connect(render, "button-press-event",
                         G_CALLBACK(on_schedule_item_icon_clicked), GINT_TO_POINTER(ITEM_REMOVE_COLUMN));

    */
    gtk_tree_view_set_model(view, GTK_TREE_MODEL(store));
    selection = gtk_tree_view_get_selection(view);

    program_widgets->program_item_schedule_treeview = view;
    program_widgets->program_item_schedule_treestore = store;

    //signal connect
    g_signal_connect(SPL_OBJECT("schedule_btn_edit"), "clicked", G_CALLBACK(on_schedule_item_btn_clicked), GINT_TO_POINTER(BTN_ITEM_EDIT));
    g_signal_connect(SPL_OBJECT("schedule_btn_add"), "clicked", G_CALLBACK(on_schedule_item_btn_clicked), GINT_TO_POINTER(BTN_ITEM_ADD));
    g_signal_connect(SPL_OBJECT("schedule_btn_remove"), "clicked", G_CALLBACK(on_schedule_item_btn_clicked), GINT_TO_POINTER(BTN_ITEM_REMOVE));
}

gboolean smartstreetlight_program_schedule_init(void)
{
    program_widgets = g_slice_new(SPL_PROGRAM_Widgets);

    schedule_item_widgets = g_slice_new(SPL_SCHEDULE_ITEM_Widgets);

    spl_program_schedule_init_view();

    spl_month_schedule_init_view();

    spl_dcu_list_schedule_view_init();

    spl_day_schedule_init_view();

    if(!smartstreetlight_schedule_tree_view_init())
        return FALSE;
    if(!smartstreetlight_schedule_store_init())
        return FALSE;
    if(!smartstreetlight_schedule_item_element_init())
        return FALSE;
    /* if(!smartstreetlight_schedule_callback_init())
         return FALSE;
     if(!smartstreetlight_program_popup_menu_init())
         return FALSE;
     if(!smartstreetlight_schedule_day_popup_menu_init())
         return FALSE;
     if(!smartstreetlight_schedule_list_popup_menu_init())
         return FALSE;
     if(!smartstreetlight_schedule_item_popup_menu_init())
         return FALSE;


     gtk_widget_set_visible(GTK_WIDGET(SPL_OBJECT("program_id_current_show_label")), FALSE);
    */
    return TRUE;
}


static gboolean smartstreetlight_schedule_tree_view_init(void)
{
    GtkTreeViewColumn *column;
    GtkCellRenderer   *renderer;


    /** init for combobox text of day schedule new **/

    program_widgets->program_month_schedule_new_combobox = GTK_COMBO_BOX_TEXT(SPL_OBJECT("program_month_schedule_new_combobox"));
#if 0
    /** init for list item schedule **/
    program_widgets->program_item_schedule_treeview = GTK_TREE_VIEW(SPL_OBJECT("program_item_schedule_treeview"));

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes ("Tên", renderer, "text", ITEM_SCHEDULE_NAME_COLUMN, NULL);
    gtk_tree_view_column_set_resizable(column,TRUE);
    gtk_tree_view_column_set_reorderable(column, TRUE);
    gtk_tree_view_append_column (GTK_TREE_VIEW(program_widgets->program_item_schedule_treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes ("Thời gian mở", renderer, "text", ITEM_SCHEDULE_STARTTIME_COLUMN, NULL);
    gtk_tree_view_column_set_resizable(column,TRUE);
    gtk_tree_view_column_set_reorderable(column, TRUE);
    gtk_tree_view_append_column (GTK_TREE_VIEW(program_widgets->program_item_schedule_treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes ("Thời gian sáng", renderer, "text", ITEM_SCHEDULE_TIMEON_COLUMN, NULL);
    gtk_tree_view_column_set_resizable(column,TRUE);
    gtk_tree_view_column_set_reorderable(column, TRUE);
    gtk_tree_view_append_column (GTK_TREE_VIEW(program_widgets->program_item_schedule_treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes ("Mức sáng", renderer, "text", ITEM_SCHEDULE_LEVEL_COLUMN, NULL);
    gtk_tree_view_column_set_resizable(column,TRUE);
    gtk_tree_view_column_set_reorderable(column, TRUE);
    gtk_tree_view_append_column (GTK_TREE_VIEW(program_widgets->program_item_schedule_treeview), column);

    /** init for combobox text of day schedule change **/
#endif // 0
    program_widgets->list_schedule_combobox_change = GTK_COMBO_BOX(SPL_OBJECT("list_schedule_combobox_change"));

    /** init for list DCU used specific program **/


    return TRUE;
}

static gboolean smartstreetlight_schedule_store_init(void)
{
    /** init for YEAR program store **/
    gboolean isInitProgram = FALSE;
    if(isInitProgram)
        return FALSE;
#if 0
    // GDK_TYPE_PIXBUF, GDK_TYPE_RGBA //

    gtk_tree_view_set_model(GTK_TREE_VIEW(program_widgets->program_year_schedule_treeview),
                            GTK_TREE_MODEL(program_widgets->program_year_schedule_treestore));

    g_object_unref(G_OBJECT(program_widgets->program_year_schedule_treestore));



    program_widgets->program_month_schedule_new_liststore = gtk_list_store_new(1, G_TYPE_INT);

    gtk_combo_box_set_model(GTK_COMBO_BOX(program_widgets->program_month_schedule_new_combobox),
                            GTK_TREE_MODEL(program_widgets->program_month_schedule_new_liststore));

    g_object_unref(G_OBJECT(program_widgets->program_month_schedule_new_liststore));

    /** init tree store for list item schedule **/
    /*
        enum
        {
            ITEM_SCHEDULE_NAME_COLUMN = 0,

            ITEM_SCHEDULE_STARTTIME_COLUMN,
            ITEM_SCHEDULE_TIMEON_COLUMN,
            ITEM_SCHEDULE_LEVEL_COLUMN,

            ITEM_SCHEDULE_PROGRAM_ID_COLUMN,
            ITEM_SCHEDULE_LIST_ID_COLUMN,
            ITEM_SCHEDULE_ID_COLUMN,

            ITEM_SCHEDULE_TYPE_COLUMN,

            ITEM_SCHEDULE_NUM_COLUMNS
        };
    */
    program_widgets->program_item_schedule_treestore = gtk_tree_store_new(ITEM_SCHEDULE_NUM_COLUMNS,
            G_TYPE_STRING,      // Thang + name schedule
            G_TYPE_STRING,      // starttime
            G_TYPE_STRING,      // ontine
            G_TYPE_STRING,      // level
            G_TYPE_INT,         // program id
            G_TYPE_INT,         // schedule id
            G_TYPE_INT,        // list schedule id
            G_TYPE_INT);        // type column

    gtk_tree_view_set_model(GTK_TREE_VIEW(program_widgets->program_item_schedule_treeview),
                            GTK_TREE_MODEL(program_widgets->program_item_schedule_treestore));

    /** init for day schedule new **/

    program_widgets->day_schedule_liststore_change = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_INT);

    gtk_combo_box_set_model(GTK_COMBO_BOX(program_widgets->list_schedule_combobox_change),
                            GTK_TREE_MODEL(program_widgets->day_schedule_liststore_change));

    gtk_combo_box_set_entry_text_column(GTK_COMBO_BOX(program_widgets->list_schedule_combobox_change), 0);

    g_object_unref(G_OBJECT(program_widgets->day_schedule_liststore_change));
    /** init for dcu list used specific program **/
    /*
        enum
        {
            PROGRAM_DCU_LIST_NAME_COLUMN = 0,
            PROGRAM_DCU_LIST_STATUS_COLUMN,
            PROGRAM_DCU_LIST_RGBA_COLUMN,

            PROGRAM_DCU_LIST_ZONEID_COLUMN,
            PROGRAM_DCU_LIST_TYPE_COLUMN,

            PROGRAM_DCU_LIST_NUM_COLUMNS
        };
    */
    program_widgets->program_dcu_list_treestore = gtk_tree_store_new(PROGRAM_DCU_LIST_NUM_COLUMNS,
            G_TYPE_STRING, GDK_TYPE_PIXBUF, GDK_TYPE_RGBA,
            G_TYPE_INT, G_TYPE_INT);

    gtk_tree_view_set_model(GTK_TREE_VIEW(program_widgets->program_dcu_list_treeview),
                            GTK_TREE_MODEL(program_widgets->program_dcu_list_treestore));

    g_object_unref(G_OBJECT(program_widgets->program_dcu_list_treestore));


    /** init for list schedule item of special schedule **/
    gtk_combo_box_set_model(GTK_COMBO_BOX(gtk_builder_get_object (smartstreetlight_builder, "dcu_info_program_combobox")),
                            GTK_TREE_MODEL(program_list_store));


    /** init for avaliable value for hour combobox **/
    combobox_hour_list_store = gtk_list_store_new(1, G_TYPE_INT);
    combobox_minute_list_store = gtk_list_store_new(1, G_TYPE_INT);

    gtk_combo_box_set_model(GTK_COMBO_BOX(SPL_OBJECT("schedule_combobox_hour")),
                            GTK_TREE_MODEL(combobox_hour_list_store));

    gtk_combo_box_set_model(GTK_COMBO_BOX(SPL_OBJECT("schedule_combobox_minute")),
                            GTK_TREE_MODEL(combobox_minute_list_store));

    g_object_unref(program_list_store);
    g_object_unref(schedule_list_store);
    g_object_unref(combobox_hour_list_store);
    g_object_unref(combobox_minute_list_store);
#endif // 0
    isInitProgram = TRUE;
    return TRUE;
}

void smartstreetlight_program_show_all(void)
{
    GtkTreeIter iter;
    GtkTreeStore *store = program_widgets->program_year_schedule_treestore;
    g_return_if_fail(!IS_EMPTY_LIST_ZONE && store);

    gtk_tree_store_clear(store);

    GSList *item;
    //add all zone
    LIST_ZONE_FOR_EACH_ENTRY(item)
    {
        SplZone *zone = (SplZone*)item->data;
        if(zone)
        {
            gtk_tree_store_append(store, &iter, NULL);
            gtk_tree_store_set(store, &iter,
                               OBJECT_NAME_COLUMN, zone->zonename,
                               OBJECT_POINTER_COLUMN, zone,
                               OBJECT_TYPE_COLUMN, OBJECT_IS_ZONE_TYPE, -1);
            smartstreetlight_program_fill_program_of_zone(zone, &iter);
        }
    }
    //add all list dcu
    store = program_widgets->program_dcu_list_treestore;
    g_return_if_fail(!IS_EMPTY_LIST_DCU && store);
    LIST_DCU_FOR_EACH_ENTRY(item)
    {
        pSplDcu dcu = (pSplDcu)item->data;
        if(dcu && dcu->priv)
        {
            GdkRGBA *status_color = &BG_COLOR_ERROR;
            if (dcu->priv->status == ACTIVE_STATUS)
            {
                status_color = &BG_COLOR_NORMAL;
            }
            else if (dcu->priv->status & (ERROR_RF_DCU_STATUS       |
                                          ERROR_SYNC_MODE_STATUS          |
                                          ERROR_SYNC_LCU_STATUS           |
                                          ERROR_SYNC_LINE_STATUS          |
                                          ERROR_SCHEDULE_LCU_STATUS       |
                                          ERROR_MEM_STATUS                |
                                          MODE_MANUAL_STATUS                ))
            {
                status_color = &BG_COLOR_ERROR;
            }
            else if (dcu->priv->status & MODE_MANUAL_STATUS) // 0x111 & 0x100 = 0x100
            {
                status_color = &BG_COLOR_MANUAL;
            }
            gtk_tree_store_append(store, &iter, NULL);
            gtk_tree_store_set(store, &iter,
                               OBJECT_NAME_COLUMN, dcu->priv->id,
                               OBJECT_POINTER_COLUMN, dcu,
                               OBJECT_TYPE_COLUMN, OBJECT_IS_DCU_TYPE,
                               OBJECT_NUM_COLUMNS + 1, status_color, -1);
        }
    }
    gtk_tree_model_filter_refilter(program_widgets->program_dcu_list_filter);
}


static void smartstreetlight_schedule_choose_liststore_fill_information(gchar *listschedule_name, gint listschedule_id)
{
    GtkTreeIter iter;
    gtk_list_store_append(GTK_LIST_STORE(program_widgets->day_schedule_liststore_change), &iter);
    gtk_list_store_set(GTK_LIST_STORE(program_widgets->day_schedule_liststore_change), &iter,
                       0, listschedule_name,
                       1, listschedule_id, -1);
}


void smartstreetlight_program_fill_program_of_zone(SplZone *zone, GtkTreeIter *parent)
{
    GtkTreeIter iter;
    ns1__PROGRAM_USCOREINFO_USCOREType ** program = NULL;
    gint program_size;
    GtkTreeStore *store = program_widgets->program_year_schedule_treestore;
    SplSoap spl_soap;
    g_return_if_fail(!IS_EMPTY_LIST_ZONE && store && parent);
    gint soap_err = smartstreetlight_get_program_list_nofree_execute(&spl_soap,zone->zonecode,0, &program, &program_size);
    if (soap_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
    {
        if (program != NULL)
        {
            for(gint i = 0; i<program_size; i++)
            {
                gtk_tree_store_append(store, &iter, parent);
                gtk_tree_store_set(store, &iter, OBJECT_NAME_COLUMN, (const gchar *)program[i]->program_USCOREname,
                                   OBJECT_POINTER_COLUMN, zone,
                                   OBJECT_TYPE_COLUMN, OBJECT_IS_PROGRAM_TYPE,
                                   PROGRAM_ID_COLUMN, program[i]->program_USCOREid, -1);
            }
        }
    } else {
        gchar * msg = g_strdup("Lỗi lấy danh sách chương trình từ server. ");
        GtkWidget *parent = stack_widget_active_top();
        smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
        g_char_free(msg);

    }
    smartstreetlight_free_soap_operation(&spl_soap);
}



static void on_combo_box_time_activated(GtkComboBoxText *cbbt, gpointer data)
{
    gint hS, hE, mS, mE;
    g_return_if_fail(!passSignal);
    if(gtk_combo_box_get_active(GTK_COMBO_BOX(cbbt)) < 0)
    {
        gchar *content = gtk_combo_box_text_get_active_text(cbbt);
        //content chi chua 2 chu so
        gint len = strlen(content);
        if(len > 0 && content[0] >= '0' && content[0] <= '9'
           && ( len == 1 || content[1] >= '0' && content[1] <= '9'))
        {
            gint index;
            if(sscanf(content, "%d", &index) == 1 && index <= GPOINTER_TO_INT(data))
            {
                g_object_set(G_OBJECT(cbbt), "active", index, NULL);
                g_free(content);
                return;
            }
        }
        g_free(content);
    }
    hS = gtk_combo_box_get_active(GTK_COMBO_BOX(SPL_OBJECT("cbb_startHour")));
    hE = gtk_combo_box_get_active(GTK_COMBO_BOX(SPL_OBJECT("cbb_endHour")));
    mS = gtk_combo_box_get_active(GTK_COMBO_BOX(SPL_OBJECT("cbb_startMinute")));
    mE = gtk_combo_box_get_active(GTK_COMBO_BOX(SPL_OBJECT("cbb_endMinute")));
    gtk_widget_set_visible(GTK_WIDGET(SPL_OBJECT("image_startTime")), FALSE);
    gtk_widget_set_visible(GTK_WIDGET(SPL_OBJECT("image_endTime")), FALSE);
    GSList *item;
    if(!dayTmp)
    {
        startTime = endTime = -1;
        gtk_widget_set_visible(GTK_WIDGET(SPL_OBJECT("image_endTime")), TRUE);
        gtk_widget_set_visible(GTK_WIDGET(SPL_OBJECT("image_startTime")), TRUE);
        return;
    }
    //DEBUG("%02d:%02d - %02d:%02d\n", hS, mS, hE, mE);

    if(hS < 0 || mS < 0)
        goto __showImageStartFail;
    if(hE < 0 || mE < 0)
        goto __showImageEndFail;
    if(hS == 24 && mS > 0)
        goto __showImageStartFail;
    if(hE == 24 && mE > 0)
        goto __showImageEndFail;

    startTime = hS * 60 + mS;
    endTime = hE * 60 + mE;

    if(startTime >= endTime)
        goto __showImageEndFail;

    for(item = dayTmp->itemlistTmp; item != NULL; item = item->next)
    {
        SplDayScheduleItem *it = (SplDayScheduleItem*)item->data;
        if(it == itemTmp)
            continue;
        gint endtimeofitem = it->timeBegin + it->timeOn;
        if(startTime == it->timeBegin || startTime > it->timeBegin && startTime < endtimeofitem)
            goto __showImageStartFail;
        if(endTime == endtimeofitem || endTime > it->timeBegin && endTime < endtimeofitem)
            goto __showImageEndFail;
    }
    return;
__showImageStartFail:
    gtk_widget_set_visible(GTK_WIDGET(SPL_OBJECT("image_startTime")), TRUE);
    startTime = -1;
    return;
__showImageEndFail:
    gtk_widget_set_visible(GTK_WIDGET(SPL_OBJECT("image_endTime")), TRUE);
    endTime = -1;
    return;
}

static void btn_add_clicked()
{
    gint hS, hE, mS, mE;
    startTime = endTime = -1;
    hS = mS  =0;
    hE = 24;
    mE = 0;
    if(!dayTmp)
        return;
    itemTmp = NULL;
    dayTmp->itemlistTmp = g_slist_sort(dayTmp->itemlistTmp, (GCompareFunc)item_compare);
    GSList *it = dayTmp->itemlistTmp;

    if(g_slist_length(it) >= 10)
    {
        GtkWidget *parent = stack_widget_active_top();
        SPL_WARNING_POPUP(parent, "Không thể tạo hơn 10 lần bât tắt");
        return;
    }
    //find the suitable time
    gboolean first = FALSE;
    while(it)
    {
        SplDayScheduleItem *item1 = (SplDayScheduleItem*)it->data;
        if(!first && item1->timeBegin > 0)
        {
            hE = item1->timeBegin / 60;
            mE = item1->timeBegin % 60;
            break;
        }
        first = TRUE;
        GSList *next = it->next;
        if(next != NULL)
        {
            SplDayScheduleItem *item2 = (SplDayScheduleItem*)next->data;
            if(item1->timeBegin + item1->timeOn >= item2->timeBegin)
            {
                it = next;
                continue;
            }
            else
            {
                startTime = item1->timeBegin + item1->timeOn;
                endTime   = item2->timeBegin;
                hS = startTime / 60;
                mS = startTime % 60;
                hE = endTime / 60;
                mE = endTime % 60;
                break;
            }
        }
        else
        {
            if(item1->timeBegin + item1->timeOn >= FULL_MINUTE_OF_DAY)
            {
                GtkWidget *parent = stack_widget_active_top();
                SPL_WARNING_POPUP(parent, "Không còn thời gian thích hợp");
                return;
            }
            else
            {
                startTime = item1->timeBegin + item1->timeOn;
                endTime = FULL_MINUTE_OF_DAY;
                hS = startTime / 60;
                mS = startTime % 60;
                hE = endTime / 60;
                mE = endTime % 60;
            }
        }
        break;
    }
    DEBUG("hS: %d mS: %d hE: %d mE: %d\n", hS, mS, hE, mE);
    passSignal = TRUE;
    gtk_combo_box_set_active(GTK_COMBO_BOX(SPL_OBJECT("cbb_startHour")), hS);
    gtk_combo_box_set_active(GTK_COMBO_BOX(SPL_OBJECT("cbb_endHour")), hE);
    gtk_combo_box_set_active(GTK_COMBO_BOX(SPL_OBJECT("cbb_startMinute")), mS);
    gtk_combo_box_set_active(GTK_COMBO_BOX(SPL_OBJECT("cbb_endMinute")), mE);
    passSignal = FALSE;
    on_combo_box_time_activated(NULL, NULL);
}

static gboolean btn_accept_clicked()
{
    if(endTime < 1 || startTime < 0)
        return FALSE; //show infomation why this fail; //may be
    //DEBUG("=========================================================================>>>>>>>>>>\n");
    gint level = (gint)gtk_adjustment_get_value(GTK_ADJUSTMENT(SPL_OBJECT("lcu_brightness_adjustment")));
    if(itemTmp)
    {
        itemTmp->level = level * DIV_BRIGHTNESS;
        itemTmp->timeBegin = startTime;
        itemTmp->timeOn = endTime - startTime;
    }
    else
    {
        itemTmp = g_new0(SplDayScheduleItem, 1);
        itemTmp->level = level * DIV_BRIGHTNESS;
        itemTmp->timeBegin = startTime;
        itemTmp->timeOn = endTime - startTime;
        dayTmp->itemlistTmp = g_slist_append(dayTmp->itemlistTmp, itemTmp);
    }
    spl_item_dialog_fill_tree(NULL);
    return TRUE;

}


static void on_btn_item_clicked(GtkButton *btn, gpointer data)
{
    GtkTreeSelection    *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(schedule_item_widgets->schedule_item_content_treeview));
    GtkTreeIter         iter;
    GtkTreeModel        *model;
    gboolean            sensitive = FALSE;
    switch(GPOINTER_TO_INT(data))
    {
    case BTN_ITEM_ACCEPT:
        sensitive = !btn_accept_clicked();
        break;
    case BTN_ITEM_ADD:
        btn_add_clicked();
        sensitive = TRUE;
        break;
    case BTN_ITEM_EDIT:
        itemTmp = NULL;
        if(gtk_tree_selection_get_selected(selection, &model, &iter))
        {
            //get itemTmp;
            gtk_tree_model_get(model, &iter, NEW_ITEM_SCHEDULE_POINTER_COLUMN, &itemTmp, -1);
        }
        if(!itemTmp)
            return;
        sensitive = TRUE;
        spl_schedule_item_modify(itemTmp);
        break;
    case BTN_ITEM_REMOVE:
        itemTmp = NULL;
        if(gtk_tree_selection_get_selected(selection, &model, &iter))
        {
            //get itemTmp;
            gtk_tree_model_get(model, &iter, NEW_ITEM_SCHEDULE_POINTER_COLUMN, &itemTmp, -1);
            if(itemTmp)
            {
                dayTmp->itemlistTmp = g_slist_remove(dayTmp->itemlistTmp, itemTmp);
            }
            gtk_list_store_remove(schedule_item_widgets->schedule_item_content_liststore, &iter);
        }
        break;
    default:
        break;
    }
    gtk_widget_set_sensitive(GTK_WIDGET(SPL_OBJECT("frame_config_schedule")), sensitive);
    gtk_widget_set_sensitive(GTK_WIDGET(SPL_OBJECT("dialog_action_area_schedule")), !sensitive);
}


static gboolean smartstreetlight_schedule_item_element_init(void)
{

    static gboolean isInitSchedule = FALSE;
    GtkTreeViewColumn *column;
    GtkCellRenderer   *renderer;
    GtkTreeIter iter1, iter2;
    gint i = 0;

    if(isInitSchedule)
        return  FALSE;

    schedule_item_widgets->schedule_item_content_treeview = GTK_WIDGET(SPL_OBJECT("schedule_item_content_treeview"));
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes ("Thời gian mở", renderer, "text", NEW_ITEM_SCHEDULE_STARTTIME_COLUMN, NULL);
    gtk_tree_view_column_set_resizable(column,TRUE);
    gtk_tree_view_column_set_reorderable(column, TRUE);
    gtk_tree_view_append_column (GTK_TREE_VIEW(schedule_item_widgets->schedule_item_content_treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes ("Thời gian tắt", renderer, "text", NEW_ITEM_SCHEDULE_TIMEON_COLUMN, NULL);
    gtk_tree_view_column_set_resizable(column,TRUE);
    gtk_tree_view_column_set_reorderable(column, TRUE);
    gtk_tree_view_append_column (GTK_TREE_VIEW(schedule_item_widgets->schedule_item_content_treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes ("Mức sáng", renderer, "text", NEW_ITEM_SCHEDULE_LEVEL_COLUMN, NULL);
    gtk_tree_view_column_set_resizable(column,TRUE);
    gtk_tree_view_column_set_reorderable(column, TRUE);
    gtk_tree_view_append_column (GTK_TREE_VIEW(schedule_item_widgets->schedule_item_content_treeview), column);

    schedule_item_widgets->schedule_item_name_entry = GTK_WIDGET(SPL_OBJECT("schedule_item_name_entry"));
    schedule_item_widgets->schedule_item_commit_button = GTK_WIDGET(SPL_OBJECT("schedule_item_commit_button"));

    schedule_item_widgets->schedule_item_content_liststore = GTK_LIST_STORE(gtk_list_store_new(NEW_ITEM_SCHEDULE_NUM_COLUMNS,
            G_TYPE_STRING,      // starttime
            G_TYPE_STRING,      // timeon
            G_TYPE_STRING,      // level
            G_TYPE_INT,         // starttime int
            G_TYPE_INT,         // timeon int
            G_TYPE_INT,         // level int
            G_TYPE_POINTER));

    gtk_tree_view_set_model(GTK_TREE_VIEW(schedule_item_widgets->schedule_item_content_treeview),
                            GTK_TREE_MODEL(schedule_item_widgets->schedule_item_content_liststore));


    //set hour for hour combobox
    for(i = 0; i <= 24; i++)
    {
        gchar *item = g_strdup_printf("%d", i);
        gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(SPL_OBJECT("cbb_startHour")), i, NULL, item);
        gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(SPL_OBJECT("cbb_endHour")), i, NULL, item);
        g_free(item);
    }

    for(i = 0; i < 60; i++)
    {
        gchar *item = g_strdup_printf("%d", i);
        gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(SPL_OBJECT("cbb_startMinute")), i, NULL, item);
        gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(SPL_OBJECT("cbb_endMinute")), i, NULL, item);
        g_free(item);
    }
    //smartstreetlight_schedule_list_name_popup_menu_init();
    // smartstreetlight_schedule_list_content_popup_menu_init();

    /**signal connect*/
    g_signal_connect(SPL_OBJECT("cbb_startHour"), "changed", G_CALLBACK(on_combo_box_time_activated), GINT_TO_POINTER(24));
    g_signal_connect(SPL_OBJECT("cbb_endHour"), "changed", G_CALLBACK(on_combo_box_time_activated), GINT_TO_POINTER(24));
    g_signal_connect(SPL_OBJECT("cbb_startMinute"), "changed", G_CALLBACK(on_combo_box_time_activated), GINT_TO_POINTER(59));
    g_signal_connect(SPL_OBJECT("cbb_endMinute"), "changed", G_CALLBACK(on_combo_box_time_activated), GINT_TO_POINTER(59));

    g_signal_connect(SPL_OBJECT("btn_item_add"), "clicked", G_CALLBACK(on_btn_item_clicked), GINT_TO_POINTER(BTN_ITEM_ADD));
    g_signal_connect(SPL_OBJECT("btn_item_remove"), "clicked", G_CALLBACK(on_btn_item_clicked),GINT_TO_POINTER(BTN_ITEM_REMOVE) );
    g_signal_connect(SPL_OBJECT("btn_item_edit"), "clicked", G_CALLBACK(on_btn_item_clicked), GINT_TO_POINTER(BTN_ITEM_EDIT));
    g_signal_connect(SPL_OBJECT("btn_item_accept"), "clicked", G_CALLBACK(on_btn_item_clicked), GINT_TO_POINTER(BTN_ITEM_ACCEPT));



    isInitSchedule = TRUE;
    return TRUE;
}



static void smartstreetlight_program_popup_menu_clicked(GtkWidget *popup_menu_item, gpointer userdata)
{
    SPL_PROGRAM_POPUP_MENU_Enum type = (SPL_PROGRAM_POPUP_MENU_Enum)GPOINTER_TO_INT(userdata);
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(program_widgets->program_year_schedule_treeview));
    GtkTreeModel *model;
    GtkTreeIter iter;
    if(!gtk_tree_selection_get_selected(selection, &model, &iter))
        return;

    switch(type)
    {
    case SPL_PROGRAM_M_ADD:

        gboolean ret;
        do
        {
            ret = smartstreetlight_program_popup_menu_add_clicked();
        }
        while(!ret);

        break;
    case SPL_PROGRAM_M_SCHEDULE:
        //smartstreetlight_program_popup_menu_schedule_clicked();
        break;
    case SPL_PROGRAM_M_REMOVE:
    {
        if(programID <=0 )
            return;
        gchar *name, *msg;
        gtk_tree_model_get(model, &iter, OBJECT_NAME_COLUMN, &name, -1);
        msg = g_strdup_printf("Bạn muốn xóa chương trình \"%s\"?", name);
        GtkWidget *parent = stack_widget_active_top();
        if(SPL_QUESTION_POPUP(parent, msg) == GTK_RESPONSE_OK)
        {
            SplSoap spl_soap;
            gint soap_err = smartstreetlight_remove_program_execute(&spl_soap,programID);
            if(soap_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
                gtk_tree_store_remove(program_widgets->program_year_schedule_treestore, &iter);
            else{
                gchar * msg = g_strconcat("Lỗi xoá chương trình '", name,"'. ", NULL);
                GtkWidget *parent = stack_widget_active_top();
                smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
                g_char_free(msg);
            }
        }
        g_char_free(msg);
        g_char_free(name);

    }
    break;
    default:
        break;
    }
}


static gboolean smartstreetlight_program_popup_menu_add_clicked(void)
{
    gboolean exit_here = FALSE;
    GtkTreeIter      parent_iter, iter;
    GtkTreeModel     *model;
    GtkTreeSelection *selection;
    gint zone_id = -1;
    gint program_id=0;
    GtkWidget *new_program_entry_name = GTK_WIDGET(SPL_OBJECT("new_program_entry_name"));
    GtkWidget *add_program_label_error = GTK_WIDGET(SPL_OBJECT("add_program_label_error"));

    SPL_DIALOG_SHOW(main_widgets->create_schedule_dialog);
    gint response_id = gtk_dialog_run((GtkDialog *)main_widgets->create_schedule_dialog);

    const gchar *program_name = gtk_entry_get_text(GTK_ENTRY(SPL_OBJECT("new_program_entry_name")));

    switch(response_id)
    {
    case DIALOG_OK_RESPONSE:
        if(g_strcmp0(program_name, "")==0)
        {
            gtk_label_set_text(GTK_LABEL(add_program_label_error), "Thông tin tên program không được để trống!");
        }
        else
        {
            GtkTreeIter *zoneiter;
            GtkTreeIter addIter;
            selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(program_widgets->program_year_schedule_treeview));
            if(gtk_tree_selection_get_selected(selection, &model, &iter))
            {
                SplSoap spl_soap;
                if(gtk_tree_model_iter_parent(GTK_TREE_MODEL(model), &parent_iter, &iter))
                {
                    zoneiter = &parent_iter;
                }
                else
                    zoneiter = &iter;

                gint soap_err = smartstreetlight_add_program_execute(&spl_soap,zoneID, program_name, &program_id);
                if(soap_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
                {
                    DEBUG("Tao thanh cong\n");
                    if (program_id !=0)
                    {
                        DEBUG("update interface\n");
                        SplZone *zone;
                        GtkTreeStore *store = program_widgets->program_year_schedule_treestore;
                        gtk_tree_model_get(model, zoneiter, OBJECT_POINTER_COLUMN, &zone, -1);
                        gtk_tree_store_append(store, &addIter, zoneiter);
                        gtk_tree_store_set(store, &addIter,
                                           OBJECT_NAME_COLUMN, program_name,
                                           OBJECT_TYPE_COLUMN, OBJECT_IS_PROGRAM_TYPE,
                                           PROGRAM_ID_COLUMN, program_id,
                                           OBJECT_POINTER_COLUMN, zone, -1);
                    }
                    exit_here = TRUE;
                }
                else {

                    DEBUG("Tao that bai\n");
                    gchar * msg = g_strconcat("Lỗi thêm mới chương trình '", program_name,"'. ", NULL);
                    GtkWidget *parent = stack_widget_active_top();
                    smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
                    g_char_free(msg);
                }
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
        gtk_entry_set_text(GTK_ENTRY(new_program_entry_name), "");
        gtk_label_set_text(GTK_LABEL(add_program_label_error), "");
    }
    SPL_DIALOG_HIDE(main_widgets->create_schedule_dialog);
    return exit_here;
}

