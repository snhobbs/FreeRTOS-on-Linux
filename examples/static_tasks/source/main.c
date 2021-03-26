/*
 * Basic example using no dynamic allocation
 *
 * See: https://www.freertos.org/xTaskCreateStatic.html
 *
 * NOTE: When supporting static tasks you have to have configSUPPORT_STATIC_ALLOCATION set to 1 in the config header
 * See: https://www.freertos.org/a00110.html#configSUPPORT_STATIC_ALLOCATION
 * A couple extra functions need to be declared to use this
 *
 *  TaskHandle_t xTaskCreateStatic( TaskFunction_t pxTaskCode,
                                 const char * const pcName,
                                 const uint32_t ulStackDepth,
                                 void * const pvParameters,
                                 UBaseType_t uxPriority,
                                 StackType_t * const puxStackBuffer,
                                 StaticTask_t * const pxTaskBuffer );
 * */

#include <stdio.h>
#include <FreeRTOS.h>
#include <task.h>

#include "StaticAllocation.h"
#include "hooks.h"
#define STACK_SIZE 200
#define TASK_COUNT
/* Structure that will hold the TCB of the task being created. */
StaticTask_t xTask1Buffer;
StaticTask_t xTask2Buffer;

/* Buffer that the task being created will use as its stack.  Note this is
an array of StackType_t variables.  The size of StackType_t is dependent on
the RTOS port. */
StackType_t xStack1[ STACK_SIZE ];
StackType_t xStack2[ STACK_SIZE ];

// TaskFunction_t
void task(void *arg){
    char *s = arg;

    while(1){
        printf("%s\n", s);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main(){
    xTaskCreateStatic(task, "task1", STACK_SIZE, "task1", 5, xStack1, &xTask1Buffer);
    xTaskCreateStatic(task, "task2", STACK_SIZE, "task2", 5, xStack2, &xTask2Buffer);
    vTaskStartScheduler();
}
