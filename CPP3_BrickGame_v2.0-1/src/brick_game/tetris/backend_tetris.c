#include "backend_tetris.h"

// Инициализация игры: установка начальных значений для всех параметров и
// загрузка рекорда.
void initGame() {
  GameState_t *gs = getGameState();  // Получаем текущее состояние игры.

  // Начальные координаты фигуры и базовые параметры игры.
  gs->x = START_X;
  gs->y = START_Y;
  gs->status = Initial;  // Игра начинается в состоянии Initial.
  gs->score = 0;  // Начальный счет равен 0.
  gs->level = 1;  // Стартовый уровень - 1.
  gs->speed = 1200;  // Начальная скорость игры (1200 миллисекунд).
  gs->pause = false;      // Игра не на паузе.
  gs->is_playing = true;  // Флаг, что игра запущена.
  gs->win = false;  // Флаг, что игра не завершена победой.
  gs->time = getTime();  // Получаем текущее время для отслеживания таймеров.

  // Создание игрового поля (матрицы).
  gs->field = createMatrix(FIELD_N, FIELD_M);

  // Инициализация случайных чисел для генерации фигур.
  srand(getTime());

  int size;
  // Генерация первой следующей фигуры.
  gs->next_figure = generateFigure(&size);
  gs->next_figure_size = size;  // Сохранение ее размера.

  // Копирование следующей фигуры как текущей.
  gs->figure = createMatrix(size, size);
  gs->figure_size = size;
  copyMatrix(size, size, gs->next_figure, gs->figure);

  // Чтение рекорда из файла.
  char puth[512];
  high_score_path(puth);
  FILE *file = fopen(puth, "r");
  if (file) {
    fscanf(file, "%d", &gs->high_score);
    fclose(file);
  }
}

// Генерация новой фигуры случайного типа.
int **generateFigure(int *size) {
  int random_type = rand() % NUM_FIGURES;  // Случайный выбор типа фигуры.
  // Определение размера фигуры на основе ее типа.
  *size = (random_type == 0) ? 4 : (random_type == 3) ? 2 : 3;

  // Создание матрицы для фигуры и ее заполнение.
  int **figure = createMatrix(*size, *size);
  if (figure != NULL)
    fillFigure(random_type, figure);  // Заполнение фигуры на основе ее типа.

  return figure;  // Возвращаем сгенерированную фигуру.
}

// Заполнение матрицы фигуры в зависимости от ее типа.
void fillFigure(int number, int **figure) {
  switch (number) {
    case 0:  // Линия (4 блока)
      figure[0][0] = 2;
      figure[0][1] = 2;
      figure[0][2] = 2;
      figure[0][3] = 2;
      break;
    case 1:  // L-образная фигура
      figure[0][0] = 3;
      figure[1][0] = 3;
      figure[1][1] = 3;
      figure[1][2] = 3;
      break;
    case 2:  // Обратная L-образная фигура
      figure[0][2] = 4;
      figure[1][0] = 4;
      figure[1][1] = 4;
      figure[1][2] = 4;
      break;
    case 3:  // Квадрат (2x2)
      figure[0][0] = 5;
      figure[0][1] = 5;
      figure[1][0] = 5;
      figure[1][1] = 5;
      break;
    case 4:  // Z-образная фигура
      figure[0][1] = 6;
      figure[0][2] = 6;
      figure[1][0] = 6;
      figure[1][1] = 6;
      break;
    case 5:  // T-образная фигура
      figure[0][1] = 7;
      figure[1][0] = 7;
      figure[1][1] = 7;
      figure[1][2] = 7;
      break;
    case 6:  // Обратная Z-образная фигура
      figure[0][0] = 8;
      figure[0][1] = 8;
      figure[1][1] = 8;
      figure[1][2] = 8;
      break;
    default:
      break;
  }
}

