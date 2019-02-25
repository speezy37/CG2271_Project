/*
 * main.cpp
 *
 *  Created on: 25 Feb 2019
 *  Author: ChuaCY
 */

#include <Arduino.h>
#include "FreeRTOS.h"
#include "task.h"
#include "croutine.h"

void TaskLED(void *pvParameters);
void TaskSerial(void *pvParameters);
void TaskMotor(void *pvParameters);
void TaskAudio(void *pvParameters);

void setup() {
	xTaskCreate(TaskLED, (const portCHAR*) "LED", 256, NULL, 3, NULL);
	vTaskStartScheduler();
}

void loop() {

}

void TaskLED(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  pinMode(13, OUTPUT);

  while(1)
  {
    digitalWrite(13, HIGH);
    vTaskDelay( 1000 / portTICK_PERIOD_MS );
    digitalWrite(13, LOW);
    vTaskDelay( 1000 / portTICK_PERIOD_MS );
  }
}

void TaskSerial(void *pvParameters)
{
	(void) pvParameters;

	while(1)
	{

	}
}

void TaskMotor(void *pvParameters)
{
	(void) pvParameters;

	while(1)
	{

	}
}

void TaskAudio(void *pvParameters)
{
	(void) pvParameters;

	while(1)
	{

	}
}

