#include <SDL2/SDL.h>

#define LOGICAL_SCREEN_HEIGHT 1080
#define LOGICAL_SCREEN_WIDTH 1920
#define PHYSICAL_SCREEN_HEIGHT 1080
#define PHYSICAL_SCREEN_WIDTH 1920

#define FOV 90
#define DOF 11
#define PI 3.14159265359
#define DEGREE_TO_RADIAN 0.0174533

#define SPEED 0.002
#define LOOK_SENSITIVITY 0.001

extern SDL_Renderer *renderer;
extern SDL_Window *window;
// extern SDL_Surface *surface;

extern int mapSize;
extern int mapWidth;
extern int mapHeight;
extern unsigned char *map;

extern float playerX;
extern float playerY;
extern float playerAngle;

extern unsigned char key_W_isDown;
extern unsigned char key_A_isDown;
extern unsigned char key_S_isDown;
extern unsigned char key_D_isDown;

extern unsigned long deltaTime;
