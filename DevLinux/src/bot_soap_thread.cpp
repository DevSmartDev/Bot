#include "bot_dcu.h"
#include "bot_lcu.h"
#include "bot_soap_thread.h"
#include "bot_soap.h"
#include "bot_error.h"


static void * bot_execute_thread(gpointer args);
static void bot_soap_create_thread_err(void);
static gboolean bot_init_thread(gpointer data, void (*execute_soap)(gpointer args),
                                                    void *(*rsp_thread)(gpointer data));

struct botSoapThread soap_thread = {
    bot_init_thread,
    NULL,
    NULL,
    NULL
};

static void* bot_soap_receive(gpointer data)
{
    DEBUG_1();
    bot_waiting_hide();
    DEBUG_1();
    soap_thread.rsp_thread(data);
    DEBUG_1();
    return NULL;
}

static void * bot_execute_thread(gpointer args)
{
    DEBUG_1();
    SoapResponse *soap_response = g_new(SoapResponse, 1);
    soap_response->data = args;
    DEBUG_1();
    soap_thread.execute_soap(soap_response);
    DEBUG_1();
    g_idle_add((GSourceFunc)bot_soap_receive, soap_response);
    return NULL;
}


static gboolean bot_init_thread(gpointer args,  void (*execute_soap)(gpointer args),
                                                             void *(*rsp_thread)(gpointer data))
{
    //pthread_t new_thread;
    GThread * new_thread = NULL;
    if (rsp_thread == NULL || execute_soap == NULL)
        return FALSE;
    soap_thread.rsp_thread = rsp_thread;
    soap_thread.execute_soap = execute_soap;
    DEBUG_1();
    bot_waiting_show();
    DEBUG_1();
//    gboolean is_ok = pthread_create(&new_thread, NULL, bot_execute_thread, args)==0?TRUE:FALSE;
//    if (is_ok == FALSE)
//         bot_waiting_hide();
    gboolean is_ok;
    new_thread = g_thread_new("soap_thead", GThreadFunc(bot_execute_thread), gpointer(args));
    if(new_thread==NULL)
    {
        DEBUG_1();
        bot_waiting_hide();
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

