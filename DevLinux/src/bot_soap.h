#ifndef BOT_SOAP_H_INCLUDED
#define BOT_SOAP_H_INCLUDED
#include <stack>          // std::stack
//
#include "gsoap/soapH.h"
#ifdef __bot_CHART__
#include "../gtkdatabox/main.h"
#else
#include "main.h"
#include "bot_utils.h"
#include "bot_dcu.h"
#include "bot_lcu.h"
#include "bot_schedule.h"
#endif
#define SOAP_FAIL -1


typedef struct botSoap
{
	struct soap *soap;
    //pthread_mutex_t soap_mutex;
    std::stack<struct soap *> soap_stack;
} botSoap;

extern char * bot_username;
extern int bot_session_id;
void bot_soap_int(botSoap* bot_soap);
void bot_free_soap_operation(botSoap* bot_soap);
void free_bot_username();
void bot_free_soap_operation_thread(botSoap* bot_soap);

#ifdef __bot_CHART__
void setup_user_soap(gchar* user, gint id, gchar *url);
#else
/************************** LOGIN ********************************/
gint bot_login_nofree_execute(botSoap* bot_soap,const gchar *username, const gchar* password, ns1__USER_USCOREINFO_USCOREType **user_info, gboolean * is_admin);
gint bot_logout_execute(botSoap* bot_soap);
/************************* dcu ************************************/
gint bot_get_dcu_list_nofree_execute(botSoap* bot_soap,gint zone_id, gint program_id,ns1__DCU_USCOREINFO_USCOREType ***dcu_list, gint * dcu_list_size);
gint bot_add_dcu_execute(botSoap* bot_soap,pbotDcu dcu);
gint bot_edit_dcu_execute(botSoap* bot_soap,pbotDcu dcu);

gint bot_remove_dcu_execute(botSoap* bot_soap,const gchar *dcu_id);
gint bot_set_program_for_dcu_execute(botSoap* bot_soap,const gchar *dcu_id,
                                                      const gint dcu_mode,
                                                      const gint dcu_program_id); // wait
/************************* lcu ************************************/
gint bot_get_lcu_list_nofree_execute(botSoap* bot_soap,const gchar * dcu_id, ns1__LCU_USCOREINFO_USCOREType ***lcu_list, gint* lcu_list_size);
gint  bot_add_lcu_execute(botSoap* bot_soap,pbotLcu lcu);
//gboolean  bot_add_lcu_execute(pbotLcu lcu);
gint bot_edit_lcu_execute(botSoap* bot_soap,pbotLcu lcu);
gint bot_remove_lcu_execute(botSoap* bot_soap,const gchar *lcu_id,const gchar *lcu_dcuid); // wait

gint bot_control_lcu_nofree(botSoap* bot_soap,const gchar *dcu_id,
                                             GString * listOnlcu ,GString * listOfflcu,
                                             const gint level,
                                             gint mode,
                                             gboolean istemp,
                                             ns1__LCU_USCOREINFO_USCOREType ***rsp_lcu_list, gint* rsp_lcu_list_size,
                                             gboolean isprogram); // wait
/************************* line ************************************/
gint bot_get_line_list_nofree_execute(botSoap* bot_soap,const gchar * dcu_id, ns1__LINE_USCOREINFO_USCOREType ***line_list, gint* line_list_size);
gint bot_add_line_execute(botSoap* bot_soap,struct ns1__LINE_USCOREINFO_USCOREType *line_info);
gint bot_remove_line_execute(botSoap* bot_soap,gint line_id,const gchar *line_dcuid);
/************************* zone ************************************/
gint bot_get_all_zone_nofree_execute(botSoap* bot_soap,ns1__ZONE_USCOREINFO_USCOREType ***zone_list, gint* zone_list_size);

gint bot_add_zone_execute(botSoap* bot_soap,ns1__ZONE_USCOREINFO_USCOREType *zone_info, gint *zone_id);

gint  bot_edit_zone_execute(botSoap* bot_soap,ns1__ZONE_USCOREINFO_USCOREType *zone_info);

gint bot_remove_zone_execute(botSoap* bot_soap,gint zone_id);

/************************* Proggram ************************************/
gint bot_get_program_list_nofree_execute(botSoap* bot_soap,gint zone_id, gint program_id,
                                                   ns1__PROGRAM_USCOREINFO_USCOREType *** program, gint *program_size);
