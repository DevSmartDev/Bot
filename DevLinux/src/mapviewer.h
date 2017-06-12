#ifndef __H_MAP_VIEWER___H
#define __H_MAP_VIEWER___H
#include <osm-gps-map.h>
#include <gtk/gtk.h>
#include "main.h"

extern OsmGpsMap *map;
extern GdkPixbuf *light_image[ICON_LIGHT_NUM_COUNT];
extern GtkImage  *image_remove;
extern GtkImage  *image_edit;


enum
{
    NOTE_PAGE_DCU = 0,
    NOTE_PAGE_LCU,
};
int map_main(void);
float rad2deg(float rad);
float deg2rad(float deg);
static gboolean on_gps_light_changed_add (GtkWidget *widget, gpointer user_data);
float distance_lat_lon(float lat1, float lon1, float lat2, float lon2, char unit);


#endif // __H_MAP_VIEWER___H
