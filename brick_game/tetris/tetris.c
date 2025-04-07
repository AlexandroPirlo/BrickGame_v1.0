#include "../../gui/cli/cli.h"

int main() {
  initGui();
  srand(time(NULL));
  UserAction_t action;
  GameInfo_t *game = getGame();
  while (getch() != 27) {
    printFrogger();
    printInfo(*game);
    refresh();
    if (getch() == '\n') {
      game->game_start = 1;
      break;
    }
  }
  game->coord_x = 10;
  game->coord_y = 0;
  while (game->game_start && action != Terminate) {
    game->tick = 20;
    while (game->tick != 0) {
      game->tick--;
      userInput(action = getAction(), 0);
      collision();
      if (game->game_over || action == Terminate) {
        mvwprintw(stdscr, 14, 16, "GAME OVER");
        refresh();
        napms(1000);
        action = Terminate;
        game->game_start = 0;
        game->game_over = 0;
        break;
      }
      napms(game->speed - game->level * 3);
      erase();
      printGame(game);
      check_and_remove_lines();
    }
    if (!game->game_over) mvDown();
    refresh();
  }
  // getch();          // Ожидаем ввода пользователя
  free_memory(game);
  endwin();
}