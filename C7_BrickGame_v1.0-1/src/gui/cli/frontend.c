#include "frontend.h"

// Инициализация ncurses-библиотеки для работы с терминалом
void initNcurses() {
  // Инициализирует окно терминала для работы с ncurses.
  initscr();
  // Включает режим посимвольного ввода (без ожидания ввода целой строки).
  cbreak();
  // Отключает отображение введенных символов (удобно для управления клавишами).
  noecho();
  // Разрешает использование функциональных клавиш, например, стрелок.
  keypad(stdscr, 1);
  // Включает неблокирующий ввод — программа продолжает работу без ожидания
  // ввода.
  nodelay(stdscr, 1);
  // Включает прокрутку, если ввод выходит за пределы экрана.
  scrollok(stdscr, 1);
  // Отключает курсор (скрывает его во время игры).
  curs_set(0);
  // Устанавливает задержку для обработки событий мыши (в миллисекундах).
  mouseinterval(1);
}

// Инициализация цветовых пар для отображения различных элементов интерфейса
void initColors() {
  start_color();
  // белый текст на черном фоне.
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  // Линия (4 блока) - красный
  init_pair(2, COLOR_RED, COLOR_RED);

  // Определение новых цветов.
  if (can_change_color()) {
    // Оранжевый цвет (1000 - красный, 500 - зеленый, 0 - синий)
    init_color(13, 1000, 500, 0);

    // Фиолетовый (800 - красный, 0 - зеленый, 1000 - синий)
    init_color(14, 800, 0, 1000);

    // Обратная L-образная фигура - оранжевый
    init_pair(3, 13, 13);

    // Z-образная фигура - фиолетовый
    init_pair(8, 14, 14);

  } else {
    // Если терминал не поддерживает изменение цветов, используем замену

    init_pair(3, COLOR_YELLOW, COLOR_YELLOW);  // Желтый вместо оранжевого

    init_pair(8, COLOR_GREEN, COLOR_GREEN);  // Зеленый вместо фиолетового
  }

  // L-образная - желтый
  init_pair(4, COLOR_YELLOW, COLOR_YELLOW);
  // Квадрат (2x2) - розовый
  init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA);
  // Обратная Z-образная фигура - зеленый
  init_pair(6, COLOR_GREEN, COLOR_GREEN);
  // T-образная фигура - синий
  init_pair(7, COLOR_BLUE, COLOR_BLUE);

  init_pair(9, COLOR_CYAN, COLOR_BLACK);
  init_pair(10, COLOR_YELLOW, COLOR_BLACK);
  init_pair(11, COLOR_RED, COLOR_BLACK);
  init_pair(12, COLOR_GREEN, COLOR_BLACK);
  init_pair(15, COLOR_CYAN, COLOR_CYAN);
}

// Основная функция рендеринга игры
void render(int status, bool win, GameInfo_t gi) {
  refresh();  // Обновляем экран, чтобы отобразить изменения.
  // Отображение окна управления игрой
  WINDOW *controls_window = printControls();
  wrefresh(controls_window);  // Отображаем окно управления.

  WINDOW *game_window = NULL;
  // Если игра не на паузе, отображаем игровое поле.
  if (!gi.pause) {
    game_window = printGameField(gi);
    wrefresh(game_window);  // Отображаем окно игры.
  }

  // В зависимости от состояния игры выводим нужные экраны
  if (status == Initial) {
    printStartMenu();  // Отображаем меню старта.
  } else if (gi.pause) {
    printPauseMenu();  // Отображаем меню паузы.
  } else if (win) {
    printWin(gi);  // Отображаем экран победы.
  } else if (status == GameOver) {
    printGameOver(gi);  // Отображаем экран проигрыша.
  }

  // Отображаем информацию о текущем состоянии игры (счет, уровень и т. д.).
  WINDOW *info_window = printGameInfo(gi);
  wrefresh(info_window);  // Обновляем окно с информацией.

  // Освобождение ресурсов
  if (game_window != NULL) delwin(game_window);
  delwin(info_window);
  delwin(controls_window);
}

