#include "cli.h"

void initGui() {
  initscr();
  curs_set(0);
  start_color();
  init_pair(1, COLOR_BLUE, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);
  init_pair(4, COLOR_GREEN, COLOR_BLACK);

  cbreak();
  noecho();
  // clrtoeol();
  nodelay(stdscr, TRUE);
  scrollok(stdscr, TRUE);
  keypad(stdscr, TRUE);
}

void printGame(GameInfo_t *game) {
  printFrogger();

  print_field(game->field);

  print_next(game->next);

  print_current(*game);

  printInfo(*game);

  refresh();
}

void printFrogger() {
  printRectangle(frogger_y, window_y, frogger_x + 1,
                 window_x + 9);  //основное окно
  printRectangle(frogger_y + 1, frogger_y + field_y, frogger_x + 3,
                 frogger_x + field_x);  //игровое полу
  printRectangle(frogger_y + 1, frogger_y + field_y, frogger_x + field_x + 2,
                 frogger_x + field_x + 17);

  printRectangle(3, 5, frogger_x + field_x + 4, window_x + 5);
  printRectangle(7, 9, frogger_x + field_x + 4, window_x + 5);
  printRectangle(11, 17, frogger_x + field_x + 4, window_x + 5);
  printRectangle(19, 21, frogger_x + field_x + 4, window_x + 5);

  attron(A_BOLD);
  mvprintw(3, frogger_x + field_y + 10, "LEVEL");
  mvprintw(7, frogger_x + field_y + 10, "SCORE");
  mvprintw(11, frogger_x + field_y + 10, "NEXT");
  mvprintw(19, frogger_x + field_y + 9, "RECORD");
  mvprintw(22, frogger_x + field_y + 8, "laciecon");
  attroff(A_BOLD);
}

void printRectangle(int top_y, int bottom_y, int left_x, int right_x) {
  mvaddch(top_y, left_x, ACS_ULCORNER);

  int i = left_x + 1;

  for (; i < right_x; i++) mvaddch(top_y, i, ACS_HLINE);
  mvaddch(top_y, i, ACS_URCORNER);

  for (int i = top_y + 1; i < bottom_y; i++) {
    mvaddch(i, left_x, ACS_VLINE);
    mvaddch(i, right_x, ACS_VLINE);
  }

  mvaddch(bottom_y, left_x, ACS_LLCORNER);
  i = left_x + 1;
  for (; i < right_x; i++) mvaddch(bottom_y, i, ACS_HLINE);
  mvaddch(bottom_y, i, ACS_LRCORNER);
}

void printInfo(GameInfo_t game) {
  attron(COLOR_PAIR(3));
  mvwprintw(stdscr, 1, window_x / 2 + 8, "TETRIS");
  attroff(COLOR_PAIR(3));
  attron(COLOR_PAIR(4));
  mvwprintw(stdscr, 4, 41, "%d", game.level);
  mvwprintw(stdscr, 8, 41, "%d", game.score);
  print_next(game.next);
  print_field(game.field);
  mvwprintw(stdscr, 20, 39, "%d", game.high_score);
  attroff(COLOR_PAIR(4));
  attron(COLOR_PAIR(2));
  if (game.pause) {
    mvwprintw(stdscr, 4 + rand() % 18, 14, "GAME IS PAUSED");
    napms(200);
  }
  if (!game.game_start) {
    mvwprintw(stdscr, 11, 14, "PRESS \"ENTER\"");
    mvwprintw(stdscr, 12, 12, "TO START THE GAME");
    mvwprintw(stdscr, 13, 18, "OR");
    mvwprintw(stdscr, 14, 15, "PRESS \"ESC\"");
    mvwprintw(stdscr, 15, 12, "TO EXIT THE GAME");
  }
  attroff(COLOR_PAIR(2));
  //  if (!game.pause) mvwprintw(stdscr, 12, frogger_x+4, "Press ENTER to
  //  play.");

  //   attron(COLOR_PAIR(5));
  mvwprintw(stdscr, 25, 8, "Press:");
  mvwprintw(stdscr, 25, 14, "Start: 'Enter'");
  mvwprintw(stdscr, 26, 14, "Pause: 'p'");
  mvwprintw(stdscr, 27, 14, "Exit: 'q'");
  mvwprintw(stdscr, 28, 14, "Arrows to move: '<' '>'");
  mvwprintw(stdscr, 29, 14, "Space to rotate: '___'");
  mvwprintw(stdscr, 30, 14, "Arrow down to plant: 'v'");

  // mvwprintw(stdscr, 27, 40, "figure = %d", game.type_figure);
  // mvwprintw(stdscr, 28, 40, "side = %d", game.orientation_figure);
  // mvwprintw(stdscr, 29, 40, "x = %d", game.coord_x);
  // mvwprintw(stdscr, 30, 40, "y = %d", game.coord_y);
  //  attroff(COLOR_PAIR(5));
}

int print_next(int **next) {
  if (next) {
    for (int i = -1; i < 3; i++) {
      for (int j = -1; j < 3; j++) {
        if (next[i + 1][j + 1]) {
          mvwprintw(stdscr, 14 + i, 38 + 2 * j, "[]");
        }
      }
    }
  }
  return 0;
}

int print_field(int **field) {
  if (field) {
    for (int i = 0; i < 20; i++) {
      for (int j = 0; j < 10; j++) {
        // mvwprintw(stdscr, 3 + i, 60 + 2*j, "%d", field[i][j]); // field
        // matrix //
        if (field[i][j]) mvwprintw(stdscr, 3 + i, 11 + 2 * j, "[]");
      }
    }
  }
  return 0;
}

void print_current(GameInfo_t game) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (game.current[i][j])
        mvwprintw(stdscr, game.coord_y + 3 + i, game.coord_x * 2 + 2 * j - 1,
                  "[]");
      // else mvwprintw(stdscr, game.coord_y + 3 + i, game.coord_x*2 + 2*j - 1,
      // "||");
    }
  }
  // mvwprintw(stdscr, game.coord_y + 3, game.coord_x*2 - 1, "**");
}
