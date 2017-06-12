#ifndef SMARTSTREETLIGHT_DCU_H_INCLUDED
#define SMARTSTREETLIGHT_DCU_H_INCLUDED


#include "main.h"
#include "smartstreetlight_utils.h"
#include "smartstreetlight_callback.h"
#include "smartstreetlight_ui_method.h"
#include "mapviewer.h"
/* status of DCU */
#define ACTIVE_STATUS					0x0
#define ERROR_RF_DCU_STATUS 			(1<<7)
#define ERROR_SYNC_MODE_STATUS 			(1<<8)
#define ERROR_SYNC_LCU_STATUS 			(1<<9)
#define ERROR_SYNC_LINE_STATUS 			(1<<10)
#define ERROR_SCHEDULE_LCU_STATUS 		(1<<11)
#define ERROR_SCHEDULE_LINE_STATUS 		(1<<12)
#define ERROR_LOCK_DCU_STATUS 			(1<<13)
#define ERROR_MEM_STATUS 				(1<<14)
#define MODE_MANUAL_STATUS 				(1<<15)
#define ONLINE_STATUS 					(1<<24)
#define DELETE_STATUS 					(1<<25)
#define ADD_STATUS 					    (1<<26)

#define MAX_DCU_MAYBE       20

typedef struct _SplZone
{
    gchar       *zonename;
    gint        zonecode;
    gchar       *zonenote;
    gboolean    isshowmap;
    GSList      *dculistzone;
    GtkTreeIter zoneIter;
}SplZone, *pSplZone;

typedef struct _SplDcuPrivate
{
    gchar           *id;
    gchar           *name;
    gchar           *phonenum;
    gchar           *note;
    gchar           *gps;
    gchar           *address;
    gchar           *zonename;
    gint            zonecode;
    gint            programId;
    gint            programIdPrev;
    gchar           *programName;
    gint            scheduleId;
    gint            mode;
    gint            status;
    GtkTreeIter     iter;


    GSList          *childlist;
    GHashTable      *childmap;

#define INIT_LIST_LCU(dcu) {\
    dcu->priv->childlist = NULL; \
    dcu->priv->childmap = g_hash_table_new_full(g_str_hash, g_str_equal,NULL, NULL);\
    }
#define IS_EMPTY_LIST_LCU(dcu)  (!(dcu && dcu->priv && dcu->priv->childlist))
#define LIST_LCU_FOR_EACH_ENTRY(dcu,item) \
                for(item = dcu->priv->childlist; item != NULL; item = item->next)
#define SIZE_LIST_LCU(dcu) g_slist_length(dcu->priv->childlist)
#define REMOVE_LIST_LCU(dcu,lcu) {\
            dcu->priv->childlist = g_slist_remove(dcu->priv->childlist, lcu); \
            g_hash_table_remove (dcu->priv->childmap,(gconstpointer )lcu->id); \
            }
#define PREPEND_LIST_LCU(dcu,lcu) {\
                    dcu->priv->childlist = g_slist_prepend(dcu->priv->childlist, lcu);\
                    g_hash_table_insert(dcu->priv->childmap, (gpointer )lcu->id,(gpointer ) lcu); \
                    }

#define FREE_LIST_LCU(dcu, free_func) {\
        if(IS_EMPTY_LIST_LCU(dcu)) {\
            spl_utils_free_slist(&dcu->priv->childlist, (GDestroyNotify)free_func);\
            if (dcu->priv->childmap) \
                g_hash_table_remove_all(dcumap); \
        } \
    }
#define LOCKUP_LIST_LCU(dcu, lcu_id, lcu) (\
    g_hash_table_lookup_extended(dcu->priv->childmap, lcu_id, \
                                        NULL, (gpointer*)&lcu) \
    )
}SplDcuPrivate;

typedef struct _SplDcu
{
    SplDcuPrivate   *priv;
    GtkTreeIter     controlIter;
}SplDcu, *pSplDcu;

typedef struct _SplDcuClosestUsing
{
    GTimeVal        last_edit_time;
    pSplDcu         dcu;
}SplDcuClosestUsing, *pSplDcuClosestUsing;

