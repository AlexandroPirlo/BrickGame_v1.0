
#include "../../brick_game/tetris/backend.h"

#define frogger_y 1
#define frogger_x 7

#define window_y 24
#define window_x 41

#define field_y 22
#define field_x 24

#define y 20
#define x 10

void initGui();

void printFrogger();

void printGame(GameInfo_t *game);

void printRectangle(int top_y, int bottom_y, int left_x, int right_x);

void printInfo(GameInfo_t game);

int print_next(int **next);

int print_field(int **field);

void print_current(GameInfo_t game);
