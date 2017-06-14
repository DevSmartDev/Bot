#ifdef HAVE_CONFIG_H
# include <config.h>
#endif
#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>
#include <mysql.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"
GtkWidget *create_ddc (gchar *table_name, gchar *server_name,
            gchar *user_name, gchar *user_pwd,
            gchar *db_name, GtkWidget *frm_target)
{
 MYSQL   *conx;
 GtkWidget *scrolledwindow1;
 GtkWidget *clist_table;
 GtkWidget *label;
 gint   counter;
 gint   cols = 3;
 gchar   *sql;
 MYSQL_RES *result_set;
 MYSQL_ROW db_row;
 MYSQL_FIELD *field;
 gchar   *row[20] = {"", "", "",
"", "",
            "", "", "", "",
"",
            "", "", "", "",
"",
            "", "", "", "",
""};
 scrolledwindow1 = gtk_scrolled_window_new (NULL, NULL);
 gtk_widget_show (scrolledwindow1);
 conx = mysql_init(0L);
 if (conx == 0L)
  {
    g_print("mysql_init failure...\n");
    return 0L;
  }
 mysql_real_connect (conx, server_name, user_name,
           user_pwd, db_name, 0, 0L, 0);
 if (conx == 0L)
  {
    g_print("mysql_real_connect failure...\n");
    return 0L;
  }
 sql = g_strconcat("select * from ", table_name, 0L);
 g_print("sql is: %s\n", sql);
 if (mysql_query (conx, sql) != 0)
  {
   g_print("query failure...\n");
   return 0L;
  }

 result_set = mysql_store_result (conx);
 cols = mysql_num_fields (result_set);
 clist_table = gtk_clist_new (cols);
 gtk_object_set_data_full(GTK_OBJECT(frm_target),
"clist_table",
       clist_table, 0L);
 gtk_widget_show (clist_table);
 gtk_container_add (GTK_CONTAINER (scrolledwindow1),
clist_table);
 gtk_clist_column_titles_show (GTK_CLIST (clist_table));
 /* First iterate through the columns. */
 for (counter = 0; counter < cols; counter++)
  {
    mysql_field_seek(result_set, counter);
    field = mysql_fetch_field(result_set);
    label = gtk_label_new (field->name);
    gtk_widget_show (label);
    gtk_clist_set_column_widget (GTK_CLIST (clist_table), counter,
label);
    gtk_clist_set_column_width (GTK_CLIST (clist_table), counter,
80);
  }
 /* Next iterate through the rows. */
 while ((db_row = mysql_fetch_row (result_set)) != 0L)
   {
    for (counter = 0; counter < cols; counter++)
     {
       row[counter] = db_row[counter];
     }
    gtk_clist_append(GTK_CLIST(clist_table), row);
   }
 mysql_close(conx);
 return scrolledwindow1;
}
