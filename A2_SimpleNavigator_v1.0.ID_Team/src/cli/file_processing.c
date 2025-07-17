#include "cli.h"

static void print_files(const char *prompt, int count,
                        char files[][FILENAME_MAX - 1], int selected,
                        int scroll_offset, int window_height);
static int get_files(const char *path, char files[][FILENAME_MAX - 1],
                     int *count);
static void scroll_options(int ch, int *selected, int *scroll_offset, int count,
                           int window_height);
static int selection_fd(char path[], char files[][FILENAME_MAX - 1],
                        char path_file[], int *selected, int *scroll_offset,
                        int *count, int mode);

/**
 * @brief Получить путь к файлу или к директории.
 * @param path_file Полный путь к выбранному файлу или директории.
 * @param mode Режим работы (MODE_F или MODE_D).
 * @return Статус выполнения:
 *   - 0 успешный выбор,
 *   - 1 продолжение работы (внутренний статус),
 *   - ESCAPE операция отменена пользователем.
 * @note Для файла MODE_F, для директории MODE_D.
 * Навигация начинается с текущей директории.
 *
 * Выводит интерактивное меню навигации по файловой системе.
 */
int get_file_path(char path_file[], char mode) {
  char files[MAX_FILES][FILENAME_MAX - 1]; /* Список файлов. */
  char path[FILENAME_MAX] = "."; /* Директория для чтения. */
  const char *masage_f = "File selection, press enter to select:";
  const char *masage_d =
      "Directory selection, press enter to select, select \".\" to confirm:";
  int status = 1;
  int count = 0;         /* Счетчик файлов. */
  int selected = 0;      /* Выбранный файл/директория. */
  int scroll_offset = 0; /* Смещение для прокрутки. */
  int window_height = getmaxy(stdscr); /* Получаем высоту окна.  */

  get_files(path, files, &count);

  /* Пока не получен путь или пока не отменено действие.  */
  while (status == 1 && status != ESCAPE) {
    print_files(mode == MODE_F ? masage_f : masage_d, count, files, selected,
                scroll_offset, window_height);

    /* Ожидание ввода управляющего символа.  */
    int ch = 0;
    while (ch != KEY_UP && ch != KEY_DOWN && ch != ENTER && ch != ESCAPE)
      ch = getch();

    if (ch == KEY_UP || ch == KEY_DOWN)
      scroll_options(ch, &selected, &scroll_offset, count, window_height);

    /* Выбор файла/директории в заисимости от мода.  */
    if (ch == ENTER) {
      status = selection_fd(path, files, path_file, &selected, &scroll_offset,
                            &count, mode);
    }

    /* Если введет ESCAPE, завершить работу функции.  */
    if (ch == ESCAPE) status = ESCAPE;
  }
  return status;
}

/**
 * @brief Обрабатывает выбор файла/директории в файловом меню.
 * @param path Текущий путь (обновляется при входе в директорию).
 * @param files Массив имен файлов в текущей директории.
 * @param path_file Полный путь к выбранному файлу или директории.
 * @param selected Указатель на индекс выбранного элемента.
 * @param scroll_offset Указатель на смещение прокрутки.
 * @param count Указатель на количество файлов.
 * @param mode Режим работы:
 *   - MODE_D обработка директорий,
 *   - MODE_F обработка файлов.
 * @return Статус выполнения:
 *   - 0 Успешная обработка файла,
 *   - 1 Успешный переход в директорию,
 *   - ESCAPE Ошибка (переполнение буфера или ошибка чтения).
 */
static int selection_fd(char path[], char files[][FILENAME_MAX - 1],
                        char path_file[], int *selected, int *scroll_offset,
                        int *count, int mode) {
  char new_path[FILENAME_MAX] = {0};
  int status;
  sprintf(new_path, "%s/%s", path, files[*selected]);
  status = strlen(path) < FILENAME_MAX - 2 ? 0 : ESCAPE;
  struct stat fileStat; /* Структура для хранения метаданных файла.  */
  /* Получить метаданные файла.  */
  if (stat(new_path, &fileStat) == -1) {
    return ESCAPE; /* Обработка ошибки доступа.  */
  }

  if (S_ISDIR(fileStat.st_mode) && status != ESCAPE) {
    /* Если режим MODE_D и выбрана текущая директория, сформировать
     * путь к выбранной директории.  */
    if (mode == MODE_D && strcmp(files[*selected], ".") == 0) {
      strcpy(path_file, new_path);
      /* Если буфер переполнен статус ESCAPE иначе 0.  */
      status = strlen(path_file) < FILENAME_MAX - 2 ? 0 : ESCAPE;

      /* Если режи MODE_F прочитать выбранную директорию.  */
    } else {
      /* Сброс четчиков.  */
      *selected = *scroll_offset = *count = 0;
      /* Сформировать путь для чтения новой директории.  */
      strcpy(path, new_path);
      /* Если буфер переполнен статус ESCAPE иначе 1 (для продолжения работы
       * основной функции).  */
      status = strlen(path) < FILENAME_MAX - 2 ? 1 : ESCAPE;
      /* Прочитать содержимое новой директории. Если не удалось ее прочитать
       * вернуться в текущую.  */
      if (status != ESCAPE && get_files(path, files, count)) {
        strcpy(path, ".");
        status = get_files(path, files, count);
      }
    }
    /* Если выбран файл и режим MODE_F, сформировать путь к выбранному файлу. */
  } else {
    if (mode == MODE_F) {
      strcpy(path_file, new_path);
      status = strlen(path_file) < FILENAME_MAX - 2 ? 0 : ESCAPE;
    }
  }
  return status;
}