extern GSList *dculist;
extern GHashTable* dcumap;
#define IS_EMPTY_LIST_DCU  (dculist==NULL)
#define NEW_LIST_DCU \
                 if (dcumap == NULL) \
                        dcumap = g_hash_table_new_full(g_str_hash, g_str_equal,NULL, NULL); \

#define REMOVE_LIST_DCU(dcu) {\
                    SplZone * zone_define; \
                    dculist = g_slist_remove(dculist, dcu); /*delete this*/ \
                    g_hash_table_remove(dcumap, (gpointer )dcu->priv->id); \
                    if(LOCKUP_LIST_ZONE(&dcu->priv->zonecode,zone_define)) \
                    { \
                        if (zone_define)  \
                            zone_define->dculistzone =  g_slist_remove( zone_define->dculistzone, dcu); /*delete dcu in zone*/\
                    } \
                    spl_dcu_free(dcu); \
                }
#define PREPEND_LIST_DCU(dcu,zone) {\
                    dculist = g_slist_prepend(dculist, dcu);\
                    zone->dculistzone = g_slist_prepend(zone->dculistzone, dcu);\
                    g_hash_table_insert(dcumap, (gpointer )dcu->priv->id,(gpointer ) dcu); \
                    }
#define APPEND_LIST_DCU(dcu,zone) {\
                    dculist = g_slist_append(dculist, dcu);\
                    zone->dculistzone = g_slist_append(zone->dculistzone, dcu);\
                    g_hash_table_insert(dcumap, (gpointer )dcu->priv->id,(gpointer ) dcu); \
                    }
#define SIZE_LIST_DCU() g_slist_length(dculist)
#define FREE_LIST_DCU(free_func) { \
        if(dculist) \
            spl_utils_free_slist(&dculist, (GDestroyNotify)free_func); \
        if (dcumap) \
            g_hash_table_remove_all(dcumap); \
        }
#define FREE_LIST_DCU_FINAL(free_func) \
        if(dculist) \
            spl_utils_free_slist(&dculist, (GDestroyNotify)free_func); \
        if (dcumap) \
            g_hash_table_destroy(dcumap);

#define LIST_DCU_FOR_EACH_ENTRY(item) \
                for(item = dculist; item != NULL; item = item->next)

#define GET_DCU_FROM_LIST_DCU(index) \
                ((pSplDcu)(g_slist_nth(dculist,index))->data)

#define LOCKUP_LIST_DCU(dcuId,dcu) (\
    g_hash_table_lookup_extended(dcumap, (gpointer)dcuId, \
                                        NULL, (gpointer*)&dcu) \
    )
extern GSList *closestUsingDculist;
extern GSList *zonelist;
extern GHashTable* zonemap;
#define IS_EMPTY_LIST_ZONE  (zonelist==NULL)
#define NEW_LIST_ZONE \
                 if (zonelist == NULL) \
                        zonemap = g_hash_table_new_full(g_int_hash,  g_int_equal,NULL, NULL); \

#define REMOVE_LIST_ZONE(zone) {\
                    zonelist = g_slist_remove(zonelist, zone); /*delete this*/ \
                    g_hash_table_remove(zonemap, (gpointer )&zone->zonecode); \
                    }
#define PREPEND_LIST_ZONE(zone) {\
                    zonelist = g_slist_prepend(zonelist, zone);\
                    g_hash_table_insert(zonemap, (gpointer )&zone->zonecode,(gpointer ) zone); \
                    }
#define APPEND_LIST_ZONE(zone) {\
                    zonelist = g_slist_append(zonelist, zone);\
                    g_hash_table_insert(zonemap, (gpointer )&zone->zonecode,(gpointer ) zone); \
                    }
#define SIZE_LIST_ZONE() g_slist_length(zonelist)
#define FREE_LIST_ZONE(free_func) { \
        if(zonelist) \
            spl_utils_free_slist(&zonelist, (GDestroyNotify)free_func); \
        if (zonemap) \
            g_hash_table_remove_all(zonemap); \
        }
