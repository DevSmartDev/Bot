#include <pthread.h>

#include "gsoap/soapH.h"
#include "smartstreetlight_soap.h"
#include "gsoap/smartstreetlightServiceSOAP.nsmap"
#ifndef __SPL_CHART__

#include "smartstreetlight_login.h"
#include "smartstreetlight_dcu.h"
#include "smartstreetlight_lcu.h"
#include "smartstreetlight_line.h"
#include "smartstreetlight_schedule.h"
#include "smartstreetlight_server.h"
#include "smartstreetlight_zone.h"
#include "smartstreetlight_admin_user.h"
#include "smartstreetlight_log.h"
#include "smartstreetlight_soap_thread.h"

#endif


char * smartstreetlight_username = NULL;
int smartstreetlight_session_id;
#ifdef __SPL_CHART__
static gchar * smartstreetlight_server_url;
void setup_user_soap(gchar* user, gint id, gchar *url)
{
    smartstreetlight_username= user;
    smartstreetlight_session_id = id;
    smartstreetlight_server_url = url;
    //DEBUG("smartstreetlight_server_url: %s\n",smartstreetlight_server_url);
}
#endif // __SPL_CHART__

static gint smartstreetlight_control_lcu_nofree_execute(SplSoap* spl_soap,const gchar *dcu_id,
                                             ns1__LCU_USCOREINFO_USCOREType **ctrl_lcu_list, gint ctrl_lcu_list_size,
                                             gboolean istemp,
                                             ns1__LCU_USCOREINFO_USCOREType ***rsp_lcu_list, gint* rsp_lcu_list_size,
                                             gboolean isprogram);
static gboolean smartstreetlight_edit_list_schedule(SplSoap* spl_soap,ns1__LISTSCHEDULE_USCOREINFO_USCOREType *listschedule,
                                                          gint *listschedule_id);


void smartstreetlight_soap_int(SplSoap* spl_soap)
{
    spl_soap->soap = soap_new();
    spl_soap->soap->recv_timeout = 30; /* seconds */
    spl_soap->soap->send_timeout = 60;
    //DEBUG("===============> size: %d\n",spl_soap->soap_stack.size());
    spl_soap->soap_stack.push(spl_soap->soap);
}

void smartstreetlight_free_soap_operation(SplSoap* spl_soap)
{
    //DEBUG("===============> size: %d\n",spl_soap->soap_stack.size());
    struct soap *soap_in_stack = (struct soap *)spl_soap->soap_stack.top();

    if (spl_soap->soap !=soap_in_stack)
        DEBUG("===============> error internal: free soap\n");
    if (spl_soap->soap == NULL)
        return;
    soap_destroy(spl_soap->soap);                   /*delete managed and deserialized data*/
    soap_end(spl_soap->soap);                       /*delete other data*/
    soap_free(spl_soap->soap);                     // detach context (last use and no longer in scope)
    spl_soap->soap_stack.pop();
    spl_soap->soap = NULL;
    if (!spl_soap->soap_stack.empty())
        spl_soap->soap = (struct soap *)spl_soap->soap_stack.top();
}


void free_smartstreetlight_username()
{
    if (smartstreetlight_username != NULL)
    {
        g_free(smartstreetlight_username);
    }
}
#ifndef __SPL_CHART__
/** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ LOGIN @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ **/
/** ************************************************ LOGIN *********************************************** **/


gint smartstreetlight_login_nofree_execute(SplSoap* spl_soap,const gchar *username, const gchar* password, ns1__USER_USCOREINFO_USCOREType **user_info, gboolean * is_admin)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__LoginPcOperation login_input;
    struct _ns1__LoginPcOperationResponse login_output;

    login_input.login_USCOREusername = g_strdup(username);
    login_input.login_USCOREpassword = g_strdup(password);

    if(soap_call___ns1__LoginPcOperation(spl_soap->soap, smartstreetlight_server_url, "", &login_input, &login_output) == SOAP_OK)
    {
        if(login_output.login_USCOREresult == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
        {

            free_smartstreetlight_username();

            smartstreetlight_username = g_strdup(username);
            smartstreetlight_session_id= login_output.session_USCOREID;
            *user_info=login_output.user;
            *is_admin = login_output.admin_USCOREprivilege;

            /** Set current session number for this login action **/
//            smartstreetlight_login_success(username, login_output.session_USCOREID, login_output.admin_USCOREprivilege);

        }
        execute_result = login_output.login_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
//        smartstreetlight_error_notifice_run(g_strdup_printf("Error \"Login fail.\""));
//        smartstreetlight_error_notifice_run(g_strdup_printf("Error \"Login fail: %s\": %d at %s:%d", soap->error, __FILE__, __LINE__));
    }

    g_free(login_input.login_USCOREusername);
    g_free(login_input.login_USCOREpassword);


    return execute_result;
}


/** *********************************************** LOGOUT ******************************************** **/
gint smartstreetlight_logout_execute(SplSoap* spl_soap)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__LogoutOperation          input_data;
    struct _ns1__LogoutOperationResponse   output_data;

    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    input_data.current_USCORElogin_USCOREinfo = &current_user_info;
    if(soap_call___ns1__LogoutOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        if(output_data.message_USCOREresult == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
        {
            execute_result=TRUE;
        }
        execute_result = output_data.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }
    smartstreetlight_free_soap_operation(spl_soap);
    return execute_result;
}

/** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ LCU @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ **/
/** *********************************************** GET DCU ******************************************** **/
gint smartstreetlight_get_dcu_list_nofree_execute(SplSoap* spl_soap,gint zone_id, gint program_id,ns1__DCU_USCOREINFO_USCOREType ***dcu_list, gint * dcu_list_size)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__getDcuListOperation            req;
    struct _ns1__getDcuListOperationResponse    rsp;

    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;

    req.current_USCORElogin_USCOREinfo = &current_user_info;
    req.zone_USCOREid = zone_id;
    req.program_USCOREid = program_id;

    if(soap_call___ns1__getDcuListOperation(spl_soap->soap, smartstreetlight_server_url, "", &req, &rsp)==SOAP_OK)
    {
        if(rsp.message_USCOREresult == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
        {
            *dcu_list = rsp.dcu_USCORElist;
            *dcu_list_size = rsp.__sizedcu_USCORElist;
             DEBUG("*dcu_list: %p, dcu_list_size: %d\n", rsp.dcu_USCORElist, *dcu_list_size);
        }
        execute_result = rsp.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }
    return execute_result;
}

/** *********************************************** ADD DCU ******************************************** **/
gint smartstreetlight_add_dcu_execute(SplSoap* spl_soap,pSplDcu dcu)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__addDcuOperation            input_data;
    struct _ns1__addDcuOperationResponse    output_data;

    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    input_data.current_USCORElogin_USCOREinfo = &current_user_info;

    struct ns1__DCU_USCOREINFO_USCOREType dcu_info;

    dcu_info.dcu_USCOREid = g_strdup(dcu->priv->id);
    dcu_info.dcu_USCOREphone = g_strdup(dcu->priv->phonenum);
    dcu_info.dcu_USCOREgps = g_strdup(dcu->priv->gps);
    dcu_info.dcu_USCOREnote = g_strdup(dcu->priv->note);
    dcu_info.dcu_USCOREaddress = g_strdup(dcu->priv->address);
    dcu_info.dcu_USCOREzoneid = dcu->priv->zonecode;

    dcu_info.dcu_USCOREstatus = 0;
    dcu_info.dcu_USCOREprogram_USCOREid = dcu->priv->programId = 0;
    dcu_info.dcu_USCOREmode = dcu->priv->mode;
    input_data.dcu = &dcu_info;

    if(soap_call___ns1__addDcuOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        execute_result = output_data.message_USCOREresult;
    }
    else
    {
        execute_result= -1;
        soap_print_fault(spl_soap->soap, stderr);
    }

    g_char_free(dcu_info.dcu_USCOREid);
    g_char_free(dcu_info.dcu_USCOREphone);
    g_char_free(dcu_info.dcu_USCOREgps);
    g_char_free(dcu_info.dcu_USCOREnote);
    g_char_free(dcu_info.dcu_USCOREaddress);
    smartstreetlight_free_soap_operation(spl_soap);
    return execute_result;
}