// Обновление текущего состояния игры и возвращение информации о текущем
// состоянии.
GameInfo_t updateCurrentState(GameState_t *gs) {
  GameInfo_t gi;

  gi.score = gs->score;  // Текущий счет.
  gi.level = gs->level;  // Текущий уровень.
  gi.speed = gs->speed;  // Текущая скорость.

  // Копирование игрового поля для отображения.
  gi.field = createMatrix(FIELD_N, FIELD_M);
  copyMatrix(FIELD_N, FIELD_M, gs->field, gi.field);

  if (gi.field != NULL) updateField(gs, gi.field);  // Обновление игрового поля.

  // Копирование следующей фигуры.
  int size = gs->next_figure_size;
  gi.next = createMatrix(size, size);
  copyMatrix(size, size, gs->next_figure, gi.next);
  gi.next_size = size;

  gi.high_score = gs->high_score;  // Рекордный счет.
  gi.pause = gs->pause;  // Проверка, на паузе ли игра.

  return gi;  // Возвращаем обновленное состояние игры.
}

// Обновление игрового поля в зависимости от текущего состояния фигуры.
void updateField(const GameState_t *gs, int **field) {
  for (int i = 0; i < gs->figure_size; i++) {
    for (int j = 0; j < gs->figure_size; j++) {
      int x = gs->x + j;  // Позиция фигуры на поле (по оси X).
      int y = gs->y + i;  // Позиция фигуры на поле (по оси Y).

      // Если блок фигуры активен (значение 1), то обновляем игровое поле.
      if (gs->figure[i][j] > 0 && y > -1 && y < FIELD_N && x > -1 &&
          x < FIELD_M) {
        field[y][x] = gs->figure[i][j];
      }
    }
  }
}

// Обработка ввода пользователя в зависимости от состояния игры.
void userInput(GameState_t *gs, UserAction_t action) {
  if (gs->status == Initial) {
    if (action == Terminate) {
      finishGame(gs);  // Если действие - завершение игры, завершаем игру.
    } else if (action == Start) {
      gs->status =
          Spawn;  // Если действие - старт, запускаем генерацию новой фигуры.
    }

  } else if (gs->status == Spawn) {
    if (action == Terminate || gs->win) {
      finishGame(gs);  // Завершаем игру при победе или действии завершения.
    } else {
      spawnFigure(gs);  // Генерация новой фигуры.
    }

  } else if (gs->status == Moving) {
    moveFigure(gs, action);  // Если статус движения, двигаем фигуру.
  } else if (gs->status == Shifting) {
    moveDown(gs);  // Если статус сдвига, сдвигаем фигуру вниз.
  } else if (gs->status == Attaching) {
    attachFigure(gs);  // Если фигура прикрепляется к полю, выполняем
                       // соответствующую обработку.
  } else if (gs->status == GameOver) {
    finishGame(gs);  // Если игра окончена, завершаем процесс.
  }
}

// Завершение игры, освобождение памяти и сброс состояния.
void finishGame(GameState_t *gs) {
  // Останавливаем игру, если она не завершена победой.
  if (gs->status != GameOver && !gs->win) {
    gs->is_playing = false;
  }

  if (gs->field != NULL) {
    freeMatrix(FIELD_N, gs->field);
    gs->field = NULL;
  }
  if (gs->figure != NULL) {
    freeMatrix(gs->figure_size, gs->figure);
    gs->figure = NULL;
  }
  if (gs->next_figure != NULL) {
    freeMatrix(gs->next_figure_size, gs->next_figure);
    gs->next_figure = NULL;
  }
}

// Спавн новой фигуры в начале игры или после сдвига фигур.
void spawnFigure(GameState_t *gs) {
  // Освобождаем память, выделенную для текущей фигуры.
  freeMatrix(gs->figure_size, gs->figure);

  // Текущая фигура становится предыдущей "следующей" фигурой.
  gs->figure = gs->next_figure;
  gs->figure_size = gs->next_figure_size;

  // Генерация новой следующей фигуры.
  int size;

  gs->next_figure = generateFigure(&size);
  gs->next_figure_size = size;

  // Установка стартовой позиции для новой фигуры.
  gs->x = (gs->figure_size == 2) ? 4 : 3;
  gs->y = 0;

  gs->time = getTime();  // Обновление таймера.
  gs->status = Moving;   // Переход в статус движения.
}