// Отображение стартового меню
void printStartMenu() {
  WINDOW *start_menu_window =
      newwin(START_MENU_N, START_MENU_M, (GAME_FIELD_N - START_MENU_N) / 2,
             CONTROLS_M + 3);  // Создаем новое окно для стартового меню.
  box(start_menu_window, 0, 0);  // Рисуем границу вокруг окна.

  // Текст в стартовом меню
  wattron(start_menu_window, COLOR_PAIR(12));  // Включаем цветовую пару.
  mvwprintw(start_menu_window, (START_MENU_N - 3) / 2,
            (START_MENU_M - 20) / 2 + 1, "Welcome to Tetris");
  mvwprintw(start_menu_window, (START_MENU_N - 3) / 2 + 1,
            (START_MENU_M - 20) / 2 + 3, "from Lioncoco");
  wattroff(start_menu_window, COLOR_PAIR(12));  // Отключаем цветовую пару.

  wattron(start_menu_window, COLOR_PAIR(11));  // Включаем цветовую пару.
  mvwprintw(start_menu_window, (START_MENU_N - 3) / 2 + 3,
            (START_MENU_M - 20) / 2, "Press Enter to start");
  wattroff(start_menu_window, COLOR_PAIR(11));  // Отключаем цветовую пару.

  wrefresh(start_menu_window);  // Обновляем окно для отображения.
  delwin(start_menu_window);  // Удаляем окно для освобождения памяти.
}

// Отображение меню паузы
void printPauseMenu() {
  WINDOW *pause_menu_window =
      newwin(PAUSE_MENU_N, PAUSE_MENU_M, (GAME_FIELD_N - PAUSE_MENU_N) / 2,
             CONTROLS_M + 3);  // Создаем окно для меню паузы.
  box(pause_menu_window, 0, 0);  // Рисуем границу окна.
  // Устанавливаем фон окна.
  wbkgd(pause_menu_window, COLOR_PAIR(10));

  // Текст "Paused"
  mvwprintw(pause_menu_window, (PAUSE_MENU_N - 1) / 2, (PAUSE_MENU_M - 6) / 2,
            "Paused");

  wrefresh(pause_menu_window);  // Обновляем окно для отображения.
  delwin(pause_menu_window);  // Удаляем окно для освобождения памяти.
}

// Отображение экрана победы
void printWin(GameInfo_t gi) {
  // Создаем окно для победы.
  WINDOW *win_window =
      newwin(FINISH_GAME_N, FINISH_GAME_M, (GAME_FIELD_N - FINISH_GAME_N) / 2,
             CONTROLS_M + 3);
  box(win_window, 0, 0);  // Рисуем границу окна.
  wbkgd(win_window, COLOR_PAIR(12));

  // Текст "You win!"
  mvwprintw(win_window, (FINISH_GAME_N - 2) / 2, (FINISH_GAME_M - 14) / 2,
            "You win! (*_*)");
  mvwprintw(win_window, (FINISH_GAME_N - 2) / 2 + 2, (FINISH_GAME_M - 11) / 2,
            "Score  %d", gi.score);

  wrefresh(win_window);  // Обновляем окно.
  delwin(win_window);    // Удаляем окно.
}

// Отображение экрана проигрыша
void printGameOver(GameInfo_t gi) {
  // Создаем окно для экрана проигрыша.
  WINDOW *game_over_window =
      newwin(FINISH_GAME_N, FINISH_GAME_M, (GAME_FIELD_N - FINISH_GAME_N) / 2,
             CONTROLS_M + 3);
  box(game_over_window, 0, 0);  // Рисуем границу окна.
  // Устанавливаем цветовую пару (красный фон).
  wbkgd(game_over_window, COLOR_PAIR(11));

  // Текст "Game over"
  mvwprintw(game_over_window, (FINISH_GAME_N - 4) / 2, (FINISH_GAME_M - 16) / 2,
            "Game over (X_x)");
  mvwprintw(game_over_window, (FINISH_GAME_N - 4) / 2 + 2,
            (FINISH_GAME_M - 12) / 2, "Score  %d", gi.score);
  mvwprintw(game_over_window, (FINISH_GAME_N - 4) / 2 + 3,
            (FINISH_GAME_M - 12) / 2, "Level  %d", gi.level);

  wrefresh(game_over_window);  // Обновляем окно.
  delwin(game_over_window);  // Удаляем окно для освобождения памяти.
}

// Отображение окна с управлением (помощь пользователю)
WINDOW *printControls() {
  // Создаем окно для отображения управления.
  WINDOW *controls_window =
      newwin(GAME_FIELD_N, CONTROLS_M, TOP_MARGIN, LEFT_MARGIN);
  box(controls_window, 0, 0);

  mvwprintw(controls_window, 0, (CONTROLS_M - 8) / 2,
            "Controls");  // Заголовок "Controls" по центру.

  // Вывод подсказок для управления игрой
  wattron(controls_window, COLOR_PAIR(9));
  mvwprintw(controls_window, 2, 2, "Start    Enter");
  mvwprintw(controls_window, 4, 2, "Pause    Space");
  mvwprintw(controls_window, 6, 2, "Rotate   Up arrow, z");
  mvwprintw(controls_window, 8, 2, "Left     Left arrow");
  mvwprintw(controls_window, 10, 2, "Right    Right arrow");
  mvwprintw(controls_window, 12, 2, "Down     Down arrow");
  mvwprintw(controls_window, 14, 2, "Quit     ESC or q");
  wattroff(controls_window, COLOR_PAIR(9));
  return controls_window;  // Возвращаем указатель на окно с управлением.
}

