#ifndef BRICK_GAME_H
#define BRICK_GAME_H

#define FIELD_N 20
#define FIELD_M 10

#define KEY_ESC 27
#define KEY_SPACE 32
#define KEY_Q 113
#define KEY_Z 122

#include <stdbool.h>
#include <sys/time.h>

typedef struct {
  int **field;
  int **next;
  int figure_color;
  int next_figure_color;
  int next_size;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

#include "brick_game/tetris/backend.h"
#include "gui/cli/frontend.h"

void gameLoop();

#endif