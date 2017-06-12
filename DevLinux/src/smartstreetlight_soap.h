#ifndef SMARTSTREETLIGHT_SOAP_H_INCLUDED
#define SMARTSTREETLIGHT_SOAP_H_INCLUDED
#include <stack>          // std::stack
//
#include "gsoap/soapH.h"
#ifdef __SPL_CHART__
#include "../gtkdatabox/main.h"
#else
#include "main.h"
#include "smartstreetlight_utils.h"
#include "smartstreetlight_dcu.h"
#include "smartstreetlight_lcu.h"
#include "smartstreetlight_schedule.h"
#endif
#define SOAP_FAIL -1


typedef struct SplSoap
{
	struct soap *soap;
    //pthread_mutex_t soap_mutex;
    std::stack<struct soap *> soap_stack;
} SplSoap;

extern char * smartstreetlight_username;
extern int smartstreetlight_session_id;
void smartstreetlight_soap_int(SplSoap* spl_soap);
void smartstreetlight_free_soap_operation(SplSoap* spl_soap);
void free_smartstreetlight_username();
void smartstreetlight_free_soap_operation_thread(SplSoap* spl_soap);

#ifdef __SPL_CHART__
void setup_user_soap(gchar* user, gint id, gchar *url);
#else
/************************** LOGIN ********************************/
gint smartstreetlight_login_nofree_execute(SplSoap* spl_soap,const gchar *username, const gchar* password, ns1__USER_USCOREINFO_USCOREType **user_info, gboolean * is_admin);
gint smartstreetlight_logout_execute(SplSoap* spl_soap);
/************************* dcu ************************************/
gint smartstreetlight_get_dcu_list_nofree_execute(SplSoap* spl_soap,gint zone_id, gint program_id,ns1__DCU_USCOREINFO_USCOREType ***dcu_list, gint * dcu_list_size);
gint smartstreetlight_add_dcu_execute(SplSoap* spl_soap,pSplDcu dcu);
gint smartstreetlight_edit_dcu_execute(SplSoap* spl_soap,pSplDcu dcu);

gint smartstreetlight_remove_dcu_execute(SplSoap* spl_soap,const gchar *dcu_id);
gint smartstreetlight_set_program_for_dcu_execute(SplSoap* spl_soap,const gchar *dcu_id,
                                                      const gint dcu_mode,
                                                      const gint dcu_program_id); // wait
/************************* lcu ************************************/
gint smartstreetlight_get_lcu_list_nofree_execute(SplSoap* spl_soap,const gchar * dcu_id, ns1__LCU_USCOREINFO_USCOREType ***lcu_list, gint* lcu_list_size);
gint  smartstreetlight_add_lcu_execute(SplSoap* spl_soap,pSplLcu lcu);
//gboolean  smartstreetlight_add_lcu_execute(pSplLcu lcu);
gint smartstreetlight_edit_lcu_execute(SplSoap* spl_soap,pSplLcu lcu);
gint smartstreetlight_remove_lcu_execute(SplSoap* spl_soap,const gchar *lcu_id,const gchar *lcu_dcuid); // wait

gint smartstreetlight_control_lcu_nofree(SplSoap* spl_soap,const gchar *dcu_id,
                                             GString * listOnlcu ,GString * listOfflcu,
                                             const gint level,
                                             gint mode,
                                             gboolean istemp,
                                             ns1__LCU_USCOREINFO_USCOREType ***rsp_lcu_list, gint* rsp_lcu_list_size,
                                             gboolean isprogram); // wait
/************************* line ************************************/
gint smartstreetlight_get_line_list_nofree_execute(SplSoap* spl_soap,const gchar * dcu_id, ns1__LINE_USCOREINFO_USCOREType ***line_list, gint* line_list_size);
gint smartstreetlight_add_line_execute(SplSoap* spl_soap,struct ns1__LINE_USCOREINFO_USCOREType *line_info);
gint smartstreetlight_remove_line_execute(SplSoap* spl_soap,gint line_id,const gchar *line_dcuid);
/************************* zone ************************************/
gint smartstreetlight_get_all_zone_nofree_execute(SplSoap* spl_soap,ns1__ZONE_USCOREINFO_USCOREType ***zone_list, gint* zone_list_size);

gint smartstreetlight_add_zone_execute(SplSoap* spl_soap,ns1__ZONE_USCOREINFO_USCOREType *zone_info, gint *zone_id);

gint  smartstreetlight_edit_zone_execute(SplSoap* spl_soap,ns1__ZONE_USCOREINFO_USCOREType *zone_info);

gint smartstreetlight_remove_zone_execute(SplSoap* spl_soap,gint zone_id);

/************************* Proggram ************************************/
gint smartstreetlight_get_program_list_nofree_execute(SplSoap* spl_soap,gint zone_id, gint program_id,
                                                   ns1__PROGRAM_USCOREINFO_USCOREType *** program, gint *program_size);
