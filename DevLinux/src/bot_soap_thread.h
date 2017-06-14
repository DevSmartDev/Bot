#ifndef BOT_SOAP_THREAD_H_INCLUDED
#define BOT_SOAP_THREAD_H_INCLUDED

#include "main.h"
#include "bot_utils.h"
#include "bot_callback.h"
#include "bot_ui_method.h"
#include "bot_soap.h"
typedef struct SoapResponse
{
    gint result_value;
    gpointer data;

} SoapResponse;
struct botSoapThread {
    gboolean (*init_thread)(gpointer data,  void (*execute_soap)(gpointer args),
                                                    void *(*rsp_thread)(gpointer data));
    void (*execute_soap)(gpointer args);
    void *(*rsp_thread)(gpointer data);
    botSoap bot_soap;
};

extern struct botSoapThread soap_thread;
#endif // BOT_SOAP_THREAD_H_INCLUDED
