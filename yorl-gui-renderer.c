/*
 * Yorl GUI Renderer - Renders whiteboard class to GTK4 window
 */

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTENT 1024 * 1024

typedef struct {
    char* yorl_data;
    GtkWidget* drawing_area;
} AppData;

static void draw_function(GtkDrawingArea* area, cairo_t* cr, int width, int height, gpointer user_data) {
    AppData* data = (AppData*)user_data;
    
    // White background
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_paint(cr);
    
    // Draw orange rectangle (from whiteboard example)
    cairo_set_source_rgb(cr, 1.0, 0.4, 0.0); // #FF6600
    cairo_rectangle(cr, 100, 100, 200, 150);
    cairo_fill(cr);
    
    // Draw white text on rectangle
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 16);
    cairo_move_to(cr, 120, 180);
    cairo_show_text(cr, "Hello from Yorl GUI!");
    
    // Draw header text
    cairo_set_source_rgb(cr, 0.2, 0.2, 0.2); // #333333
    cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 24);
    cairo_move_to(cr, 20, 40);
    cairo_show_text(cr, "Yorl Whiteboard Application");
}

static void activate(GtkApplication* app, gpointer user_data) {
    AppData* data = (AppData*)user_data;
    
    GtkWidget* window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Yorl Whiteboard");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    
    GtkWidget* drawing_area = gtk_drawing_area_new();
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(drawing_area), draw_function, data, NULL);
    
    gtk_window_set_child(GTK_WINDOW(window), drawing_area);
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char* argv[]) {
    // Read Yorl data from stdin or embedded
    char* yorl_data = NULL;
    
    if (argc > 1 && strcmp(argv[1], "--embedded") == 0) {
        // Embedded mode - data passed as argument
        if (argc > 2) {
            yorl_data = strdup(argv[2]);
        }
    } else {
        // Read from stdin
        yorl_data = malloc(MAX_CONTENT);
        size_t len = fread(yorl_data, 1, MAX_CONTENT - 1, stdin);
        yorl_data[len] = '\0';
    }
    
    AppData data = { .yorl_data = yorl_data };
    
    GtkApplication* app = gtk_application_new("com.yorl.whiteboard", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), &data);
    
    int status = g_application_run(G_APPLICATION(app), 0, NULL);
    
    g_object_unref(app);
    if (yorl_data) free(yorl_data);
    
    return status;
}
