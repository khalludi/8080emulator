/*
 * DO NOT EDIT THIS FILE. Generated by checkmk.
 * Edit the original source file "diff_test.check" instead.
 */

#include <check.h>

#line 1 "diff_test.check"
#include "emu_shell.h"
#include <stdlib.h>
#include <stdio.h>

START_TEST(second_test)
{
#line 6
    State8080* state = malloc(64001);

    // Store hex value into a char *
    char * buffer = "000102"; char * pos = buffer;
    unsigned char val[3];
    for(int i = 0; i < sizeof(val); i++) {
        sscanf(pos, "%2hhx", &val[i]);
        pos += 2;
    }

    state->memory = val;
    Emulate8080Op(state);

}
END_TEST

START_TEST(mov_d_to_a)
{
#line 20
    State8080* state = malloc(64001);

    // Store hex value into a char *
    char * buffer = "7a"; char * pos = buffer;
    unsigned char val[1];
    for(int i = 0; i < sizeof(val); i++) {
        sscanf(pos, "%2hhx", &val[i]);
        pos += 2;
    }

    state->memory = val;
    state->d = 0x11;
    Emulate8080Op(state);

    ck_assert_uint_eq(state->a, 0x11);

}
END_TEST

START_TEST(nop_check_00)
{
#line 37
    State8080* state = malloc(64001);

    // Store hex value into a char *
    char * buffer = "00"; char * pos = buffer;
    unsigned char val[1];
    for(int i = 0; i < sizeof(val); i++) {
        sscanf(pos, "%2hhx", &val[i]);
        pos += 2;
    }

    state->memory = val;
    state->sp = 0xf000;
    Emulate8080Op(state);

    ck_assert_uint_eq(state->a, 0x00);
    ck_assert_uint_eq(state->b, 0x00);
    ck_assert_uint_eq(state->c, 0x00);
    ck_assert_uint_eq(state->d, 0x00);
    ck_assert_uint_eq(state->e, 0x00);
    ck_assert_uint_eq(state->h, 0x00);
    ck_assert_uint_eq(state->l, 0x00);
    ck_assert_uint_eq(state->sp, 0xf000);
    ck_assert_uint_eq(state->pc, 0x01);
    ck_assert_uint_eq(state->cc.z, 0x00);
    ck_assert_uint_eq(state->cc.s, 0x00);
    ck_assert_uint_eq(state->cc.p, 0x00);
    ck_assert_uint_eq(state->cc.cy, 0x00);
    ck_assert_uint_eq(state->cc.ac, 0x00);
    ck_assert_uint_eq(state->cc.pad, 0x00);

    free(state);

}
END_TEST

START_TEST(lxi_b_01)
{
#line 70
    State8080* state = malloc(64001);

    // Store hex value into a char *
    char * buffer = "01abcdef"; char * pos = buffer;
    unsigned char val[4];
    for(int i = 0; i < sizeof(val); i++) {
        sscanf(pos, "%2hhx", &val[i]);
        pos += 2;
    }

    state->memory = val;
    state->sp = 0xf000;
    Emulate8080Op(state);

    ck_assert_uint_eq(state->memory[state->pc], 0xef);
    ck_assert_uint_eq(state->a, 0x00);
    ck_assert_uint_eq(state->b, 0xcd);
    ck_assert_uint_eq(state->c, 0xab);
    ck_assert_uint_eq(state->d, 0x00);
    ck_assert_uint_eq(state->e, 0x00);
    ck_assert_uint_eq(state->h, 0x00);
    ck_assert_uint_eq(state->l, 0x00);
    ck_assert_uint_eq(state->sp, 0xf000);
    ck_assert_uint_eq(state->pc, 0x03);
    ck_assert_uint_eq(state->cc.z, 0x00);
    ck_assert_uint_eq(state->cc.s, 0x00);
    ck_assert_uint_eq(state->cc.p, 0x00);
    ck_assert_uint_eq(state->cc.cy, 0x00);
    ck_assert_uint_eq(state->cc.ac, 0x00);
    ck_assert_uint_eq(state->cc.pad, 0x00);

    free(state);
}
END_TEST

int main(void)
{
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, second_test);
    tcase_add_test(tc1_1, mov_d_to_a);
    tcase_add_test(tc1_1, nop_check_00);
    tcase_add_test(tc1_1, lxi_b_01);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
