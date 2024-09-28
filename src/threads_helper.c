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

/**
 * This method attempts to create a deadlock situation
 */
void deadlock (void *args){

    //get the deadLock args
    struct DeadlockArgs *dargs = (struct DeadlockArgs *)args;
    printf("\n Starting Deadlock %c", dargs->source);
    //take the first semaphore
    xSemaphoreTake(dargs->a,portMAX_DELAY);
    printf("\n inside first semaphore source %c",dargs->source);
    dargs->counter++;
    //create a delay that should cause deadlock
    vTaskDelay(100);
    //take the second lock it should deadlock here
    xSemaphoreTake(dargs->b, portMAX_DELAY);
    printf("\n inside the second semaphore source %c",dargs->source);
    dargs->counter++;
    //release the semaphores
    xSemaphoreGive(dargs->a);
    xSemaphoreGive(dargs->b);
    vTaskSuspend(NULL);

}

int orphaned_lock(SemaphoreHandle_t semaphore, int *counter){

        if(xSemaphoreTake(semaphore, 500) == pdFALSE){
            return pdFALSE;
        }
        (*counter)++;
        if (*counter % 2) {
            return pdFALSE;
        }
        printf("Count %d\n", counter);
        xSemaphoreGive(semaphore);
        return pdTRUE;
    
}
/**
 * Fixed it so that functionality is the same but the semaphore always is given back.
 */
int unorphaned_lock(SemaphoreHandle_t semaphore, int *counter){

        if(xSemaphoreTake(semaphore, 500) == pdFALSE){
            return pdFALSE;
        }
        (*counter)++;
        if (*counter % 2) {
            xSemaphoreGive(semaphore);
            return pdFALSE;
        }
        else{
            printf("Count %d\n", counter);
            xSemaphoreGive(semaphore);
            return pdTRUE;
        }
    
}