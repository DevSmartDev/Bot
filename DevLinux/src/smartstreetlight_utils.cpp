#include "main.h"
#include "smartstreetlight_utils.h"
#include "smartstreetlight_lcu.h"
#include "smartstreetlight_dcu.h"
#include <map>
#include "mapviewer.h"
#include "smartstreetlight_soap.h"
#include "smartstreetlight_error.h"
SmartStreetLight_Widgets	*main_widgets;
GtkBuilder               *smartstreetlight_builder;

GdkRGBA BG_COLOR_UNKNOWN           = {0,0,0,1};
GdkRGBA BG_COLOR_NORMAL            = {0,0,0,1};
GdkRGBA BG_COLOR_ACTIVE            = {0,1,0,1};
GdkRGBA BG_COLOR_ERROR             = {1,0,0,1};
GdkRGBA BG_COLOR_OFF               = {1,1,1,0.3};
GdkRGBA BG_COLOR_MANUAL            = {0.5,0,0.4,1};


gboolean spl_utils_mkdir(const gchar *path, gboolean create_parent_dirs)
{
	gint mode = 0700;
	gboolean result;

	if (path == NULL || strlen(path) == 0)
		return FALSE;

	result = (create_parent_dirs) ? g_mkdir_with_parents(path, mode) : g_mkdir(path, mode);
	if (result != 0)
		return FALSE;

	return TRUE;
}


void spl_utils_widgets_hide_all(void)
{
//    gtk_widget_hide(main_widgets->login_dialog);
//	gtk_widget_hide(main_widgets->main_window);
#ifndef WIN32
	gtk_window_close(GTK_WINDOW(main_widgets->main_window));
#endif
//    gtk_widget_set_visible(main_widgets->main_window, FALSE);
//	gtk_widget_hide(main_widgets->create_schedule_dialog);
//	gtk_widget_hide(main_widgets->lcu_info_dialog);
//	gtk_widget_hide(main_widgets->starttime_choose_dialog);
//	gtk_widget_hide(main_widgets->dcu_update_window);
//
//	gtk_widget_hide(main_widgets->add_dcu_dialog);
//	gtk_widget_hide(main_widgets->delete_element_dialog);
//	gtk_widget_hide(main_widgets->notification_dialog);
//	gtk_widget_hide(main_widgets->edit_dcu_dialog);
//
//    gtk_widget_hide(main_widgets->lcu_info_box);
//	gtk_widget_hide(main_widgets->add_lcu_dialog);
//	gtk_widget_hide(main_widgets->lcu_control_dialog);
//
//	gtk_widget_hide(main_widgets->line_info_box);
//	gtk_widget_hide(main_widgets->add_line_dialog);
//
//	gtk_widget_hide(main_widgets->new_schedule_dialog);
//
//	gtk_widget_hide(main_widgets->program_choose_dialog);
//
//    gtk_widget_hide(main_widgets->devices_log_dialog);
//
//    gtk_widget_hide(main_widgets->day_schedule_dialog_new);
//
//    gtk_widget_hide(main_widgets->schedule_item_new_dialog);
//
//    gtk_widget_hide(main_widgets->dcu_custom_program_dialog);
}


//
//MYSQL                    *smartlight_sql_connection;



gint spl_utils_message_box(GtkWindow *parent, GtkMessageType type, GtkButtonsType btn, const gchar* msg)
{
    GtkWidget *dlg;
    gint responseId;

    dlg = gtk_message_dialog_new(parent, (GtkDialogFlags)(GTK_DIALOG_DESTROY_WITH_PARENT | GTK_DIALOG_MODAL), type, btn, msg);
    /* Check if parent is different from main_window */
    //if (parent != GTK_WINDOW(main_widgets->main_window))
    {
        gtk_window_set_modal(GTK_WINDOW(GTK_DIALOG(dlg)), TRUE);
        gtk_window_set_transient_for(GTK_WINDOW(GTK_DIALOG(dlg)), GTK_WINDOW(parent));
        gtk_widget_set_sensitive(GTK_WIDGET(parent), FALSE);
    }
    //else /* main_window need to check */
    //{
       //set_parent_widget_active(dlg);
    //}
    /* Make window transient for the root window */
    gtk_widget_show_all(dlg);
    responseId = gtk_dialog_run(GTK_DIALOG(dlg));
    gtk_widget_set_sensitive(GTK_WIDGET(parent), TRUE);
    gtk_widget_destroy(dlg);
    return responseId;
}

