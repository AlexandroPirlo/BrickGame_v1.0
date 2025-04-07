
#include "backend.h"

static int Figures[7][4][4][4] = {
    {{{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}},
     {{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}},
     {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}},
     {{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}}},

    {{{0, 1, 0, 0}, {0, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 1, 1, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
     {{0, 1, 1, 1}, {0, 0, 0, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}},

    {{{0, 0, 0, 1}, {0, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 0}},
     {{0, 1, 1, 1}, {0, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}}},

    {{{0, 0, 1, 1}, {0, 0, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 0, 1, 1}, {0, 0, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 0, 1, 1}, {0, 0, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 0, 1, 1}, {0, 0, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}}},

    {{{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}},
     {{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}}},

    {{{0, 1, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
     {{0, 1, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}},

    {{{0, 0, 1, 0}, {0, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 0, 1, 0}, {0, 0, 1, 1}, {0, 0, 1, 0}, {0, 0, 0, 0}},
     {{0, 1, 1, 1}, {0, 0, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 0, 1, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}}}};

GameInfo_t *getGame() {
  static GameInfo_t *game = NULL;
  if (game == NULL) {
    game = malloc(sizeof(GameInfo_t));
    if (game != NULL) {
      field_init();
      next_init();
      current_init();
      drop_next();
      drop_current();
      game->score = 0;
      game->high_score = load_high_score();
      game->level = 1;
      game->speed = 50;
      game->pause = 0;
      game->game_over = 0;
      game->game_start = 0;

    } else {
      free_memory(game);
      terminateIfError("Memory allocation error");
    }
  }
  return game;
}

void field_init() {
  GameInfo_t *game = getGame();
  if (game != NULL) {  // Handle the case where getGame failed
    game->field = malloc(22 * sizeof(int *) + 22 * 10 * sizeof(int));
    if (game->field != NULL) {
      int *ptr = (int *)((int **)game->field + 22);
      for (int i = 0; i < 22; i++) game->field[i] = ptr + 10 * i;
    }
  }
}

void next_init() {
  GameInfo_t *game = getGame();
  if (game != NULL) {
    game->next = malloc(4 * 4 * sizeof(int) + 4 * sizeof(int *));
    if (game->next != NULL) {
      int *ptr = (int *)(game->next + 4);
      for (int i = 0; i < 4; i++) game->next[i] = ptr + 4 * i;
    }
  }
}

void current_init() {
  GameInfo_t *game = getGame();
  if (game != NULL) {
    game->current = malloc(4 * 4 * sizeof(int) + 4 * sizeof(int *));
    if (game->current != NULL) {
      int *ptr = (int *)(game->current + 4);
      for (int i = 0; i < 4; i++) game->current[i] = ptr + 4 * i;
    }
  }
}

void drop_next() {
  GameInfo_t *game = getGame();

  game->new_orientation_figure = game->orientation_figure;
  game->type_current = game->type_figure;

  game->type_figure = rand() % 7;
  game->orientation_figure = rand() % 4;

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      game->next[i][j] =
          Figures[game->type_figure][game->orientation_figure][i][j];
}

void drop_current() {
  GameInfo_t *game = getGame();
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      game->current[i][j] = game->next[i][j];
    }
  drop_next();
}

int load_high_score() {
  FILE *file;
  int high_score = 0;
  file = fopen("max_score.txt", "r");
  if (!file)
    file = fopen("max_score.txt", "w");
  else {
    fscanf(file, "%d", &high_score);
    fclose(file);
  }
  return high_score;
}

void save_high_score(int high_score) {
  FILE *file = fopen("max_score.txt", "w");
  if (file != NULL) {
    fprintf(file, "%d", high_score);
    fclose(file);
  }
}

void drop_figure() {
  GameInfo_t *game = getGame();
  if (game->coord_y > 0 && game->game_over == 0) {
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++) {
        if (game->current[i][j])
          game->field[game->coord_y + i - 1][game->coord_x + j - 6] =
              game->current[i][j];
      }
    game->coord_x = 10;
    game->coord_y = 0;
  } else
    game->game_over = 1;
}

void free_memory(GameInfo_t *game) {
  free(game->field);
  free(game->next);
  free(game->current);
  free(game);
}

void game_start() {
  GameInfo_t *game = getGame();
  game->game_start = 1;
}

void userInput(UserAction_t action, bool hold) {
  if (!hold) switch (action) {
      case Start:
        break;
      case Pause:
        pauseGame();
        break;
      case Action:
        rotateFigure();
        collision();
        break;
      case Down:
        hard_drop();
        break;
      case Left:
        mvLeft();
        collision_left();
        break;
      case Right:
        mvRight();
        collision_Right();
        break;
      case Terminate:
        terminateButtonPushed();
        break;
      case Up:
        break;
    }
}
void rotateFigure() {
  GameInfo_t *game = getGame();
  if (game->pause == 0) {
    int rotate = 0;
    game->new_orientation_figure = (game->new_orientation_figure + 1) % 4;
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
        if (game->field[game->coord_y + i][game->coord_x - 6 + j] &&
            Figures[game->type_current][game->new_orientation_figure][i][j]) {
          rotate = 1;
          break;
        }
    if (!rotate)
      for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
          game->current[i][j] =
              Figures[game->type_current][game->new_orientation_figure][i][j];
        }
  }
}

UserAction_t getAction() {
  switch (getch()) {
    case KEY_LEFT:
      return Left;
    case KEY_RIGHT:
      return Right;
    case KEY_UP:
      return Up;
    case KEY_DOWN:
      return Down;
    case '\n':
      return Start;
    case 'p':
    case 'P':
      return Pause;
    case 'q':
    case 'Q':
      return Terminate;
    case ' ':
      return Action;
    default:
      return Up;
  }
}

void terminateButtonPushed() {
  GameInfo_t *game = getGame();
  game->game_over = 1;
}

void pauseGame() {
  GameInfo_t *game = getGame();
  if (game->pause == 1) {
    game->pause = 0;
  } else {
    game->pause = 1;
  }
}

void collision() {
  GameInfo_t *game = getGame();
  for (int j = 0; j < 4; j++)
    for (int i = 0; i < 4; i++) {
      if (game->current[i][j] && game->coord_x < 6 - j) {
        mvRight();
        break;
      }
      if (game->current[i][3 - j] && game->coord_x > 12 + j) {
        mvLeft();
        break;
      }
      if ((game->current[3 - j][i] && game->coord_y > 16 + j) ||
          (game->current[3 - j][i] &&
           game->field[game->coord_y + 3 - j][game->coord_x - 6 + i])) {
        drop_figure();
        drop_current();
        game->coord_x = 10;
        game->coord_y = 0;
      }
    }
}

void collision_left() {
  GameInfo_t *game = getGame();
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      if (game->current[i][j] &&
          game->field[game->coord_y + i][game->coord_x - 6 + j]) {
        mvRight();
        break;
      }
    }
}

void collision_Right() {
  GameInfo_t *game = getGame();
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      if (game->current[i][j] &&
          game->field[game->coord_y + i][game->coord_x - 6 + j]) {
        mvLeft();
        break;
      }
    }
}