#define FREE_LIST_ZONE_FINAL(free_func) \
         if(zonelist) \
            spl_utils_free_slist(&zonelist, (GDestroyNotify)free_func); \
        if (zonemap) \
            g_hash_table_destroy(zonemap);

#define LIST_ZONE_FOR_EACH_ENTRY(item) \
                for(item = zonelist; item != NULL; item = item->next)
#define GET_ZONE_FROM_LIST_ZONE(index) \
            ((SplZone *)(g_slist_nth(zonelist, index)->data))
#define LOCKUP_LIST_ZONE(zonecode, zone) (\
    g_hash_table_lookup_extended(zonemap, (gpointer)zonecode, \
                                        NULL, (gpointer*)&zone) \
)

//extern pSplZone lastSelectedZone;
extern pSplDcu lastSelectedDcu;
extern pSplDcu dcuprev;
extern gboolean showAllLightEnable;
//extern GtkWidget *dcu_dialog_control;
extern gboolean isControlShow;

typedef enum SPL_DCU_POPUP_MENU_Enum
{
    SPL_DCU_M_ADD = 0,
    SPL_DCU_M_EDIT,
    SPL_DCU_M_LOG,
    SPL_DCU_M_SCHEDULE,
    SPL_DCU_M_REMOVE,
    SPL_DCU_M_REMOVE_ALL,
    SPL_DCU_M_CONTROL,

    SPL_DCU_M_NUMBER
} SPL_DCU_POPUP_MENU_Enum;


typedef struct _SplDcuMenuPopup
{
    GtkWidget *parent;
    GtkWidget *mAdd;
    GtkWidget *mEdit;
    GtkWidget *mLog;
    GtkWidget *mSchedule;
    GtkWidget *mRemove;
    GtkWidget *mRemove_all;
    GtkWidget *mControl;
} SplDcuMenuPopup;

enum SPL_DCU_MODE_Enum
{
    SPL_DCU_UnknownMode = 0,
    SPL_DCU_WirelessMode,
    SPL_DCU_LineMode,
    SPL_DCU_Init
};

// SPL_DCU_STATUS_Enum

#define    SPL_DCU_ERROR_RF             (1<<7)
#define    SPL_DCU_ERROR_SYNC_MODE      (1<<8)
#define    SPL_DCU_ERROR_SYNC_LCU       (1<<9)
#define    SPL_DCU_ERROR_SYNC_LINE      (1<<10)
#define    SPL_DCU_ERROR_SCHEDULE_LCU   (1<<11)
#define    SPL_DCU_ERROR_SCHEDULE_LINE  (1<<12)
#define    SPL_DCU_ERROR_LOCK_DCU       (1<<13)
#define    SPL_DCU_ERROR_MEM_DCU        (1<<14)
#define    SPL_DCU_MANUAL_MODE          (1<<15)
#define    SPL_DCU_ONLINE               (1<<24)


enum
{
    OBJECT_IS_UNKNOW    = -1,
    OBJECT_IS_ZONE_TYPE = 0,
    OBJECT_IS_DCU_TYPE,
    OBJECT_IS_LCU_TYPE,
    OBJECT_IS_PROGRAM_TYPE,
    OBJECT_IS_DAY_SCHEDULE_TYPE,
    OBJECT_IS_ITEM_SCHEDULE_TYPE,
};

enum
{
    DIALOG_CONTROL_IS_ON_OFF = 0,
    DIALOG_CONTROL_IS_SCHEDULE,
};

enum
{
    SPL_DCU_STORE = 0,
    SPL_LCU_STORE,
    SPL_LCU_ALL_STORE,
    SPL_LOG_STORE,
    SPL_SCHEDULE_STORE,
    SPL_PROGRAM_STORE,
    SPL_DCU_PROGRAM_STORE,
    SPL_MONTH_STORE,
};

enum
{
    OBJECT_NAME_COLUMN = 0,
    OBJECT_POINTER_COLUMN,
    OBJECT_TYPE_COLUMN,
    OBJECT_NUM_COLUMNS,
};

