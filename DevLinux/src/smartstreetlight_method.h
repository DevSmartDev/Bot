#ifndef SMARTSTREETLIGHT_METHOD_H_INCLUDED
#define SMARTSTREETLIGHT_METHOD_H_INCLUDED

#include "main.h"

#define waiting_for_update(){\
    while(g_main_context_pending(NULL))\
       g_main_context_iteration(NULL, FALSE);}



#endif // SMARTSTREETLIGHT_METHOD_H_INCLUDED
