/**
 * @file backend_tetris.h
 * @brief Логика игры "Тетрис" на языке C — генерация фигур, управление, уровни,
 * очки.
 * @ingroup TetrisGame
 * @author lioncoco
 * @version 2.0
 * @date 2025-06-27
 */

/**
 * @defgroup TetrisGame Логика игры Тетрис
 * @brief Внутренняя реализация тетриса: поведение фигур, состояние игры, уровни
 * и рекорды.
 */

#ifndef BACKEND_TETRIS_H
#define BACKEND_TETRIS_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// === Константы игры ===

#define START_X 4     ///< Стартовая позиция фигуры по X
#define START_Y (-4)  ///< Стартовая позиция фигуры по Y
#define NUM_FIGURES 7        ///< Количество типов фигур
#define MAX_LEVEL 10         ///< Максимальный уровень
#define SCORE_PER_LEVEL 600  ///< Очки для повышения уровня
#define DELAY_MS 1000  ///< Начальная задержка в миллисекундах
#define FIELD_N 20  ///< Высота игрового поля
#define FIELD_M 10  ///< Ширина игрового поля

// === Структуры данных ===

/**
 * @struct GameInfo_t
 * @brief Информация об игре для отрисовки (GUI).
 * @ingroup TetrisGame
 */
typedef struct {
  int **field;     ///< Игровое поле.
  int **next;      ///< Следующая фигура.
  int next_size;   ///< Размер следующей фигуры.
  int score;       ///< Текущий счёт.
  int high_score;  ///< Рекорд.
  int level;       ///< Текущий уровень.
  int speed;       ///< Скорость.
  int pause;       ///< Флаг паузы.
} GameInfo_t;

/**
 * @enum UserAction_t
 * @brief Возможные действия игрока.
 * @ingroup TetrisGame
 */
typedef enum {
  Start,      ///< Начать игру
  Pause,      ///< Пауза/возобновление
  Terminate,  ///< Завершить игру
  Left,       ///< Влево
  Right,      ///< Вправо
  Up,         ///< Поворот
  Down,       ///< Быстрое падение
  Action      ///< Действие (аналогично повороту)
} UserAction_t;

/**
 * @enum GameStatus_t
 * @brief Статусы состояния игры.
 * @ingroup TetrisGame
 */
typedef enum {
  Initial,    ///< Игра не началась
  Spawn,      ///< Появление новой фигуры
  Moving,     ///< Фигура в движении
  Attaching,  ///< Фигура фиксируется
  Shifting,   ///< Очистка строк
  GameOver    ///< Игра окончена
} GameStatus_t;

/**
 * @struct GameState_t
 * @brief Полное состояние игры Тетрис.
 * @ingroup TetrisGame
 */
typedef struct {
  int **field;           ///< Поле игры
  int **figure;          ///< Текущая фигура
  int figure_size;       ///< Размер текущей фигуры
  int **next_figure;     ///< Следующая фигура
  int next_figure_size;  ///< Размер следующей фигуры
  int x;                 ///< Позиция по X
  int y;                 ///< Позиция по Y
  int status;            ///< Статус игры
  int score;             ///< Счёт
  int high_score;        ///< Рекорд
  int level;             ///< Уровень
  int speed;             ///< Скорость
  bool pause;            ///< Пауза
  bool is_playing;       ///< Активна ли игра
  bool win;              ///< Победа
  long long time;        ///< Время таймера
} GameState_t;

// === Основные функции ===

/**
 * @brief Инициализация игры: состояние, поле, фигура, рекорд.
 */
void initGame();

/**
 * @brief Генерирует случайную фигуру.
 * @param[out] size Указатель на переменную, куда записывается размер фигуры.
 * @return Указатель на матрицу фигуры.
 */
int **generateFigure(int *size);

/**
 * @brief Заполняет фигуру блоками по её типу.
 * @param number Номер типа фигуры.
 * @param figure Матрица, которую нужно заполнить.
 */
void fillFigure(int number, int **figure);

/**
 * @brief Обновляет состояние и возвращает данные для GUI.
 * @param gs Указатель на состояние игры.
 * @return Информация для отрисовки.
 */
GameInfo_t updateCurrentState(GameState_t *gs);

/**
 * @brief Добавляет текущую фигуру к игровому полю.
 * @param gs Состояние игры.
 * @param field Поле для отрисовки.
 */
