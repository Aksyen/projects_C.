#include <check.h>

#include "stack.h"

START_TEST(test_stack_create_and_is_empty) {
  Stack* s = stack_create();
  ck_assert_ptr_nonnull(s);
  ck_assert(empty_stack(s) == true);
  destroy_stack(s);
}
END_TEST

START_TEST(test_stack_push_and_top) {
  Stack* s = stack_create();
  push_stack(s, 42);
  ck_assert(empty_stack(s) == false);
  ck_assert_int_eq(top_stack(s), 42);
  destroy_stack(s);
}
END_TEST

START_TEST(test_stack_push_and_pop) {
  Stack* s = stack_create();
  push_stack(s, 1);
  push_stack(s, 2);
  ck_assert_int_eq(pop_stack(s), 2);
  ck_assert_int_eq(pop_stack(s), 1);
  ck_assert(empty_stack(s) == true);
  destroy_stack(s);
}
END_TEST

Suite* stack_suite(void) {
  Suite* s = suite_create("Stack");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_stack_create_and_is_empty);
  tcase_add_test(tc_core, test_stack_push_and_top);
  tcase_add_test(tc_core, test_stack_push_and_pop);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int failed;
  Suite* s = stack_suite();
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