void spl_utils_free_slist(GSList **list, GDestroyNotify free_func)
{
    g_return_if_fail(*list);
    //DEBUG("Before free: %p %d\n", free_func, g_slist_length(*list));
    if(free_func == (GDestroyNotify)NULL)
        g_slist_free(*list);
    else
        g_slist_free_full(*list, free_func);
    //DEBUG("After free: %p %d\n", free_func, g_slist_length(*list));
    *list = NULL;
}


/**
 *  Wraps g_key_file_get_integer() to add a default value argument.
 *
 *  @param config A GKeyFile object.
 *  @param section The group name to look in for the key.
 *  @param key The key to find.
 *  @param default_value The default value which will be returned when @a section or @a key
 *         don't exist.
 *
 *  @return The value associated with @a key as an integer, or the given default value if the value
 *          could not be retrieved.
 **/
gint utils_get_setting_integer(GKeyFile *config, const gchar *section, const gchar *key,
							   const gint default_value)
{
	gint tmp;
	GError *error = NULL;

	if (G_UNLIKELY(config == NULL))
		return default_value;

	tmp = g_key_file_get_integer(config, section, key, &error);
	if (error)
	{
		g_error_free(error);
		return default_value;
	}
	return tmp;
}

/**
 *  Wraps g_key_file_get_boolean() to add a default value argument.
 *
 *  @param config A GKeyFile object.
 *  @param section The group name to look in for the key.
 *  @param key The key to find.
 *  @param default_value The default value which will be returned when @c section or @c key
 *         don't exist.
 *
 *  @return The value associated with @a key as a boolean, or the given default value if the value
 *          could not be retrieved.
 **/
gboolean utils_get_setting_boolean(GKeyFile *config, const gchar *section, const gchar *key,
								   const gboolean default_value)
{
	gboolean tmp;
	GError *error = NULL;

	if (G_UNLIKELY(config == NULL))
		return default_value;

	tmp = g_key_file_get_boolean(config, section, key, &error);
	if (error)
	{
		g_error_free(error);
		return default_value;
	}
	return tmp;
}


/**
 *  Wraps g_key_file_get_string() to add a default value argument.
 *
 *  @param config A GKeyFile object.
 *  @param section The group name to look in for the key.
 *  @param key The key to find.
 *  @param default_value The default value which will be returned when @a section or @a key
 *         don't exist.
 *
 *  @return A newly allocated string, either the value for @a key or a copy of the given
 *          default value if it could not be retrieved.
 **/
gchar *utils_get_setting_string(GKeyFile *config, const gchar *section, const gchar *key,
								const gchar *default_value)
{
	gchar *tmp;

	if (G_UNLIKELY(config == NULL))
		return g_strdup(default_value);

	tmp = g_key_file_get_string(config, section, key, NULL);
	if (!tmp)
	{
		return g_strdup(default_value);
	}
	return tmp;
}


/**
 *  Converts the given UTF-8 encoded string into locale encoding.
 *  On Windows platforms, it does nothing and instead it just returns a copy of the input string.
 *
 *  @param utf8_text UTF-8 encoded text.
 *
 *  @return The converted string in locale encoding, or a copy of the input string if conversion
 *    failed. Should be freed with g_free(). If @a utf8_text is @c NULL, @c NULL is returned.
 **/