gint smartstreetlight_add_program_execute(SplSoap* spl_soap,gint zone_id,const gchar *program_name, gint * programe_id);
gint smartstreetlight_remove_program_execute(SplSoap* spl_soap,gint program_id);
/************************* Day schedule ************************************/
gint smartstreetlight_get_day_schedule_list_nofree_execute(SplSoap* spl_soap,gint program_id, gint dayschedule_id,ns1__DAYSCHEDULE_USCOREINFO_USCOREType ***dayschedule_list, gint * dayschedule_list_size);
gint smartstreetlight_add_day_schedule_execute(SplSoap* spl_soap,gint day_schedule_program_id,gint day_schedule_month, gint *day_schedule_id);
gint smartstreetlight_edit_day_schedule_execute(SplSoap* spl_soap,gint dayschedule_id,
                                                          gint dayschedule_listscheduleid,
                                                          gint dayschedule_programid,
                                                          gint dayschedule_month);
gint smartstreetlight_remove_day_schedule_execute(SplSoap* spl_soap,gint day_schedule_id); // chua sd
/************************* List schedule ************************************/
gint smartstreetlight_get_list_schedule_nofree_execute(SplSoap* spl_soap,gint list_schedule_id,gint program_id,
                                                            ns1__LISTSCHEDULE_USCOREINFO_USCOREType ***listschedule_list,
                                                            gint *listschedule_list_size);

gint smartstreetlight_edit_list_schedule_execute(SplSoap* spl_soap,SplDaySchedule* daySchedule);

gint smartstreetlight_add_list_schedule_execute(SplSoap* spl_soap,const gchar *listschedule_name,
                                                          gint *listschedule_id,
                                                          gint program_id); // chua sd
gint smartstreetlight_remove_list_schedule_execute(SplSoap* spl_soap,gint listschedule_id);
/************************* schedule ************************************/
gint smartstreetlight_get_schedule_nofree_execute(SplSoap* spl_soap,gint list_schedule_id,gint shedule_id,
                                                      ns1__SCHEDULE_USCOREINFO_USCOREType ***schedule_list,
                                                      gint* schedule_list_size); // chua sd, gop get list schedule
gint smartstreetlight_add_item_schedule_execute(SplSoap* spl_soap,gint listschedle_id,
                                                          gint starttime,
                                                          gint timeon,
                                                          gint level,
                                                          gint *schedule_id); // chua sd, gop set all list schedule

gint smartstreetlight_remove_schedule_execute(SplSoap* spl_soap,gint schedule_id);
/************************* Event log ************************************/
gint smartstreetlight_get_event_log_nofree_execute(SplSoap* spl_soap,gchar *dcu_id, ns1__EVENTLOG_USCORETYPE_USCOREEnum type_log,
                                              ns1__EVENT_USCORELOG_USCOREINFO_USCOREType ***eventlog_list, gint * eventlog_list_size);
gint smartstreetlight_delete_event_log_execute(SplSoap* spl_soap,gint eventlog_id);

/************************* User log ************************************/
gint smartstreetlight_get_user_log_nofree_execute(SplSoap* spl_soap,gint user_id,
                                                      ns1__USER_USCORELOG_USCOREINFO_USCOREType *** userlog_List, gint* userlog_List_size); // chua sd
gint smartstreetlight_delete_user_log_execute(SplSoap* spl_soap,gint userlog_id);
/*************************** User ***************************************/
gint smartstreetlight_get_user_nofree_execute(SplSoap* spl_soap,gint user_id,ns1__USER_USCOREINFO_USCOREType ***user_list, gint * user_list_size);
gint  smartstreetlight_edit_user_by_user_execute(SplSoap* spl_soap,gint user_id,
                                                   const gchar *password,
                                                   const gchar *phone,
                                                   const gchar *email,
                                                   gboolean enable_sms_notify,
                                                   gboolean enable_email_notify);
gint  smartstreetlight_add_user_execute(SplSoap* spl_soap,ns1__USER_USCOREINFO_USCOREType user, gint * new_user_id);
gint  smartstreetlight_edit_user_execute(SplSoap* spl_soap, ns1__USER_USCOREINFO_USCOREType user, gboolean isAddZone);
gint  smartstreetlight_remove_user_execute(SplSoap* spl_soap,gint user_id);
// add remove edit user.
/*************************** Update runtime User ***************************************/
gint spl_event_runtime_update_nofree(SplSoap* spl_soap,ns1__DCU_USCOREINFO_USCOREType ***dcu_list, gint *dcu_list_size,
                                         ns1__LCU_USCOREINFO_USCOREType ***lcu_list, gint *lcu_list_size,
                                         ns1__EVENT_USCORELOG_USCOREINFO_USCOREType ***eventlog_list, gint *eventlog_list_size);
#endif
/*************************** get log lcu ***************************************/
gint smartstreetlight_get_log_lcu_nofree_execute(SplSoap* spl_soap, gchar * lcu_id, gchar * time_from,
                                                    gchar * time_to
#ifdef __SPL_CHART__
                                                    , ns1__LCULOGINFOType*** lcu_log_list,
                                                    gint * lcu_log_list_size
 #endif
                                                    );
#endif // SMARTSTREETLIGHT_SOAP_H_INCLUDED


