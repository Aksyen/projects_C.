#ifndef TETRIS_H
#define TETRIS_H

// Определение стартовой позиции для тетромино
#define START_X 4
#define START_Y (-4)

#define NUM_FIGURES 7  // Количество типов фигур
#define MAX_LEVEL 10   // Максимальный уровень игры
#define SCORE_PER_LEVEL 600  // Количество очков для повышения уровня
// Начальная задержка для падения фигуры (в миллисекундах)
#define DELAY_MS 1000

#include <math.h>
#include <stdlib.h>

// Подключение основного заголовочного файла игры, который содержит общие
// элементы игры
#include "../../brick_game.h"

// Определение действий пользователя (ввод с клавиатуры)
typedef enum {
  Start,      // Начало игры
  Pause,      // Пауза
  Terminate,  // Завершение игры
  Left,       // Движение влево
  Right,      // Движение вправо
  Up,         // Поворот фигуры
  Down,       // Ускоренное падение фигуры
  Action      // Действие (например, подтверждение)
} UserAction_t;

// Определение статусов игры
typedef enum {
  Initial,    // Инициализация игры
  Spawn,      // Спавн новой фигуры
  Moving,     // Фигура движется
  Attaching,  // Фигура прикрепляется к полю
  Shifting,   // Сдвиг фигур (после очистки линии)
  GameOver    // Игра окончена
} GameStatus_t;

// Структура, описывающая состояние игры
typedef struct {
  int **field;  // Поле игры (двумерная матрица, представляющая игровую сетку)
  int **figure;           // Текущая фигура
  int figure_size;        // Размер фигуры (например, 4x4)
  int **next_figure;      // Следующая фигура
  int next_figure_size;   // Размер следующей фигуры
  int figure_color;       // Цвет текущей фигуры
  int next_figure_color;  // Цвет следующей фигуры
  int x;       // Текущая позиция фигуры по оси X
  int y;       // Текущая позиция фигуры по оси Y
  int status;  // Текущий статус игры (например, движение или конец игры)
  int score;   // Очки
  int high_score;   // Рекордный счет
  int level;        // Уровень игры
  int speed;        // Текущая скорость игры
  bool pause;       // Игра на паузе или нет
  bool is_playing;  // Флаг, активна ли игра
  bool win;         // Победа в игре
  long long time;   // Время для различных таймеров
} GameState_t;

// Функция инициализации игры
void initGame();

// Генерация новой фигуры с возвращением указателя на матрицу фигуры
int **generateFigure(int *size, int *color);

// Заполнение фигуры номером (например, тип фигуры)
void fillFigure(int number, int **figure);

// Обновление текущего состояния игры
GameInfo_t updateCurrentState(GameState_t *gs);

// Обновление игрового поля на основе состояния игры
void updateField(const GameState_t *gs, int **field);

// Получение действия пользователя на основе нажатой клавиши
UserAction_t getUserAction(int ch);

// Обработка ввода пользователя
void userInput(GameState_t *gs, UserAction_t action);

// Завершение игры
void finishGame(GameState_t *gs);

// Спавн новой фигуры
void spawnFigure(GameState_t *gs);

// Движение фигуры в зависимости от действия пользователя
void moveFigure(GameState_t *gs, UserAction_t action);

// Движение фигуры влево
void moveLeft(GameState_t *gs);

// Движение фигуры вправо
void moveRight(GameState_t *gs);

// Движение фигуры вниз
void moveDown(GameState_t *gs);

// Вращение фигуры
void rotate(GameState_t *gs);

// Прикрепление фигуры к игровому полю (когда она достигла нижней части)
void attachFigure(GameState_t *gs);

// Проверка верхней строки на заполнение (для завершения игры)
bool checkTopLine(GameState_t *gs);

// Обработка полных линий на поле (очистка заполненных линий)
void processFullLines(GameState_t *gs);

// Сдвиг линий вниз после очистки заполненной линии
void shiftLines(GameState_t *gs, int i);

// Заполнение верхней строки после сдвига линий
void fillTopLine(GameState_t *gs);

// Обновление счета и уровня после очистки линий
void updateScoreAndLevel(GameState_t *gs, int num_full_lines);

// Вспомогательные функции

// Получение состояния игры
GameState_t *getGameState();

// Создание матрицы (например, для игрового поля или фигуры)
int **createMatrix(int N, int M);

// Копирование одной матрицы в другую
void copyMatrix(int N, int M, int **src_matrix, int **dest_matrix);

// Освобождение памяти, выделенной под матрицу
void freeMatrix(int N, int **matrix);

// Проверка, прикрепляется ли фигура (достигла ли она дна)
bool figureIsAttaching(const GameState_t *gs);

// Получение текущего времени (например, для таймеров)
long long getTime();

// Таймер для управления задержкой между движениями фигуры
bool timer(GameState_t *gs, int delay);

// Освобождение памяти, выделенной под информацию о состоянии игры
void freeGameInfo(GameInfo_t *gi);

// Возвращает путь(строку) к файлу
void high_score_path(char *new_puth);

#endif
