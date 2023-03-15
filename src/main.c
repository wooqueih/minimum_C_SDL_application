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
  unsigned long lastFrameTime = 0;
  unsigned long thisFrameTime = 1;
  while (1) {
    deltaTime = thisFrameTime - lastFrameTime;
    prepare_scene();

    pollInput();
    handleInput();
    draw_scene();
    SDL_Delay(100);
    lastFrameTime = thisFrameTime;
    thisFrameTime = SDL_GetTicks();
    printf("\n%f,%f | %f | %lu", playerX, playerY, playerAngle, deltaTime);
  }
  return 0;
}
