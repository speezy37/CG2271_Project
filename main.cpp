/*
 * main.cpp
 *
 *  Created on: 25 Feb 2019
 *  Author: ChuaCY
 */
#include "main.h"

void setup() {
    Serial.begin(9600);
    pinMode(PIN_AUDIO, OUTPUT);
}

void loop() {
    xTaskCreate(TaskRedLED, "redLED", STACK_SIZE, NULL, 2, NULL);
//  xTaskCreate(TaskGreenLED(), "greenLED", STACK_SIZE, NULL, 2, NULL);
	xTaskCreate(TaskAudio, "Audio", STACK_SIZE, NULL, 2, NULL);
	xTaskCreate(TaskSerial, "Serial", STACK_SIZE, NULL, 2, NULL);
	xTaskCreate(TaskMotor, "Motor", STACK_SIZE, NULL, 2, NULL);
	vTaskStartScheduler();
}

void TaskRedLED(void *p)  // This is a task.
{
  pinMode(PIN_REDLED, OUTPUT);
  TickType_t xLastWakeTime = xTaskGetTickCount();
  TickType_t period;

  while(1)
  {
    if (blueToothVal == BT_CONNECTED){	//BT connection established
        digitalWrite(PIN_REDLED, HIGH);
        vTaskDelay(500);
        digitalWrite(PIN_REDLED, LOW);
        vTaskDelay(500);
        digitalWrite(PIN_REDLED, HIGH);
        vTaskDelay(500);
        digitalWrite(PIN_REDLED, LOW);
        vTaskDelay(500);
        blueToothVal = EMPTY;
    }

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
        if (Serial.available()){	//if there is data being received
			blueToothVal = Serial.read();
		}
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