enum
{
    DIALOG_CONTROL_BTN_SELECT_ALL,
    DIALOG_CONTROL_BTN_DESELECT_ALL,
    DIALOG_CONTROL_BTN_QUIT,

    DIALOG_MANUAL_SUBMIT_SET,
    DIALOG_SCHEDULE_SUBMIT_SET
};

typedef struct _SplWidgets
{
    //dcu_info
    GtkTreeView     *dcu_view;
    GtkTreeStore    *dcu_store;
    //lcu_info
    GtkTreeView     *lcu_view;
    GtkTreeStore    *lcu_store;
    //lcu_all
    GtkTreeView     *lcu_all_view;
    GtkTreeStore    *lcu_all_store;
    GtkTreeModelFilter *lcu_all_filter;

}SplWidgets, *pSplWidgets;

enum
{
    DCU_SCHEDULE_INTERLEAVED_0   = 0,         // don't choose interleaved //
    DCU_SCHEDULE_INTERLEAVED_1_1 = 1,       // schedule 1 light on 1 light off //
    DCU_SCHEDULE_INTERLEAVED_2_2 = 2,       // schedule 1 light on 2 light off //
    DCU_SCHEDULE_INTERLEAVED_1_2 = 3        // schedule 1 light on 2 light off //
};
typedef struct _SplControlSchedule_Widgets
{
    // common widgets //
    GtkWidget       *dcu_control_window;
    GtkWidget       *dcu_control_core_frame_label;
    GtkWidget       *dcu_control_treeview;
    GtkWidget       *dcu_control_select_button_box;
    GtkWidget       *dcu_control_is_temp;
    GtkTreeStore    *dcu_control_lcu_list;

    // schedule setting widgets //
    GtkWidget       *dcu_schedule_program_box;
    GtkWidget       *dcu_schedule_program_comboboxtext;
    GtkWidget       *dcu_schedule_interleaved_comboboxtext;
    GtkListStore    *dcu_schedule_interleaved_liststore;
    GtkWidget       *dcu_schedule_summit_button;
    GtkListStore    *dcu_schedule_program_store;

    GSList          *dcu_schedule_lcu_sorted_list;

    // control maunal widgets //
    GtkWidget       *dcu_manual_level_grid;
    GtkWidget       *dcu_manual_summit_button;

}_SplControlSchedule_Widgets;

extern struct _SplControlSchedule_Widgets *dcu_control_schedule_widgets;

extern pSplWidgets  main_view_widgets;
extern SplDcuMenuPopup *dcu_popup_menu;

/** ***************************************************************************************************** **/

void spl_main_view_widgets_init();

void spl_dcu_set_information(pSplDcu dcu);

gboolean smartstreetlight_dcu_info_init(void);

void smartstreetlight_tree_store_clean(gint storeIndex);

//void smartstreetlight_dcu_get_info_form_sql(MYSQL_RES *data);

void smartstreetlight_dcu_finalize(void);

void smartstreetlight_dcu_show_specific_info(gchar *dcu_id, gchar *dcu_phone, gchar *dcu_gps, gchar *dcu_address,
                                             gchar *dcu_note, gchar *dcu_mode, gchar *dcu_status,
                                             gchar *dcu_lcu_program, gchar *dcu_line_program,
                                             gint dcu_zone_id, gchar *dcu_zone_name);

void smartstreetlight_dcu_show_all();

void smartstreetlight_dcu_choose_time(void);

void smartstreetlight_dcu_update(void);

void smartstreetlight_dcu_liststore_clean(void);

void smartstreetlight_dcu_fill_infomation(GtkTreeIter *zone_tree_iter,
                                          gchar *dcu_name,
                                           gchar *dcu_phone,
                                           gchar *dcu_gps,
                                           gchar *dcu_address,
                                           gchar *dcu_note,
                                           gchar *dcu_mode,
                                           gchar *dcu_status,
                                           gchar *dcu_lcu_program,
                                           gchar *dcu_line_program);

gchar * smartstreetlight_get_mode_name(SPL_DCU_MODE_Enum index);

