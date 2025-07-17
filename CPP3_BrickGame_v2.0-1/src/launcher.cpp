#include <ncurses.h>

#include <fstream>
#include <string>

#define HEIGHT 22
#define WIDTH 60
#define FIELD_WIDTH 32
#define CONTROLS_WIDTH 24
#define INFO_WIDTH 25

std::string ReadInstallPath(const std::string& fallback = "builds") {
  std::ifstream file("install_path.txt");
  if (!file.is_open()) return fallback;
  std::string path;
  std::getline(file, path);
  file.close();
  return path.empty() ? fallback : path;
}

void initNcurses() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);
  start_color();

  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_CYAN, COLOR_BLACK);
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);
  init_pair(4, COLOR_GREEN, COLOR_BLACK);
  init_pair(5, COLOR_RED, COLOR_BLACK);
}

void drawControls(WINDOW* win) {
  box(win, 0, 0);
  mvwprintw(win, 0, (CONTROLS_WIDTH - 8) / 2, "Controls");
  wattron(win, COLOR_PAIR(2));
  mvwprintw(win, 2, 2, "Select    Enter");
  mvwprintw(win, 4, 2, "Move      Arrows");
  mvwprintw(win, 6, 2, "Quit      ESC");
  wattroff(win, COLOR_PAIR(2));
  wrefresh(win);
}

void drawInfo(WINDOW* win) {
  box(win, 0, 0);
  mvwprintw(win, 0, (INFO_WIDTH - 9) / 2, "Game_Info");
  wattron(win, COLOR_PAIR(3));
  mvwprintw(win, 2, 8, "Welcome to");
  mvwprintw(win, 3, 6, "BrickGame 2.0");
  wattroff(win, COLOR_PAIR(3));
  wrefresh(win);
}

void drawMenu(WINDOW* win, const char* choices[], int n_choices,
              int highlight) {
  box(win, 0, 0);
  mvwprintw(win, 0, (FIELD_WIDTH - 6) / 2, "Menu");

  for (int i = 0; i < n_choices; ++i) {
    if (i == highlight) wattron(win, A_REVERSE);
    mvwprintw(win, 4 + i * 2, 10, "%s", choices[i]);
    if (i == highlight) wattroff(win, A_REVERSE);
  }

  wrefresh(win);
}

int main() {
  const char* choices[] = {"Play TETRIS", "Play SNAKE", "Exit"};
  const int n_choices = sizeof(choices) / sizeof(choices[0]);
  int highlight = 0;

  std::string install_path = ReadInstallPath();

  initNcurses();

  int start_y = 0;
  int start_x = 0;

  WINDOW* controls_win = newwin(HEIGHT, CONTROLS_WIDTH, start_y, start_x);
  WINDOW* menu_win =
      newwin(HEIGHT, FIELD_WIDTH, start_y, start_x + CONTROLS_WIDTH);
  WINDOW* info_win = newwin(HEIGHT, INFO_WIDTH, start_y,
                            start_x + CONTROLS_WIDTH + FIELD_WIDTH);
  keypad(menu_win, TRUE);

  drawControls(controls_win);
  drawMenu(menu_win, choices, n_choices, highlight);
  drawInfo(info_win);

  int ch;
  while (true) {
    ch = wgetch(menu_win);
    switch (ch) {
      case KEY_UP:
        highlight = (highlight - 1 + n_choices) % n_choices;
        break;
      case KEY_DOWN:
        highlight = (highlight + 1) % n_choices;
        break;
      case '\n': {
        delwin(menu_win);
        delwin(controls_win);
        delwin(info_win);
        endwin();

        if (highlight == 0) {
          std::string cmd = install_path + "/tetris";
          system(cmd.c_str());
        } else if (highlight == 1) {
          std::string cmd = install_path + "/snake";
          system(cmd.c_str());
        }
        return 0;
      }
      case 27:  // ESC
        delwin(menu_win);
        delwin(controls_win);
        delwin(info_win);
        endwin();
        return 0;
    }

    drawMenu(menu_win, choices, n_choices, highlight);
  }

  endwin();
  return 0;
}
