
/*
 * Copyright (C) 2016  Elvis Teixeira
 *
 * This source code is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General
 * Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any
 * later version.
 *
 * This source code is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 */
#include <slope/sampler.h>
#include <slope/slope.h>

#include <math.h>

#define VIEW_BY_OPTION 1

#if VIEW_BY_OPTION
SlopeSample *slope_sampler_option = NULL;
#endif

void gen_chart( GtkWidget *chart, double *x, double *y1, double *y2, int n)

{
    int k;
    SlopeScale *scale;
    SlopeItem *series1, *series2;
    scale = slope_xyscale_new();
    slope_chart_add_scale(SLOPE_CHART(chart), scale);
#if VIEW_BY_OPTION
    SlopeSampler *sampler;
    SlopeItem *axis;
     slope_sampler_option = g_malloc(n*sizeof(SlopeSample));
    for (k = 0; k < n; k++){
        slope_sampler_option[k].coord = k;
        slope_sampler_option[k].label = g_strdup_printf("Day %d",k);
    }
    axis = slope_xyscale_get_axis(SLOPE_XYSCALE(scale), SLOPE_XYSCALE_AXIS_BOTTOM);

    sampler = slope_xyaxis_get_sampler(SLOPE_XYAXIS(axis));
    slope_sampler_set_samples(sampler, slope_sampler_option, n);
#endif

    series1 = slope_xyseries_new_filled("K", x, y1, n, "m");
    slope_scale_add_item(scale, series1);

    series2 = slope_xyseries_new_filled("K", x, y2, n, "b");
    slope_scale_add_item(scale, series2);

}
int main(int argc, char *argv[])
{
    double *x, *y1, *y2;
    GtkWidget *chart;
    gtk_init(&argc, &argv);
    chart = slope_chart_new();

    g_signal_connect(G_OBJECT(chart), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    /* create some sinusoidal data points */
    long k, n = 30;
    x = g_malloc(n * sizeof(double));
    y1 = g_malloc(n * sizeof(double));
    y2 = g_malloc(n * sizeof(double));


	for (k=0; k<n; k++) {
		if ((k%2) == 0)
            y1[k] = 10;
        else
            y1[k] = 20;
        y2[k] = 15;
        x[k] = k;
		printf("x: %f, y : %f\n", x[k],y1[k]);
    }

    gen_chart(chart,x,y1,y2,n);


    gtk_widget_show_all(chart);
    gtk_main();

    g_free(x);
    g_free(y1);
    g_free(y2);
    #if VIEW_BY_OPTION
    for (k = 0; k< n ; k++){
        g_free(slope_sampler_option[k].label);
    }
    g_free(slope_sampler_option);
    #endif // VIEW_BY_OPTION
    return 0;
}
