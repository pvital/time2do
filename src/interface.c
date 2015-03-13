
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

#define GLADE_HOOKUP_OBJECT(component,widget,name) \
  g_object_set_data_full (G_OBJECT (component), name, \
    gtk_widget_ref (widget), (GDestroyNotify) gtk_widget_unref)

#define GLADE_HOOKUP_OBJECT_NO_REF(component,widget,name) \
  g_object_set_data (G_OBJECT (component), name, widget)

GtkWidget*
create_main_window (char *str2print)
{
  GtkWidget *main_window;
  GtkWidget *fixed1;
  GtkWidget *main_label;
  GtkWidget *ok_button;
  GtkWidget *image;
  GtkTooltips *tooltips;
  int pos1 = 300, pos2 = 100;
  int label_size = 0, str_is_big = 0, has_mail = 0;

  tooltips = gtk_tooltips_new ();

  if (strlen(str2print) > 23)
      str_is_big = 1;
  if (!strncmp (str2print, "mail", 4)) {
      //has_mail = 1;
      str2print = "You have mail !!!";
  }

  /* creating the window */
  main_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  if (str_is_big)
      pos1 = pos1+100;
  if (has_mail)
      pos2 = pos2+70;
  gtk_window_set_default_size (GTK_WINDOW (main_window), pos1, pos2);
  gtk_window_set_title (GTK_WINDOW (main_window), _("time2do"));
  gtk_window_set_position (GTK_WINDOW (main_window), GTK_WIN_POS_CENTER);
  gtk_window_set_resizable (GTK_WINDOW (main_window), TRUE);

  /* creating and adding the fixed */
  fixed1 = gtk_fixed_new ();
  gtk_widget_show (fixed1);
  gtk_container_add (GTK_CONTAINER (main_window), fixed1);

  /* mail string */
  if (has_mail) {
      // add the pixmap/mail.png icon 
      image = gtk_image_new_from_file ("/home/pvital/my_files/projects/Projects/time2do//pixmap/mail.png");
      if (image) {
        gtk_widget_show (image);
        pos1 = (pos1/2)-32;
        gtk_fixed_put (GTK_FIXED (fixed1), image, pos1, 8);
        gtk_widget_set_size_request (image, 64, 64);
      }
  }    
  
  /* adding the label */
  main_label = gtk_label_new (NULL);
  gtk_label_set_width_chars (GTK_LABEL (main_label), strlen(str2print));
  gtk_label_set_text (GTK_LABEL (main_label), str2print);
  gtk_widget_show (main_label);

  if (str_is_big) {
      /* used when the label is large than 23 characters */
      pos1 = 5;
      label_size = 380;
  } else {
      /* used when the label is small */
      pos1 = 56;
      label_size = 184;
  }

  if (has_mail)
      pos2 = 8+70;
  else
      pos2 = 8;

  gtk_fixed_put (GTK_FIXED (fixed1), main_label, pos1, pos2);
  gtk_widget_set_size_request (main_label, label_size, 24);
  gtk_label_set_justify (GTK_LABEL (main_label), GTK_JUSTIFY_CENTER);
  gtk_label_set_line_wrap (GTK_LABEL (main_label), TRUE);
  gtk_label_set_ellipsize (GTK_LABEL (main_label), PANGO_ELLIPSIZE_MIDDLE);

  /* adding the OK button */
  pos1 = 120;
  ok_button = gtk_button_new_from_stock ("gtk-ok");
  gtk_widget_show (ok_button);
  if (str_is_big)
      pos1 = pos1+55;
  if (has_mail)
      pos2 = 48+70;
  else
      pos2 = 48;
  gtk_fixed_put (GTK_FIXED (fixed1), ok_button, pos1, pos2);
  gtk_widget_set_size_request (ok_button, 62, 29);
  gtk_tooltips_set_tip (tooltips, ok_button, _("Click here to close this window."), NULL);

  g_signal_connect ((gpointer) ok_button, "clicked",
                    G_CALLBACK (gtk_main_quit),
                    NULL);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (main_window, main_window, "main_window");
  GLADE_HOOKUP_OBJECT (main_window, fixed1, "fixed1");
  if (has_mail)
      GLADE_HOOKUP_OBJECT (main_window, image, "image");
  GLADE_HOOKUP_OBJECT (main_window, main_label, "main_label");
  GLADE_HOOKUP_OBJECT (main_window, ok_button, "ok_button");
  GLADE_HOOKUP_OBJECT_NO_REF (main_window, tooltips, "tooltips");

  return main_window;
}
