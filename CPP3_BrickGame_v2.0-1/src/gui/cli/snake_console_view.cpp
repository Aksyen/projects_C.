

#include "snake_console_view.hpp"

namespace s21 {

/**
 * @brief Конструктор.
 * @param controller Контроллер игры "Змейка".
 */
SnakeConsoleView::SnakeConsoleView(SnakeController& controller)
    : controller_(controller) {}

/// @brief Запускает основной игровой цикл и интерфейс.
void SnakeConsoleView::Run() {
  InitNcurses();
  InitColors();

  int start_y = 0;
  int start_x = 0;
  WINDOW* controls_win = newwin(HEIGHT, CONTROLS_WIDTH, start_y, start_x);
  WINDOW* field_win =
      newwin(HEIGHT, FIELD_WIDTH, start_y, start_x + CONTROLS_WIDTH);
  WINDOW* info_win = newwin(HEIGHT, INFO_WIDTH, start_y,
                            start_x + CONTROLS_WIDTH + FIELD_WIDTH);

  // Сначала отрисовать весь фон
  Render(controls_win, field_win, info_win);

  refresh();
  // Затем отобразить стартовое меню поверх
  PrintStartMenu();

  // И запустить игру
  controller_.HandleUserInput(UserAction_t::Start);

  bool running = true;

  auto last_update_time = std::chrono::steady_clock::now();

  while (running) {
    auto info = controller_.GetGameInfo();

    while (info.status != GameState::GameOver &&
           info.status != GameState::Win) {
      int ch = getch();
      if (ch != ERR) {
        HandleInput(ch);
      }

      auto now = std::chrono::steady_clock::now();
      if (info.status == GameState::Playing &&
          (now - last_update_time >= std::chrono::milliseconds(info.speed))) {
        controller_.Tick();
        last_update_time = now;
      }

      Render(controls_win, field_win, info_win);
      if (controller_.GetGameInfo().status == GameState::Paused) {
        PrintPauseMenu();
      }

      info = controller_.GetGameInfo();
      std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    Render(controls_win, field_win, info_win);
    PrintRestartMenu();
  }

  delwin(controls_win);
  delwin(field_win);
  delwin(info_win);
  endwin();
}

/// @brief Инициализация ncurses.
void SnakeConsoleView::InitNcurses() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  curs_set(0);
  mouseinterval(1);
}

/// @brief Настройка цветовых пар.
void SnakeConsoleView::InitColors() {
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLACK);    // поле
  init_pair(5, COLOR_RED, COLOR_BLACK);      // яблоко
  init_pair(6, COLOR_GREEN, COLOR_BLACK);    // змейка
  init_pair(9, COLOR_CYAN, COLOR_BLACK);     // Controls
  init_pair(10, COLOR_YELLOW, COLOR_BLACK);  // Заголовки
}

/**
 * @brief Рендерит все окна (controls, field, info).
 * @param controls_win Окно управления.
 * @param field_win Окно поля игры.
 * @param info_win Окно с информацией.
 */
void SnakeConsoleView::Render(WINDOW* controls_win, WINDOW* field_win,
                              WINDOW* info_win) {
  werase(controls_win);
  werase(field_win);
  werase(info_win);

  DrawControls(controls_win);
  DrawField(field_win);
  DrawInfo(info_win);
}

/// @brief Отображает панель управления (управляющие клавиши).
void SnakeConsoleView::DrawControls(WINDOW* win) {
  box(win, 0, 0);
  mvwprintw(win, 0, (CONTROLS_WIDTH - 8) / 2, "Controls");

  wattron(win, COLOR_PAIR(9));
  mvwprintw(win, 2, 2, "Start     Enter");
  mvwprintw(win, 4, 2, "Pause     Space");
  mvwprintw(win, 6, 2, "Left      Left arrow");
  mvwprintw(win, 8, 2, "Right     Right arrow");
  mvwprintw(win, 10, 2, "Up        Up arrow");
  mvwprintw(win, 12, 2, "Down      Down arrow");
  mvwprintw(win, 14, 2, "Quit      ESC");
  wattroff(win, COLOR_PAIR(9));

  wrefresh(win);
}

/// @brief Отображает игровое поле: змейку, яблоко, фон.
void SnakeConsoleView::DrawField(WINDOW* win) {
  box(win, 0, 0);
  mvwprintw(win, 0, (FIELD_WIDTH - 5) / 2, "Snake");

  auto info = controller_.GetGameInfo();
  const auto& snake = info.snake;
  const auto& apple = info.apple;

  for (int y = 0; y < info.height; ++y) {
    for (int x = 0; x < info.width; ++x) {
      Position pos{x, y};
      if (std::find(snake.begin(), snake.end(), pos) != snake.end()) {
        wattron(win, COLOR_PAIR(6));
        mvwprintw(win, y + 1, 3 * x + 1, " 0 ");
        wattroff(win, COLOR_PAIR(6));
      } else if (pos == apple) {
        wattron(win, COLOR_PAIR(5));
        mvwprintw(win, y + 1, 3 * x + 1, " @ ");
        wattroff(win, COLOR_PAIR(5));
      } else {
        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, y + 1, 3 * x + 1, " . ");
        wattroff(win, COLOR_PAIR(1));
      }
    }
  }

  wrefresh(win);
}

