#include "debug.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

SDL_Window *debugWindow;
SDL_Renderer *debugRenderer;

void debug_InitTopDownView(void) {
  SDL_Window *debugWindow =
      SDL_CreateWindow("debugView", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, 1000, 1000, 0);
  SDL_Renderer *debugRenderer = SDL_CreateRenderer(debugWindow, -1, 0);
  SDL_RenderSetLogicalSize(debugRenderer, 1000, 1000);
}
void debug_DrawTopDownView(void) {
  SDL_SetRenderDrawColor(debugRenderer, 0, 0, 0, 255);
  SDL_RenderClear(debugRenderer);
  for (int i = 0; i < mapWidth - 1; i++) {
    for (int j = 0; j < mapHeight - 1; j++) {
      if (map[i * mapWidth + j]) {
        SDL_SetRenderDrawColor(debugRenderer, 255, 255, 255, 255);
      } else {
        SDL_SetRenderDrawColor(debugRenderer, 0, 0, 0, 255);
      }
      SDL_Rect rect;
      rect.x = i;
      rect.y = j;
      rect.w = 100;
      rect.h = 100;
      SDL_Rect *rect_ptr = &rect;
      SDL_RenderFillRect(debugRenderer, rect_ptr);
    }
  }
  SDL_RenderPresent(debugRenderer);
}