gint bot_add_program_execute(botSoap* bot_soap,gint zone_id,const gchar *program_name, gint * programe_id);
gint bot_remove_program_execute(botSoap* bot_soap,gint program_id);
/************************* Day schedule ************************************/
gint bot_get_day_schedule_list_nofree_execute(botSoap* bot_soap,gint program_id, gint dayschedule_id,ns1__DAYSCHEDULE_USCOREINFO_USCOREType ***dayschedule_list, gint * dayschedule_list_size);
gint bot_add_day_schedule_execute(botSoap* bot_soap,gint day_schedule_program_id,gint day_schedule_month, gint *day_schedule_id);
gint bot_edit_day_schedule_execute(botSoap* bot_soap,gint dayschedule_id,
                                                          gint dayschedule_listscheduleid,
                                                          gint dayschedule_programid,
                                                          gint dayschedule_month);
gint bot_remove_day_schedule_execute(botSoap* bot_soap,gint day_schedule_id); // chua sd
/************************* List schedule ************************************/
gint bot_get_list_schedule_nofree_execute(botSoap* bot_soap,gint list_schedule_id,gint program_id,
                                                            ns1__LISTSCHEDULE_USCOREINFO_USCOREType ***listschedule_list,
                                                            gint *listschedule_list_size);

gint bot_edit_list_schedule_execute(botSoap* bot_soap,botDaySchedule* daySchedule);

gint bot_add_list_schedule_execute(botSoap* bot_soap,const gchar *listschedule_name,
                                                          gint *listschedule_id,
                                                          gint program_id); // chua sd
gint bot_remove_list_schedule_execute(botSoap* bot_soap,gint listschedule_id);
/************************* schedule ************************************/
gint bot_get_schedule_nofree_execute(botSoap* bot_soap,gint list_schedule_id,gint shedule_id,
                                                      ns1__SCHEDULE_USCOREINFO_USCOREType ***schedule_list,
                                                      gint* schedule_list_size); // chua sd, gop get list schedule
gint bot_add_item_schedule_execute(botSoap* bot_soap,gint listschedle_id,
                                                          gint starttime,
                                                          gint timeon,
                                                          gint level,
                                                          gint *schedule_id); // chua sd, gop set all list schedule

gint bot_remove_schedule_execute(botSoap* bot_soap,gint schedule_id);
/************************* Event log ************************************/
gint bot_get_event_log_nofree_execute(botSoap* bot_soap,gchar *dcu_id, ns1__EVENTLOG_USCORETYPE_USCOREEnum type_log,
                                              ns1__EVENT_USCORELOG_USCOREINFO_USCOREType ***eventlog_list, gint * eventlog_list_size);
gint bot_delete_event_log_execute(botSoap* bot_soap,gint eventlog_id);

/************************* User log ************************************/
gint bot_get_user_log_nofree_execute(botSoap* bot_soap,gint user_id,
                                                      ns1__USER_USCORELOG_USCOREINFO_USCOREType *** userlog_List, gint* userlog_List_size); // chua sd
gint bot_delete_user_log_execute(botSoap* bot_soap,gint userlog_id);
/*************************** User ***************************************/
gint bot_get_user_nofree_execute(botSoap* bot_soap,gint user_id,ns1__USER_USCOREINFO_USCOREType ***user_list, gint * user_list_size);
gint  bot_edit_user_by_user_execute(botSoap* bot_soap,gint user_id,
                                                   const gchar *password,
                                                   const gchar *phone,
                                                   const gchar *email,
                                                   gboolean enable_sms_notify,
                                                   gboolean enable_email_notify);
gint  bot_add_user_execute(botSoap* bot_soap,ns1__USER_USCOREINFO_USCOREType user, gint * new_user_id);
gint  bot_edit_user_execute(botSoap* bot_soap, ns1__USER_USCOREINFO_USCOREType user, gboolean isAddZone);
gint  bot_remove_user_execute(botSoap* bot_soap,gint user_id);
// add remove edit user.
/*************************** Update runtime User ***************************************/
gint bot_event_runtime_update_nofree(botSoap* bot_soap,ns1__DCU_USCOREINFO_USCOREType ***dcu_list, gint *dcu_list_size,
                                         ns1__LCU_USCOREINFO_USCOREType ***lcu_list, gint *lcu_list_size,
                                         ns1__EVENT_USCORELOG_USCOREINFO_USCOREType ***eventlog_list, gint *eventlog_list_size);
#endif
/*************************** get log lcu ***************************************/
gint bot_get_log_lcu_nofree_execute(botSoap* bot_soap, gchar * lcu_id, gchar * time_from,
                                                    gchar * time_to
#ifdef __bot_CHART__
                                                    , ns1__LCULOGINFOType*** lcu_log_list,
                                                    gint * lcu_log_list_size
 #endif
                                                    );
#endif // BOT_SOAP_H_INCLUDED


