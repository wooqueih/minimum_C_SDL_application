#include "main.h"
#include <SDL2/SDL_render.h>

SDL_Renderer *renderer;
SDL_Window *window;
// SDL_Surface *surface;

int main(int argc, char *argv[]) {
  initSDL();
  while (1) {
    SDL_RenderClear(renderer);
    handle_input();
    SDL_RenderPresent(renderer);

    SDL_Delay(16);
  }
  return 0;
}
