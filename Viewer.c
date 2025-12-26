#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>


struct Dimension {
    int width;
    int height;
};





int main(int argc, char **argv){
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    
    char *path = "/home/albionii/Desktop/357479338_6387107201378091_6123221653863258753_n.jpg";
    SDL_Surface * surface = IMG_Load(path);
    
    if (!surface) {
        printf("Loading image failed");
        return 1;
    }
    
    SDL_Window *window = SDL_CreateWindow(
        "My Image Viewer",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        surface->w,
        surface->h,
        0
    );
    
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_FreeSurface(surface);
    
    SDL_Event e;
    int running = 1;

    while (running) {
        //This loop is non-blocking and when an event happens it checks if I clicked "X" button.
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = 0;
        }
    
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
    }
    
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
