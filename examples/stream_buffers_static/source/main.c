#include <stdio.h>
#include <FreeRTOS.h>
#include <task.h>
#include <stream_buffer.h>
#include "StreamBufferInterrupt.h"
#include <stdint.h>

uint8_t ucStreamBufferStorageArea[1024];
StaticStreamBuffer_t xStreamBufferStruct;



StackType_t xProducerStack[ configMINIMAL_STACK_SIZE ];
StackType_t xReceiverStack[ configMINIMAL_STACK_SIZE ];

StaticTask_t xProducerTaskBuffer;
StaticTask_t xReceiverTaskBuffer;


void producer(void* args) {
  while(1) {
    vBasicStreamBufferSendFromISR();
    vTaskDelay(1);
  }
}
StreamBufferHandle_t xStreamBuffer = NULL;
int main(){
	xStreamBuffer = xStreamBufferCreateStatic(
	    /* The buffer length in bytes. */
		sizeof(ucStreamBufferStorageArea),
		/* The stream buffer's trigger level. */
		10,
	    ucStreamBufferStorageArea,
	    &xStreamBufferStruct
	);

	xTaskCreateStatic(
			prvReceivingTask, /* The function that implements the task. */
			"StrIntRx",	   /* Human readable name for the task. */
			configMINIMAL_STACK_SIZE,	/* Stack size (in words!). */
			NULL,			   /* Task parameter is not used. */
			tskIDLE_PRIORITY + 1, /* The priority at which the task is created. */
			xReceiverStack,
			&xReceiverTaskBuffer);		   /* No use for the task handle. */

    xTaskCreateStatic(
    		producer,
			"producer",
			configMINIMAL_STACK_SIZE,
			NULL,
    		tskIDLE_PRIORITY + 2, /* The priority at which the task is created. */
			xProducerStack,
			&xProducerTaskBuffer);
    vTaskStartScheduler();
    return 0;
}

void vApplicationIdleHook(void) {
	static unsigned long last_count = 0;
	if (xTaskGetTickCount()-last_count > 1000) {
		last_count = xTaskGetTickCount();
		const auto still_running = xIsInterruptStreamBufferDemoStillRunning();
		printf("Still Running: %d\n", still_running==pdPASS);
	}
}