/** *********************************************** EDIT DCU ******************************************** **/
gint smartstreetlight_edit_dcu_execute(SplSoap* spl_soap, pSplDcu dcu)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__editDcuOperation            input_data;
    struct _ns1__editDcuOperationResponse    output_data;

    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    input_data.current_USCORElogin_USCOREinfo = &current_user_info;

    struct ns1__DCU_USCOREINFO_USCOREType dcu_info;
    dcu_info.dcu_USCOREid = g_strdup(dcu->priv->id);
    dcu_info.dcu_USCOREphone = g_strdup(dcu->priv->phonenum);
    dcu_info.dcu_USCOREgps = g_strdup(dcu->priv->gps);
    dcu_info.dcu_USCOREnote = g_strdup(dcu->priv->note);
    dcu_info.dcu_USCOREaddress =  g_strdup(dcu->priv->address);
    dcu_info.dcu_USCOREzoneid = dcu->priv->zonecode;
    dcu_info.dcu_USCOREmode = dcu->priv->mode;
    dcu_info.dcu_USCOREprogram_USCOREid = dcu->priv->programId;

    input_data.dcu_USCOREdata = &dcu_info;
    input_data.dcu_USCOREid = g_strdup(dcu->priv->id);

    if(soap_call___ns1__editDcuOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        execute_result = output_data.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }

    g_free(input_data.dcu_USCOREid);
    g_free(dcu_info.dcu_USCOREid);
    g_free(dcu_info.dcu_USCOREphone);
    g_free(dcu_info.dcu_USCOREgps);
    g_free(dcu_info.dcu_USCOREnote);
    g_free(dcu_info.dcu_USCOREaddress);

    smartstreetlight_free_soap_operation(spl_soap);
    return execute_result;
}

/** *********************************************** REMOVE DCU ******************************************** **/
gint smartstreetlight_remove_dcu_execute(SplSoap* spl_soap,const gchar *dcu_id)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__removeDcuOperation            input_data;
    struct _ns1__removeDcuOperationResponse    output_data;

    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    input_data.current_USCORElogin_USCOREinfo = &current_user_info;

    input_data.dcu_USCOREid = g_strdup(dcu_id);

    if(soap_call___ns1__removeDcuOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        execute_result = output_data.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }
    g_free(input_data.dcu_USCOREid);

    smartstreetlight_free_soap_operation(spl_soap);
    return execute_result;
}

/** *********************************************** SET PROGRAM FOR DCU ******************************************** **/
gint smartstreetlight_set_program_for_dcu_execute(SplSoap* spl_soap,const gchar *dcu_id,
                                                      const gint dcu_mode,
                                                      const gint dcu_program_id)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__setProgramDcuOperation            input_data;
    struct _ns1__setProgramDcuOperationResponse    output_data;

    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
     current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    input_data.current_USCORElogin_USCOREinfo = &current_user_info;

    /*
        char*                                dcu_USCOREid
        int                                  dcu_USCOREmode
        char*                                dcu_USCOREprogram
    */

    input_data.dcu_USCOREid = g_strdup(dcu_id);
    input_data.dcu_USCOREmode = dcu_mode;
    input_data.dcu_USCOREprogramId = dcu_program_id;
    if(soap_call___ns1__setProgramDcuOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        execute_result = output_data.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }

    g_free(input_data.dcu_USCOREid);
//    g_free(input_data.dcu_USCOREprogram);
    smartstreetlight_free_soap_operation(spl_soap);
    return execute_result;
}
/** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ LCU @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ **/
/** *********************************************** GET LCU ******************************************** **/

gint smartstreetlight_get_lcu_list_nofree_execute(SplSoap* spl_soap,const gchar * dcu_id, ns1__LCU_USCOREINFO_USCOREType ***lcu_list, gint *lcu_list_size)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__getLcuListOperation            req;
    struct _ns1__getLcuListOperationResponse    rsp;
    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;

    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;

    req.current_USCORElogin_USCOREinfo = &current_user_info;
    req.dcu_USCOREid = g_strdup(dcu_id);

    if(soap_call___ns1__getLcuListOperation(spl_soap->soap, smartstreetlight_server_url, "", &req, &rsp)==SOAP_OK)
    {
        if(rsp.message_USCOREresult == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
        {
            *lcu_list = rsp.lcu_USCORElist;
            *lcu_list_size = rsp.__sizelcu_USCORElist;
        }
        execute_result = rsp.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }
    g_free( req.dcu_USCOREid);
    return execute_result;
}

/** *********************************************** ADD LCU ******************************************** **/
gint  smartstreetlight_add_lcu_execute(SplSoap* spl_soap,pSplLcu lcu)
{
    smartstreetlight_soap_int(spl_soap);
    gboolean execute_result;

    struct _ns1__addLcuOperation            input_data;
    struct _ns1__addLcuOperationResponse    output_data;

    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    input_data.current_USCORElogin_USCOREinfo = &current_user_info;


    struct ns1__LCU_USCOREINFO_USCOREType lcu_info;
    lcu_info.lcu_USCOREid = g_strdup(lcu->id);
    lcu_info.lcu_USCOREgps = g_strdup(lcu->gps);
    lcu_info.lcu_USCOREnote = g_strdup(lcu->note);
    lcu_info.lcu_USCORElightname = g_strdup(lcu->lightname);
    lcu_info.lcu_USCOREdcuid = g_strdup(lcu->parent->priv->id);
    lcu_info.lcu_USCOREmode = lcu->mode;
    lcu_info.lcu_USCOREpower = lcu->power;
    lcu_info.lcu_USCOREtolerance = lcu->tolerance;

    /** other empty element **/

    input_data.lcu = &lcu_info;

    if(soap_call___ns1__addLcuOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        execute_result = output_data.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }
    g_free(lcu_info.lcu_USCOREid);
    g_free(lcu_info.lcu_USCOREgps);
    g_free(lcu_info.lcu_USCOREnote);
    g_free(lcu_info.lcu_USCOREdcuid);
    g_free(lcu_info.lcu_USCORElightname);

    smartstreetlight_free_soap_operation(spl_soap);
    return execute_result;
}

