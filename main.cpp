/*
 * main.cpp
 *
 *  Created on: 25 Feb 2019
 *  Author: ChuaCY
 */

#include "main.h"

void setup() {
	initPins();
	Serial.begin(9600);
	xTaskCreate(tRedLED, "Red LED", STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(tGreenLED, "Green LED", STACK_SIZE, NULL, 1, NULL);
	//xTaskCreate(tAudio, "Audio", STACK_SIZE, NULL, 2, NULL);
	xTaskCreate(tSerial, "Serial", STACK_SIZE, NULL, 1, NULL);
	//xTaskCreate(tMotorCOntrol, "Motor Control", STACK_SIZE, NULL, 2, NULL);
	vTaskStartScheduler();
}

void loop() {

}

void initPins() {
	// LEDs
	pinMode(PIN_RLED, OUTPUT);
	pinMode(PIN_GLED1, OUTPUT);
	pinMode(PIN_GLED2, OUTPUT);
	pinMode(PIN_GLED3, OUTPUT);
	pinMode(PIN_GLED4, OUTPUT);
	pinMode(PIN_GLED5, OUTPUT);
	pinMode(PIN_GLED6, OUTPUT);
	pinMode(PIN_GLED7, OUTPUT);
	pinMode(PIN_GLED8, OUTPUT);

	// Motor
	pinMode(PIN_MOTORFRP, OUTPUT);
	pinMode(PIN_MOTORFRN, OUTPUT);
	pinMode(PIN_MOTORFLP, OUTPUT);
	pinMode(PIN_MOTORFLN, OUTPUT);
	pinMode(PIN_MOTORBRP, OUTPUT);
	pinMode(PIN_MOTORBRN, OUTPUT);
	pinMode(PIN_MOTORBLP, OUTPUT);
	pinMode(PIN_MOTORBLN, OUTPUT);

	// Audio
	pinMode(PIN_AUDIO, OUTPUT);
}

void tRedLED(void *p) {
	TickType_t xLastWakeTime = 0;
	TickType_t period;

	while(1) {
		if(moveState == Idle) {
			period = PERIOD_LED_SLOW;
		}
		else {
			period = PERIOD_LED_FAST;
		}

		digitalWrite(PIN_RLED, HIGH);
		vTaskDelayUntil(&xLastWakeTime, period );
		digitalWrite(PIN_RLED, LOW);
		vTaskDelayUntil(&xLastWakeTime, period );
	}
}

void tGreenLED(void *p) {
	TickType_t xLastWakeTime = 0;

	while(1) {
		if(moveState == Idle) {
			digitalWrite(PIN_GLED1, HIGH);
			digitalWrite(PIN_GLED1, HIGH);
			digitalWrite(PIN_GLED1, HIGH);
			digitalWrite(PIN_GLED1, HIGH);
			digitalWrite(PIN_GLED1, HIGH);
			digitalWrite(PIN_GLED1, HIGH);
			digitalWrite(PIN_GLED1, HIGH);
			digitalWrite(PIN_GLED1, HIGH);
			vTaskDelayUntil(&xLastWakeTime, PERIOD_LED_RUNNING);
		}
		else {
			digitalWrite(PIN_GLED8, LOW);
			digitalWrite(PIN_GLED1, HIGH);
			vTaskDelayUntil(&xLastWakeTime, PERIOD_LED_RUNNING);

			digitalWrite(PIN_GLED1, LOW);
			digitalWrite(PIN_GLED2, HIGH);
			vTaskDelayUntil(&xLastWakeTime, PERIOD_LED_RUNNING);

			digitalWrite(PIN_GLED2, LOW);
			digitalWrite(PIN_GLED3, HIGH);
			vTaskDelayUntil(&xLastWakeTime, PERIOD_LED_RUNNING);

			digitalWrite(PIN_GLED3, LOW);
			digitalWrite(PIN_GLED4, HIGH);
			vTaskDelayUntil(&xLastWakeTime, PERIOD_LED_RUNNING);

			digitalWrite(PIN_GLED4, LOW);
			digitalWrite(PIN_GLED5, HIGH);
			vTaskDelayUntil(&xLastWakeTime, PERIOD_LED_RUNNING);

			digitalWrite(PIN_GLED5, LOW);
			digitalWrite(PIN_GLED6, HIGH);
			vTaskDelayUntil(&xLastWakeTime, PERIOD_LED_RUNNING);

			digitalWrite(PIN_GLED6, LOW);
			digitalWrite(PIN_GLED7, HIGH);
			vTaskDelayUntil(&xLastWakeTime, PERIOD_LED_RUNNING);

			digitalWrite(PIN_GLED7, LOW);
			digitalWrite(PIN_GLED8, HIGH);
			vTaskDelayUntil(&xLastWakeTime, PERIOD_LED_RUNNING);
		}
	}
}

void tSerial(void *p) {
	while(1) {
        if (Serial.available()) {	//if there is data being received
        	if((btState == Disconnected) && (moveState == Stop)) {
        		btState = Connected;
        	}
			blueToothVal = Serial.read();

			switch(blueToothVal) {
			case CMD_CONNECTED:
				btState = Connected;
				moveState = Start;
				break;
			case CMD_OFF:
				moveState = End;
				break;
			case CMD_SONG:
				break;
			case CMD_EMPTY:
				break;
			case CMD_FORWARD:
				moveState = Forward;
				break;
			case CMD_REVERSE:
				moveState = Reverse;
				break;
			case CMD_LEFT:
				moveState = Left;
				break;
			case CMD_RIGHT:
				moveState = Right;
				break;
			default:
				moveState = Idle;
			}
		}
	}
}

void tMotorControl(void *p) {

	while(1) {
		switch(moveState) {
		case Forward:
			digitalWrite(PIN_MOTORFRP, HIGH);
			digitalWrite(PIN_MOTORFRN, LOW);
			digitalWrite(PIN_MOTORFLP, HIGH);
			digitalWrite(PIN_MOTORFLN, LOW);
			digitalWrite(PIN_MOTORBRP, HIGH);
			digitalWrite(PIN_MOTORBRN, LOW);
			digitalWrite(PIN_MOTORBLP, HIGH);
			digitalWrite(PIN_MOTORBLN, LOW);
			break;
		case Reverse:
			digitalWrite(PIN_MOTORFRP, LOW);
			digitalWrite(PIN_MOTORFRN, HIGH);
			digitalWrite(PIN_MOTORFLP, LOW);
			digitalWrite(PIN_MOTORFLN, HIGH);
			digitalWrite(PIN_MOTORBRP, LOW);
			digitalWrite(PIN_MOTORBRN, HIGH);
			digitalWrite(PIN_MOTORBLP, LOW);
			digitalWrite(PIN_MOTORBLN, HIGH);
			break;
		case Left:
			digitalWrite(PIN_MOTORFRP, HIGH);
			digitalWrite(PIN_MOTORFRN, LOW);
			digitalWrite(PIN_MOTORFLP, LOW);
			digitalWrite(PIN_MOTORFLN, HIGH);
			digitalWrite(PIN_MOTORBRP, HIGH);
			digitalWrite(PIN_MOTORBRN, LOW);
			digitalWrite(PIN_MOTORBLP, LOW);
			digitalWrite(PIN_MOTORBLN, HIGH);
			break;
		case Right:
			digitalWrite(PIN_MOTORFRP, LOW);
			digitalWrite(PIN_MOTORFRN, HIGH);
			digitalWrite(PIN_MOTORFLP, HIGH);
			digitalWrite(PIN_MOTORFLN, LOW);
			digitalWrite(PIN_MOTORBRP, LOW);
			digitalWrite(PIN_MOTORBRN, HIGH);
			digitalWrite(PIN_MOTORBLP, HIGH);
			digitalWrite(PIN_MOTORBLN, LOW);
			break;
		default:
			digitalWrite(PIN_MOTORFRP, LOW);
			digitalWrite(PIN_MOTORFRN, LOW);
			digitalWrite(PIN_MOTORFLP, LOW);
			digitalWrite(PIN_MOTORFLN, LOW);
			digitalWrite(PIN_MOTORBRP, LOW);
			digitalWrite(PIN_MOTORBRN, LOW);
			digitalWrite(PIN_MOTORBLP, LOW);
			digitalWrite(PIN_MOTORBLN, LOW);
		}
	}
}
void tAudio(void *p) {
	TickType_t xLastWakeTime = 0;
    int specialTuneBT[3] = {261, 294, 330};
	int specialTuneEnd[3] = {330, 294, 261};
	int babyShark[30] = {
	    294, 330, 392, 392, 392, 392, 392, 392, 392,
		294, 330, 392, 392, 392, 392, 392, 392, 392,
		294, 330, 392, 392, 392, 392, 392, 392, 392,
		392, 392, 370};

	while(1) {
		if (btState == Connected) {
			if (moveState == Start) {
				for(int i = 0; i < 3; i++){
					tone(PIN_AUDIO, specialTuneBT[i]);
					vTaskDelayUntil(&xLastWakeTime, 300);
					noTone(PIN_AUDIO);
					vTaskDelayUntil(&xLastWakeTime, 100);
					moveState = Idle;
				}
			}
			else if (moveState == End) {
				for(int i = 0; i < 3; i++){
					tone(PIN_AUDIO, specialTuneEnd[i]);
					vTaskDelayUntil(&xLastWakeTime, 300);
					noTone(PIN_AUDIO);
					vTaskDelayUntil(&xLastWakeTime, 100);
					btState = Disconnected;
				}
			}
			else {
				for(int i = 0; i < 30; i++) {
					tone(PIN_AUDIO, babyShark[i]);
					vTaskDelayUntil(&xLastWakeTime, 35);
					noTone(PIN_AUDIO);
					vTaskDelayUntil(&xLastWakeTime, 15);
				}
				vTaskDelayUntil(&xLastWakeTime, 500);
			}
		}
	}
}

