#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

void on_ok_button_clicked (GtkButton *button, gpointer user_data)
{
    gtk_main_quit();
}