/** *********************************************** EDIT LCU ******************************************** **/
gint smartstreetlight_edit_lcu_execute(SplSoap* spl_soap,pSplLcu lcu)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__editLcuOperation            input_data;
    struct _ns1__editLcuOperationResponse    output_data;
    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    struct ns1__LCU_USCOREINFO_USCOREType lcu_soap;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;

    lcu_soap.lcu_USCOREid = g_strdup((const gchar*)lcu->id);
    lcu_soap.lcu_USCOREgps = g_strdup((const gchar*)lcu->gps);
    lcu_soap.lcu_USCOREnote = g_strdup ((const gchar*)lcu->note);
    lcu_soap.lcu_USCOREdcuid = g_strdup ((const gchar*)lcu->parent->priv->id);
    lcu_soap.lcu_USCORElightname = g_strdup ((const gchar*)lcu->lightname);
    lcu_soap.lcu_USCOREpower = lcu->power;
    lcu_soap.lcu_USCOREtolerance = lcu->tolerance;
    //DEBUG ("lcu->gps: '%s', lcu->note: '%s'\n", lcu->gps, lcu->note);
    input_data.current_USCORElogin_USCOREinfo = &current_user_info;
    input_data.lcu_USCOREid = g_strdup((const gchar*)lcu->id); //g_strdup_printf("%d", zone->zonecode);
    input_data.lcu_USCOREdata = &lcu_soap;

    if(soap_call___ns1__editLcuOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        execute_result = output_data.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }

    g_free(input_data.lcu_USCOREid);
    g_free(lcu_soap.lcu_USCOREid);
    g_free(lcu_soap.lcu_USCOREgps);
    g_free(lcu_soap.lcu_USCOREnote);
    g_free(lcu_soap.lcu_USCOREdcuid);
    smartstreetlight_free_soap_operation(spl_soap);
    return execute_result;
}
/** *********************************************** REMOVE LCU ******************************************** **/
gint smartstreetlight_remove_lcu_execute(SplSoap* spl_soap, const gchar *lcu_id,
                                                            const gchar *lcu_dcuid)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__removeLcuOperation            input_data;
    struct _ns1__removeLcuOperationResponse    output_data;

    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    input_data.current_USCORElogin_USCOREinfo = &current_user_info;

    input_data.lcu_USCOREid = g_strdup(lcu_id);
    input_data.dcu_USCOREid = g_strdup(lcu_dcuid);

    if(soap_call___ns1__removeLcuOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        execute_result = output_data.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }
    g_free(input_data.lcu_USCOREid);
    g_free(input_data.dcu_USCOREid);
    smartstreetlight_free_soap_operation(spl_soap);
    return execute_result;
}
/** *********************************************** CONTROL LCU ******************************************** **/
gint smartstreetlight_control_lcu_nofree(SplSoap* spl_soap,const gchar *dcu_id,
                                             GString * listOnlcu ,GString * listOfflcu,
                                             const gint level,
                                             gint mode,
                                             gboolean istemp,
                                             ns1__LCU_USCOREINFO_USCOREType ***rsp_lcu_list, gint* rsp_lcu_list_size,
                                             gboolean isprogram)
{

    DEBUG("CONTROL WITH LEVEL IS: %d", level);

    gint ret;
    gchar ** on_lcu_id_tocken = NULL;
    gchar ** off_lcu_id_tocken = NULL;
    smartstreetlight_soap_int(spl_soap);
    gint ctrl_lcu_list_size= 0;
    if (listOnlcu != NULL)
    {
        on_lcu_id_tocken = g_strsplit_set (listOnlcu->str,"-",-1);
        ctrl_lcu_list_size+= g_strv_length(on_lcu_id_tocken);
    }
    if (listOfflcu != NULL)
    {
        off_lcu_id_tocken = g_strsplit_set (listOfflcu->str,"-",-1);
        ctrl_lcu_list_size+= g_strv_length(off_lcu_id_tocken);
    }
    if (ctrl_lcu_list_size == 0){
        DEBUG("error internal: ctrl_lcu_list_size = 0");
        return false;
    }
    DEBUG("ctrl_lcu_list_size: %d", ctrl_lcu_list_size);
    ns1__LCU_USCOREINFO_USCOREType *ctrl_lcu_list[ctrl_lcu_list_size];
    DEBUG("ctrl_lcu_list: %p", ctrl_lcu_list);
    gint index = 0;
    // on light
    if (on_lcu_id_tocken)
    {
        DEBUG("on_lcu_id_tocken");
         for (; index<g_strv_length(on_lcu_id_tocken); index++)
        {

            ns1__LCU_USCOREINFO_USCOREType* ctrl_lcu = new ns1__LCU_USCOREINFO_USCOREType();
            ctrl_lcu_list[index] =  ctrl_lcu;
            DEBUG("@ctrl_lcu_list[%d] =  %p", index, &ctrl_lcu_list[index]);
            DEBUG("==>ctrl_lcu_list[%d] =  %p", index, ctrl_lcu_list[index]);
            ctrl_lcu->lcu_USCOREid = on_lcu_id_tocken[index];
            ctrl_lcu->lcu_USCOREdcuid = g_strdup(dcu_id);
            ctrl_lcu->lcu_USCOREgps = (gchar *)"";
            ctrl_lcu->lcu_USCOREnote = (gchar *)"";
            ctrl_lcu->lcu_USCORElightname = (gchar *)"";
            ctrl_lcu->lcu_USCOREison =TRUE;
            ctrl_lcu->lcu_USCORElevel = level;
            if (isprogram == TRUE)
                ctrl_lcu->lcu_USCOREmode = SPL_LCU_ScheduleMode;
            else
                ctrl_lcu->lcu_USCOREmode = mode;
        }
    }
    if (off_lcu_id_tocken)
    {
        DEBUG("off_lcu_id_tocken");
         for (int i =0 ; index<ctrl_lcu_list_size; index++, i++)
        {
            ns1__LCU_USCOREINFO_USCOREType* ctrl_lcu = new ns1__LCU_USCOREINFO_USCOREType();
            ctrl_lcu_list[index] =  ctrl_lcu;
//            DEBUG("ctrl_lcu_list[%d] =  %p", index, &ctrl_lcu_list[index]);
//            DEBUG("==>ctrl_lcu_list[%d] =  %p", index, ctrl_lcu_list[index]);
            ctrl_lcu->lcu_USCOREid = off_lcu_id_tocken[i];
            ctrl_lcu->lcu_USCOREdcuid = g_strdup(dcu_id);
            ctrl_lcu->lcu_USCOREgps =(gchar *)"";
            ctrl_lcu->lcu_USCOREnote =(gchar *)"";
            ctrl_lcu->lcu_USCORElightname =(gchar *)"";
            ctrl_lcu->lcu_USCOREison =FALSE;
            ctrl_lcu->lcu_USCORElevel = level;
            if (isprogram == TRUE)
                ctrl_lcu->lcu_USCOREmode = SPL_LCU_OffMode;
            else
                ctrl_lcu->lcu_USCOREmode = mode;
        }
    }
//    DEBUG_1();


    ret = smartstreetlight_control_lcu_nofree_execute(spl_soap,dcu_id,
                                             ctrl_lcu_list, ctrl_lcu_list_size,
                                             istemp,
                                             rsp_lcu_list, rsp_lcu_list_size, isprogram);
    for (index = 0; index<ctrl_lcu_list_size; index++)
    {
        ns1__LCU_USCOREINFO_USCOREType* ctrl_lcu = ctrl_lcu_list[index];
        g_char_free(ctrl_lcu->lcu_USCOREdcuid);
        free(ctrl_lcu);
    }
    if (on_lcu_id_tocken)
    {
        g_strfreev(on_lcu_id_tocken);
    }
    if (off_lcu_id_tocken)
    {
        g_strfreev(off_lcu_id_tocken);
    }
    return ret;
}
gint smartstreetlight_control_lcu_nofree_execute(SplSoap* spl_soap,const gchar *dcu_id,
                                             ns1__LCU_USCOREINFO_USCOREType **ctrl_lcu_list, gint ctrl_lcu_list_size,
                                             gboolean istemp,
                                             ns1__LCU_USCOREINFO_USCOREType ***rsp_lcu_list, gint* rsp_lcu_list_size, gboolean isprogram)
{
    //DEBUG("ctrl_lcu_list_size: %d", ctrl_lcu_list_size);
//    DEBUG("ctrl_lcu_list: %s", ctrl_lcu_list[0]->);

    gint execute_result;

    struct _ns1__controlLcuOperation            input_data;
    struct _ns1__controlLcuOperationResponse    output_data;

    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    input_data.current_USCORElogin_USCOREinfo = &current_user_info;
    input_data.istemp = istemp;
    input_data.dcuid= g_strdup(dcu_id);
    input_data.lculist = ctrl_lcu_list;
    input_data.__sizelculist = ctrl_lcu_list_size;
    input_data.is_USCOREProgram = isprogram;
    if(soap_call___ns1__controlLcuOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        if(output_data.message_USCOREresult == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
        {
            *rsp_lcu_list = output_data.lculist;
            *rsp_lcu_list_size = output_data.__sizelculist;
        }
        execute_result = output_data.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }
    g_free(input_data.dcuid);
    return execute_result;
}
/** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ LINE @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ **/
/** *********************************************** GET LINE ******************************************** **/

gint smartstreetlight_get_line_list_nofree_execute(SplSoap* spl_soap,const gchar * dcu_id, ns1__LINE_USCOREINFO_USCOREType ***line_list, gint* line_list_size)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__getLineListOperation            req;
    struct _ns1__getLineListOperationResponse    rsp;


    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;

    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;


    req.current_USCORElogin_USCOREinfo = &current_user_info;
    req.dcu_USCOREid = g_strdup(dcu_id);

    if(soap_call___ns1__getLineListOperation(spl_soap->soap, smartstreetlight_server_url, "", &req, &rsp)==SOAP_OK)
    {
        if(rsp.message_USCOREresult == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
        {
            *line_list_size = rsp.__sizeline_USCORElist;
            *line_list = rsp.line_USCORElist;
        }
        execute_result = rsp.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }
    g_free( req.dcu_USCOREid);
    return execute_result;
}

/** *********************************************** ADD LINE ******************************************** **/
gint smartstreetlight_add_line_execute(SplSoap* spl_soap,struct ns1__LINE_USCOREINFO_USCOREType *line_info)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__addLineOperation            input_data;
    struct _ns1__addLineOperationResponse    output_data;

    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    input_data.current_USCORElogin_USCOREinfo = &current_user_info;
    /** other empty element **/
    input_data.line = line_info;

    if(soap_call___ns1__addLineOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        execute_result = output_data.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }
    smartstreetlight_free_soap_operation(spl_soap);
    return execute_result;
}