void check_and_remove_lines() {
  GameInfo_t *game = getGame();
  int lines_removed = 0;
  for (int i = 0; i < 20; i++) {
    if (is_line_full(i)) {
      remove_line(i);
      lines_removed++;
      i--;  // Декремент, чтобы перепроверить текущую строку.  Важно!
    }
  }
  if (lines_removed == 1) {
    game->score += 100;
  } else if (lines_removed == 2) {
    game->score += 300;
  } else if (lines_removed == 3) {
    game->score += 700;
  } else if (lines_removed == 4) {
    game->score += 1500;
  }

  if (game->score > game->high_score) {
    save_high_score(game->score);
    game->high_score = game->score;
  }
  update_level();
}

void update_level() {
  GameInfo_t *game = getGame();
  if (game->score / 600) game->level = game->score / 600 + 1;
  if (game->level > 10) game->level = 10;
}

bool is_line_full(int row) {
  GameInfo_t *game = getGame();
  for (int j = 0; j < 10; j++) {
    if (game->field[row][j] == 0) {
      return false;  // Найдена пустая клетка, строка не полная.
    }
  }
  return true;  // Все клетки заняты, строка полная.
}

void remove_line(int row) {
  // Сдвигаем все строки, находящиеся выше удаляемой, на одну позицию вниз.
  GameInfo_t *game = getGame();
  for (int i = row; i > 0; i--) {
    for (int j = 0; j < 10; j++) {
      game->field[i][j] = game->field[i - 1][j];
    }
  }
  // Очищаем самую верхнюю строку (делаем ее пустой)
  for (int j = 0; j < 10; j++) {
    game->field[0][j] = 0;
  }
}

void mvDown() {
  GameInfo_t *game = getGame();
  if (game->pause == 0 && game->game_over == 0) game->coord_y++;
}

void hard_drop() {
  GameInfo_t *game = getGame();
  int new_coord_y = game->coord_y;
  mvDown();
  while (game->coord_y > new_coord_y) {
    mvDown();
    collision();
  }
}

void mvLeft() {
  GameInfo_t *game = getGame();
  if (game->pause == 0) game->coord_x--;
}

void mvRight() {
  GameInfo_t *game = getGame();
  if (game->pause == 0) game->coord_x++;
}

void terminateIfError(char *msg) {
  quitNcurses();
  perror(msg);
  exit(EXIT_FAILURE);
}

void quitNcurses() {
  delwin(stdscr);
  curs_set(0);
  endwin();
  refresh();
}
