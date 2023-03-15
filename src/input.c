#include "input.h"

void pollInput(void) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
      case SDLK_a:
        key_A_isDown = 1;
        break;
      case SDLK_w:
        key_W_isDown = 1;
        break;
      case SDLK_s:
        key_S_isDown = 1;
        break;
      case SDLK_d:
        key_D_isDown = 1;
        break;
      }
      break;
    case SDL_KEYUP:
      switch (event.key.keysym.sym) {
      case SDLK_a:
        key_A_isDown = 0;
        break;
      case SDLK_w:
        key_W_isDown = 0;
        break;
      case SDLK_s:
        key_S_isDown = 0;
        break;
      case SDLK_d:
        key_D_isDown = 0;
        break;
      }
      break;
    case SDL_QUIT:
      SDL_DestroyWindow(window);
      SDL_DestroyRenderer(renderer);
      SDL_Quit();
      exit(0);
      break;
    default:
      break;
    }
  }
}

void handleInput(void) {
  if (key_W_isDown) {
    // if (castRay(playerAngle) < 0.5) {
    //   return;
    // }
    playerX += cos(playerAngle) * SPEED * deltaTime;
    playerY -= sin(playerAngle) * SPEED * deltaTime;
  }
  if (key_S_isDown) {
    // if (castRay(fmod(playerAngle + PI, PI * 2)) < 0.5) {
    //   return;
    // }
    playerX -= cos(playerAngle) * SPEED * deltaTime;
    playerY += sin(playerAngle) * SPEED * deltaTime;
  }
  if (key_A_isDown) {
    playerAngle += LOOK_SENSITIVITY * deltaTime;
    if (playerAngle < 0) {
      playerAngle = 2 * PI - playerAngle;
    } else if (playerAngle > 2 * PI) {
      playerAngle = playerAngle - 2 * PI;
    }
  }
  if (key_D_isDown) {
    playerAngle -= LOOK_SENSITIVITY * deltaTime;
    if (playerAngle < 0) {
      playerAngle = 2 * PI - playerAngle;
    } else if (playerAngle > 2 * PI) {
      playerAngle = playerAngle - 2 * PI;
    }
  }
}
