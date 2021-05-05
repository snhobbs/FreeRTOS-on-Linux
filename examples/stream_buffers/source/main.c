#include <stdio.h>
#include <FreeRTOS.h>
#include <task.h>
#include "StreamBufferInterrupt.h"
#include <stdint.h>

void producer(void* args) {
  while(1) {
    vBasicStreamBufferSendFromISR();
    vTaskDelay(1);
  }
}

int main(){
    vStartStreamBufferInterruptDemo();
    xTaskCreate(producer, "producer", configMINIMAL_STACK_SIZE, NULL,
				 tskIDLE_PRIORITY + 1, /* The priority at which the task is created. */
        NULL);
    vTaskStartScheduler();
}

void vApplicationIdleHook(void) {
	static unsigned long last_count = 0;
	if (xTaskGetTickCount()-last_count > 1000) {
		last_count = xTaskGetTickCount();
		const auto still_running = xIsInterruptStreamBufferDemoStillRunning();
		printf("Still Running: %d\n", still_running==pdPASS);
	}
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
