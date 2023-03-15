#include "draw.h"
#include <math.h>

float castRay(float angle) {
  if (angle < 0) {
    angle = 2 * PI - angle;
  } else if (angle > 2 * PI) {
    angle = angle - 2 * PI;
  }
  float horizontalRay_Distance;
  float verticalRay_Distance;

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
  nextY = round(currentY);
  nextX = currentX + cotAngle * (currentY - nextY);

  totalY += currentY - nextY;
  totalX += currentX - nextX;
  while (1) {
    if (nextY >= 0 && nextY <= mapHeight - 1 && nextX >= 0 &&
        nextX <= mapWidth - 1) {
      if (map[(int)(round(nextY) * mapWidth + round(nextX))]) {
        break;
      }
    } else if (sqrtf(totalX * totalX + totalY * totalY) > (float)DOF ||
               isnan(totalX) || isnan(totalY)) {
      totalX = DOF;
      totalY = 0;
      break;
    }
    nextY += -1 * direction;
    nextX += cotAngle;

    totalY += -1 * direction;
    totalX += cotAngle;
    // printf("loop1 | %f,%f : %f\n", tanAngle, cotAngle,
    //        sqrtf(totalX * totalX + totalY * totalY));
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
  nextX = round(currentX);
  nextY = currentY - tanAngle * (currentX - nextX);

  totalY += currentY - nextY;
  totalX += currentX - nextX;
  while (1) {
    if (nextY >= 0 && nextY <= mapHeight - 1 && nextX >= 0 &&
        nextX <= mapWidth - 1) {
      if (map[(int)(round(nextY) * mapWidth + round(nextX))]) {
        // printf("| %d,%d |", (int)round(nextY), (int)round(nextX));
        break;
      }
    } else if (sqrtf(totalX * totalX + totalY * totalY) > (float)DOF ||
               isnan(totalX) || isnan(totalY)) {
      totalY = 8;
      totalX = 0;
      break;
    }
    nextX += -1 * direction;
    nextY += tanAngle;

    totalX += -1 * direction;
    totalY += tanAngle;
    // printf("loop2 | %f,%f : %f\n", totalX, totalY,
    //        sqrtf(totalX * totalX + totalY * totalY));
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
    float deltaAngle = (fovInRad / 2) - i * (fovInRad / LOGICAL_SCREEN_WIDTH);
    float rayAngle = playerAngle + deltaAngle;
    float distance = castRay(rayAngle);
    if (distance == 0) {
      distance = 0.0001;
    }
    int height = (1 / (distance * cos(deltaAngle))) * LOGICAL_SCREEN_HEIGHT;

    SDL_SetRenderDrawColor(renderer, 1 / distance * 255, 1 / distance * 255,
                           1 / distance * 255, 255);
    SDL_RenderDrawLine(renderer, i, LOGICAL_SCREEN_HEIGHT * 0.5 + height * 0.1,
                       i, LOGICAL_SCREEN_HEIGHT * 0.5 - height * 0.1);
  }
  printf("%f", castRay(playerAngle));
  SDL_RenderPresent(renderer);
}
