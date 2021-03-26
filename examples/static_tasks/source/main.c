/* Standard includes. */
#include <stdio.h>
#include <stdlib.h>

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Standard demo includes. */
#include "StaticAllocation.h"
#include "hooks.h"

int main( void )
{
	/* This demo has configSUPPORT_STATIC_ALLOCATION set to 1 and
	configSUPPORT_DYNAMIC_ALLOCATION set to 0, so the only standard temo tasks
	created are the ones that only use static allocation.  This allow the
	application to be built without including a FreeRTOS heap file (without one
	of the heap files described on http://www.freertos.org/a00111.html */
	vStartStaticallyAllocatedTasks();

	/* Start a task that periodically inspects the tasks created by
	vStartStaticallyAllocatedTasks() to ensure they are still running, and not
	reporting any errors. */
	prvStartCheckTask();

	/* Start the scheduler so the demo tasks start to execute. */
	vTaskStartScheduler();

	/* vTaskStartScheduler() would only return if RAM required by the Idle and
	Timer tasks could not be allocated.  As this demo uses statically allocated
	RAM only, there are no allocations that could fail, and
	vTaskStartScheduler() cannot return - so there is no need to put the normal
	infinite loop after the call to vTaskStartScheduler(). */

	return 0;
}
/*-----------------------------------------------------------*/

static void prvStartCheckTask( void )
{
/* Allocate the data structure that will hold the task's TCB.  NOTE:  This is
declared static so it still exists after this function has returned. */
static StaticTask_t xCheckTask;

/* Allocate the stack that will be used by the task.  NOTE:  This is declared
static so it still exists after this function has returned. */
static StackType_t ucTaskStack[ configMINIMAL_STACK_SIZE * sizeof( StackType_t ) ];

	/* Create the task, which will use the RAM allocated by the linker to the
	variables declared in this function. */
	xTaskCreateStatic( prvCheckTask, "Check", configMINIMAL_STACK_SIZE, NULL, configMAX_PRIORITIES - 1, ucTaskStack, &xCheckTask );
}
/*-----------------------------------------------------------*/

static void prvCheckTask( void *pvParameters )
{
const TickType_t xCycleFrequency = pdMS_TO_TICKS( 2500UL );
static char *pcStatusMessage = "No errors";

	/* Just to remove compiler warning. */
	( void ) pvParameters;

	for( ;; )
	{
		/* Place this task in the blocked state until it is time to run again. */
		vTaskDelay( xCycleFrequency );

		/* Check the tasks that use static allocation are still executing. */
		if( xAreStaticAllocationTasksStillRunning() != pdPASS )
		{
			pcStatusMessage = "Error: Static allocation";
		}

		/* This is the only task that uses stdout so its ok to call printf()
		directly. */
		printf( "%s - tick count %d - number of tasks executing %d\r\n",
													pcStatusMessage,
													xTaskGetTickCount(),
													uxTaskGetNumberOfTasks() );
	}
}
