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

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <FreeRTOS.h>
#include <task.h>
#include "StaticAllocation.h"
#include "hooks.h"

#define STACK_SIZE 200
#define TASK_COUNT
 /* good place to look if dynamic allocations aren't working as expected... */
#if 0
 void *malloc (size_t sz) { if (sz>0) errno = ENOMEM; return NULL; }
 void free(void*ptr) { }
#endif

#if 0
void* malloc (size_t size) {
  printf("Malloc called %s %s\n", __LINE__, __FILE__);
  assert(0);
  return NULL;
}
#endif
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
    // Check to see that malloc is disabled
#if 0
    auto mem = malloc(100);
    assert(mem == NULL);
#endif

    xTaskCreateStatic(task, "task1", STACK_SIZE, "task1", 5, xStack1, &xTask1Buffer);
    xTaskCreateStatic(task, "task2", STACK_SIZE, "task2", 5, xStack2, &xTask2Buffer);
    vTaskStartScheduler();
    return 0;
}
