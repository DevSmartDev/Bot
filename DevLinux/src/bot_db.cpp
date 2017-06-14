#include "bot_db.h"
#include "bot_login.h"


static MYSQL *sql = NULL;
static final gchar* INIT_FAIL = "sql_init failure ...";
static final gchar* CONN_FAIL = "sql_connect failure ...";

gint database_connect()
{
    if(sql != NULL)
        return -1;
    sql = mysql_init(0L);
    if(sql == NULL)
        return -2;
    mysql_real_connect (sql, server_name, user_name,
           user_pwd, db_name, db_port, 0L, 0);
    if(sql == NULL)
        return -3;
    return 0;
}

void *database_close()
{
    if(sql)
        mysql_close(sql);
}

