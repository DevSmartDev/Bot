#ifndef SMARTSTREETLIGHT_SOAP_THREAD_H_INCLUDED
#define SMARTSTREETLIGHT_SOAP_THREAD_H_INCLUDED

#include "main.h"
#include "smartstreetlight_utils.h"
#include "smartstreetlight_callback.h"
#include "smartstreetlight_ui_method.h"
#include "smartstreetlight_soap.h"
typedef struct SoapResponse
{
    gint result_value;
    gpointer data;

} SoapResponse;
struct SplSoapThread {
    gboolean (*init_thread)(gpointer data,  void (*execute_soap)(gpointer args),
                                                    void *(*rsp_thread)(gpointer data));
    void (*execute_soap)(gpointer args);
    void *(*rsp_thread)(gpointer data);
    SplSoap spl_soap;
};

extern struct SplSoapThread soap_thread;
#endif // SMARTSTREETLIGHT_SOAP_THREAD_H_INCLUDED
