#include <check.h>

#include "queue.h"

START_TEST(test_queue_create_and_is_empty) {
  Queue* q = queue_create();
  ck_assert_ptr_nonnull(q);
  ck_assert(empty_queue(q) == true);
  destroy_queue(q);
}
END_TEST

START_TEST(test_queue_push_front_back) {
  Queue* q = queue_create();
  push_queue(q, 10);
  ck_assert_int_eq(front_queue(q), 10);
  ck_assert_int_eq(back_queue(q), 10);
  push_queue(q, 20);
  ck_assert_int_eq(front_queue(q), 10);
  ck_assert_int_eq(back_queue(q), 20);
  destroy_queue(q);
}
END_TEST

START_TEST(test_queue_push_and_pop) {
  Queue* q = queue_create();
  push_queue(q, 1);
  push_queue(q, 2);
  push_queue(q, 3);
  ck_assert_int_eq(pop_queue(q), 1);
  ck_assert_int_eq(pop_queue(q), 2);
  ck_assert_int_eq(pop_queue(q), 3);
  ck_assert(empty_queue(q) == true);
  destroy_queue(q);
}
END_TEST

Suite* queue_suite(void) {
  Suite* s = suite_create("Queue");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_queue_create_and_is_empty);
  tcase_add_test(tc_core, test_queue_push_front_back);
  tcase_add_test(tc_core, test_queue_push_and_pop);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int failed;
  Suite* s = queue_suite();
  SRunner* sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  const char* red = "\033[1;91m";
  const char* green = "\033[1;32m";
  printf("=========%s FAILED \033[0m: %d =========\n", failed ? red : green,
         failed);
  return (failed == 0) ? 0 : 1;
}
