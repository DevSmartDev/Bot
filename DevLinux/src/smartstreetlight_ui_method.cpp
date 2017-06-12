#include "smartstreetlight_ui_method.h"
#include "smartstreetlight_utils.h"
#include "smartstreetlight_error.h"

pthread_mutex_t waiting_show_mutex;

static GtkCssProvider* smartstreetlight_get_private_css_provide(CSSTYPE wid);

struct SPL_WAITING_Widgets *spl_waiting_widgets = NULL;

static void spl_waiting_init(void);
static gboolean spl_waiting_window_draw(GtkWidget *widget, cairo_t *cr, gpointer userdata);
static void spl_waiting_window_screen_changed(GtkWidget *widget, GdkScreen *old_screen, gpointer userdata);
/** =============================================================  **/


//GtkWidget *ui_gtk_builder_get_widget(const gchar *widget_name)
//{
//    GtkWidget tmp = (GtkWidget *)gtk_builder_get_object(smartstreetlight_builder, widget_name);
//    return tmp;
//}

void smartstreetlight_clear_list_store(GtkTreeModel *model)
{
    GtkTreeIter iter;

    if (gtk_tree_model_get_iter_first(model, &iter) == TRUE)
        gtk_list_store_clear(GTK_LIST_STORE(model));
}

void smartstreetlight_clear_tree_store(GtkTreeModel *model)
{
    GtkTreeIter iter;

    if (gtk_tree_model_get_iter_first(model, &iter) == TRUE)
        gtk_tree_store_clear(GTK_TREE_STORE(model));
}