/** *********************************************** REMOVE LINE ******************************************** **/
gint smartstreetlight_remove_line_execute(SplSoap* spl_soap,gint line_id,
                                              const gchar *line_dcuid)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__removeLineOperation            input_data;
    struct _ns1__removeLineOperationResponse    output_data;

    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    input_data.current_USCORElogin_USCOREinfo = &current_user_info;

    input_data.line_USCOREid = line_id;
    input_data.dcu_USCOREid = g_strdup(line_dcuid);

    if(soap_call___ns1__removeLineOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        execute_result = output_data.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }

    g_free(input_data.dcu_USCOREid);

    smartstreetlight_free_soap_operation(spl_soap);
    return execute_result;
}


/** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ZONE @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ **/
/** ******************************************* GET ALL ZONE ******************************************** **/

gint smartstreetlight_get_all_zone_nofree_execute(SplSoap* spl_soap, ns1__ZONE_USCOREINFO_USCOREType ***zone_list, gint* zone_list_size)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__getAllZoneOperation            req;
    struct _ns1__getAllZoneOperationResponse    rsp;

    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    req.current_USCORElogin_USCOREinfo = &current_user_info;
    if(soap_call___ns1__getAllZoneOperation(spl_soap->soap, smartstreetlight_server_url, "", &req, &rsp)==SOAP_OK)
    {
        if(rsp.message_USCOREresult == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
        {
            execute_result = TRUE;
//            DEBUG("zone->zone_USCOREid: %d, zone->zone_USCOREname: '%s',zone->zone_USCOREnote: '%s'\n",
//                                        rsp.zone_USCORElist[0]->zone_USCOREid, rsp.zone_USCORElist[0]->zone_USCOREname,
//                                        rsp.zone_USCORElist[0]->zone_USCOREnote);
            *zone_list = rsp.zone_USCORElist;

            *zone_list_size = rsp.__sizezone_USCORElist;

        }
        execute_result = rsp.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }
    return execute_result;
}

/** ******************************************* ADD ZONE ******************************************** **/
gint smartstreetlight_add_zone_execute(SplSoap* spl_soap,ns1__ZONE_USCOREINFO_USCOREType *zone_info, gint *zone_id)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__addZoneOperation            req;
    struct _ns1__addZoneOperationResponse    rsp;

    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    req.current_USCORElogin_USCOREinfo = &current_user_info;

    req.zone = zone_info;

    if(soap_call___ns1__addZoneOperation(spl_soap->soap, smartstreetlight_server_url, "", &req, &rsp)==SOAP_OK)
    {
        if(rsp.message_USCOREresult == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
        {
            *zone_id = rsp.zone_USCOREid;
        }
         execute_result = rsp.message_USCOREresult;
    }
    else
    {
        soap_print_fault(spl_soap->soap, stderr);
    }

    smartstreetlight_free_soap_operation(spl_soap);
    return execute_result;
}
/** ******************************************* EDIT ZONE ******************************************** **/
gint  smartstreetlight_edit_zone_execute(SplSoap* spl_soap,ns1__ZONE_USCOREINFO_USCOREType *zone_info)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__editZoneOperation            req;
    struct _ns1__editZoneOperationResponse    rsp;

    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    req.current_USCORElogin_USCOREinfo = &current_user_info;

    req.zone = zone_info;

    if(soap_call___ns1__editZoneOperation(spl_soap->soap, smartstreetlight_server_url, "", &req, &rsp)==SOAP_OK)
    {
        execute_result = rsp.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }

    smartstreetlight_free_soap_operation(spl_soap);
    return execute_result;
}
/** ******************************************* REMOVE ZONE ******************************************** **/
gint smartstreetlight_remove_zone_execute(SplSoap* spl_soap,gint zone_id)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__removeZoneOperation            req;
    struct _ns1__removeZoneOperationResponse    rsp;

    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    req.current_USCORElogin_USCOREinfo = &current_user_info;

    req.zoneid = zone_id;

    if(soap_call___ns1__removeZoneOperation(spl_soap->soap, smartstreetlight_server_url, "", &req, &rsp)==SOAP_OK)
    {
        execute_result = rsp.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }

    smartstreetlight_free_soap_operation(spl_soap);
    return execute_result;
}


/** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ PROGRAM @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ **/
/** *********************************************** GET PROGRAM ******************************************** **/

gint smartstreetlight_get_program_list_nofree_execute(SplSoap* spl_soap,gint zone_id, gint program_id,
                                                   ns1__PROGRAM_USCOREINFO_USCOREType *** program, gint* program_size)
{
    smartstreetlight_soap_int(spl_soap);

    gint execute_result;
    /* Send current user login to server */
    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;

    struct _ns1__getProgramOperation            input_data;
    struct _ns1__getProgramOperationResponse    output_data;

    input_data.current_USCORElogin_USCOREinfo = &current_user_info;
    input_data.program_USCOREid = program_id;
    input_data.zone_USCOREid = zone_id;
    if(soap_call___ns1__getProgramOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        if(output_data.message_USCOREresult==ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
        {
            //DEBUG("output_data.program_USCORElist: %p\n", output_data.program_USCORElist);
            *program = output_data.program_USCORElist;
            *program_size = output_data.__sizeprogram_USCORElist;
        }
        execute_result = output_data.message_USCOREresult;
    }                   // we're done
     else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }

    return execute_result;
}

