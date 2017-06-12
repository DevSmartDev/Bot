#ifndef SMARTSTREETLIGHT_CALLBACK_H
#define SMARTSTREETLIGHT_CALLBACK_H

#include "main.h"
#include "smartstreetlight_utils.h"

void on_dcu_selection_changed (GtkTreeSelection *selection, gpointer user_data);

gboolean smartstreetlight_callback_init(void);
//
//gboolean
//on_login_dialog_response                    (GtkDialog          *dialog,
//                                             gint               response_id,
//                                             gpointer           custom_data);
void
on_smartstreetlight_dcu_combobox_modified_clicked (GtkComboBox *widget,
                                                   gpointer     user_data);

gboolean
on_smartstreetlight_main_notebook_switch_page (GtkNotebook *notebook,
                                               GtkWidget   *page,
                                               guint        page_num,
                                               gpointer     user_data);

gboolean
on_smartstreetlight_program_year_treeview_clicked (GtkTreeView        *treeview,
                                                    GdkEventButton     *event,
                                                    gpointer           userdata);

gboolean
on_smartstreetlight_schedule_specical_clicked (GtkTreeView        *treeview,
                                                    GdkEventButton     *event,
                                                    gpointer           userdata);

gboolean
on_dcu_view_info_clicked                    (GtkTreeView        *treeview,
                                             GdkEventButton     *event,
                                             gpointer           userdata);

gboolean
on_smartstreetlight_lcu_specical_clicked    (GtkTreeView        *treeview,
                                             GdkEventButton     *event,
                                             gpointer           userdata);

gboolean
on_smartstreetlight_line_specical_clicked    (GtkTreeView        *treeview,
                                             GdkEventButton     *event,
                                             gpointer           userdata);

gboolean
on_smartstreetlight_dcu_choose_start_time   (GtkButton          *button,
                                             gpointer           userdata);

gboolean
on_smartstreetlight_dcu_update              (GtkButton          *button,
                                             gpointer           userdata);
//
//gboolean
//on_smartstreetlight_schedule_create_new     (GtkButton          *button,
//                                             gpointer           userdata);

gboolean
on_smartstreetlight_dcu_program_modified_clicked(GtkButton      *button,
                                                 gpointer       userdata);

gboolean
on_smartstreetlight_dcu_info_modified_clicked(GtkButton      *button,
                                                 gpointer       userdata);


void
on_smartstreetlight_schedule_timeon_on_change (GtkAdjustment *adjustment,
                                                  gpointer       user_data);

void
on_smartstreetlight_lcu_control_mode_combobox_modified_clicked (GtkComboBox *widget,
                                                                gpointer user_data);

gboolean
on_smartstreetlight_lcu_control_ison_state_changed (GtkWidget *widget,
                                                    GdkEvent  *event,
                                                    gpointer   user_data);

gboolean
on_smartstreetlight_login_custom_expander  (GtkWidget *widget,
                                            GdkEvent  *event,
                                            gpointer   user_data);

gboolean
on_smartstreetlight_current_username_login_activate(GtkLabel *label,
                                                    gchar    *uri,
                                                    gpointer  user_data);


gboolean
on_smartstreetlight_schedule_item_specical_clicked(GtkTreeView        *treeview,
                                                    GdkEventButton     *event,
                                                    gpointer           userdata);

gboolean on_smartstreetlight_dcu_info_hide_clicked(GtkButton *button, gpointer userdata);

gboolean on_smartstreetlight_dcu_active_info_reload_clicked(GtkButton *button, gpointer userdata);

void smartstreetlight_dcu_popup_menu_clicked(GtkWidget *popup_menu_item, gpointer userdata);

void smartstreetlight_popup_menu_show(GtkWidget *w, GdkEventButton *ev);

void spl_lcu_popup_menu_clicked(GtkWidget *w, gpointer usr_data);

void on_dcu_control_btn_clicked (GtkButton *button, gpointer   user_data);

gboolean spl_login_key_event(GtkWidget    *widget,
                             GdkEventKey  *event,
                             gpointer     user_data);
gboolean mouse_moved(GtkWidget *widget,GdkEvent *event, gpointer user_data);
gboolean on_gps_entry_changed_text(GtkEntry *entry, GdkEventKey *event, gpointer userdata);
#endif // SMARTSTREETLIGHT_CALLBACK_H
