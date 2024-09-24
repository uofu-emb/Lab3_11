#include <FreeRTOS.h>
#include <semphr.h>
#include "threads_helper.h"

int updateCounter(int thread, int *counter, SemaphoreHandle_t semaphore){
    if (xSemaphoreTake(semaphore, 500) == pdFALSE) {
        return pdFALSE;
        }

        (*counter)++;

        if(thread == 0){
            printf("hello world from %s! Count %d\n", "main", *counter);
        }
        else{
            printf("hello world from %s! Count %d\n", "thread", *counter);
        }
        
        xSemaphoreGive(semaphore);
        return pdTRUE;
    
}   