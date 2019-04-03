/*
 * main.cpp
 *
 *  Created on: 25 Feb 2019
 *  Author: ChuaCY
 */
#include "main.h"

void setup() {
	xTaskCreate(TaskRedLED, "LED", STACK_SIZE, NULL, 1, NULL);
	vTaskStartScheduler();
}

void loop() {

}

void TaskRedLED(void *p)  // This is a task.
{
  pinMode(PIN_REDLED, OUTPUT);
  TickType_t xLastWakeTime = xTaskGetTickCount();
  TickType_t period;

  while(1)
  {

	if(moveState == Stationary) {
		period = 250;
	}
	else {
		period = 500;
	}

    digitalWrite(PIN_REDLED, HIGH);
    vTaskDelayUntil(&xLastWakeTime, period );
    digitalWrite(PIN_REDLED, LOW);
    vTaskDelayUntil(&xLastWakeTime, period );
  }
}

void TaskSerial(void *p)
{
	while(1)
	{

	}
}

void TaskMotor(void *p)
{
	while(1)
	{

	}
}

void TaskAudio(void *p)
{
	while(1)
	{

	}
}

