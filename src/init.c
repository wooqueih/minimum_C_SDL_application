#include "init.h"

void initSDL(void) {
  int rendererFlags, windowFlags, surfaceFlags;

  rendererFlags = SDL_RENDERER_ACCELERATED;

  windowFlags = 0;

  // surfaceFlags = 0;

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
    printf("Couldn't initialize SDL: %s\n", SDL_GetError());
    exit(1);
  }

  window = SDL_CreateWindow("minimum_SDL", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, PHYSICAL_SCREEN_WIDTH,
                            PHYSICAL_SCREEN_HEIGHT, windowFlags);

  if (!window) {
    printf("Failed to open %d x %d window: %s\n", PHYSICAL_SCREEN_WIDTH,
           PHYSICAL_SCREEN_HEIGHT, SDL_GetError());
    exit(1);
  }

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

  renderer = SDL_CreateRenderer(window, -1, rendererFlags);

  if (!renderer) {
    printf("Failed to create renderer: %s\n", SDL_GetError());
    exit(1);
  }
  SDL_RenderSetLogicalSize(renderer, LOGICAL_SCREEN_WIDTH,
                           LOGICAL_SCREEN_HEIGHT);

  // surface = SDL_CreateRGBSurfaceWithFormat(surfaceFlags,
  // LOGICAL_SCREEN_WIDTH,
  //                                          LOGICAL_SCREEN_HEIGHT, 32,
  //                                          SDL_PIXELFORMAT_RGBA32);
}

void initGame(void) {
  mapWidth = 10;
  mapHeight = 10;
  mapSize = mapHeight * mapWidth;
  map = malloc(mapSize);
  for (int i = 0; i < mapWidth; i++) {
    for (int j = 0; j < mapHeight; j++) {
      unsigned char *ptr = map + (i * mapWidth) + j;
      if (j == 0 || i == 0 || j == mapWidth - 1 || i == mapHeight - 1) {
        *ptr = 1;
      } else {
        *ptr = 0;
      }
    }
  }
  playerX = 2;
  playerY = 7;
  playerAngle = 0;
}
