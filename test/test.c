#include <stdio.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <unity.h>
#include "unity_config.h"
#include "threads_helper.h"

void setUp(void) {}

void tearDown(void) {}

/**\
 * This test creates a counter and semaphore and makes sure it updates counter.
 */
void test_updateCounter_runs()
{
   SemaphoreHandle_t semaphore = xSemaphoreCreateCounting(1, 1);
   int count = 0;
   int result = updateCounter(1,&count,semaphore);
    //test that count happened and the count was updated.
   TEST_ASSERT_EQUAL_INT16_MESSAGE(pdTRUE,result, "updateCounter did not run when it should have");
   TEST_ASSERT_EQUAL_INT16_MESSAGE(1,count,"the counter did not update itself.");

}


int main (void)
{
    stdio_init_all();
    sleep_ms(10000); // Give time for TTY to attach.
    printf("Start tests\n");
    UNITY_BEGIN();
    RUN_TEST(test_updateCounter_runs);
    sleep_ms(5000);
    return UNITY_END();
}