// Логика перемещения фигуры влево, вправо, вниз или вращение.
void moveFigure(GameState_t *gs, UserAction_t action) {
  if (action == Left && !gs->pause) {
    moveLeft(gs);  // Перемещение влево.
  } else if (action == Right && !gs->pause) {
    moveRight(gs);  // Перемещение вправо.
  } else if (action == Down && !gs->pause) {
    moveDown(gs);  // Ускоренное падение вниз.
  } else if ((action == Action || action == Up) && !gs->pause) {
    rotate(gs);  // Вращение фигуры.
  } else if (action == Pause) {
    gs->pause = !gs->pause;  // Включение или отключение паузы.
  } else if (action == Terminate) {
    finishGame(gs);  // Завершение игры.
  }

  if (timer(gs, gs->speed) && !gs->pause) {
    gs->status =
        Shifting;  // Переход к сдвигу, если таймер сработал и игра не на паузе.
  }
}

// Логика перемещения фигуры влево с проверкой возможных препятствий.
void moveLeft(GameState_t *gs) {
  bool can_move = true;  // Флаг, можно ли двигаться влево.

  // Проверка, можно ли двигать фигуру влево (нет ли коллизий с границами или
  // другими фигурами).
  for (int i = 0; i < gs->figure_size; i++) {
    for (int j = 0; j < gs->figure_size; j++) {
      int x = gs->x + j - 1;
      int y = gs->y + i;

      if (gs->figure[i][j] > 0 &&
          (x >= FIELD_M || x < 0 || gs->field[y][x] > 0)) {
        can_move = false;
      }
    }
  }

  // Если можно двигать влево, сдвигаем координату X.
  if (can_move) {
    gs->x--;
  }

  gs->status =
      figureIsAttaching(gs) ? Attaching : Moving;  // Определяем новый статус.
}

// Логика перемещения фигуры вправо с проверкой возможных препятствий.
void moveRight(GameState_t *gs) {
  bool can_move = true;  // Флаг, можно ли двигаться вправо.

  // Проверка, можно ли двигать фигуру вправо (нет ли коллизий с границами или
  // другими фигурами).
  for (int i = 0; i < gs->figure_size; i++) {
    for (int j = 0; j < gs->figure_size; j++) {
      int x = gs->x + j + 1;
      int y = gs->y + i;

      if (gs->figure[i][j] > 0 &&
          (x >= FIELD_M || x < 0 || gs->field[y][x] > 0)) {
        can_move = false;
      }
    }
  }

  // Если можно двигать вправо, сдвигаем координату X.
  if (can_move) {
    gs->x++;
  }

  gs->status =
      figureIsAttaching(gs) ? Attaching : Moving;  // Определяем новый статус.
}

// Логика перемещения фигуры вниз. Если фигура не достигла дна, двигаем ее вниз.
void moveDown(GameState_t *gs) {
  if (!figureIsAttaching(gs)) {  // Проверка, достигла ли фигура дна.
    gs->y++;  // Сдвигаем фигуру вниз по оси Y.
    gs->status = Moving;  // Переходим к статусу движения.
  } else {
    gs->status =
        Attaching;  // Если фигура достигла дна, переходим к прикреплению.
  }
}

// Логика вращения фигуры с проверкой на возможность вращения (нет ли коллизий с
// другими фигурами или границами).
void rotate(GameState_t *gs) {
  bool can_move = true;  // Флаг, можно ли вращать фигуру.

  // Создаем временную матрицу для хранения поворота фигуры.
  int **temp_figure = createMatrix(gs->figure_size, gs->figure_size);

  // Вращаем фигуру (переставляем значения по часовой стрелке).
  for (int i = 0; i < gs->figure_size; i++) {
    for (int j = 0; j < gs->figure_size; j++) {
      temp_figure[j][gs->figure_size - i - 1] = gs->figure[i][j];
    }
  }

  // Проверка, не выйдет ли фигура за пределы поля или не столкнется ли с
  // другими фигурами.
  for (int i = 0; i < gs->figure_size; i++) {
    for (int j = 0; j < gs->figure_size; j++) {
      int x = gs->x + j;
      int y = gs->y + i;

      if (temp_figure[i][j] > 0 && (y >= FIELD_N || y < 0 || x >= FIELD_M ||
                                    x < 0 || gs->field[y][x] > 0)) {
        can_move = false;
      }
    }
  }

  // Если вращение возможно, заменяем текущую фигуру на повернутую.
  if (can_move) {
    freeMatrix(gs->figure_size,
               gs->figure);  // Освобождаем память под старую фигуру.
    gs->figure =
        temp_figure;  // Назначаем временную матрицу как текущую фигуру.
  } else {
    freeMatrix(gs->figure_size, temp_figure);  // Освобождаем временную матрицу,
                                               // если вращение невозможно.
  }
}

