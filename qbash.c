#include <gtk/gtk.h>
#include <stdlib.h>
#include <unistd.h>

GtkWidget *window;

void submit(GtkEntry *entry, gpointer user_data)
{
    const char *text = gtk_entry_get_text(entry);
    gtk_widget_hide(window);
    execl("/bin/sh", "sh", "-c", text, (char *) NULL);
    exit(0);
}

static void activate(GtkApplication* app, gpointer user_data)
{
    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Srun");
    gtk_window_set_default_size (GTK_WINDOW (window), 400, 25);
    gtk_window_set_decorated (GTK_WINDOW (window), FALSE);
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);

    GtkWidget *input = gtk_entry_new();
    gtk_container_add (GTK_CONTAINER (window), input);
    g_signal_connect (input, "activate", G_CALLBACK (submit), NULL);

    gtk_widget_show_all(window);
}

int main(int argc, char **argv) 
{
    GtkApplication *app;
    int status;

    app = gtk_application_new("com.wasykes.qbash", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}