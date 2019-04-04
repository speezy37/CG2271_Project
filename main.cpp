/*
 * main.cpp
 *
 *  Created on: 25 Feb 2019
 *  Author: ChuaCY
 */
#include "main.h"

void setup() {
	xTaskCreate(TaskRedLED, "Red LED", STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(TaskGreenLED, "Green LED", STACK_SIZE, NULL, 1, NULL);
	vTaskStartScheduler();
}

void loop() {

}

void TaskRedLED(void *p) {
  pinMode(PIN_REDLED, OUTPUT);
  TickType_t xLastWakeTime = xTaskGetTickCount();
  TickType_t period;

  while(1) {
	if(moveState == Idle) {
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

void TaskGreenLED(void *p) {
	pinMode(PIN_GREENLED1, OUTPUT);
	pinMode(PIN_GREENLED2, OUTPUT);
	pinMode(PIN_GREENLED3, OUTPUT);
	pinMode(PIN_GREENLED4, OUTPUT);
	pinMode(PIN_GREENLED5, OUTPUT);
	pinMode(PIN_GREENLED6, OUTPUT);
	pinMode(PIN_GREENLED7, OUTPUT);
	pinMode(PIN_GREENLED8, OUTPUT);

	while(1) {

	}
}

void TaskSerial(void *p) {
	pinMode(PIN_RX, INPUT);
	pinMode(PIN_TX, OUTPUT);
	while(1)
	{

	}
}

void TaskMotor(void *p) {
	pinMode(PIN_MOTORFR, OUTPUT);
	pinMode(PIN_MOTORFL, OUTPUT);
	pinMode(PIN_MOTORBR, OUTPUT);
	pinMode(PIN_MOTORBL, OUTPUT);
	while(1) {
		switch(moveState) {
		case Idle:
			digitalWrite(PIN_MOTORFR, LOW);
			digitalWrite(PIN_MOTORFL, LOW);
			digitalWrite(PIN_MOTORBR, LOW);
			digitalWrite(PIN_MOTORBL, LOW);
			break;
		case Forward:
			digitalWrite(PIN_MOTORFR, HIGH);
			digitalWrite(PIN_MOTORFL, HIGH);
			digitalWrite(PIN_MOTORBR, HIGH);
			digitalWrite(PIN_MOTORBL, HIGH);
			break;
		case Reverse:
			digitalWrite(PIN_MOTORFR, LOW);
			digitalWrite(PIN_MOTORFL, LOW);
			digitalWrite(PIN_MOTORBR, LOW);
			digitalWrite(PIN_MOTORBL, LOW);
			break;
		case Left:
			digitalWrite(PIN_MOTORFR, HIGH);
			digitalWrite(PIN_MOTORFL, LOW);
			digitalWrite(PIN_MOTORBR, HIGH);
			digitalWrite(PIN_MOTORBL, LOW);
			break;
		case Right:
			digitalWrite(PIN_MOTORFR, LOW);
			digitalWrite(PIN_MOTORFL, HIGH);
			digitalWrite(PIN_MOTORBR, LOW);
			digitalWrite(PIN_MOTORBL, HIGH);
			break;
		default:
			digitalWrite(PIN_MOTORFR, LOW);
			digitalWrite(PIN_MOTORFL, LOW);
			digitalWrite(PIN_MOTORBR, LOW);
			digitalWrite(PIN_MOTORBL, LOW);
		}
	}
}

void TaskAudio(void *p) {
	while(1) {

	}
}

