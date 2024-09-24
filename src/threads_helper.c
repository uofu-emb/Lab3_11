#include <FreeRTOS.h>
#include <semphr.h>
#include "threads_helper.h"

/**
 * This method updates the counter given in a thread safe manor using a given semaphore
 */
int updateCounter(int thread, int *counter, SemaphoreHandle_t semaphore){
    //checks if semaphore is available. If false return false.
    if (xSemaphoreTake(semaphore, 500) == pdFALSE) {
        return pdFALSE;
        }
        //if semaphore is available return true and increment counter.
        (*counter)++;
        //check the source of the function call
        if(thread == 0){
            printf("hello world from %s! Count %d\n", "main", *counter);
        }
        else{
            printf("hello world from %s! Count %d\n", "thread", *counter);
        }
        //release the semaphore
        xSemaphoreGive(semaphore);
        return pdTRUE;
    
}   