/*
 * main.cpp
 *
 *  Created on: 25 Feb 2019
 *  Author: ChuaCY
 */
#include "main.h"

void setup() {
	Serial.begin(9600);
	xTaskCreate(TaskRedLED, "Red LED", STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(TaskGreenLED, "Green LED", STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(TaskAudio, "Audio", STACK_SIZE, NULL, 2, NULL);
	xTaskCreate(TaskSerial, "Serial", STACK_SIZE, NULL, 2, NULL);
	xTaskCreate(TaskMotor, "Motor", STACK_SIZE, NULL, 2, NULL);
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

void TaskSerial(void *p)
{
	while(1)
	{
        if (Serial.available()){	//if there is data being received
			blueToothVal = Serial.read();
		}
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
void TaskAudio(void *p)
{
	pinMode(PIN_AUDIO, OUTPUT);
    int specialTuneBT[3] = {261, 294, 330};

	int specialTuneEnd[3] = {330, 294, 261};

	int babyShark[30] = {
	    294, 330, 392, 392, 392, 392, 392, 392, 392,
		294, 330, 392, 392, 392, 392, 392, 392, 392,
		294, 330, 392, 392, 392, 392, 392, 392, 392,
		392, 392, 370};

	while(1) {
		if (blueToothVal == BT_CONNECTED){
			for(int i = 0; i < 3; i++){
				tone(PIN_AUDIO, specialTuneBT[i]);
				vTaskDelay(300);
				noTone(PIN_AUDIO);
				vTaskDelay(100);
				blueToothVal = EMPTY;
			}
		}
		else if (blueToothVal == BABY_SHARK){
			while (blueToothVal != OFF){
				for(int i = 0; i < 30; i++){
					tone(PIN_AUDIO, babyShark[i]);
					vTaskDelay(300);
					noTone(PIN_AUDIO);
					vTaskDelay(100);
				}
			}
			for(int i = 0; i < 3; i++){
				tone(PIN_AUDIO, specialTuneEnd[i]);
				vTaskDelay(300);
				noTone(PIN_AUDIO);
				vTaskDelay(100);
			}
		}
	}
}