// Прикрепление фигуры к игровому полю, если она достигла дна.
void attachFigure(GameState_t *gs) {
  bool is_game_over = checkTopLine(
      gs);  // Проверка верхней строки на наличие блоков (игра окончена?).

  // Переносим фигуру на игровое поле.
  for (int i = 0; i < gs->figure_size && !is_game_over; i++) {
    for (int j = 0; j < gs->figure_size; j++) {
      if (gs->figure[i][j] > 0) {
        gs->field[gs->y + i][gs->x + j] = gs->figure[i][j];
      }
    }
  }

  // Если игра окончена, меняем статус на GameOver.
  if (is_game_over) {
    gs->status = GameOver;
  } else {
    processFullLines(gs);  // Обрабатываем полные линии.
    gs->status = Spawn;  // Переходим к спавну новой фигуры.
  }
}

// Проверка верхней строки поля на наличие блоков для определения завершения
// игры.
bool checkTopLine(GameState_t *gs) {
  bool is_filled = false;

  // Если в верхней строке есть блок, игра считается завершенной.
  for (int j = 0; j < FIELD_M && !is_filled; j++) {
    is_filled = gs->field[0][j] > 0;
  }

  return is_filled;  // Возвращаем флаг, заполнена ли верхняя строка.
}

// Обработка полных линий: проверка, сдвиг и очистка заполненных линий.
void processFullLines(GameState_t *gs) {
  int num_full_lines = 0;

  // Проходим по каждой строке поля, начиная с нижней.
  for (int i = FIELD_N - 1; i >= 0; i--) {
    bool is_full = true;

    // Проверка, заполнена ли текущая строка.
    for (int j = 0; j < FIELD_M && is_full; j++) {
      if (gs->field[i][j] == 0) {
        is_full = false;
      }
    }

    // Если строка полная, сдвигаем все линии выше вниз и очищаем верхнюю
    // строку.
    if (is_full) {
      shiftLines(gs, i);
      fillTopLine(gs);
      num_full_lines++;  // Увеличиваем счетчик полных линий.
      i++;  // Проверяем снова ту же строку, так как сдвиг может заполнить ее
            // снова.
    }
  }

  updateScoreAndLevel(gs, num_full_lines);  // Обновляем счет и уровень на
                                            // основе количества полных линий.
}

// Сдвиг всех линий выше на одну позицию вниз.
void shiftLines(GameState_t *gs, int i) {
  for (int j = i; j > 0; j--) {
    for (int k = 0; k < FIELD_M; k++) {
      gs->field[j][k] = gs->field[j - 1][k];
    }
  }
}

// Заполнение верхней строки пустыми блоками (очистка после сдвига).
void fillTopLine(GameState_t *gs) {
  for (int j = 0; j < FIELD_M; j++) {
    gs->field[0][j] = 0;  // Очищаем верхнюю строку.
  }
}

// Обновление счета и уровня игры после очистки линий.
void updateScoreAndLevel(GameState_t *gs, int num_full_lines) {
  // Добавление очков в зависимости от количества очищенных линий.
  switch (num_full_lines) {
    case 1:
      gs->score += 100;
      break;
    case 2:
      gs->score += 300;
      break;
    case 3:
      gs->score += 700;
      break;
    case 4:
      gs->score += 1500;
      break;
    default:
      break;
  }

  // Обновляем уровень, если достигнуто нужное количество очков.
  if (gs->score >= SCORE_PER_LEVEL) {
    gs->level = gs->score / SCORE_PER_LEVEL + 1;
    // Ускоряем игру с повышением уровня.
    gs->speed = DELAY_MS - gs->level * 120;
  }

  // Победа, если уровень выше максимального.
  if (gs->level > MAX_LEVEL) gs->win = true;

  // Обновляем рекорд, если текущий счет выше рекорда.
  if (gs->score > gs->high_score) {
    gs->high_score = gs->score;  // Обновляем рекорд.
    char puth[512];
    high_score_path(puth);
    FILE *file = fopen(puth, "w");

    if (file) {
      fprintf(file, "%d", gs->score);  // Записываем новый рекорд.
      fclose(file);
    }
  }
}

