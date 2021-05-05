/*
 * FreeRTOS V202011.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

/******************************************************************************
 *
 * This project is provided as an example of how to create a FreeRTOS project
 * that does not need a heap.  configSUPPORT_STATIC_ALLOCATION is set to 1 to
 * allow RTOS objects to be created using statically allocated RAM, and
 * configSUPPORT_DYNAMIC_ALLOCATION is set to 0 to remove any build dependency
 * on the FreeRTOS heap.  When configSUPPORT_DYNAMIC_ALLOCATION is set to 0
 * pvPortMalloc() just equates to NULL, and calls to vPortFree() have no
 * effect.  See:
 *
 * http://www.freertos.org/a00111.html and
 * http://www.freertos.org/Static_Vs_Dynamic_Memory_Allocation.html
 *
 *******************************************************************************
 */

/* Standard includes. */
#include <stdio.h>
#include <stdlib.h>
#ifdef WIN32 
#include <conio.h>
#endif

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Standard demo includes. */
#include "StaticAllocation.h"


/*-----------------------------------------------------------*/

/* This demo only uses the standard demo tasks that use statically allocated
RAM.  A 'check' task is also created to periodically inspect the demo tasks to
ensure they are still running, and that no errors have been detected. */
static void prvStartCheckTask( void );
static void prvCheckTask( void *pvParameters );

/*-----------------------------------------------------------*/

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