/// @brief Отображает информационную панель (очки, уровень, скорость).
void SnakeConsoleView::DrawInfo(WINDOW* win) {
  box(win, 0, 0);
  mvwprintw(win, 0, (INFO_WIDTH - 9) / 2, "Game_Info");

  auto info = controller_.GetGameInfo();

  wattron(win, COLOR_PAIR(10));
  mvwprintw(win, 3, 2, "Score      %d", info.score);
  mvwprintw(win, 5, 2, "HighScore  %d", info.high_score);
  mvwprintw(win, 7, 2, "Level      %d", info.level);
  mvwprintw(win, 9, 2, "Speed(ms)  %d", info.speed);
  wattroff(win, COLOR_PAIR(10));

  wrefresh(win);
}

/// @brief Отображает стартовое меню (до начала игры).
void SnakeConsoleView::PrintStartMenu() {
  int width = 32, height = 7;
  int startx = (CONTROLS_WIDTH);
  int starty = (HEIGHT - height) / 2;

  WINDOW* win = newwin(height, width, starty, startx);
  box(win, 0, 0);
  wbkgd(win, COLOR_PAIR(10));

  mvwprintw(win, 1, (width - 18) / 2, "Welcome to Snake!");
  mvwprintw(win, 3, (width - 12) / 2, "Press ENTER");
  mvwprintw(win, 5, (width - 18) / 2, "to start the game");
  mvwprintw(win, 7, (width - 11) / 2, "ESC - Exit");

  wrefresh(win);
  timeout(-1);  // ждать нажатия
  while (true) {
    int ch = getch();
    if (ch == '\n') {
      controller_.HandleUserInput(UserAction_t::Start);
      break;
    } else if (ch == 27) {
      delwin(win);
      endwin();
      exit(0);
    }
  }

  delwin(win);
  timeout(0);  // снова неблокирующий ввод
}

/// @brief Отображает меню паузы.
void SnakeConsoleView::PrintPauseMenu() {
  int width = 24, height = 5;
  int startx = CONTROLS_WIDTH + (FIELD_WIDTH - width) / 2;
  int starty = (HEIGHT - height) / 2;

  WINDOW* win = newwin(height, width, starty, startx);
  box(win, 0, 0);
  wbkgd(win, COLOR_PAIR(9));

  mvwprintw(win, 2, (width - 6) / 2, "Paused");

  wrefresh(win);
  delwin(win);
}

/// @brief Отображает меню перезапуска после окончания игры.
void SnakeConsoleView::PrintRestartMenu() {
  int width = 36, height = 7;
  int startx = CONTROLS_WIDTH + (FIELD_WIDTH - width) / 2;
  int starty = (HEIGHT - height) / 2;

  WINDOW* win = newwin(height, width, starty, startx);
  box(win, 0, 0);

  if (controller_.IsWin()) {
    wbkgd(win, COLOR_PAIR(6));  // зелёный
    mvwprintw(win, 2, (width - 10) / 2, "You Win!");
  } else {
    wbkgd(win, COLOR_PAIR(5));  // красный
    mvwprintw(win, 2, (width - 12) / 2, "Game Over!");
  }

  mvwprintw(win, 4, (width - 23) / 2, "Press ENTER to restart");

  wrefresh(win);
  timeout(-1);
  while (true) {
    int ch = getch();
    if (ch == '\n') {
      controller_.HandleUserInput(UserAction_t::Start);
      timeout(0);
      break;
    } else if (ch == 27) {
      delwin(win);
      endwin();
      exit(0);
    }
  }
}

/**
 * @brief Обрабатывает нажатие клавиши и преобразует в действие пользователя.
 * @param ch Код нажатой клавиши.
 */
void SnakeConsoleView::HandleInput(int ch) {
  switch (ch) {
    case '\n':
      controller_.HandleUserInput(UserAction_t::Start);
      break;
    case ' ':
      controller_.HandleUserInput(UserAction_t::Pause);
      break;
    case 27:  // ESC
      endwin();
      exit(0);
      break;
    case KEY_UP:
      controller_.HandleUserInput(UserAction_t::Up);
      break;
    case KEY_DOWN:
      controller_.HandleUserInput(UserAction_t::Down);
      break;
    case KEY_LEFT:
      controller_.HandleUserInput(UserAction_t::Left);
      break;
    case KEY_RIGHT:
      controller_.HandleUserInput(UserAction_t::Right);
      break;
    default:
      break;
  }
}

}  // namespace s21
