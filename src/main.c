#include "main.h"

SDL_Renderer *renderer;
SDL_Window *window;
// SDL_Surface *surface;

int mapWidth, mapHeight, mapSize;
unsigned char *map;

float playerX, playerY, playerAngle;

unsigned char key_W_isDown = 0;
unsigned char key_A_isDown = 0;
unsigned char key_S_isDown = 0;
unsigned char key_D_isDown = 0;

unsigned long deltaTime;

int main(int argc, char *argv[]) {
  initSDL();
  initGame();
  // debug_InitTopDownView();
  unsigned long lastFrameTime = 0;
  unsigned long thisFrameTime = 1;
  map[2 * mapWidth + 3] = 1;
  while (1) {
    deltaTime = thisFrameTime - lastFrameTime;
    prepare_scene();

    pollInput();
    handleInput();
    draw_scene();
    lastFrameTime = thisFrameTime;
    thisFrameTime = SDL_GetTicks();
    printf("\n%f,%f | %f | %lu\n", playerX, playerY, playerAngle, deltaTime);
    // debug_DrawTopDownView();
    for (int i = 0; i < mapWidth; i++) {
      for (int j = 0; j < mapHeight; j++) {
        if ((int)round(playerX) == i && (int)round(playerY) == j) {
          printf("#");
          continue;
        }
        printf("%d", map[i * mapWidth + j]);
      }
      printf("\n");
    }
  }
  return 0;
}
