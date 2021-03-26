#include <stdio.h>
#include <FreeRTOS.h>
#include <task.h>

void task(void *arg){
    char *s = arg;

    while(1){
        printf("%s\n", s);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main(){
    xTaskCreate(task, "task1", 32, "task1", 5, NULL);
    xTaskCreate(task, "task2", 32, "task2", 5, NULL);
    vTaskStartScheduler();
}

void vAssertCalled( unsigned long ulLine, const char * const pcFileName )
{
    printf("ASSERT: %s : %d\n", pcFileName, (int)ulLine);
    while(1);
}

void vApplicationMallocFailedHook(void)
{
    while(1);
}