/** *********************************************** ADD PROGRAM ******************************************** **/
gint smartstreetlight_add_program_execute(SplSoap* spl_soap,gint zone_id, const gchar *program_name, gint * programe_id)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;
    struct _ns1__addProgramOperation            input_data;
    struct _ns1__addProgramOperationResponse    output_data;
    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    input_data.current_USCORElogin_USCOREinfo = &current_user_info;
    input_data.program_USCOREname = g_strdup(program_name);
    input_data.program_USCOREzoneId = zone_id;
    if(soap_call___ns1__addProgramOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        if(output_data.message_USCOREresult == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
        {
            *programe_id= output_data.program_USCOREid;
        }
        execute_result = output_data.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }
    g_free(input_data.program_USCOREname);

    smartstreetlight_free_soap_operation(spl_soap);
    return execute_result;
}

/** *********************************************** REMOVE PROGRAM ******************************************** **/
gint smartstreetlight_remove_program_execute(SplSoap* spl_soap,gint program_id)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;
    struct _ns1__removeProgramOperation            input_data;
    struct _ns1__removeProgramOperationResponse    output_data;
    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    input_data.current_USCORElogin_USCOREinfo = &current_user_info;
    input_data.program_USCOREid = program_id;
    if(soap_call___ns1__removeProgramOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        execute_result = output_data.message_USCOREresult;
    }
    else
    {
        execute_result =-1;
        soap_print_fault(spl_soap->soap, stderr);
    }

    smartstreetlight_free_soap_operation(spl_soap);
    return execute_result;
}
/** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ DAY SCHEDULE @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ **/
/** ******************************************* GET DAY SCHEDULE ******************************************** **/
gint smartstreetlight_get_day_schedule_list_nofree_execute(SplSoap* spl_soap,gint program_id,gint dayschedule_id,ns1__DAYSCHEDULE_USCOREINFO_USCOREType ***dayschedule_list, gint * dayschedule_list_size)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__getDayScheduleOperation            input_data;
    struct _ns1__getDayScheduleOperationResponse    output_data;

    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    input_data.current_USCORElogin_USCOREinfo = &current_user_info;

    input_data.program_USCOREid = program_id;
    input_data.dayschedule_USCOREid = dayschedule_id;  // 0 to get all


    if(soap_call___ns1__getDayScheduleOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        if(output_data.message_USCOREresult == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
        {
            *dayschedule_list = output_data.dayschedule_USCORElist;
            *dayschedule_list_size=output_data.__sizedayschedule_USCORElist;
        }
        execute_result = output_data.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }
    return execute_result;
}
/** ******************************************* ADD DAY SCHEDULE ******************************************** **/
gint smartstreetlight_add_day_schedule_execute(SplSoap* spl_soap,gint day_schedule_program_id,gint day_schedule_month, gint *day_schedule_id)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__addDayScheduleOperation            input_data;
    struct _ns1__addDayScheduleOperationResponse    output_data;

    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    input_data.current_USCORElogin_USCOREinfo = &current_user_info;

    ns1__DAYSCHEDULE_USCOREINFO_USCOREType day_schedule;

    day_schedule.dayschedule_USCOREmonth = day_schedule_month;
    day_schedule.dayschedule_USCOREprogram_USCOREid = day_schedule_program_id;
    input_data.dayschedule = &day_schedule;
    if(soap_call___ns1__addDayScheduleOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        if(output_data.message_USCOREresult == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
        {
            *day_schedule_id = output_data.dayschedule_USCOREid;
            DEBUG("GET ID: %d --out: %d\n", *day_schedule_id, output_data.dayschedule_USCOREid);
        }
        execute_result = output_data.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }

    smartstreetlight_free_soap_operation(spl_soap);
    return execute_result;
}

/** ******************************************* EDIT DAY SCHEDULE ******************************************** **/
gint smartstreetlight_edit_day_schedule_execute(SplSoap* spl_soap,gint dayschedule_id,
                                                          gint dayschedule_listscheduleid,
                                                          gint dayschedule_programid,
                                                          gint dayschedule_month)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__editDayScheduleOperation           input_data;
    struct _ns1__editDayScheduleOperationResponse   output_data;

    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    input_data.current_USCORElogin_USCOREinfo = &current_user_info;

    ns1__DAYSCHEDULE_USCOREINFO_USCOREType day_schedule;
    day_schedule.dayschedule_USCOREid = dayschedule_id;
    day_schedule.dayschedule_USCORElistScheduel_USCOREid = dayschedule_listscheduleid;
    day_schedule.dayschedule_USCOREprogram_USCOREid = dayschedule_programid;
    day_schedule.dayschedule_USCOREmonth = dayschedule_month;

    input_data.dayschedule = &day_schedule;

    if(soap_call___ns1__editDayScheduleOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        if(output_data.message_USCOREresult == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
        {
            execute_result = TRUE;
        }
        execute_result = output_data.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }


    smartstreetlight_free_soap_operation(spl_soap);
    return execute_result;
}

/** ******************************************* REMOVE DAY SCHEDULE ******************************************** **/
gint smartstreetlight_remove_day_schedule_execute(SplSoap* spl_soap,gint day_schedule_id)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__removeDayScheduleOperation            input_data;
    struct _ns1__removeDayScheduleOperationResponse    output_data;

    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
//    day_schedule.dayschedule_USCOREmonth = day_schedule_month;
//    day_schedule.dayschedule_USCOREprogram_USCOREid = day_schedule_program_id;
    input_data.current_USCORElogin_USCOREinfo = &current_user_info;

    input_data.dayschedule_USCOREid = day_schedule_id;

    if(soap_call___ns1__removeDayScheduleOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
//        if(output_data.message_USCOREresult == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
//        {
//            execute_result = TRUE;
//        }
//        else
//        {
//            gchar * msg = g_strdup("Lỗi xoá lập lịch tháng. ");
//            smartstreetlight_error_check_message_result(GTK_WIDGET(main_widgets->main_window),msg,output_data.message_USCOREresult);
//            g_char_free(msg);
//        }
        execute_result = output_data.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }

    smartstreetlight_free_soap_operation(spl_soap);
    return execute_result;
}

/** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ LIST SCHEDULE @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ **/
/** ******************************************* GET LIST SCHEDULE ******************************************** **/

gint smartstreetlight_get_list_schedule_nofree_execute(SplSoap* spl_soap,gint list_schedule_id,gint program_id,
                                                            ns1__LISTSCHEDULE_USCOREINFO_USCOREType ***listschedule_list,
                                                            gint *listschedule_list_size)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__getListScheduleOperation            input_data;
    struct _ns1__getListScheduleOperationResponse    output_data;

    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    input_data.current_USCORElogin_USCOREinfo = &current_user_info;

    input_data.listschedule_USCOREid = list_schedule_id;
    input_data.listschedule_USCOREprogramid = program_id;


    if(soap_call___ns1__getListScheduleOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        if(output_data.message_USCOREresult == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
        {
            *listschedule_list = output_data.listschedule_USCORElist;
            *listschedule_list_size = output_data.__sizelistschedule_USCORElist;
        }
        execute_result = output_data.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }
    return execute_result;
}