gchar *utils_get_locale_from_utf8(const gchar *utf8_text)
{
#ifdef WIN32
	/* just do nothing on Windows platforms, this ifdef is just to prevent unwanted conversions
	 * which would result in wrongly converted strings */
	return g_strdup(utf8_text);
#else
	gchar *locale_text;

	if (! utf8_text)
		return NULL;
	locale_text = g_locale_from_utf8(utf8_text, -1, NULL, NULL, NULL);
	if (locale_text == NULL)
		locale_text = g_strdup(utf8_text);
	return locale_text;
#endif
}

/**
 * Writes @a text into a file named @a filename.
 * If the file doesn't exist, it will be created.
 * If it already exists, it will be overwritten.
 *
 * @warning You should use @c g_file_set_contents() instead if you don't need
 * file permissions and other metadata to be preserved, as that always handles
 * disk exhaustion safely.
 *
 * @param filename The filename of the file to write, in locale encoding.
 * @param text The text to write into the file.
 *
 * @return 0 if the file was successfully written, otherwise the @c errno of the
 *         failed operation is returned.
 **/
gboolean utils_write_file(const gchar *filename, const gchar *text)
{
	g_return_val_if_fail(filename != NULL, FALSE);
	g_return_val_if_fail(text != NULL, FALSE);
    FILE *fp;
    gsize bytes_written, len;
    gboolean fail = FALSE;
    if (filename == NULL)
    {
        return FALSE;
    }
    len = strlen(text);
    fp = g_fopen(filename, "w");

    if (fp == NULL)
    {
        fail = TRUE;
    }
    else
    {
        bytes_written = fwrite(text, sizeof(gchar), len, fp);
        if (len != bytes_written)
        {
            fail = TRUE;
        }
        if (fclose(fp) != 0)
            fail = TRUE;
    }
    if (fail)
    {
        return FALSE;
    }

	return TRUE;
}

gchar *get_homedir(void)
{
    gchar *home_dir;
#ifdef _WIN32
//    snprintf(homedir, 1024, "%s%s", getenv("HOMEDRIVE"), getenv("HOMEPATH"));
    home_dir = g_strdup_printf("%s%s", getenv("HOMEDRIVE"), getenv("HOMEPATH"));
#else
//    snprintf(homedir, 1024, "%s", getenv("HOME"));
    home_dir = g_strdup(getenv("HOME"));
#endif
    return home_dir;
}

gboolean osm_gps_map_change_parent(const gchar* oldparent, const gchar* newparent)
{
    if(!GTK_IS_WIDGET(map))
        return FALSE;
    OsmGpsMap *tmp = map;
    map = (OsmGpsMap *)g_object_ref(tmp);
    gtk_container_remove(GTK_CONTAINER(SPL_OBJECT(oldparent)), GTK_WIDGET(tmp));
    gtk_box_pack_start (
                GTK_BOX(SPL_OBJECT(newparent)),
                GTK_WIDGET(map), TRUE, TRUE, 0);
    return TRUE;
}


gboolean osm_gps_map_set_lcu_center(gpointer data)
{
    pSplLcu lcu = (pSplLcu)data;
    if(lcu != NULL)
    {
        gchar delimiter;
        gfloat lat, lon;
        if(sscanf(lcu->gps, "%f-%f", &lat,  &lon) != 2)
        {
#ifdef SET_LOCATION_ROOT
            ROOT_GPS(lat, lon);
#else
            HOME_GPS(lat, lon);
#endif
        }

        osm_gps_map_set_center(map, lat, lon);
    }
}


/**
* NOTE: please read this information before USE
* ObjMove must be assigned value: ObjMove->type and ObjMove->image
* ObjMove->name and ObjMove->image must be constant value and don't free these values, important.
* ObjMove->object is lcu or dcu pointer, it must be assigned before call this function
* This function will be updated the gps of Object automatic when you press Accept (Đồng ý) Button
* If you press Cancel (Đóng) button or close this dialog it will not update
*/

