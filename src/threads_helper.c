#include <FreeRTOS.h>
#include <semphr.h>
#include "threads_helper.h"

int updateCounter(int *thread, int *counter, SemaphoreHandle_t semaphore){
    if (xsemaphoreTake(semaphore, portMAX_DELAY) == pdTRUE) {
        *counter++;

        
    }
    return 0;
}   