#include "smartstreetlight_dcu.h"
#include "smartstreetlight_lcu.h"
#include "smartstreetlight_soap_thread.h"
#include "smartstreetlight_soap.h"
#include "smartstreetlight_error.h"


static void * smartstreetlight_execute_thread(gpointer args);
static void smartstreetlight_soap_create_thread_err(void);
static gboolean smartstreetlight_init_thread(gpointer data, void (*execute_soap)(gpointer args),
                                                    void *(*rsp_thread)(gpointer data));

struct SplSoapThread soap_thread = {
    smartstreetlight_init_thread,
    NULL,
    NULL,
    NULL
};

static void* smartstreetlight_soap_receive(gpointer data)
{
    DEBUG_1();
    spl_waiting_hide();
    DEBUG_1();
    soap_thread.rsp_thread(data);
    DEBUG_1();
    return NULL;
}

static void * smartstreetlight_execute_thread(gpointer args)
{
    DEBUG_1();
    SoapResponse *soap_response = g_new(SoapResponse, 1);
    soap_response->data = args;
    DEBUG_1();
    soap_thread.execute_soap(soap_response);
    DEBUG_1();
    g_idle_add((GSourceFunc)smartstreetlight_soap_receive, soap_response);
    return NULL;
}


static gboolean smartstreetlight_init_thread(gpointer args,  void (*execute_soap)(gpointer args),
                                                             void *(*rsp_thread)(gpointer data))
{
    //pthread_t new_thread;
    GThread * new_thread = NULL;
    if (rsp_thread == NULL || execute_soap == NULL)
        return FALSE;
    soap_thread.rsp_thread = rsp_thread;
    soap_thread.execute_soap = execute_soap;
    DEBUG_1();
    spl_waiting_show();
    DEBUG_1();
//    gboolean is_ok = pthread_create(&new_thread, NULL, smartstreetlight_execute_thread, args)==0?TRUE:FALSE;
//    if (is_ok == FALSE)
//         spl_waiting_hide();
    gboolean is_ok;
    new_thread = g_thread_new("soap_thead", GThreadFunc(smartstreetlight_execute_thread), gpointer(args));
    if(new_thread==NULL)
    {
        DEBUG_1();
        spl_waiting_hide();
        is_ok = FALSE;
    }
    else
    {
        DEBUG_1();
        is_ok = TRUE;
    }
    DEBUG_1();
    return is_ok;
}

