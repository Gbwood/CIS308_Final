//main class for project
//main.c

//GO

#include <gtk/gtk.h>
#include "types.h"

static void print_hello (GtkWidget *widget, gpointer data)
{
  g_print ("Hello World\n");
}

static void activate (GtkApplication *app, gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *button1;
  GtkWidget *button2;
  GtkWidget *button_box;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

  button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add (GTK_CONTAINER (window), button_box);

  button1 = gtk_toggle_button_new();
  g_signal_connect (button1, "clicked", G_CALLBACK (gtk_toggle_button_set_active), button1);
  button2 = gtk_toggle_button_new();
  g_signal_connect (button2, "clicked", G_CALLBACK (gtk_toggle_button_set_active), button2);

  gtk_container_add (GTK_CONTAINER (button_box), button1);
  gtk_container_add (GTK_CONTAINER (button_box), button2);
  gtk_widget_show_all (window);
}

int main (int argc, char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
