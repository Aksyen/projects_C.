#include "cli.h"

/**
 * Вывести сообщение и принять значение с клавиатуры.
 * @param prompt строка сообщения.
 * @return Код введенного символа.
 */
int key_prompt(const char *prompt) {
  attron(A_BOLD);
  addstr(prompt);
  attroff(A_BOLD);
  return getch();
}

/**
 * @brief Вывести сообщение об ошибке.
 * @param message строка сообщения.
 */
void show_error(const char *message) {
  attron(COLOR_PAIR(3) | A_BOLD);
  mvprintw(LINES / 2, (COLS - strlen(message)) / 2, "%s", message);
  attroff(COLOR_PAIR(3) | A_BOLD);
  mvprintw(LINES / 2 + 2, (COLS - 20) / 2, "Press any key to continue...");
  refresh();
  getch();
}

/**
 * Выбор опции.
 *
 * @param prompt строка сообщения.
 * @param count_opt количество опций.
 * @param options массив строк меню.
 *
 * @return Индекс выбранной опции.
 * @note Выводит список меню, у выбранного пункта инвертированы цвета.
 * ENTER подтвердить выбор и вернуть значение.
 */
int option_select(const char *prompt, int count_opt, const char **options) {
  int current_option = 0;
  int ch = 0;
  /* ENTER подтвердить выбор.  */
  while (ch != ENTER) {
    clear();
    attron(A_BOLD);
    addstr(prompt);
    attroff(A_BOLD);
    for (int i = 0; i < count_opt; ++i) {
      if (i == current_option) {
        attron(A_REVERSE); /* Инвертировать цвет для выбранной опции.  */
      }
      printw("%s\n", options[i]);
      if (i == current_option) {
        attroff(A_REVERSE); /* Отключить инвертирование цвета.  */
      }
    }
    refresh();

    /* Вверх вниз по пунктам меню.  */
    ch = getch();
    switch (ch) {
      case KEY_UP:
        current_option = (current_option + count_opt - 1) % count_opt;
        break;
      case KEY_DOWN:
        current_option = (current_option + 1) % count_opt;
        break;
    }
  }
  return current_option;
}

/**
 * Выполняет запрос подтвердения выполнения для графов большого размера.
 * Для алгоритма Хеда-Лакпа.
 *
 * @param size Размер графа.
 * @return true при подтверждении, иначе false.
 */
bool confirm_large_graph_processing(int size) {
  bool confirm = true;
  if (size > 21) {
    const char *message =
        "Do you really want to continue? Enter \'y\' to confirm or any other "
        "key "
        "to cancel.";
    clear();
    refresh();
    attron(COLOR_PAIR(3) | A_BOLD);
    if (size == 22)
      mvprintw(2, 4, "%s", "Graph size 22 requires 0.8g of memory");
    if (size == 23)
      mvprintw(2, 4, "%s", "Graph size 23 requires 1.9g of memory");
    if (size == 24)
      mvprintw(2, 4, "%s", "Graph size 24 requires 3.8g of memory");
    if (size == 25)
      mvprintw(2, 4, "%s", "Graph size 25 requires 7.5g of memory");

    mvprintw(4, 4, "%s", message);
    attroff(COLOR_PAIR(3) | A_BOLD);
    char c = 0;
    c = getch();
    if (c != 'y') confirm = false;
    clear();
    refresh();
  }

  return confirm;
}
