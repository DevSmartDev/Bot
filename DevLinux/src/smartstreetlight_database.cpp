#include "smartstreetlight_database.h"

struct _STL_DATABASE STL_DATABASE = _STL_DATABASE_INITIALIZER;
struct _STL_DCUTABLE STL_DCUTABLE = _STL_DCUTABLE_INITIALIZER;
struct _STL_LCUTABLE STL_LCUTABLE = _STL_LCUTABLE_INITIALIZER;

gboolean smartstreetlight_database_init()
{
    return TRUE;
}


void smartstreetlight_database_finalize()
{
    return;
}