gchar * smartstreetlight_get_status_mode(gint status);
gchar * smartstreetlight_get_status_name(gint status);
gchar * smartstreetlight_get_status_connect(gint status);
void smartstreetlight_dcu_popup_menu_show(GtkTreeView *treeview, GdkEventButton *event, gpointer userdata);

gboolean smartstreetlight_dcu_set_program(const gint zone_id, gchar *dcu_id, gchar *new_program_name);

void smartstreetlight_show_button_combobox(void);

void smartstreetlight_hide_button_combobox(void);

void smartstreetlight_dcu_schedule_setting(void);

void smartstreetlight_dcu_info_edit(void);

void smartstreetlight_dcu_log_connect_log_liststore_clean(void);
void smartstreetlight_dcu_log_dcu_log_liststore_clean(void);
void smartstreetlight_dcu_log_lcu_log_liststore_clean(void);
void smartstreetlight_dcu_log_line_log_liststore_clean(void);


void smartstreetlight_dcu_log_connect_log_fill_infomation(const gint event_id,
                                                          const gchar *event_dcu_id,
                                                          const gint event_type,
                                                          const gchar *event_content,
                                                          const gchar *event_time);

void smartstreetlight_dcu_log_dcu_log_fill_infomation(const gint event_id,
                                                      const gchar *event_dcu_id,
                                                      const gint event_type,
                                                      const gchar *event_content,
                                                      const gchar *event_time);

void smartstreetlight_dcu_log_lcu_log_fill_infomation(const gint event_id,
                                                      const gchar *event_dcu_id,
                                                      const gint event_type,
                                                      const gchar *event_content,
                                                      const gchar *event_time);

void smartstreetlight_dcu_log_line_log_fill_infomation(const gint event_id,
                                                      const gchar *event_dcu_id,
                                                      const gint event_type,
                                                      const gchar *event_content,
                                                      const gchar *event_time);

void smartstreetlight_zone_fill_infomation(const gint zone_id,
                                           const gchar *zone_name,
                                           const gchar *zone_note);

void spl_dcu_free(pSplDcu pDcu);
gboolean smartstreetlight_dcu_add_new(void);
gboolean smartstreetlight_dcu_edit(pSplDcu dcu);
void spl_delete_all_lcu_on_dcu(pSplDcu dcu);
void spl_add_new_dcu_into_closest_list(pSplDcu dcu);
void spl_closeset_list_sort();

void spl_zone_free(void *data);

pSplDcu spl_dcu_init();


void spl_dcu_control_display_light_on_map();
void spl_dcu_control_set_all_selected(gboolean select);
void spl_dcu_select_iter_of_light(OsmGpsMapImage *im);

/** Fill runtime data into lcu's data struct @by alvinnguyen **/
void * spl_lcu_runtime_data_update(gpointer data);

void * spl_dcu_runtime_data_update(gpointer data);

void spl_dcu_control_execute();

void osm_osm_gps_map_show_lights(pSplDcu dcu);
/** ------------------------------------------------------------------------------ **/
 /* ------------------------------------------------------------------------------ */
 /*                             CONTROL AND SCHEDULE FOR DCU                       */
/** ------------------------------------------------------------------------------ **/

void spl_dcu_control_dialog_show(gint type, pSplDcu dcu);

gboolean on_combo_box_display_changed(GtkWidget *cbb, gpointer p);
void osm_osm_gps_map_show_lights(gint index, pSplDcu dcu);
void osm_gps_map_show_lights_of_zone(pSplDcu dcu);
void osm_osm_gps_map_remove_dcu( pSplDcu dcu);
void osm_gps_map_show_lights_of_dcu(pSplDcu dcu);
void map_image_remove_all();
gboolean spl_dcu_info_show_tab_on_notebook();
void spl_zone_clear_is_show();
/** ------------------------------------------------------------------------------ **/
/** ------------------------------------------------------------------------------ **/
/** ------------------------------------------------------------------------------ **/


#endif // SMARTSTREETLIGHT_DCU_H_INCLUDED