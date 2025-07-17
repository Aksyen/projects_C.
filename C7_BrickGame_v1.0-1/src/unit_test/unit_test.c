#include "unit_test.h"

START_TEST(init_1) {
  initGame();
  GameState_t *gs = getGameState();
  GameInfo_t gi = updateCurrentState(gs);

  ck_assert_int_eq(gs->score, 0);

  finishGame(gs);
  freeGameInfo(&gi);
}
END_TEST

START_TEST(init_2) {
  initGame();
  GameState_t *gs = getGameState();
  GameInfo_t gi = updateCurrentState(gs);

  ck_assert_int_eq(gs->level, 1);

  finishGame(gs);
  freeGameInfo(&gi);
}
END_TEST

START_TEST(init_3) {
  initGame();
  GameState_t *gs = getGameState();
  GameInfo_t gi = updateCurrentState(gs);

  ck_assert_int_eq(gs->pause, false);

  finishGame(gs);
  freeGameInfo(&gi);
}
END_TEST

START_TEST(init_4) {
  initGame();
  GameState_t *gs = getGameState();
  GameInfo_t gi = updateCurrentState(gs);

  userInput(gs, getUserAction(KEY_Q));
  ck_assert_int_eq(gs->is_playing, false);

  freeGameInfo(&gi);
}
END_TEST

START_TEST(start_1) {
  initGame();
  GameState_t *gs = getGameState();
  GameInfo_t gi = updateCurrentState(gs);

  userInput(gs, getUserAction(KEY_ENTER));
  ck_assert_int_eq(gs->status, Spawn);

  finishGame(gs);
  freeGameInfo(&gi);
}
END_TEST

START_TEST(spawn_1) {
  initGame();
  GameState_t *gs = getGameState();
  GameInfo_t gi = updateCurrentState(gs);
  ;

  userInput(gs, getUserAction(KEY_ENTER));
  userInput(gs, getUserAction(KEY_Q));
  ck_assert_int_eq(gs->is_playing, false);

  freeGameInfo(&gi);
}
END_TEST

START_TEST(spawn_2) {
  initGame();
  GameState_t *gs = getGameState();
  GameInfo_t gi = updateCurrentState(gs);

  userInput(gs, getUserAction(KEY_ENTER));
  userInput(gs, getUserAction(ERR));
  ck_assert_int_eq(gs->status, Moving);

  finishGame(gs);
  freeGameInfo(&gi);
}
END_TEST

START_TEST(moving_left) {
  initGame();
  GameState_t *gs = getGameState();
  GameInfo_t gi = updateCurrentState(gs);

  userInput(gs, getUserAction(KEY_ENTER));
  userInput(gs, getUserAction(ERR));
  userInput(gs, getUserAction(KEY_LEFT));
  ck_assert_int_eq(gs->pause, false);
  ck_assert_int_eq(gs->status, Moving);

  finishGame(gs);
  freeGameInfo(&gi);
}
END_TEST

START_TEST(moving_right) {
  initGame();
  GameState_t *gs = getGameState();
  GameInfo_t gi = updateCurrentState(gs);

  userInput(gs, getUserAction(KEY_ENTER));
  userInput(gs, getUserAction(ERR));
  userInput(gs, getUserAction(KEY_RIGHT));
  ck_assert_int_eq(gs->pause, false);
  ck_assert_int_eq(gs->status, Moving);

  finishGame(gs);
  freeGameInfo(&gi);
}
END_TEST

START_TEST(moving_down) {
  initGame();
  GameState_t *gs = getGameState();
  GameInfo_t gi = updateCurrentState(gs);

  userInput(gs, getUserAction(KEY_ENTER));
  userInput(gs, getUserAction(ERR));
  userInput(gs, getUserAction(KEY_DOWN));
  ck_assert_int_eq(gs->pause, false);
  ck_assert_int_eq(gs->status, Moving);

  finishGame(gs);
  freeGameInfo(&gi);
}
END_TEST

START_TEST(moving_action) {
  initGame();
  GameState_t *gs = getGameState();
  GameInfo_t gi = updateCurrentState(gs);

  userInput(gs, getUserAction(KEY_ENTER));
  userInput(gs, getUserAction(ERR));
  userInput(gs, getUserAction(KEY_Z));
  ck_assert_int_eq(gs->pause, false);
  ck_assert_int_eq(gs->status, Moving);

  finishGame(gs);
  freeGameInfo(&gi);
}
END_TEST