// Вспомогательные функции

// Получение состояния игры (используется статическая переменная для хранения
// состояния).
GameState_t *getGameState() {
  static GameState_t
      gs;  // Статическое состояние игры (инициализируется один раз).
  return &gs;
}

// Создание матрицы для поля или фигуры с заданными размерами.
int **createMatrix(int N, int M) {
  int **result =
      (int **)malloc(N * sizeof(int *));  // Выделяем память под строки матрицы.

  if (result != NULL) {
    for (int i = 0; i < N; i++) {
      result[i] =
          (int *)calloc(M, sizeof(int));  // Выделяем память под каждый столбец.
      if (result[i] == NULL) {
        freeMatrix(i, result);  // Если память не выделена, освобождаем уже
                                // выделенные строки.
        break;
      }
    }
  }

  return result;  // Возвращаем указатель на созданную матрицу.
}

// Копирование одной матрицы в другую.
void copyMatrix(int N, int M, int **src_matrix, int **dest_matrix) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      dest_matrix[i][j] = src_matrix[i][j];  // Копируем каждое значение.
    }
  }
}

// Освобождение памяти, выделенной под матрицу.
void freeMatrix(int N, int **matrix) {
  if (matrix != NULL) {
    for (int i = 0; i < N; i++) {
      free(matrix[i]);  // Освобождаем память для каждой строки.
    }
    free(matrix);  // Освобождаем память для массива указателей.
  }

  matrix = NULL;  // Устанавливаем указатель на NULL для предотвращения
                  // дальнейшего использования.
}

// Проверка, достигает ли фигура дна или других фигур (для прикрепления).
bool figureIsAttaching(const GameState_t *gs) {
  bool is_attaching = false;

  // Проверяем каждый блок фигуры.
  for (int i = 0; i < gs->figure_size && !is_attaching; i++) {
    for (int j = 0; j < gs->figure_size && !is_attaching; j++) {
      int x = gs->x + j;
      int y = gs->y + i + 1;

      if (gs->figure[i][j] > 0 &&
          (y > FIELD_N - 1 || (y > -1 && gs->field[y][x] > 0))) {
        is_attaching = true;  // Фигура достигает дна или другого блока.
      }
    }
  }

  return is_attaching;  // Возвращаем результат проверки.
}

// Получение текущего времени в миллисекундах для работы с таймерами.
long long getTime() {
  struct timeval t;
  gettimeofday(&t, NULL);  // Получаем текущее время.
  // Преобразуем секунды и микросекунды в миллисекунды.
  return (long long)t.tv_sec * 1000 + t.tv_usec / 1000;
}

// Таймер, который возвращает true, если прошло заданное время.
bool timer(GameState_t *gs, int delay) {
  bool result = false;
  long long time = getTime();  // Получаем текущее время.

  if (time - gs->time >=
      delay) {  // Проверяем, прошло ли заданное количество миллисекунд.
    gs->time = time;  // Обновляем время.
    result = true;  // Возвращаем true, если время истекло.
  }

  return result;  // Возвращаем результат проверки таймера.
}

// Освобождение памяти, выделенной под информацию о состоянии игры.
void freeGameInfo(GameInfo_t *gi) {
  if (gi->field != NULL) {
    freeMatrix(FIELD_N, gi->field);
    gi->field = NULL;
  }
  if (gi->next != NULL) {
    freeMatrix(gi->next_size, gi->next);
    gi->next = NULL;
  }
}

void high_score_path(char *new_path) {
  // Открываем файл install_path.txt для получения пути
  FILE *path_file = fopen("install_path.txt", "r");
  char install_path[256];  // Буфер для хранения пути

  if (path_file) {
    fscanf(path_file, "%255s", install_path);  // Считываем путь из файла
    fclose(path_file);
  } else {
    // Если файл install_path.txt не найден, используем путь по умолчанию
    snprintf(install_path, sizeof(install_path), "build");
  }

  // Создаем полный путь к файлу high_score.txt и копируем его в new_path
  snprintf(new_path, 512, "%s/high_score.txt", install_path);
}