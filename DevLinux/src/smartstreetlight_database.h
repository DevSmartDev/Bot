#ifndef SMARTSTREETLIGHT_DATABASE_H_INCLUDED
#define SMARTSTREETLIGHT_DATABASE_H_INCLUDED

#include "main.h"
#include "smartstreetlight_common.h"

extern struct _STL_DATABASE
{
    const gchar *DCUTABLE;
    const gchar *LCUTABLE;
} _STL_DATABASE;

extern struct _STL_DCUTABLE
{
    const gchar *DCUID;
    const gchar *DCUPHONE;
    const gchar *DCUSCHEDULE;
} _STL_DCUTABLE;

extern struct _STL_LCUTABLE
{
    const gchar *LCUID;
    const gchar *LCUSTATUS;
    const gchar *LCUSTART;
    const gchar *LCULEVEL;
    const gchar *LCUBROKEN;
    const gchar *LCUDCUCODE;

} _STL_LCUTABLE;

#define _STL_DATABASE_INITIALIZER {"DCUTable","LCUTable"}
#define _STL_DCUTABLE_INITIALIZER {"DCUID","DCUPhone","CalendarTable_CalendarID"}
#define _STL_LCUTABLE_INITIALIZER {"LCUID","LCUStatus","LCUStartTime","LCULightLevel","LCUIsBroken","DCUTable_DCUID"}

extern struct _STL_DATABASE STL_DATABASE;
extern struct _STL_DCUTABLE STL_DCUTABLE;
extern struct _STL_LCUTABLE STL_LCUTABLE;


gboolean smartstreetlight_database_init();
void smartstreetlight_database_finalize();
#endif // SMARTSTREETLIGHT_DATABASE_H_INCLUDED