/** ******************************************* ADD LIST SCHEDULE ******************************************** **/
gint smartstreetlight_add_list_schedule_execute(SplSoap* spl_soap,const gchar *listschedule_name,
                                                          gint *listschedule_id,
                                                          gint program_id)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__addListScheduleOperation           input_data;
    struct _ns1__addListScheduleOperationResponse   output_data;

    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    input_data.current_USCORElogin_USCOREinfo = &current_user_info;

    input_data.listschedule_USCOREprogram_USCOREid = program_id;
    input_data.listschedule_USCOREname = g_strdup(listschedule_name);

    if(soap_call___ns1__addListScheduleOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        if(output_data.message_USCOREresult == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
        {
            *listschedule_id = output_data.listschedule_USCOREid;
        }
//        else
//        {
//            gchar * msg = g_strdup("Lỗi thêm mới danh sách lập lịch ngày. ");
//            smartstreetlight_error_check_message_result(msg,output_data.message_USCOREresult);
//            g_char_free(msg);
//        }
        execute_result = output_data.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }
    g_char_free(input_data.listschedule_USCOREname);

    smartstreetlight_free_soap_operation(spl_soap);
    return execute_result;
}
/** ******************************************* EDIT LIST SCHEDULE ******************************************** **/
gint smartstreetlight_edit_list_schedule_execute(SplSoap* spl_soap,SplDaySchedule* daySchedule)
{
    smartstreetlight_soap_int(spl_soap);
    gint ret;
    ns1__LISTSCHEDULE_USCOREINFO_USCOREType listschedule;
    guint schedule_list_length = g_slist_length(daySchedule->itemlistTmp);
    ns1__SCHEDULE_USCOREINFO_USCOREType *listItemSchedule[schedule_list_length];

    GSList  *iter;
    gint i;
    listschedule.listscheduleId = daySchedule->Id;
    listschedule.listscheduleName = daySchedule->name;
    listschedule.listscheduleProgramId = daySchedule->programId;
    listschedule.sheduleList = (ns1__SCHEDULE_USCOREINFO_USCOREType **) listItemSchedule;
    listschedule.__sizesheduleList = schedule_list_length;
    for (iter = daySchedule->itemlistTmp, i = 0; iter; iter = g_slist_next(iter), i++)
    {

        ns1__SCHEDULE_USCOREINFO_USCOREType* schedule = new ns1__SCHEDULE_USCOREINFO_USCOREType();
        SplDayScheduleItem* tmp_schedule_item =( SplDayScheduleItem*) iter->data;
        listItemSchedule[i] =  schedule;
        schedule->scheduleListscheduleId= listschedule.listscheduleProgramId;
        schedule->scheduleStarttime = tmp_schedule_item->timeBegin;
        schedule->scheduleOntime =tmp_schedule_item->timeOn;
        schedule->scheduleLevel = tmp_schedule_item->level;
        DEBUG("timeBegin: %d\n", tmp_schedule_item->timeBegin);
    }

    ret = smartstreetlight_edit_list_schedule(spl_soap,&listschedule,&daySchedule->Id);

    smartstreetlight_free_soap_operation(spl_soap);
    return ret;
}
/** ******************************************* EDIT LIST SCHEDULE ******************************************** **/
gint smartstreetlight_edit_list_schedule(SplSoap* spl_soap,ns1__LISTSCHEDULE_USCOREINFO_USCOREType *listschedule,
                                                          gint *listschedule_id)
{

    gint execute_result;

    struct _ns1__editListScheduleOperation           input_data;
    struct _ns1__editListScheduleOperationResponse   output_data;

    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    input_data.current_USCORElogin_USCOREinfo = &current_user_info;

    input_data.listschedule = listschedule;
    if(soap_call___ns1__editListScheduleOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        if(output_data.message_USCOREresult == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
        {
            *listschedule_id = output_data.listscheduleId;
        }
        execute_result = output_data.message_USCOREresult;

    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }

    return execute_result;
}
/** ******************************************* REMOVE LIST SCHEDULE ******************************************** **/
gint smartstreetlight_remove_list_schedule_execute(SplSoap* spl_soap,gint listschedule_id)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__removeListScheduleOperation           input_data;
    struct _ns1__removeListScheduleOperationResponse   output_data;

    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    input_data.current_USCORElogin_USCOREinfo = &current_user_info;

    input_data.listschedule_USCOREid = listschedule_id;

    if(soap_call___ns1__removeListScheduleOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        execute_result = output_data.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }


    smartstreetlight_free_soap_operation(spl_soap);
    return execute_result;
}

/** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ SCHEDULE @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ **/
/** ******************************************* GET SCHEDULE ******************************************** **/
gint smartstreetlight_get_schedule_nofree_execute(SplSoap* spl_soap,gint list_schedule_id,gint schedule_id,
                                                      ns1__SCHEDULE_USCOREINFO_USCOREType ***schedule_list,
                                                      gint *schedule_list_size)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__getScheduleOperation            input_data;
    struct _ns1__getScheduleOperationResponse    output_data;

    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    input_data.current_USCORElogin_USCOREinfo = &current_user_info;

    input_data.listschedule_USCOREid = list_schedule_id;
    input_data.schedule_USCOREid = schedule_id;  // 0 to get all


    if(soap_call___ns1__getScheduleOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        if(output_data.message_USCOREresult == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
        {
            *schedule_list= output_data.schedule_USCORElist;
            *schedule_list_size = output_data.__sizeschedule_USCORElist;
        }
//        else
//        {
//            gchar * msg = g_strdup("Lỗi lấy thông tin lập lịch. ");
//            smartstreetlight_error_check_message_result(msg,output_data.message_USCOREresult);
//            g_char_free(msg);
//        }
        execute_result = output_data.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }
    return execute_result;
}
/** ******************************************* REMOVE SCHEDULE ******************************************** **/
gint smartstreetlight_remove_schedule_execute(SplSoap* spl_soap,gint schedule_id)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__removeScheduleOperation           input_data;
    struct _ns1__removeScheduleOperationResponse   output_data;

    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    input_data.current_USCORElogin_USCOREinfo = &current_user_info;

    input_data.schedule_USCOREid = schedule_id;

    if(soap_call___ns1__removeScheduleOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        execute_result = output_data.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }


    smartstreetlight_free_soap_operation(spl_soap);
    return execute_result;
}
/** ******************************************* ADD SCHEDULE ******************************************** **/
gint smartstreetlight_add_item_schedule_execute(SplSoap* spl_soap,gint listschedle_id,
                                                          gint starttime,
                                                          gint timeon,
                                                          gint level,
                                                          gint *schedule_id)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__addScheduleOperation           input_data;
    struct _ns1__addScheduleOperationResponse   output_data;

    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    input_data.current_USCORElogin_USCOREinfo = &current_user_info;

    ns1__SCHEDULE_USCOREINFO_USCOREType schedule_data;

    schedule_data.scheduleListscheduleId = listschedle_id;
    schedule_data.scheduleStarttime = starttime;
    schedule_data.scheduleOntime = timeon;
    schedule_data.scheduleLevel = level;

    input_data.schedule = &schedule_data;

    if(soap_call___ns1__addScheduleOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        if(output_data.message_USCOREresult == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
        {
            *schedule_id = output_data.schedule_USCOREid;
        }
//        else
//        {
//            gchar * msg = g_strdup("Lỗi thêm mới lập lịch. ");
//            smartstreetlight_error_check_message_result(msg,output_data.message_USCOREresult);
//            g_char_free(msg);
//        }
        execute_result = output_data.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }


    smartstreetlight_free_soap_operation(spl_soap);
    return execute_result;
}
/** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ EVENT LOG @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ **/
/** ******************************************* GET EVENT LOG ******************************************** **/
gint smartstreetlight_get_event_log_nofree_execute(SplSoap* spl_soap,gchar *dcu_id, ns1__EVENTLOG_USCORETYPE_USCOREEnum type_log,
                                              ns1__EVENT_USCORELOG_USCOREINFO_USCOREType ***eventlog_list, gint * eventlog_list_size)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__getEventLogOperation            input_data;
    struct _ns1__getEventLogOperationResponse    output_data;
    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    input_data.current_USCORElogin_USCOREinfo = &current_user_info;
    input_data.dcu_USCOREid = g_strdup(dcu_id);

    input_data.eventlog_USCOREtype = (ns1__EVENTLOG_USCORETYPE_USCOREEnum)type_log;
    if(soap_call___ns1__getEventLogOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        if(output_data.message_USCOREresult == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
        {
            *eventlog_list = output_data.eventlog_USCORElist;
            * eventlog_list_size=output_data.__sizeeventlog_USCORElist;
        }
        execute_result = output_data.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }
    g_free(input_data.dcu_USCOREid);
//    DEBUG("* eventlog_list_size: %d/n", * eventlog_list_size);
    return execute_result;
}
/** ******************************************* DELETE EVENT LOG ******************************************** **/
gint smartstreetlight_delete_event_log_execute(SplSoap* spl_soap,gint eventlog_id)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__deleteEventLogOperation            input_data;
    struct _ns1__deleteEventLogOperationResponse    output_data;
    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    input_data.current_USCORElogin_USCOREinfo = &current_user_info;
    input_data.even_USCOREid = eventlog_id;
    if(soap_call___ns1__deleteEventLogOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        execute_result = output_data.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }
    smartstreetlight_free_soap_operation(spl_soap);
    return execute_result;
}
/** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ USER LOG @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ **/
/** ******************************************* GET USER LOG ******************************************** **/
gint smartstreetlight_get_user_log_nofree_execute(SplSoap* spl_soap,gint user_id, ns1__USER_USCORELOG_USCOREINFO_USCOREType *** userlog_List, gint* userlog_List_size)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__getUserLogOperation            input_data;
    struct _ns1__getUserLogOperationResponse   output_data;
    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    input_data.current_USCORElogin_USCOREinfo = &current_user_info;
    input_data.user_USCOREid = user_id;
    if(soap_call___ns1__getUserLogOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        if(output_data.message_USCOREresult == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
        {
            *userlog_List = output_data.userlog_USCORElist;
            *userlog_List_size=output_data.__sizeuserlog_USCORElist;
        }
        execute_result = output_data.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }
    return execute_result;
}
/** ******************************************* DELETE USER LOG ******************************************** **/
gint smartstreetlight_delete_user_log_execute(SplSoap* spl_soap,gint userlog_id)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__deleteUserLogOperation            input_data;
    struct _ns1__deleteUserLogOperationResponse    output_data;

    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    input_data.current_USCORElogin_USCOREinfo = &current_user_info;
    input_data.userlog_USCOREid = userlog_id;
    if(soap_call___ns1__deleteUserLogOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        execute_result = output_data.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }
    smartstreetlight_free_soap_operation(spl_soap);
    return execute_result;
}
/** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ USER @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ **/
/** ******************************************** Get USER ******************************************* **/
gint smartstreetlight_get_user_nofree_execute(SplSoap* spl_soap,gint user_id,ns1__USER_USCOREINFO_USCOREType ***user_list, gint * user_list_size)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__getAllUserOperation            input_data;
    struct _ns1__getAllUserOperationResponse    output_data;
    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;

    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;

    input_data.current_USCORElogin_USCOREinfo = &current_user_info;

    input_data.userid = user_id;

    if(soap_call___ns1__getAllUserOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        if(output_data.message_USCOREresult == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
        {
            *user_list= output_data.user_USCORElist;
            *user_list_size = output_data.__sizeuser_USCORElist;
            //DEBUG("*user_list_size: %d --out: %d", *user_list_size, output_data.__sizeuser_USCORElist);
        }
        execute_result = output_data.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }

    return execute_result;
}
/** ***************************************** Add USER ************************************** **/
gint  smartstreetlight_add_user_execute(SplSoap* spl_soap,ns1__USER_USCOREINFO_USCOREType user, gint * new_user_id)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__addUserOperation            input_data;
    struct _ns1__addUserOperationResponse    output_data;

    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    input_data.current_USCORElogin_USCOREinfo = &current_user_info;
    input_data.user = &user;

//    DEBUG_0("\n EDIT SEND");
//    DEBUG_0("\n dcu manage:  %d", user.user_USCOREaccount);
//    DEBUG_0("\n dcu manage:  %d", user.user_USCOREpass);
//    DEBUG_0("\n dcu manage:  %d", user.user_USCOREemail);
//    DEBUG_0("\n dcu manage:  %d", user.user_USCOREphone);
//
//    DEBUG_0("\n dcu manage:  %d", user.user_USCOREmanage_USCOREdcu_USCOREprivilege);
//    DEBUG_0("\n lcu manage:  %d", user.user_USCOREmanage_USCORElculine_USCOREprivilege);
//    DEBUG_0("\n lcu control: %d", user.user_USCOREcontrol_USCORElculine_USCOREprivilege);
//    DEBUG_0("\n lcu control: %d", user.user_USCOREcontrol_USCORElculine_USCOREprivilege);
//    DEBUG_0("\n device setup: %d", user.user_USCOREsetup_USCOREdevice_USCOREprivilege);
//    DEBUG_0("\n program     : %d", user.user_USCOREprogram_USCOREprivilege);
//    DEBUG_0("\n email       : %d", user.user_USCOREnotify_USCOREmail_USCOREprivilege);
//    DEBUG_0("\n sms         : %d", user.user_USCOREnotify_USCOREsms_USCOREprivilege);
//
//    DEBUG_0("\n email enable: %d", user.user_USCOREnotify_USCOREmail_USCOREenable);
//    DEBUG_0("\n sms   enable: %d", user.user_USCOREnotify_USCOREsms_USCOREenable);


    if(soap_call___ns1__addUserOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        if(output_data.message_USCOREresult == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
        {
            *new_user_id = output_data.user_USCOREid;
            //DEBUG("*new_user_id: %d, --out: %d", *new_user_id, output_data.user_USCOREid);
        }
        execute_result = output_data.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }
    smartstreetlight_free_soap_operation(spl_soap);
    return execute_result;
}
/** ***************************************** Edit USER ************************************** **/
gint  smartstreetlight_edit_user_execute(SplSoap* spl_soap, ns1__USER_USCOREINFO_USCOREType user, gboolean isAddZone)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__editUserOperation            input_data;
    struct _ns1__editUserOperationResponse    output_data;

    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    input_data.current_USCORElogin_USCOREinfo = &current_user_info;
    input_data.user = &user;
    input_data.isAddZone = isAddZone;


//    DEBUG_0("\n username: %s", user.user_USCOREaccount);
//    DEBUG_0("\n userid: %d", user.user_USCOREid);
//    DEBUG_0("\n size zonelist: %d", user.__sizezone_USCORElist);
//    for(gint i=0; i<user.__sizezone_USCORElist; i++)
//    {
//        DEBUG_0("\n i: %d", i);
//        DEBUG_0("\n zonelist[%d]: %d", i, user.zone_USCORElist[i]->zone_USCOREid);
//    }
//    DEBUG_1();
//    DEBUG_0("\n EDIT SEND");
//    DEBUG_0("\n dcu manage:  %d", user.user_USCOREmanage_USCOREdcu_USCOREprivilege);
//    DEBUG_0("\n lcu manage:  %d", user.user_USCOREmanage_USCORElculine_USCOREprivilege);
//    DEBUG_0("\n lcu control: %d", user.user_USCOREcontrol_USCORElculine_USCOREprivilege);
//    DEBUG_0("\n lcu control: %d", user.user_USCOREcontrol_USCORElculine_USCOREprivilege);
//    DEBUG_0("\n device setup: %d", user.user_USCOREsetup_USCOREdevice_USCOREprivilege);
//    DEBUG_0("\n program     : %d", user.user_USCOREprogram_USCOREprivilege);
//    DEBUG_0("\n email       : %d", user.user_USCOREnotify_USCOREmail_USCOREprivilege);
//    DEBUG_0("\n sms         : %d", user.user_USCOREnotify_USCOREsms_USCOREprivilege);
//
//    DEBUG_0("\n email enable: %d", user.user_USCOREnotify_USCOREmail_USCOREenable);
//    DEBUG_0("\n sms   enable: %d", user.user_USCOREnotify_USCOREsms_USCOREenable);

    if(soap_call___ns1__editUserOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        execute_result = output_data.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }
    smartstreetlight_free_soap_operation(spl_soap);
    return execute_result;
}

