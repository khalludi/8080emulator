#include <check.h>
#include <stdio.h>
#include <stdlib.h>

START_TEST (test_1)
{
  /* unit test code */
    ck_assert_int_eq(4, 5);
    ck_assert_str_eq("USD", "USD");
    printf("test_1: test finished!\n");
}
END_TEST

int main(void)
{
    test_1;
    return 0;
}