/**
 * @brief Получить файлы и папки из указанной директории.
 *
 * @param path путь к директории.
 * @param files массив файлов и директорий.
 * @param count количество элементов в массиве files.
 *
 * @return При успешном завершении 0 иначе 1.
 */
static int get_files(const char *path, char files[][FILENAME_MAX - 1],
                     int *count) {
  int status = 0;
  DIR *dir;
  /* Если чтение директории прошло успеешно, занести файлы и папки в массив
   * files.  */
  if ((dir = opendir(path)) != NULL) {
    /* указатель для чтения записей директории. Он позволяет безопасно получать
     * имена файлов, но запрещает их модификацию.  */
    struct dirent const *entry;
    while ((entry = readdir(dir)) != NULL && *count < MAX_FILES) {
      strncpy(files[*count], entry->d_name, FILENAME_MAX);
      (*count)++;
    }
    closedir(dir);
    /* Если не удалось открыть директорию.  */
  } else {
    status = 1;
    clear();
    attron(A_BOLD);
    mvprintw(0, 0, "Permission denied %s", path);
    attroff(A_BOLD);
    refresh();
    getch();
  }
  return status;
}

/**
 * @brief Отображает список файлов/директорий с прокруткой и выделением.
 *
 * @param prompt Заголовок списка (выводится жирным шрифтом).
 * @param count Общее количество элементов в массиве `files`.
 * @param files Массив имён файлов/директорий.
 * @param selected Индекс текущего выбранного элемента.
 * @param scroll_offset Смещение прокрутки (первый видимый элемент).
 * @param window_height Высота окна (максимум видимых элементов).
 */
static void print_files(const char *prompt, int count,
                        char files[][FILENAME_MAX - 1], int selected,
                        int scroll_offset, int window_height) {
  clear();
  int visible_start = scroll_offset;
  /* Определение последнего видимого элемента, не выходя за границы списка.  */
  int visible_end = (scroll_offset + window_height - 1 < count)
                        ? (scroll_offset + window_height - 1)
                        : count;

  attron(A_BOLD);
  mvprintw(0, 0, "%s", prompt);
  attroff(A_BOLD);

  /* Вывести видимую часть списка и подсветить инверсией цвета выбранный
   * элемент.
   */
  for (int i = visible_start; i < visible_end; i++) {
    int y = i - scroll_offset;

    if (i == selected) {
      attron(A_REVERSE); /* Подсветка выбранного элемента.  */
    }
    mvprintw(y + 1, 0, "%s", files[i]);
    if (i == selected) {
      attroff(A_REVERSE);
    }
  }
  refresh();
}

/**
 * @brief Прокрутка списка содержимого директории и выбор директории или файла.
 *
 * @param ch Код нажатой клавиши (KEY_UP/KEY_DOWN).
 * @param selected Указатель на индекс текущего выбранного элемента.
 * @param scroll_offset Указатель на смещение прокрутки (первый видимый
 * элемент).
 * @param count Общее количество элементов в списке.
 * @param window_height Высота окна (максимум видимых элементов).
 */
static void scroll_options(int ch, int *selected, int *scroll_offset, int count,
                           int window_height) {
  switch (ch) {
    case KEY_UP:
      /* Если не на первом элементе уменьшаем индекс.  */
      if (*selected > 0) {
        (*selected)--;
        /* Если индекс выбранного элемента находится выше первого видимого
         * сдвигаем окно на позицию выделенного элемента.  */
        if (*selected < *scroll_offset) *scroll_offset = *selected;
      }
      break;
    case KEY_DOWN:
      /* Если не на последнем элементе увеличивем индекс.  */
      if (*selected < count - 1) {
        (*selected)++;
        /* Если индекс выбранного элемента находится ниже последнего видимого
         * сдвигаем окно на 1 элемент вниз.*/
        if (*selected >= *scroll_offset + window_height) (*scroll_offset)++;
      }
      break;
  }
}