/** ***************************************** Remove USER ************************************** **/
gint  smartstreetlight_remove_user_execute(SplSoap* spl_soap, gint user_id)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__removeUserOperation            input_data;
    struct _ns1__removeUserOperationResponse    output_data;

    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    input_data.current_USCORElogin_USCOREinfo = &current_user_info;
    input_data.user_USCOREid = user_id;

    if(soap_call___ns1__removeUserOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        execute_result = output_data.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }
    smartstreetlight_free_soap_operation(spl_soap);
    return execute_result;
}
/** ***************************************** Update info USER ************************************** **/
gint  smartstreetlight_edit_user_by_user_execute(SplSoap* spl_soap, gint user_id,
                                                   const gchar *password,
                                                   const gchar *phone,
                                                   const gchar *email,
                                                   gboolean enable_sms_notify,
                                                   gboolean enable_email_notify)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__editUserByUserOperation            input_data;
    struct _ns1__editUserByUserOperationResponse    output_data;

    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;
   current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    input_data.current_USCORElogin_USCOREinfo = &current_user_info;

    struct ns1__USER_USCOREINFO_USCOREType user_info;
    user_info.user_USCOREid = user_id;
    user_info.user_USCOREaccount = smartstreetlight_username;
    user_info.user_USCOREpass = g_strdup(password);
    user_info.user_USCOREphone = g_strdup(phone);
    user_info.user_USCOREemail = g_strdup(email);
    user_info.user_USCOREnotify_USCOREmail_USCOREenable = enable_email_notify;
    user_info.user_USCOREnotify_USCOREsms_USCOREenable = enable_sms_notify;

    input_data.user = &user_info;

    if(soap_call___ns1__editUserByUserOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        execute_result = output_data.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }
     g_char_free(user_info.user_USCOREpass);
     g_char_free(user_info.user_USCOREphone);
     g_char_free(user_info.user_USCOREemail);

    smartstreetlight_free_soap_operation(spl_soap);
    return execute_result;
}



/** ***************************************** Update runtime USER ************************************** **/
gint spl_event_runtime_update_nofree(SplSoap* spl_soap, ns1__DCU_USCOREINFO_USCOREType ***dcu_list, gint *dcu_list_size,
                                         ns1__LCU_USCOREINFO_USCOREType ***lcu_list, gint *lcu_list_size,
                                         ns1__EVENT_USCORELOG_USCOREINFO_USCOREType ***eventlog_list, gint *eventlog_list_size)
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__updateRuntimeForUserOperation            input_data;
    struct _ns1__updateRuntimeForUserOperationResponse    output_data;
    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;


    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    input_data.current_USCORElogin_USCOREinfo = &current_user_info;

    if(soap_call___ns1__updateRuntimeForUserOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        if(output_data.message_USCOREresult == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
        {
            *dcu_list = output_data.dcu_USCORElist;
            *dcu_list_size = output_data.__sizedcu_USCORElist;

            *lcu_list = output_data.lcu_USCORElist;
            *lcu_list_size = output_data.__sizelcu_USCORElist;

            *eventlog_list = output_data.eventlog_USCORElist;
            *eventlog_list_size = output_data.__sizeeventlog_USCORElist;
        }
        execute_result = output_data.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }

    return execute_result;
}

#endif
/** ***************************************** Update runtime USER ************************************** **/
gint smartstreetlight_get_log_lcu_nofree_execute(SplSoap* spl_soap, gchar * lcu_id, gchar * time_from,
                                                    gchar * time_to
#ifdef __SPL_CHART__
                                                    ,ns1__LCULOGINFOType*** lcu_log_list,
                                                    gint * lcu_log_list_size
#endif
                                                    )
{
    smartstreetlight_soap_int(spl_soap);
    gint execute_result;

    struct _ns1__getLcuLogOperation            input_data;
    struct _ns1__getLcuLogOperationResponse    output_data;
    struct ns1__CURR_USCORELOGIN_USCOREINFO_USCOREType current_user_info;


    current_user_info.curr_USCOREusername           = smartstreetlight_username;
    current_user_info.curr_USCOREsession_USCOREid   = smartstreetlight_session_id;
    input_data.current_USCORElogin_USCOREinfo = &current_user_info;

    input_data.lcuId = g_strdup(lcu_id);
    input_data.timeForm = g_strdup(time_from);
    input_data.timeTo   = g_strdup(time_to);
    //DEBUG("smartstreetlight_server_url: %s\n",smartstreetlight_server_url);
    if(soap_call___ns1__getLcuLogOperation(spl_soap->soap, smartstreetlight_server_url, "", &input_data, &output_data)==SOAP_OK)
    {
        if(output_data.message_USCOREresult == ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)
        {
#ifdef __SPL_CHART__
            *lcu_log_list = output_data.lcuLoglist;
            *lcu_log_list_size = output_data.__sizelcuLoglist;
#else
            if(LcuLogList)
            {
                spl_utils_free_slist(&LcuLogList, (GDestroyNotify)spl_lcu_log_free);
                LcuLogList = NULL;
            }

            for(gint i=output_data.__sizelcuLoglist-1; i>=0; i--)
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
               // ns1__LCULOGINFOType *lcu_log_wsdl = output_data.lcuLoglist[i];
                pSplLcuLog lcu_log = spl_lcu_log_init();

                lcu_log->id = output_data.lcuLoglist[i]->lcuLogId;
                lcu_log->lcuId = g_strdup(output_data.lcuLoglist[i]->lcuLogLcuId);
                lcu_log->power_consum = (gdouble)output_data.lcuLoglist[i]->lcuLogPowerConsum;
                lcu_log->power_ctrl = (gdouble)output_data.lcuLoglist[i]->lcuLogPowerCtrl;
                lcu_log->power = (gdouble)output_data.lcuLoglist[i]->lcuLogPower;
                lcu_log->tolerance = output_data.lcuLoglist[i]->lcuLogTolerance;
                lcu_log->date_time = g_strdup(output_data.lcuLoglist[i]->lcuLogDate);
                lcu_log->status = output_data.lcuLoglist[i]->lcuLogStatus;
                lcu_log->mode = output_data.lcuLoglist[i]->lcuLogMode;
                lcu_log->lightname = g_strdup(output_data.lcuLoglist[i]->lcuLogLightName);
//                DEBUG("lcu_log->date_time: %s", lcu_log->date_time);
                LcuLogList = g_slist_prepend(LcuLogList, lcu_log);
            }
#endif
        }

        execute_result = output_data.message_USCOREresult;
    }
    else
    {
        execute_result = -1;
        soap_print_fault(spl_soap->soap, stderr);
    }
    g_free(input_data.lcuId);
    g_free(input_data.timeForm);
    g_free(input_data.timeTo);
#ifndef __SPL_CHART__
    smartstreetlight_free_soap_operation(spl_soap);
#endif
    return execute_result;
}


