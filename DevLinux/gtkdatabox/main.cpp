/* $Id: logarithmic.c 4 2008-06-22 09:19:11Z rbock $ */
/* GtkDatabox - An extension to the gtk+ library
 * Copyright (C) 2011 - 2012  Dr. Matt Flax <flatmax@>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */
#include <stdio.h>


#include <gtkdatabox.h>
#include <gtkdatabox_points.h>
#include <gtkdatabox_lines.h>
#include <gtkdatabox_ruler.h>
#include <math.h>
#include <stdlib.h>
#include "main.h"
#include "chart.h"
 #include "../../src/smartstreetlight_error.h"


/*----------------------------------------------------------------
 *  databox rulers
 *----------------------------------------------------------------*/
static void
create_grid (GtkWidget *window, gfloat *X, gfloat *Y1, gfloat *Y2, gfloat *Y3,
               gfloat *manual_tick, gchar **manual_tick_labels, gfloat min_x, gfloat max_x,
                gfloat min_y, gfloat max_y, int points, int size_label)
{
   GtkWidget *box1;
   GtkWidget *box;
   GtkWidget *table;
   GtkDataboxGraph *graph;
   GdkColor color;

   GtkDataboxRuler *ruler;
#if 0
    for (gint k=0; k<points; k++)
	{
        DEBUG("data=> x: %f; y_powerCtrl[%d]: %f", X[k], k,Y1[k]);
        DEBUG("data=> x: %f; y_powerConsum[%d]: %f", X[k], k, Y2[k]);
        DEBUG("data=> x: %f; max_char[%d]: %f", X[k], k,Y3[k]);
//        if(k != 0 && lcu_slope->x_time[k] < lcu_slope->x_time[k-1])
//        {
//            DEBUG("ERROR TIME: %s", lcu_log_iter->date_time);
//            DEBUG("ERROR TIME: %ld", _unix_datetime);
//        }
    }
#endif
   box1 = gtk_vbox_new (FALSE, 0);
   gtk_container_add (GTK_CONTAINER (window), box1);


   /* Create a GtkDatabox widget along with scrollbars and rulers */

    gtk_databox_create_box_with_scrollbars_and_rulers_positioned (&box, &table,TRUE, TRUE, TRUE,TRUE,FALSE,TRUE);
    gtk_box_pack_start (GTK_BOX (box1), table, TRUE, TRUE, 0);

    ruler=gtk_databox_get_ruler_y(GTK_DATABOX (box));
    gtk_databox_ruler_set_text_orientation(ruler, GTK_ORIENTATION_VERTICAL);
    gtk_databox_set_ruler_y (GTK_DATABOX (box), ruler);

    ruler=gtk_databox_get_ruler_x(GTK_DATABOX (box)); /* put manual labels on x */
    gtk_databox_ruler_set_draw_subticks(ruler, FALSE);

    gtk_databox_ruler_set_manual_tick_cnt(ruler, size_label);
    gtk_databox_ruler_set_manual_ticks(ruler, manual_tick);

    gtk_databox_ruler_set_manual_tick_labels(ruler, manual_tick_labels);
    gtk_databox_set_ruler_x (GTK_DATABOX (box), ruler);

     /* set the background */
    color.red = 16383;
    color.green = 16383;
    color.blue = 16383;

    gtk_widget_modify_bg (box, GTK_STATE_NORMAL, &color);


    color.red = 0;
    color.green = 65535;
    color.blue = 0;
    graph = gtk_databox_lines_new (points, X, Y1, &color, 1);
    gtk_databox_graph_add (GTK_DATABOX (box), graph);

    /* add an exp function */
#if 1
    color.red = 65535;
    color.green = 0;
    color.blue = 0;

    graph = gtk_databox_lines_new (points, X, Y2, &color, 1);

    gtk_databox_graph_add (GTK_DATABOX (box), graph);

     /* background */
    color.red = 16383;
    color.green = 16383;
    color.blue = 16383;

    graph = gtk_databox_lines_new (points, X, Y3, &color, 1);

    gtk_databox_graph_add (GTK_DATABOX (box), graph);
#endif

    gtk_databox_auto_rescale (GTK_DATABOX (box), 0.0);
#if 0
    gtk_databox_set_total_limits (GTK_DATABOX (box), min_x, max_x, 0, 200);
#endif

}
GtkWidget *window = NULL;
#define POINTS 100
gint main (gint argc, char *argv[])
{
    struct PROGRAM_OPTION option_t;
    gchar * programName= g_path_get_basename (argv[0]);
    option_t.begin_time = NULL;
    option_t.end_time = NULL;
    option_t.url = NULL;
    option_t.lcu_id = NULL;
    option_t.account = NULL;
    option_t.account_id = 0;

    if (!getOptCommandLine(argc, argv, &option_t)) {
        spl_chart_help(programName);
        if (option_t.begin_time)
            g_free(option_t.begin_time);
        if (option_t.end_time)
            g_free(option_t.end_time);
        if (option_t.account)
            g_free(option_t.account);
        if (option_t.url)
            g_free(option_t.url);
        if (option_t.lcu_id)
            g_free(option_t.lcu_id);
        g_free(programName);
        exit(EXIT_FAILURE);
    }
    //DEBUG("here\n");
    gtk_init (NULL, NULL);
    //DEBUG("here\n");
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request (window, 1000, 500);

    g_signal_connect (GTK_OBJECT (window), "destroy",
                      G_CALLBACK (gtk_main_quit), NULL);

    gchar *lcu_slope_title = g_strdup_printf("Biểu đồ hoạt động của đèn '%s'", option_t.lcu_id);
    gtk_window_set_title(GTK_WINDOW(window), lcu_slope_title);
    g_free(lcu_slope_title);

    gtk_container_set_border_width (GTK_CONTAINER (window), 0);
    //DEBUG("here\n");
    if (!smartstreetlight_error_init())
        exit(EXIT_FAILURE);
    //DEBUG("here\n");
    if (!spl_get_data_chart(&option_t))
         exit(EXIT_FAILURE);
#if 1
    if(lcu_log_list)
    {
        SplLcuSlopeData* lcu_slope = spl_lcu_chart_data_init(g_slist_length(lcu_log_list), lcu_log_list);
        if (lcu_slope)
        {
            create_grid(window, lcu_slope->x_time,
                                lcu_slope->y_powerCtrl,
                                lcu_slope->y_powerConsum,
                                lcu_slope->y_chart_max_array,
                                lcu_slope->manual_ticks,
                                lcu_slope->manual_tick_labels,
                                0,0,0, 0, lcu_slope->size_lculog,lcu_slope->size_lable);
            gtk_widget_show_all(window);

            gtk_main ();
        }
        spl_lcu_chart_data_free(lcu_slope);
    }
#else
    gfloat *x, *y1, *y2, *y3;
    gfloat min_x, max_x, min_y, max_y;
    int k;
    gfloat *manual_ticks;
    gchar **manual_tick_labels;
    manual_ticks = (gfloat *)g_malloc(POINTS * sizeof(gfloat));
    manual_tick_labels = (gchar **)g_malloc(POINTS * sizeof(gchar*));
    DEBUG("here\n");
    x = (gfloat *)g_malloc(POINTS * sizeof(gfloat));
    y1 = (gfloat *)g_malloc(POINTS * sizeof(gfloat));
    y2 = (gfloat *)g_malloc(POINTS * sizeof(gfloat));
    y3 = (gfloat *)g_malloc(POINTS * sizeof(gfloat));

    min_x = min_y= 0.0;
    max_x = POINTS + 1;
    max_y = 100;

    for (k = 0; k<POINTS; k++)
    {
		if ((k % 2) == 0)
            y1[k] = 50;
        else
            y1[k] = 56;

        if (k == 10)
        {
            y1[k] = 75;
        }
        y2[k] = 55;
        y3[k] = 76;
        x[k] = k;
        manual_ticks[k] = k;
        manual_tick_labels[k] = g_strdup_printf("Day %d",k);
		printf("x: %f, y : %f\n", x[k],y1[k]);
    }


    create_grid(window, x, y1, y2,y3, manual_ticks,manual_tick_labels,min_x,max_x,min_y, max_y, POINTS);

    gtk_widget_show_all (window);

    gtk_main ();

    g_free(x);
    g_free(y1);
    g_free(y2);
    g_free(y3);
    for (k = 0; k< POINTS ; k++){
        g_free(manual_tick_labels[k]);
    }
    g_free(manual_tick_labels);
    g_free(manual_ticks);
#endif
    if (option_t.begin_time)
        g_free(option_t.begin_time);
    if (option_t.end_time)
        g_free(option_t.end_time);
    if (option_t.account)
        g_free(option_t.account);
    if (option_t.url)
        g_free(option_t.url);
    if (option_t.lcu_id)
        g_free(option_t.lcu_id);
    g_free(programName);
    return 0;
}
gint spl_utils_message_box(GtkWindow *parent, GtkMessageType type, GtkButtonsType btn, const gchar* msg)
{
    GtkWidget *dlg;
    gint responseId;
    dlg = gtk_message_dialog_new(parent, (GtkDialogFlags)(GTK_DIALOG_DESTROY_WITH_PARENT | GTK_DIALOG_MODAL), type, btn, msg);
    gtk_widget_show_all(dlg);
    responseId = gtk_dialog_run(GTK_DIALOG(dlg));
    gtk_widget_destroy(dlg);
    return responseId;
}

