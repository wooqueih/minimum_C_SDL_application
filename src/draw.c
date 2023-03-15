#include "draw.h"

float castRay(float angle) {
  float horizontalRay_Distance;
  float verticalRay_Distance;

  float sinAngle = sin(angle);
  float cosAngle = cos(angle);
  float tanAngle = tan(angle);
  float cotAngle = 1 / tanAngle;

  float currentX = playerX;
  float nextX;
  float currentY = playerY;
  float nextY;

  float totalX = 0;
  float totalY = 0;

  signed char direction;

  if (angle < PI && angle > 0) {
    direction = 1;
  } else {
    direction = -1;
  }
  nextY = round(currentY - 0.5 * direction);
  nextX = currentX + cotAngle * (currentY - nextY);

  totalY += currentY - nextY;
  totalX += currentX - nextX;
  while (1) {
    if (nextY < 0.5 + 0.5 * direction || nextY > mapHeight - 1 || nextX < 0 ||
        nextX > mapWidth - 1 ||
        *(map + ((int)round(nextY - 0.5 - 0.5 * direction)) * mapWidth +
          (int)round(nextX)) == 1) {
      break;
    }
    nextY += -1 * direction;
    nextX += cotAngle;

    totalY += -1 * direction;
    totalX += cotAngle;
  }
  horizontalRay_Distance = sqrtf(totalX * totalX + totalY * totalY);

  currentX = playerX;
  currentY = playerY;
  totalX = 0;
  totalY = 0;
  if (angle < 1.5 * PI && angle > 0.5 * PI) {
    direction = 1;
  } else {
    direction = -1;
  }
  nextX = round(currentX - 0.5 * direction);
  nextY = currentY - tanAngle * (currentX - nextX);

  totalY += currentY - nextY;
  totalX += currentX - nextX;
  while (1) {
    if (nextY < 0 || nextY > mapHeight - 1 || nextX < 0.5 + 0.5 * direction ||
        nextX > mapWidth - 1 ||
        *(map + ((int)round(nextY)) * mapWidth +
          (int)round(nextX - 0.5 - 0.5 * direction)) == 1) {
      break;
    }
    nextX += -1 * direction;
    nextY += tanAngle;

    totalX += -1 * direction;
    totalY += tanAngle;
  }
  verticalRay_Distance = sqrtf(totalX * totalX + totalY * totalY);
  // printf("%f | %f\n", horizontalRay_Distance, verticalRay_Distance);
  return fmin(fabs(horizontalRay_Distance), fabs(verticalRay_Distance));
}

float fovInRad = (float)FOV * DEGREE_TO_RADIAN;

void prepare_scene(void) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}

void draw_scene(void) {
  printf("\n_____________________________________\n");
  for (int i = 0; i < LOGICAL_SCREEN_WIDTH; i++) {
    float distance = castRay(playerAngle - (fovInRad / 2) +
                             i * (fovInRad / LOGICAL_SCREEN_WIDTH));
    if (distance == 0) {
      distance = 0.1;
    }
    int height = 1 / distance * LOGICAL_SCREEN_HEIGHT;

    SDL_SetRenderDrawColor(renderer, 1 / distance * 255, 1 / distance * 255,
                           1 / distance * 255, 255);
    SDL_RenderDrawLine(renderer, i, LOGICAL_SCREEN_HEIGHT * 0.5 + height * 0.5,
                       i, LOGICAL_SCREEN_HEIGHT * 0.5 - height * 0.5);
  }
  printf("%f", castRay(playerAngle));
  SDL_RenderPresent(renderer);
}
