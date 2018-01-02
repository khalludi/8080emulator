/*
 *
 * DO NOT EDIT THIS FILE. Generated by checkmk.
 * Edit the original source file "check_test.ts" instead.
 */

#include <check.h>
#include "../src/emu_shell.c"
#include <stdlib.h>
#include <stdio.h>

START_TEST(test1)
{
    ck_assert_int_eq(5, 5);
    ck_assert_str_eq("USD", "USD");
    printf("test_1: test finished!\n");
}
END_TEST

START_TEST(test2)
{
    State8080 state;

    // Store hex value into a char *
    char * buffer = "000102"; char * pos = buffer;
    unsigned char val[3];
    for(int i = 0; i < sizeof(val); i++) {
        sscanf(pos, "%2hhx", &val[count]);
        pos += 2;
    }
    
    state.memory = val;
    Emulate8080Op(&state);
}



int main(void)
{
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, test1);
    tcase_add_test(tc1_1, test2);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}