void updateField(const GameState_t *gs, int **field);

/**
 * @brief Обрабатывает действие игрока.
 * @param gs Состояние игры.
 * @param action Введённое действие.
 */
void userInput(GameState_t *gs, UserAction_t action);

/**
 * @brief Завершает игру и освобождает ресурсы.
 * @param gs Состояние игры.
 */
void finishGame(GameState_t *gs);

/**
 * @brief Генерирует новую фигуру и подготавливает позицию.
 * @param gs Состояние игры.
 */
void spawnFigure(GameState_t *gs);

/**
 * @brief Обрабатывает движение или действие игрока.
 * @param gs Состояние игры.
 * @param action Введённое действие.
 */
void moveFigure(GameState_t *gs, UserAction_t action);

/**
 * @brief Перемещает фигуру влево.
 * @param gs Состояние игры.
 */
void moveLeft(GameState_t *gs);

/**
 * @brief Перемещает фигуру вправо.
 * @param gs Состояние игры.
 */
void moveRight(GameState_t *gs);

/**
 * @brief Перемещает фигуру вниз.
 * @param gs Состояние игры.
 */
void moveDown(GameState_t *gs);

/**
 * @brief Вращает фигуру по часовой стрелке.
 * @param gs Состояние игры.
 */
void rotate(GameState_t *gs);

/**
 * @brief Прикрепляет фигуру к полю.
 * @param gs Состояние игры.
 */
void attachFigure(GameState_t *gs);

/**
 * @brief Проверяет, заполнена ли верхняя строка.
 * @param gs Состояние игры.
 * @return true — если заполнена, иначе false.
 */
bool checkTopLine(GameState_t *gs);

/**
 * @brief Обрабатывает полные линии: удаляет и сдвигает.
 * @param gs Состояние игры.
 */
void processFullLines(GameState_t *gs);

/**
 * @brief Сдвигает все строки выше вниз.
 * @param gs Состояние игры.
 * @param i Индекс строки, которую нужно удалить.
 */
void shiftLines(GameState_t *gs, int i);

/**
 * @brief Очищает верхнюю строку после сдвига.
 * @param gs Состояние игры.
 */
void fillTopLine(GameState_t *gs);

/**
 * @brief Обновляет очки, уровень и скорость.
 * @param gs Состояние игры.
 * @param num_full_lines Кол-во удалённых линий.
 */
void updateScoreAndLevel(GameState_t *gs, int num_full_lines);

// === Вспомогательные функции ===

/**
 * @brief Получает указатель на текущее состояние игры.
 * @return Указатель на статическое состояние.
 */
GameState_t *getGameState();

/**
 * @brief Создаёт двумерную матрицу.
 * @param N Кол-во строк.
 * @param M Кол-во столбцов.
 * @return Указатель на матрицу.
 */
int **createMatrix(int N, int M);

/**
 * @brief Копирует данные из одной матрицы в другую.
 * @param N Кол-во строк.
 * @param M Кол-во столбцов.
 * @param src_matrix Исходная матрица.
 * @param dest_matrix Целевая матрица.
 */
void copyMatrix(int N, int M, int **src_matrix, int **dest_matrix);

/**
 * @brief Освобождает память матрицы.
 * @param N Кол-во строк.
 * @param matrix Указатель на матрицу.
 */
void freeMatrix(int N, int **matrix);

/**
 * @brief Проверяет, достигла ли фигура дна или блоков.
 * @param gs Состояние игры.
 * @return true — если пора прикреплять фигуру.
 */
bool figureIsAttaching(const GameState_t *gs);

/**
 * @brief Получает текущее время в миллисекундах.
 * @return Время в миллисекундах.
 */
long long getTime();

/**
 * @brief Проверяет, истекло ли заданное время.
 * @param gs Состояние игры.
 * @param delay Интервал в мс.
 * @return true — если таймер сработал.
 */
bool timer(GameState_t *gs, int delay);

/**
 * @brief Освобождает память, выделенную под GameInfo_t.
 * @param gi Указатель на структуру.
 */
void freeGameInfo(GameInfo_t *gi);

/**
 * @brief Формирует путь к файлу с рекордом.
 * @param[out] new_path Буфер для пути.
 */
void high_score_path(char *new_path);

#endif  // BACKEND_TETRIS_H