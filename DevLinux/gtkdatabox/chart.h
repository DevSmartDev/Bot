/*
 * =====================================================================================
 *
 *	Filename:  chart.h
 *
 *	Description:
 *
 *	Version:  1.0
 *	Created:  12/14/2016 09:01:24 AM
 *	Revision:  none
 *	Compiler:  gcc
 *
 *	Author:  Nghi Hoang (), nghi.hoangminhthe@icdrec.edu.vn
 *	Company:  ICDREC
 *
 * =====================================================================================
 */

#ifndef CHART_H_INCLUDED
#define CHART_H_INCLUDED
typedef struct SPL_LCU_SLOPE_DATA
{
    gfloat *x_time;
    gfloat *y_powerCtrl;
    gfloat *y_powerConsum;
    gfloat *y_chart_max_array;
    gint     size_lable;
    gint64  unix_first;
    gint64  unix_end;
    GSList  *lculoglist;
    gint    size_lculog;
    gfloat  *manual_ticks;
    gchar    **manual_tick_labels;

} SplLcuSlopeData;
typedef struct _SplLcuLog
{
    /** Private elements*/
    gint            id;
    gchar           *lcuId;
    gdouble         power_consum; // cong suat tieu thu 10mW -> bieu do
    gdouble         power_ctrl; // cong suat dieu khien 10mW -> bieu do
    gdouble         power; // cong suat den 10mW
    gint            tolerance;
    gchar*          date_time; // time
    gchar*          lightname;
    gint            status;
    gint            mode;

}SplLcuLog;
extern GSList *lcu_log_list;
SplLcuSlopeData *spl_lcu_chart_data_init(gint n_point, GSList *lculoglist);


void lcu_log_finalize (GtkWidget *object,
                         gpointer   user_data);
gboolean  spl_get_data_chart(struct PROGRAM_OPTION* option_t);
void gen_data_chart(SplLcuSlopeData* lcu_slope);
void spl_lcu_chart_data_free(SplLcuSlopeData* lcu_slope);
#endif