static gboolean spl_object_update_gps()
{
    SplSoap spl_soap;
    gboolean ret = TRUE;
    switch(ObjMove->type)
    {
    case OBJECT_IS_DCU_TYPE:
        {

            pSplDcu dcu = (pSplDcu)ObjMove->object;
            g_free(dcu->priv->gps);
            dcu->priv->gps = g_strdup_printf("%f-%f", ObjMove->lat, ObjMove->lon);
            gint soap_err = smartstreetlight_edit_dcu_execute(&spl_soap,dcu);
            if(soap_err != ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
            {
                gchar * msg = g_strconcat("Lỗi định vị gps cho trạm có id là ", dcu->priv->id,". ", NULL);
                GtkWidget *parent = stack_widget_active_top();
                smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
                g_char_free(msg);
                ret = FALSE;
            }
        }
        break;
    case OBJECT_IS_LCU_TYPE:
        {
            pSplLcu lcu = (pSplLcu)ObjMove->object;
            g_free(lcu->gps);
            lcu->gps = g_strdup_printf("%f-%f", ObjMove->lat, ObjMove->lon);
            gint soap_err = smartstreetlight_edit_lcu_execute(&spl_soap,lcu);
            if(soap_err != ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
            {
                gchar * msg = g_strconcat("Lỗi định vị gps cho đèn có id là %s của trạm có id là ", lcu->id, lcu->parent->priv->id,". ", NULL);
                GtkWidget *parent = stack_widget_active_top();
                smartstreetlight_error_check_message_result(GTK_WIDGET(parent), msg, soap_err);
                g_char_free(msg);
                ret = FALSE;
            }
        }
        break;
    default:
        ret = FALSE;
    }
    return ret;
}

void osm_gps_map_move_object()
{
    g_return_if_fail(ObjMove && ObjMove->image && ObjMove->object);
    gint handleId, responseId;
    gchar *devType;
    gfloat oldLat, oldLon;
    gchar  *oldGpsStr, *idStr, *latStr, *lonStr;
    gint zoom;

    GtkContainer *parent;
    OsmGpsMap *tmp = map;
    /**Init widget*/
    if(ObjMove->dialog == NULL)
    {
        ObjMove->dialog     = GTK_WIDGET(SPL_OBJECT("dialog_change_gps"));
        ObjMove->lat_entry  = GTK_ENTRY(SPL_OBJECT("setting_gps_entry_lat"));
        ObjMove->lon_entry  = GTK_ENTRY(SPL_OBJECT("setting_gps_entry_lon"));
        ObjMove->lbname     = GTK_LABEL(SPL_OBJECT("setting_gps_lb_name"));
        ObjMove->lbdevice   = GTK_LABEL(SPL_OBJECT("setting_gps_lb_device"));
        ObjMove->map_box    = GTK_BOX(SPL_OBJECT("change_gps_map_box"));
        //signal connection
        g_signal_connect(ObjMove->lat_entry, "key-press-event", G_CALLBACK(on_gps_entry_changed_text), (gpointer)0);
        g_signal_connect(ObjMove->lon_entry, "key-press-event", G_CALLBACK(on_gps_entry_changed_text), (gpointer)1);
    }
    /**get map*/
    g_object_get (G_OBJECT (map), "parent", &parent, NULL);
    if(!parent)
        return;
     /**backup map*/
    tmp = map;
    zoom = osm_gps_map_get_zoom(map);
    map = (OsmGpsMap*)g_object_ref(tmp);
    gtk_container_remove(parent, GTK_WIDGET(tmp));
    gtk_box_pack_start (GTK_BOX(ObjMove->map_box), GTK_WIDGET(map), TRUE, TRUE, 0);

    //gtk_window_maximize(GTK_WINDOW(ObjMove->dialog));
    GdkScreen *screen = gdk_screen_get_default();
    if(screen)
        gtk_widget_set_size_request(ObjMove->dialog,
                                gdk_screen_get_width(screen), gdk_screen_get_height(screen));
    gtk_window_set_transient_for(GTK_WINDOW(ObjMove->dialog), GTK_WINDOW(main_widgets->main_window));
    gtk_widget_show(ObjMove->dialog);
    switch(ObjMove->type)
    {
    case OBJECT_IS_DCU_TYPE:
        {
            pSplDcu dcu = (pSplDcu)ObjMove->object;
            oldGpsStr   = dcu->priv->gps;
            idStr       = dcu->priv->id;
            devType     = g_strdup("Mã trạm:");
        }
        break;
    case OBJECT_IS_LCU_TYPE:
        {
            pSplLcu lcu = (pSplLcu)ObjMove->object;
            oldGpsStr   = lcu->gps;
            idStr       = lcu->id;
            devType     = g_strdup("Mã đèn:");
        }
        break;
    default: //it don't be assigned yet
        return;
    }
    gtk_label_set_text(ObjMove->lbdevice, devType);
    gtk_label_set_text(ObjMove->lbname, idStr);
    g_free(devType);
    if(sscanf(oldGpsStr, "%f-%f", &oldLat,  &oldLon) != 2)
    {
        oldLat = oldLon = 0;
    }
    ObjMove->lat = oldLat;
    ObjMove->lon = oldLon;
    latStr = g_strdup_printf("%f", oldLat);
    lonStr = g_strdup_printf("%f", oldLon);
    gtk_entry_set_text(ObjMove->lat_entry, (const gchar*)latStr);
    gtk_entry_set_text(ObjMove->lon_entry, (const gchar*)lonStr);
    handleId = g_signal_connect (G_OBJECT (map), "motion-notify-event",G_CALLBACK (mouse_moved), NULL);
    if(handleId <= 0)
        return;

    SPL_DIALOG_SHOW(ObjMove->dialog);
    while(responseId = gtk_dialog_run(GTK_DIALOG(ObjMove->dialog)))
    {
        switch(responseId)
        {
        case GTK_RESPONSE_OK:
            if(oldLat == ObjMove->lat && oldLon == ObjMove->lon)
                goto __exit___;
            //update gps of this object
            if(spl_object_update_gps())
                goto __exit___;
            break;
        default:
            ObjMove->lat = oldLat;
            ObjMove->lon = oldLon;
            goto __exit___;
        }
    }

__exit___:
    /**restore map*/
    tmp = map;
    map = (OsmGpsMap*)g_object_ref(tmp);
    gtk_container_remove( GTK_CONTAINER(ObjMove->map_box), GTK_WIDGET(tmp));
    gtk_box_pack_start (GTK_BOX(parent), GTK_WIDGET(map), TRUE, TRUE, 0);
    //osm_gps_map_change_parent(newParent, oldParent);
    g_signal_handler_disconnect(G_OBJECT (map), handleId);
    osm_gps_map_redraw_object();
    osm_gps_map_set_center_and_zoom(map, ObjMove->lat, ObjMove->lon, zoom);
    SPL_DIALOG_HIDE(ObjMove->dialog);
    gtk_widget_hide_on_delete(ObjMove->dialog);
    ObjMove->image  = NULL;
    ObjMove->object = NULL;
    ObjMove->type   = OBJECT_IS_UNKNOW;
    return;
}


void osm_gps_map_redraw_object()
{
    OsmGpsMapPoint *point = g_new0(OsmGpsMapPoint, 1);
    osm_gps_map_point_set_degrees(point, ObjMove->lat, ObjMove->lon);
    GValue val = G_VALUE_INIT;
    g_value_init(&val, OSM_TYPE_GPS_MAP_POINT);
    g_value_set_boxed(&val, point);
    g_object_set_property(G_OBJECT(ObjMove->image), "point", &val);
    g_value_unset(&val);
    g_free(point);
}

void osm_gps_map_image_change_image(OsmGpsMapImage *image, GdkPixbuf *buf)
{
    GValue val = G_VALUE_INIT;
    g_value_init(&val, G_TYPE_OBJECT);
    g_value_set_object(&val, G_OBJECT(buf));
    g_object_set_property(G_OBJECT(image), "pixbuf", &val);
    g_value_unset(&val);
}

GDateTime * spl_gdatetime_from_str(gchar *data)
{
    if(data==NULL)
        return NULL;

    gchar **date_iter = g_strsplit_set (data, (gchar *)" -:.", 6);
    if(g_strv_length(date_iter)!=6)
        return NULL;
    GTimeZone * time_zone = g_time_zone_new_utc();
    GDateTime *datetime = g_date_time_new(time_zone,
                                          g_ascii_strtoll(date_iter[0], NULL, 10),
                                          g_ascii_strtoll(date_iter[1], NULL, 10),
                                          g_ascii_strtoll(date_iter[2], NULL, 10),
                                          g_ascii_strtoll(date_iter[3], NULL, 10),
                                          g_ascii_strtoll(date_iter[4], NULL, 10),
                                          g_ascii_strtoll(date_iter[5], NULL, 10)
                                          );
    return datetime;
}

std::stack<GtkWidget *> stack_widget_active;

gint gtk_widget_active = 0;
G_LOCK_DEFINE_STATIC(gtk_widget_active);

void set_parent_widget_active(GtkWidget *child)
{
    G_LOCK(gtk_widget_active);
    if (!stack_widget_active.empty())
    {
        gtk_window_set_modal(GTK_WINDOW(GTK_DIALOG(child)), TRUE);
        gtk_window_set_transient_for(GTK_WINDOW(child), GTK_WINDOW(stack_widget_active.top()));
        DEBUG("child: %p, parent: %p\n", child, stack_widget_active.top());
    }
    else
    {
        gtk_window_set_modal(GTK_WINDOW(GTK_DIALOG(child)), TRUE);
        gtk_window_set_transient_for(GTK_WINDOW(child), GTK_WINDOW(main_widgets->main_window));
        DEBUG("Cannot set parent active widget stack_widget_active is empty! set to mainwidow\n");
    }
    G_UNLOCK(gtk_widget_active);
}

void set_sensitive_widget_topstack(gboolean is_sensitive)
{
    G_LOCK(gtk_widget_active);
    if (!stack_widget_active.empty())
    {
        gtk_widget_set_sensitive(GTK_WIDGET(stack_widget_active.top()), is_sensitive);
        DEBUG_0("\n (*) gtk_widget_set_sensitive %d for stack_widget_active.top: %p \n",is_sensitive, stack_widget_active.top());
    }
    else
    {
        gtk_widget_set_sensitive(GTK_WIDGET(main_widgets->main_window), is_sensitive);
        DEBUG_0("\n (*) gtk_widget_set_sensitive %d for main_widgets->main_window\n", is_sensitive);
    }
    G_UNLOCK(gtk_widget_active);
}

void stack_widget_active_push(GtkWidget *item)
{
    G_LOCK(gtk_widget_active);
    stack_widget_active.push(item);
    G_UNLOCK(gtk_widget_active);
}
GtkWidget * stack_widget_active_top(void)
{
    G_LOCK(gtk_widget_active);
    GtkWidget *item = NULL;
    if (!stack_widget_active.empty())
    {
        item = stack_widget_active.top();
    }
    else
    {
        item = main_widgets->main_window;
    }
    G_UNLOCK(gtk_widget_active);
    return item;
}
void stack_widget_active_pop()
{
    G_LOCK(gtk_widget_active);
    DEBUG("pop: %p\n", stack_widget_active.top());
    stack_widget_active.pop();
    G_UNLOCK(gtk_widget_active);
}

gboolean spl_widget_change_parent(GtkWidget *object, GtkWidget *old_parent, GtkWidget *new_parent)
{
    g_return_if_fail(object && old_parent && new_parent);

    gtk_container_remove(GTK_CONTAINER(old_parent), GTK_WIDGET(object));
    gtk_container_add(GTK_CONTAINER(new_parent), GTK_WIDGET(object));

    return TRUE;
}

