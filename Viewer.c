#include <SDL2/SDL_surface.h>
#include <cairo/cairo.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


struct Dimension {
    int width;
    int height;
};

static void activate (GtkApplication *app, gpointer user_data)
{
  GtkWidget *window;

  struct Dimension *dim = (struct Dimension*)user_data;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Bubii Viewer");
  gtk_window_set_default_size (GTK_WINDOW (window), dim->width, dim->height);
  gtk_window_present (GTK_WINDOW (window));
}

void draw_pixel(SDL_Surface *surface, int x, int y, unsigned char r, unsigned char g, unsigned char b) {
    int offset = y * surface->pitch + x * surface->format->BytesPerPixel;
    unsigned char *pixels = (unsigned char *)surface->pixels;
    pixels[offset + 0] = r;
    pixels[offset + 1] = g;
    pixels[offset + 2] = b;
}

void convert_image_to_pixels(const char *path){
    SDL_Surface *surface = IMG_Load(path);
    if (!surface) {
        printf("IMG_Load error: %s\n", IMG_GetError());
        return;
    }
    
    printf("Loaded image %dx%d\n", surface->w, surface->h);
    SDL_LockSurface(surface);

    int width = surface -> w;
    int height = surface->h;
    int pitch = surface->pitch;
    int bytes_per_pixel = surface->format->BytesPerPixel;
    unsigned char *pixels = (unsigned char *)surface->pixels;
    
    for (int i = 0; i < surface->h; i++) {
        for (int j = 0; j < surface -> w; j++) {
            int offset = i*pitch + j*bytes_per_pixel;
            unsigned char r = pixels[offset + 0];
            unsigned char g = pixels[offset + 1];
            unsigned char b = pixels[offset + 2];    
            // printf("offset : %d", r);
        }
    }
}






int main(int argc, char **argv){
    GtkApplication *app;
    //if fail or success
    int status;
    struct Dimension dim = {1000, 1000};


    app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (activate), &dim);
    
    char *path = "/home/albionii/Desktop/357479338_6387107201378091_6123221653863258753_n.jpg";
    convert_image_to_pixels(path);

    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}
