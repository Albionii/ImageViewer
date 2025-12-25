#include <stdio.h>
#include <gtk/gtk.h>

static void activate (GtkApplication *app, gpointer user_data)
{
  GtkWidget *window;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
  gtk_window_present (GTK_WINDOW (window));
}

struct Dimension {
    int width;
    int height;
};


int main(int argc, char **argv){
    GtkApplication *app;
    //if fail or success
    int status;
    struct Dimension dim = {400, 300};    
    
    
    app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (activate), &dim);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);
    return status;
}
