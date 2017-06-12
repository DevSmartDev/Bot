/*
 * =====================================================================================
 *
 *	Filename:  chart.c
 *
 *	Description:
 *
 *	Version:  1.0
 *	Created:  12/14/2016 08:59:46 AM
 *	Revision:  none
 *	Compiler:  gcc
 *
 *	Author:  Nghi Hoang (), nghi.hoangminhthe@icdrec.edu.vn
 *	Company:  ICDREC
 *
 * =====================================================================================
 */
 #include "main.h"
 #include "chart.h"
 #include "../../src/smartstreetlight_soap.h"
 #include "../../src/smartstreetlight_error.h"
 GSList *lcu_log_list = NULL;
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

SplLcuLog* spl_lcu_log_init()
{
    SplLcuLog* lcu_log = g_new0(SplLcuLog, 1);
    lcu_log->lcuId = NULL;
    lcu_log->date_time = NULL;
    lcu_log->lightname = NULL;
    return lcu_log;
}

void spl_lcu_log_free(SplLcuLog* lcu_log)
{
    g_return_if_fail(lcu_log);
    g_free(lcu_log->lcuId);
    g_free(lcu_log->date_time);
    g_free(lcu_log->lightname);
    g_free(lcu_log);
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
    g_strfreev (date_iter);
    return datetime;
}
gboolean  spl_get_data_chart(struct PROGRAM_OPTION* option_t)
{
    SplSoap spl_soap;

    ns1__LCULOGINFOType** wsdl_lcu_log_list = NULL;
    gint  wsdl_lcu_log_list_size=0;
    gboolean ret= FALSE;
    setup_user_soap(option_t->account, option_t->account_id, option_t->url);
    if(lcu_log_list)
    {
        spl_utils_free_slist(&lcu_log_list, (GDestroyNotify)spl_lcu_log_free);
        lcu_log_list = NULL;
    }
    gint soap_err =  smartstreetlight_get_log_lcu_nofree_execute(&spl_soap,
                                                                                option_t->lcu_id,
                                                                                option_t->begin_time,
                                                                                option_t->end_time,
                                                                                &wsdl_lcu_log_list,
                                                                                &wsdl_lcu_log_list_size);
    if (soap_err == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
    {
        if (wsdl_lcu_log_list!=NULL)
        {
            for(gint i=wsdl_lcu_log_list_size-1; i>=0; i--)
            {
                /*
                    gchar           *id;
                    gchar           *lcuId;
                    gdouble         power_consum; // cong suat tieu thu 10mW -> bieu do
                    gdouble         power_ctrl; // cong suat dieu khien 10mW -> bieu do
                    gdouble         power; // cong suat den 10mW
                    gint            tolerance;
                    gchar*          date_time; // time
                    gchar*          lightname;
                    gint            status;
                    gint            mode;
                */
                ns1__LCULOGINFOType *lcu_log_wsdl = wsdl_lcu_log_list[i];
                SplLcuLog* lcu_log = spl_lcu_log_init();

                lcu_log->id = lcu_log_wsdl->lcuLogId;
                lcu_log->lcuId = g_strdup(lcu_log_wsdl->lcuLogLcuId);
                lcu_log->power_consum = (gdouble)lcu_log_wsdl->lcuLogPowerConsum;
                lcu_log->power_ctrl = (gdouble)lcu_log_wsdl->lcuLogPowerCtrl;
                lcu_log->power = (gdouble)lcu_log_wsdl->lcuLogPower;
                lcu_log->tolerance = lcu_log_wsdl->lcuLogTolerance;
                lcu_log->date_time = g_strdup(lcu_log_wsdl->lcuLogDate);
                lcu_log->status = lcu_log_wsdl->lcuLogStatus;
                lcu_log->mode = lcu_log_wsdl->lcuLogMode;
                lcu_log->lightname = g_strdup(lcu_log_wsdl->lcuLogLightName);
                //DEBUG("lcu_log->date_time: %s", lcu_log->date_time);
                lcu_log_list = g_slist_prepend(lcu_log_list, lcu_log);
            }
            ret= TRUE;
        } else {
            gchar *buffer = g_strdup_printf("Không tìm thấy dữ liệu thống kê trong khoảng thời gian \n \"%s\" -> \"%s\"",
                                            option_t->begin_time, option_t->end_time);
            smartstreetlight_error_notifice_run(window , buffer);
            g_free(buffer);
        }
    } else {
        gchar * msg = g_strdup("Lỗi lấy danh sách các tài khoản. ");
        smartstreetlight_error_check_message_result(window, msg, soap_err);
        g_free(msg);
    }
    smartstreetlight_free_soap_operation(&spl_soap);
    return ret;
}
#define CHART_DISTANCE_MAP
SplLcuSlopeData* spl_lcu_chart_data_init(gint n_point, GSList *lculoglist)
{
    SplLcuSlopeData* lcu_slope = g_new0(SplLcuSlopeData, 1);


    SplLcuLog* _first = (SplLcuLog*)g_slist_nth(lculoglist, 0)->data;
    SplLcuLog* _end = (SplLcuLog*)g_slist_nth(lculoglist, n_point-1)->data;

    GDateTime * _datetime_first = spl_gdatetime_from_str(_first->date_time);
    GDateTime * _datetime_end = spl_gdatetime_from_str(_end->date_time);


    //DEBUG("********************** _first->date_time: %s", _first->date_time);

    gint64 _unix_fisrt = g_date_time_to_unix (_datetime_first);
    gint64 _unix_end = g_date_time_to_unix (_datetime_end);
    //DEBUG("_unix_fisrt: %ld, _unix_end: %ld", _unix_fisrt, _unix_end);
    lcu_slope->x_time = NULL;
    lcu_slope->y_powerConsum = NULL;
    lcu_slope->y_powerCtrl = NULL;
    lcu_slope->lculoglist = lculoglist;
    lcu_slope->size_lculog = g_slist_length(lculoglist);
#ifdef CHART_DISTANCE_MAP
    lcu_slope->size_lable = 100;
#else
    lcu_slope->size_lable = lcu_slope->size_lculog;
#endif
    lcu_slope->unix_first = _unix_fisrt;
    lcu_slope->unix_end = _unix_end;
    gen_data_chart(lcu_slope);
    return lcu_slope;
}
void spl_lcu_chart_data_free(SplLcuSlopeData* lcu_slope)
{
    g_return_if_fail(lcu_slope);
    if (lcu_slope->x_time)
        g_free(lcu_slope->x_time);
    if (lcu_slope->y_powerConsum)
        g_free(lcu_slope->y_powerConsum);
    if (lcu_slope->y_powerCtrl)
        g_free(lcu_slope->y_powerCtrl);
    if (lcu_slope->y_chart_max_array)
        g_free(lcu_slope->y_chart_max_array);
    if (lcu_slope->manual_ticks)
        g_free(lcu_slope->manual_ticks);
    for (gint i=0; i < lcu_slope->size_lable; i++)
        if (lcu_slope->manual_tick_labels[i])
            g_free(lcu_slope->manual_tick_labels[i]);
    if (lcu_slope->manual_tick_labels)
        g_free(lcu_slope->manual_tick_labels);
    if (lcu_slope->lculoglist)
        spl_utils_free_slist(&lcu_slope->lculoglist, (GDestroyNotify)spl_lcu_log_free);

    g_free(lcu_slope);

}

void gen_data_chart(SplLcuSlopeData* lcu_slope)
{
    g_return_if_fail(lcu_slope && window);

    guint size_list = g_slist_length(lcu_slope->lculoglist);

    //DEBUG("size_list: %d", size_list);

    lcu_slope->x_time        = (gfloat *)g_malloc(size_list * sizeof(gfloat));
    lcu_slope->y_powerConsum = (gfloat *)g_malloc(size_list * sizeof(gfloat));
    lcu_slope->y_powerCtrl   = (gfloat *)g_malloc(size_list * sizeof(gfloat));
    lcu_slope->y_chart_max_array = (gfloat*)g_malloc(size_list * sizeof(gfloat));
	gfloat chart_max = 0;

	for (gint k=0; k<size_list; k++)
	{
        SplLcuLog* lcu_log_iter = (SplLcuLog*) g_slist_nth_data(lcu_slope->lculoglist, k);
        lcu_slope->y_powerConsum[k] = ((gfloat)lcu_log_iter->power_consum)/100;
        lcu_slope->y_powerCtrl[k] = ((gfloat)lcu_log_iter->power_ctrl)/100 ;

        if (lcu_slope->y_powerConsum[k] > chart_max)
        {
            chart_max = lcu_slope->y_powerConsum[k]+10;
        }
        if (lcu_slope->y_powerCtrl[k] > chart_max)
        {
            chart_max = lcu_slope->y_powerCtrl[k]+10;
        }
        GDateTime * _datetime = spl_gdatetime_from_str(lcu_log_iter->date_time);
        gint64 _unix_datetime = g_date_time_to_unix (_datetime);
        lcu_slope->x_time[k] = (gfloat)(_unix_datetime - lcu_slope->unix_first);
        g_date_time_unref (_datetime);
        if (k%2)
            lcu_slope->y_chart_max_array[k] = chart_max;
        else
            lcu_slope->y_chart_max_array[k] = 0;
        //DEBUG("[%s] data=> x: %f; y_powerCtrl[%d]: %f",lcu_log_iter->date_time, lcu_slope->x_time[k], k,lcu_slope->y_powerCtrl[k]);
        //DEBUG("[%s] data=> x: %f; y_powerConsum[%d]: %f",lcu_log_iter->date_time, lcu_slope->x_time[k], k, lcu_slope->y_powerConsum[k]);

    }

#ifdef CHART_DISTANCE_MAP
    #define LABEL_SIZE  30
    gint delta = lcu_slope->unix_end - lcu_slope->unix_first;
    gint num_point;
    gint inc = 0;
    gint64 time; // round
    if (delta < (60*15*LABEL_SIZE))
    {
        inc=60*15;

    }else if (delta < (60*30*LABEL_SIZE))
    {
        inc=60*30;
    }
    else if (delta < (60*60*LABEL_SIZE))
    {
        inc=60*60;
    }
    else if (delta < (2*60*60*LABEL_SIZE))
    {
        inc=3*60*60;
    }
    else if (delta < (4*60*60*LABEL_SIZE))
    {
        inc=6*60*60;

    }
    else if (delta < (8*60*60*LABEL_SIZE)){
        inc=12*60*60;

    }
    else{
        inc=24*60*60;
    }
     num_point = (lcu_slope->unix_end - lcu_slope->unix_first)/ (inc) +1;
    lcu_slope->manual_ticks = (gfloat *)g_malloc(num_point * sizeof(gfloat));
    lcu_slope->manual_tick_labels = (gchar **)g_malloc(num_point * sizeof(gchar*));
    time= (lcu_slope->unix_first / (inc)) * (inc) + (inc); // round

    gint64 k;
    for (k = 0; time <= lcu_slope->unix_end; k++)
    {
        lcu_slope->manual_ticks[k] = time - lcu_slope->unix_first;

        GDateTime * datetime =  g_date_time_new_from_unix_utc(time);
        //DEBUG ("time: %s", g_date_time_format (datetime, "%Y-%m-%d %H:%M:%S"));
        if ((time%(60*24*60)) == 0)
            lcu_slope->manual_tick_labels[k] = g_date_time_format (datetime, "%m-%d");
#if 0
        else if ((time%(60*60)) == 0)
            lcu_slope->manual_tick_labels[k] = g_date_time_format (datetime, "%H h");
#endif
        else
            lcu_slope->manual_tick_labels[k] = g_date_time_format (datetime, "%H:%M");
            //DEBUG("k: %d, coord: %f, label: %s", k, lcu_slope->manual_ticks[k],
            //                                    lcu_slope->manual_tick_labels[k]);
        time += inc;
        g_date_time_unref (datetime);

    }
    lcu_slope->size_lable =k;
#else
    guint num_point = lcu_slope->size_lable;
    lcu_slope->manual_ticks = (gfloat *)g_malloc(num_point * sizeof(gfloat));
    lcu_slope->manual_tick_labels = (gchar **)g_malloc(num_point * sizeof(gchar*));
     DEBUG("num_point: %d", num_point);
    for (guint k = 0; k < num_point; k++)
    {
        SplLcuLog* lcu_log_iter = (SplLcuLog*) g_slist_nth_data(lcu_slope->lculoglist, k);
        GDateTime * _datetime = spl_gdatetime_from_str(lcu_log_iter->date_time);
        gint64 _unix_datetime = g_date_time_to_unix (_datetime);
        lcu_slope->manual_ticks[k] = (gfloat)(_unix_datetime - lcu_slope->unix_first);
        lcu_slope->manual_tick_labels[k] = g_date_time_format (_datetime, "%Y-%m-%d %H:%M:%S");;
    }
#endif
}