void smartstreetlight_set_private_css_provide(CSSTYPE type, GtkWidget* widget)
{

    if(!GTK_IS_WIDGET(widget))
        return;

    GtkCssProvider *css = smartstreetlight_get_private_css_provide(type);

    if(css){
        #ifdef __UPDATE_ONLY_WIDGET
        GdkDisplay *display = gdk_display_get_default ();
        GdkScreen *screen = gdk_display_get_default_screen (display);
        gtk_style_context_add_provider_for_screen (screen,
        #else
        gtk_style_context_add_provider(gtk_widget_get_style_context(widget),
        #endif // __UPDATE_ONLY_WIDGET
        GTK_STYLE_PROVIDER(css), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        g_object_unref(css);
    }
}

static GtkCssProvider* smartstreetlight_get_private_css_provide(CSSTYPE wid)
{
    GtkCssProvider* css = gtk_css_provider_new();
    gchar *strcss;
    switch(wid){
        case CSS_FRAME:
            strcss = g_strdup("GtkFrame{border: 1px solid black;}");
            break;
        case CSS_TREEVIEW:
            strcss = g_strdup("GtkTreeView row:nth-child(even) {\
                              background-color: shade(@base_color, 0.9);\
                              }");
                              //background-color: mix(shade(@base_color, 0.9), green, 0.01);
            break;
        case CSS_TYPE_NONE:
            strcss = g_strdup("GtkTreeView column-header .button{\
                                background-image: -gtk-gradient(linear,\
                                left top,\
                                left bottom,\
                                color-stop(0.0,shade(@base_color, 0.9)),\
                                color-stop(0.83,shade(@base_color, 0.9)),\
                                color-stop(1.00,shade(@base_color, 0.9)));\
                                border-width: 1px;\
                                border-radius: 0;\
                                color: black;}");
            break;
        case CSS_MENU_BAR:
                strcss = g_strdup("GtkMenuBar{\
                                    border-width: 1px;\
                                    font-weight:bold;\
                                    }");

            break;
        case CSS_MENU:
                strcss = g_strdup("GtkMenu{\
                                    border-width: 1px;\
                                    border-color: shade(@base_color, 0.9);\
                                    background-color: mix(shade(@base_color, 0.9), green, 0.1);\
                                    }");
//                                    background-color: shade(@base_color, 0.95);
            break;
        case CSS_MENU_ITEM:
                strcss = g_strdup("GtkMenuItem{\
                                    border-width: 1px;\
                                    background-color: red;\
                                    }");
            break;
        case CSS_MENU_SEARCH:
                strcss = g_strdup("IFastDialogSearch.*.GtkEntry{\
                                    font: Monospace;\
                                    }");
            break;
        case CSS_MENU_NOTEBOOK:
                strcss = g_strdup("*.ifast-close-tab-button{\
                                    padding: 0;}\
                                  *.ifast-close-tab-button:focus{\
                                    padding: 0;\
                                    border-width: 0;\
                                    }");
            break;
        default:
            strcss = g_strdup("");
            break;
    }
    if(!gtk_css_provider_load_from_data(css, strcss, -1, NULL))
    {
        g_free(strcss);
        return NULL;
    }
    g_free(strcss);
    return css;
}



void smartstreetlight_run_notification_dialog(const gchar *content_text)
{
    GtkTextView *view = GTK_TEXT_VIEW(gtk_builder_get_object (smartstreetlight_builder, "notification_textview"));

    gtk_text_buffer_set_text(notification_text_buffer, content_text, strlen((char *)content_text));

    gtk_text_view_set_buffer(view, notification_text_buffer);
}


gboolean spl_get_current_select_iter(GtkTreeView *treeview, GtkTreeModel **model, GtkTreeIter *iter)
{
    GtkTreeSelection *selection;
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
    if (gtk_tree_selection_count_selected_rows(selection) == 1)
    {
        if(gtk_tree_selection_get_selected(selection, model, iter))
        {
            return TRUE;
        }
    }
    return FALSE;
}


void spl_notebook_tab_hide_show(GtkNotebook *notebook, gint pagenumber, gboolean is_show)
{
        GtkWidget *page;
        page = gtk_notebook_get_nth_page(notebook, pagenumber);
        if(is_show)
            gtk_widget_show(page);
        else
            gtk_widget_hide(page);
}



/** ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ **/
/** ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ **/
gboolean spl_ui_methods_init(void)
{
    spl_waiting_init();
    return TRUE;
}

static void spl_waiting_init(void)
{
    DEBUG("\n\n********************************* ENTER spl_waiting_init *****************************\n\n");
    spl_waiting_widgets = g_slice_new(SPL_WAITING_Widgets);

    spl_waiting_widgets->window = GTK_WIDGET(SPL_OBJECT("waiting_window"));
    gtk_window_set_decorated(GTK_WINDOW(spl_waiting_widgets->window), FALSE);
    spl_waiting_widgets->spinner = gtk_spinner_new();
    gtk_spinner_start(GTK_SPINNER(spl_waiting_widgets->spinner));
    #ifdef WIN32
    GdkScreen *screen = gdk_screen_get_default();
    if(screen)
    {
        DEBUG_1();
        gtk_widget_set_size_request(spl_waiting_widgets->window,
                                    gdk_screen_get_width(screen), gdk_screen_get_height(screen));
        gint x_pos = ((gint)gdk_screen_get_width(screen)-100)/2+50;
        gint y_pos = ((gint)gdk_screen_get_height(screen)-100)/2+50;
//        DEBUG("x: %d", x_pos);
//        DEBUG("y: %d", y_pos);
        GtkWidget *fix_widget = gtk_fixed_new();
        gtk_widget_set_size_request(GTK_WIDGET(fix_widget), 400, 400);
        gtk_widget_set_size_request(GTK_WIDGET(spl_waiting_widgets->spinner), 400, 400);
        gtk_container_add(GTK_CONTAINER(fix_widget), spl_waiting_widgets->spinner);
        gtk_fixed_put(GTK_FIXED(fix_widget), spl_waiting_widgets->window, x_pos, y_pos);
    }
    else
    {
        gtk_window_maximize(GTK_WINDOW(spl_waiting_widgets->window));
    }
    #else
    gtk_container_add(GTK_CONTAINER(spl_waiting_widgets->window), spl_waiting_widgets->spinner);
    gtk_window_maximize(GTK_WINDOW(spl_waiting_widgets->window));
    gtk_widget_set_app_paintable(spl_waiting_widgets->window, TRUE);
    g_signal_connect(G_OBJECT(spl_waiting_widgets->window), "draw", G_CALLBACK(spl_waiting_window_draw), NULL);
    g_signal_connect(G_OBJECT(spl_waiting_widgets->window), "screen-changed", G_CALLBACK(spl_waiting_window_screen_changed), NULL);
    spl_waiting_window_screen_changed(spl_waiting_widgets->window, NULL, NULL);
    #endif
}

void spl_ui_methods_finalize(void)
{
    gtk_widget_destroy(spl_waiting_widgets->window);
    g_slice_free(SPL_WAITING_Widgets, spl_waiting_widgets);
}

void spl_waiting_hide()
{
    DEBUG_1();
    SPL_DIALOG_HIDE(spl_waiting_widgets->window);
}


void spl_waiting_show()
{
    DEBUG_1();
    SPL_DIALOG_SHOW(spl_waiting_widgets->window);
    gtk_widget_show_all(spl_waiting_widgets->window);
//    gtk_widget_show(spl_waiting_widgets->spinner);
}

static gboolean spl_waiting_window_draw(GtkWidget *widget, cairo_t *cr, gpointer userdata)
{
   cairo_t *new_cr = gdk_cairo_create(gtk_widget_get_window(widget));

    if (spl_waiting_widgets->is_supports_alpha)
    {
        cairo_set_source_rgba (new_cr, 0.0, 0.2, 0.4, 0.3); /* transparent */
    }
    else
    {
        cairo_set_source_rgb (new_cr, 1.0, 1.0, 1.0); /* white */
    }

    /* draw the background */
    cairo_set_operator (new_cr, CAIRO_OPERATOR_SOURCE);
    cairo_paint (new_cr);
    cairo_destroy(new_cr);

    return FALSE;
}

static void spl_waiting_window_screen_changed(GtkWidget *widget, GdkScreen *old_screen, gpointer userdata)
{
    /* To check if the display supports alpha channels, get the visual */
    GdkScreen *screen = gtk_widget_get_screen(widget);
    GdkVisual *visual = gdk_screen_get_rgba_visual(screen);
    if (!visual)
    {
        DEBUG("Your screen does not support alpha channels!\n");
        visual = gdk_screen_get_system_visual(screen);
        spl_waiting_widgets->is_supports_alpha = FALSE;
    }
    else
    {
        DEBUG("Your screen supports alpha channels!\n");
        spl_waiting_widgets->is_supports_alpha = TRUE;
    }
    gtk_widget_set_visual(widget, visual);
}
