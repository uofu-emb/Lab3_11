#pragma once

#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>
#include <pico/stdlib.h>
#include <pico/multicore.h>
#include <pico/cyw43_arch.h>

int updateCounter(int thread, int *counter, SemaphoreHandle_t semaphore);

void deadlock(void *args);

int orphaned_lock(SemaphoreHandle_t semaphore, int *counter);
int unorphaned_lock(SemaphoreHandle_t semaphore, int *counter);

struct DeadlockArgs {
    SemaphoreHandle_t a;
    SemaphoreHandle_t b;
    int counter;
    char source;
};