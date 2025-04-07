#ifndef BACKEND_H
#define BACKEND_H

#define WIDTH 10
#define HEIGHT 20

#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int **current;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
  int orientation_figure;
  int new_orientation_figure;
  int type_figure;
  int type_current;
  int coord_x;
  int coord_y;
  int tick;
  int game_over;
  int game_start;
} GameInfo_t;

void userInput(UserAction_t action, bool hold);

UserAction_t getAction();

void summ();

GameInfo_t *getGame();

void field_init();

void next_init();

void current_init();
void drop_next();
void drop_current();

void drop_figure();

void rotateFigure();

int load_high_score();

void save_high_score(int high_score);

void free_memory(GameInfo_t *game);

void pauseGame();

void terminateIfError(char *msg);
void quitNcurses();

void mvDown();
void mvLeft();
void mvRight();

void collision();

void check_and_remove_lines();
bool is_line_full(int row);
void remove_line(int row);

void update_level();
void hard_drop();
void terminateButtonPushed();
void collision_left();
void collision_Right();

void game_start();

#endif