// Отображение игрового поля
WINDOW *printGameField(GameInfo_t gi) {
  const GameState_t *gs = getGameState();
  // Создаем окно для игрового поля.
  WINDOW *game_window =
      newwin(GAME_FIELD_N, GAME_FIELD_M, TOP_MARGIN, CONTROLS_M);
  box(game_window, 0, 0);  // Рисуем границу окна.
  keypad(game_window, 1);  // Разрешаем использование клавиш для управления.
  nodelay(game_window, 1);  // Включаем неблокирующий ввод.
  // Заголовок "Tetris" вверху окна.
  mvwprintw(game_window, 0, (GAME_FIELD_M - 6) / 2, "Tetris");

  // Отрисовка игрового поля
  for (int i = 0; i < FIELD_N; i++) {
    for (int j = 0; j < FIELD_M; j++) {
      if (gi.field[i][j] == 1) {  // Если клетка занята, рисуем блок.
        // Включаем цветовую пару №5 для заполненных клеток.
        wattron(game_window, COLOR_PAIR(15));
        mvwprintw(game_window, i + 1, 3 * j + 1, "   ");  // Отрисовываем блок.
        wattroff(game_window, COLOR_PAIR(15));  // Отключаем цвет.
      } else {
        // Если клетка пустая, рисуем точку.
        if (j + 1 < FIELD_M && i + 1 < FIELD_N) {
          // Включаем цветовую пару №1 для пустых клеток.
          wattron(game_window, COLOR_PAIR(1));
          mvwprintw(game_window, i + 1, 3 * j + 1,
                    "  .");  // Отрисовываем пустую клетку.
          wattroff(game_window, COLOR_PAIR(1));  // Отключаем цвет.
        } else
          continue;
      }
    }
  }
  // Отрисовываем текущую фигуру с её фиксированным цветом
  for (int i = 0; i < gs->figure_size; i++) {
    for (int j = 0; j < gs->figure_size; j++) {
      if (gs->figure[i][j] == 1) {
        // Используем цвет фигуры.
        wattron(game_window, COLOR_PAIR(gi.figure_color));
        mvwprintw(game_window, gs->y + i + 1, 3 * (gs->x + j) + 1, "   ");
        wattroff(game_window, COLOR_PAIR(gi.figure_color));
      }
    }
  }

  return game_window;  // Возвращаем указатель на окно игрового поля.
}

// Отображение информации о текущей игре (счет, уровень и т. д.)
WINDOW *printGameInfo(GameInfo_t gi) {
  // Создаем окно для информации о игре.
  WINDOW *info_window =
      newwin(GAME_FIELD_N, GAME_INFO_M, TOP_MARGIN, CONTROLS_M + GAME_FIELD_M);
  box(info_window, 0, 0);  // Рисуем границу окна.
  // Заголовок "Game Info".
  mvwprintw(info_window, 0, (GAME_INFO_M - 9) / 2, "Game_Info");
  // Отрисовываем следующую фигуру.
  printNextFigure(info_window, gi);

  // Вывод информации о текущем счете, уровне и скорости
  mvwprintw(info_window, 8, 2, "High score  %d", gi.high_score);
  mvwprintw(info_window, 11, 2, "Score       %d", gi.score);
  mvwprintw(info_window, 14, 2, "Level       %d", gi.level);
  mvwprintw(info_window, 17, 2, "Speed       %d", gi.level);

  return info_window;  // Возвращаем указатель на окно с информацией.
}

// Отображение следующей фигуры в отдельном окне информации
void printNextFigure(WINDOW *info_window, GameInfo_t gi) {
  // Заголовок для следующей фигуры.
  mvwprintw(info_window, 2, 6, "Next Figure");
  // GameState_t *gs = getGameState();

  // Отрисовываем следующую фигуру
  for (int i = 0; i < gi.next_size; i++) {
    for (int j = 0; j < gi.next_size; j++) {
      if (gi.next[i][j] == 1) {  // Если элемент фигуры активен, рисуем его.
        // Включаем цветовую пару для фигуры.
        wattron(info_window, COLOR_PAIR(gi.next_figure_color));
        mvwprintw(info_window, i + 4, j * 3 + 6, "   ");  // Отрисовываем блок.
        wattroff(info_window,
                 COLOR_PAIR(gi.next_figure_color));  // Отключаем цвет.
      }
    }
  }
}
