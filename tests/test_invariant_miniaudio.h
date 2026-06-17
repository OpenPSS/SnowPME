#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <setjmp.h>

static jmp_buf jump_buffer;
static int segfault_caught = 0;

void segfault_handler(int sig) {
    segfault_caught = 1;
    longjmp(jump_buffer, 1);
}

START_TEST(test_vsprintf_buffer_overflow_protection)
{
    // Invariant: Buffer reads never exceed declared length; oversized format strings
    // must not cause out-of-bounds access or crash
    
    const char *payloads[] = {
        "Valid short format: %s",
        "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
        "%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x",
        "%n%n%n%n%n%n%n%n%n%n",
        "%.10000d"
    };
    int num_payloads = sizeof(payloads) / sizeof(payloads[0]);
    
    signal(SIGSEGV, segfault_handler);
    
    for (int i = 0; i < num_payloads; i++) {
        segfault_caught = 0;
        
        if (setjmp(jump_buffer) == 0) {
            char buffer[256];
            va_list args;
            va_start(args, payloads[i]);
            vsnprintf(buffer, sizeof(buffer), payloads[i], args);
            va_end(args);
            
            ck_assert_int_eq(segfault_caught, 0);
            ck_assert(strlen(buffer) < sizeof(buffer));
        } else {
            ck_abort_msg("Segmentation fault detected on payload");
        }
    }
    
    signal(SIGSEGV, SIG_DFL);
}
END_TEST

Suite *security_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Security");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_vsprintf_buffer_overflow_protection);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = security_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}