START_TEST(moving_up) {
  initGame();
  GameState_t *gs = getGameState();
  GameInfo_t gi = updateCurrentState(gs);

  userInput(gs, getUserAction(KEY_ENTER));
  userInput(gs, getUserAction(ERR));
  userInput(gs, getUserAction(KEY_UP));
  ck_assert_int_eq(gs->pause, false);
  ck_assert_int_eq(gs->status, Moving);

  finishGame(gs);
  freeGameInfo(&gi);
}
END_TEST

START_TEST(moving_pause) {
  initGame();
  GameState_t *gs = getGameState();
  GameInfo_t gi = updateCurrentState(gs);

  userInput(gs, getUserAction(KEY_ENTER));
  userInput(gs, getUserAction(ERR));
  userInput(gs, getUserAction(KEY_SPACE));
  ck_assert_int_eq(gs->pause, true);
  ck_assert_int_eq(gs->status, Moving);

  finishGame(gs);
  freeGameInfo(&gi);
}
END_TEST

START_TEST(moving_terminate) {
  initGame();
  GameState_t *gs = getGameState();
  GameInfo_t gi = updateCurrentState(gs);

  userInput(gs, getUserAction(KEY_ENTER));
  userInput(gs, getUserAction(ERR));
  userInput(gs, getUserAction(KEY_Q));
  ck_assert_int_eq(gs->is_playing, false);
  ck_assert_int_eq(gs->status, Moving);

  freeGameInfo(&gi);
}
END_TEST

START_TEST(attaching_1) {
  initGame();
  GameState_t *gs = getGameState();
  GameInfo_t gi = updateCurrentState(gs);

  userInput(gs, getUserAction(KEY_ENTER));
  userInput(gs, getUserAction(ERR));

  while (gs->status != Attaching) {
    userInput(gs, getUserAction(KEY_DOWN));
  }
  userInput(gs, getUserAction(ERR));

  ck_assert_int_eq(gs->status, Spawn);

  finishGame(gs);
  freeGameInfo(&gi);
}
END_TEST

START_TEST(gameover_1) {
  initGame();
  GameState_t *gs = getGameState();
  GameInfo_t gi = updateCurrentState(gs);

  userInput(gs, getUserAction(KEY_ENTER));
  userInput(gs, getUserAction(ERR));

  while (gs->status != GameOver) {
    userInput(gs, getUserAction(KEY_DOWN));
  }
  userInput(gs, getUserAction(ERR));

  ck_assert_int_eq(gs->is_playing, true);
  ck_assert_int_eq(gs->status, GameOver);

  freeGameInfo(&gi);
}
END_TEST

Suite *tetris_suite() {
  Suite *s = suite_create("tetris_suite");
  TCase *tc = tcase_create("tetris_tc");

  tcase_add_test(tc, init_1);
  tcase_add_test(tc, init_2);
  tcase_add_test(tc, init_3);
  tcase_add_test(tc, init_4);
  tcase_add_test(tc, start_1);
  tcase_add_test(tc, spawn_1);
  tcase_add_test(tc, spawn_2);
  tcase_add_test(tc, moving_left);
  tcase_add_test(tc, moving_right);
  tcase_add_test(tc, moving_down);
  tcase_add_test(tc, moving_action);
  tcase_add_test(tc, moving_up);
  tcase_add_test(tc, moving_pause);
  tcase_add_test(tc, moving_terminate);
  tcase_add_test(tc, attaching_1);
  tcase_add_test(tc, gameover_1);

  suite_add_tcase(s, tc);

  return s;
}

int main(void) {
  int failed = 0;
  Suite *s21_tetris_test = tetris_suite();

  SRunner *sr = srunner_create(s21_tetris_test);

  srunner_set_fork_status(sr, CK_FORK);
  srunner_run_all(sr, CK_NORMAL);

  failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  if (failed)
    printf("\033[0;41m========= TESTS FAILED: %d =========\033[0m\n", failed);
  else
    printf("\033[0;32m========= TESTS SUCCESS: =========\033[0m\n");

  return 0;
}