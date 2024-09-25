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
    printf("\n The Count before update is %d\n",count);
   int result = updateCounter(1,&count,semaphore);

     printf("\n The Count after update is %d\n",count);
    //test that count happened and the count was updated.
   TEST_ASSERT_EQUAL_INT16_MESSAGE(pdTRUE,result, "updateCounter did not run when it should have");
   TEST_ASSERT_EQUAL_INT16_MESSAGE(1,count,"the counter did not update itself.");

}

/**\
 * This test creates a counter and semaphore and makes sure it does not update counter as the semaphore is not available.
 */
void test_updateCounter_blocks()
{
   SemaphoreHandle_t semaphore = xSemaphoreCreateCounting(1, 1);
   //take the semaphore
   xSemaphoreTake(semaphore,portMAX_DELAY);
   int count = 0;
    printf("\n The Count before update is %d\n",count);
   int result = updateCounter(1,&count,semaphore);
    printf("\n The Count after update is %d\n",count);
    //test that count happened and the count was updated.
   TEST_ASSERT_EQUAL_INT16_MESSAGE(pdFALSE,result, "updateCounter did run when it should not have");
   TEST_ASSERT_EQUAL_INT16_MESSAGE(0,count,"the counter did update itself when it should not have.");

}
#define A_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )
#define A_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

#define B_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )
#define B_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

void testDeadlock(){
    //create the two counters

    //create the two semaphores to deadlock
    SemaphoreHandle_t semaphore1 = xSemaphoreCreateCounting(1, 1);
    SemaphoreHandle_t semaphore2 = xSemaphoreCreateCounting(1, 1);

    //create the arguments for the two threads.
    struct DeadlockArgs a_args= {semaphore1,semaphore2,0,'a'};
    struct DeadlockArgs b_args= {semaphore2,semaphore1,0,'a'};

    //create Task handle

    TaskHandle_t a_handle, b_handle;

    xTaskCreate(deadlock,"a",A_TASK_STACK_SIZE,&a_args,A_TASK_PRIORITY,a_handle);
    xTaskCreate(deadlock,"b",B_TASK_STACK_SIZE,&b_args,B_TASK_PRIORITY,b_handle);
    
}


int main (void)
{
    stdio_init_all();
    sleep_ms(20000); // Give time for TTY to attach.
    printf("Start tests\n");
    UNITY_BEGIN();
    RUN_TEST(test_updateCounter_runs);
    RUN_TEST(test_updateCounter_blocks);
    sleep_ms(5000);
    return UNITY_END();
}
