#include "draw.h"

void prepare_scene(void) {
  SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
  SDL_RenderClear(renderer);
}

void draw_scene(void) { SDL_RenderPresent(renderer); }
