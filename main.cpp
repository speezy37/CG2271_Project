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
	xTaskCreate(tMotorControl, "Motor Control", STACK_SIZE, NULL, 2, NULL);
	xTaskCreate(tAudio, "Audio", STACK_SIZE, NULL, 3, NULL);
	xTaskCreate(tSerial, "Serial", STACK_SIZE, NULL, 4, NULL);
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
	digitalWrite(PIN_RLED, HIGH);
	digitalWrite(PIN_GLED1, HIGH);
	digitalWrite(PIN_GLED2, HIGH);
	digitalWrite(PIN_GLED3, HIGH);
	digitalWrite(PIN_GLED4, HIGH);
	digitalWrite(PIN_GLED5, HIGH);
	digitalWrite(PIN_GLED6, HIGH);
	digitalWrite(PIN_GLED7, HIGH);
	digitalWrite(PIN_GLED8, HIGH);

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
		if (moveState == Disconnect) {
			digitalWrite(PIN_RLED, HIGH);
			vTaskDelayUntil(&xLastWakeTime, PERIOD_LED_RUNNING);
		}
		else {
			if ((moveState == Idle) || (moveState == Start) || (moveState == End) || (moveState == Connect)) {
				period = PERIOD_LED_SLOW;
			}
			else {
				period = PERIOD_LED_FAST;
			}

			digitalWrite(PIN_RLED, HIGH);
			vTaskDelayUntil(&xLastWakeTime, period);
			digitalWrite(PIN_RLED, LOW);
			vTaskDelayUntil(&xLastWakeTime, period);
		}
	}
}

void tGreenLED(void *p) {
	TickType_t xLastWakeTime = xTaskGetTickCount();

	while (1) {
		if(moveState == Disconnect) {
			digitalWrite(PIN_GLED1, HIGH);
			digitalWrite(PIN_GLED2, HIGH);
			digitalWrite(PIN_GLED3, HIGH);
			digitalWrite(PIN_GLED4, HIGH);
			digitalWrite(PIN_GLED5, HIGH);
			digitalWrite(PIN_GLED6, HIGH);
			digitalWrite(PIN_GLED7, HIGH);
			digitalWrite(PIN_GLED8, HIGH);
			vTaskDelayUntil(&xLastWakeTime, PERIOD_LED_RUNNING);
		}
		else if ((moveState == Idle) || (moveState == Start) || (moveState == End)) {
			digitalWrite(PIN_GLED1, LOW);
			digitalWrite(PIN_GLED2, LOW);
			digitalWrite(PIN_GLED3, LOW);
			digitalWrite(PIN_GLED4, LOW);
			digitalWrite(PIN_GLED5, LOW);
			digitalWrite(PIN_GLED6, LOW);
			digitalWrite(PIN_GLED7, LOW);
			digitalWrite(PIN_GLED8, LOW);
			vTaskDelayUntil(&xLastWakeTime, PERIOD_LED_RUNNING);
		}
		else if (moveState == Connect) {
			for (int i=0; i<2; i++) {
				digitalWrite(PIN_GLED1, LOW);
				digitalWrite(PIN_GLED2, LOW);
				digitalWrite(PIN_GLED3, LOW);
				digitalWrite(PIN_GLED4, LOW);
				digitalWrite(PIN_GLED5, LOW);
				digitalWrite(PIN_GLED6, LOW);
				digitalWrite(PIN_GLED7, LOW);
				digitalWrite(PIN_GLED8, LOW);
				vTaskDelayUntil(&xLastWakeTime, PERIOD_LED_SLOW);

				digitalWrite(PIN_GLED1, HIGH);
				digitalWrite(PIN_GLED2, HIGH);
				digitalWrite(PIN_GLED3, HIGH);
				digitalWrite(PIN_GLED4, HIGH);
				digitalWrite(PIN_GLED5, HIGH);
				digitalWrite(PIN_GLED6, HIGH);
				digitalWrite(PIN_GLED7, HIGH);
				digitalWrite(PIN_GLED8, HIGH);
				vTaskDelayUntil(&xLastWakeTime, PERIOD_LED_SLOW);
			}
		}
		else {
			digitalWrite(PIN_GLED1, LOW);
			digitalWrite(PIN_GLED2, HIGH);
			digitalWrite(PIN_GLED3, HIGH);
			digitalWrite(PIN_GLED4, HIGH);
			digitalWrite(PIN_GLED5, HIGH);
			digitalWrite(PIN_GLED6, HIGH);
			digitalWrite(PIN_GLED7, HIGH);
			digitalWrite(PIN_GLED8, HIGH);
			vTaskDelayUntil(&xLastWakeTime, PERIOD_LED_RUNNING);

			digitalWrite(PIN_GLED1, HIGH);
			digitalWrite(PIN_GLED2, LOW);
			digitalWrite(PIN_GLED3, HIGH);
			digitalWrite(PIN_GLED4, HIGH);
			digitalWrite(PIN_GLED5, HIGH);
			digitalWrite(PIN_GLED6, HIGH);
			digitalWrite(PIN_GLED7, HIGH);
			digitalWrite(PIN_GLED8, HIGH);
			vTaskDelayUntil(&xLastWakeTime, PERIOD_LED_RUNNING);

			digitalWrite(PIN_GLED1, HIGH);
			digitalWrite(PIN_GLED2, HIGH);
			digitalWrite(PIN_GLED3, LOW);
			digitalWrite(PIN_GLED4, HIGH);
			digitalWrite(PIN_GLED5, HIGH);
			digitalWrite(PIN_GLED6, HIGH);
			digitalWrite(PIN_GLED7, HIGH);
			digitalWrite(PIN_GLED8, HIGH);
			vTaskDelayUntil(&xLastWakeTime, PERIOD_LED_RUNNING);

			digitalWrite(PIN_GLED1, HIGH);
			digitalWrite(PIN_GLED2, HIGH);
			digitalWrite(PIN_GLED3, HIGH);
			digitalWrite(PIN_GLED4, LOW);
			digitalWrite(PIN_GLED5, HIGH);
			digitalWrite(PIN_GLED6, HIGH);
			digitalWrite(PIN_GLED7, HIGH);
			digitalWrite(PIN_GLED8, HIGH);
			vTaskDelayUntil(&xLastWakeTime, PERIOD_LED_RUNNING);

			digitalWrite(PIN_GLED1, HIGH);
			digitalWrite(PIN_GLED2, HIGH);
			digitalWrite(PIN_GLED3, HIGH);
			digitalWrite(PIN_GLED4, HIGH);
			digitalWrite(PIN_GLED5, LOW);
			digitalWrite(PIN_GLED6, HIGH);
			digitalWrite(PIN_GLED7, HIGH);
			digitalWrite(PIN_GLED8, HIGH);
			vTaskDelayUntil(&xLastWakeTime, PERIOD_LED_RUNNING);

			digitalWrite(PIN_GLED1, HIGH);
			digitalWrite(PIN_GLED2, HIGH);
			digitalWrite(PIN_GLED3, HIGH);
			digitalWrite(PIN_GLED4, HIGH);
			digitalWrite(PIN_GLED5, HIGH);
			digitalWrite(PIN_GLED6, LOW);
			digitalWrite(PIN_GLED7, HIGH);
			digitalWrite(PIN_GLED8, HIGH);
			vTaskDelayUntil(&xLastWakeTime, PERIOD_LED_RUNNING);

			digitalWrite(PIN_GLED1, HIGH);
			digitalWrite(PIN_GLED2, HIGH);
			digitalWrite(PIN_GLED3, HIGH);
			digitalWrite(PIN_GLED4, HIGH);
			digitalWrite(PIN_GLED5, HIGH);
			digitalWrite(PIN_GLED6, HIGH);
			digitalWrite(PIN_GLED7, LOW);
			digitalWrite(PIN_GLED8, HIGH);
			vTaskDelayUntil(&xLastWakeTime, PERIOD_LED_RUNNING);

			digitalWrite(PIN_GLED1, HIGH);
			digitalWrite(PIN_GLED2, HIGH);
			digitalWrite(PIN_GLED3, HIGH);
			digitalWrite(PIN_GLED4, HIGH);
			digitalWrite(PIN_GLED5, HIGH);
			digitalWrite(PIN_GLED6, HIGH);
			digitalWrite(PIN_GLED7, HIGH);
			digitalWrite(PIN_GLED8, LOW);
			vTaskDelayUntil(&xLastWakeTime, PERIOD_LED_RUNNING);
		}
	}
}

void tSerial(void *p) {
	TickType_t xLastWakeTime = 0;
	while(1) {
        if (Serial.available()) {	//if there is data being received
			bluetoothVal = Serial.read();

			switch(bluetoothVal) {
			case CMD_CONNECTED:
				moveState = Connect;
				break;
			case CMD_DISCONNECTED:
				moveState = Disconnect;
				break;
			case CMD_OFF:
				moveState = End;
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
			case CMD_LEFTFRONT:
				moveState = LeftFront;
				break;
			case CMD_LEFTBACK:
				moveState = LeftBack;
				break;
			case CMD_RIGHT:
				moveState = Right;
				break;
			case CMD_RIGHTFRONT:
				moveState = RightFront;
				break;
			case CMD_RIGHTBACK:
				moveState = RightBack;
				break;
			case CMD_SONG:
				moveState = Start;
				break;
			case CMD_STOP:
				moveState = Idle;
				break;
			}
        }
        vTaskDelayUntil(&xLastWakeTime, 50);
	}
}

void tMotorControl(void *p) {
	TickType_t xLastWakeTime = 0;
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
		case LeftFront:
			digitalWrite(PIN_MOTORFRP, HIGH);
			digitalWrite(PIN_MOTORFRN, LOW);
			analogWrite(PIN_MOTORFLP, POS_PWM);
			digitalWrite(PIN_MOTORFLN, LOW);
			digitalWrite(PIN_MOTORBRP, HIGH);
			digitalWrite(PIN_MOTORBRN, LOW);
			analogWrite(PIN_MOTORBLP, POS_PWM);
			digitalWrite(PIN_MOTORBLN, LOW);
			break;
		case RightFront:
			analogWrite(PIN_MOTORFRP, POS_PWM);
			digitalWrite(PIN_MOTORFRN, LOW);
			digitalWrite(PIN_MOTORFLP, HIGH);
			digitalWrite(PIN_MOTORFLN, LOW);
			analogWrite(PIN_MOTORBRP, POS_PWM);
			digitalWrite(PIN_MOTORBRN, LOW);
			digitalWrite(PIN_MOTORBLP, HIGH);
			digitalWrite(PIN_MOTORBLN, LOW);
			break;
		case LeftBack:
			digitalWrite(PIN_MOTORFRP, LOW);
			digitalWrite(PIN_MOTORFRN, HIGH);
			analogWrite(PIN_MOTORFLP, POS_PWM);
			digitalWrite(PIN_MOTORFLN, HIGH);
			digitalWrite(PIN_MOTORBRP, LOW);
			digitalWrite(PIN_MOTORBRN, HIGH);
			analogWrite(PIN_MOTORBLP, POS_PWM);
			digitalWrite(PIN_MOTORBLN, HIGH);
			break;
		case RightBack:
			analogWrite(PIN_MOTORFRP, POS_PWM);
			digitalWrite(PIN_MOTORFRN, HIGH);
			digitalWrite(PIN_MOTORFLP, LOW);
			digitalWrite(PIN_MOTORFLN, HIGH);
			analogWrite(PIN_MOTORBRP, POS_PWM);
			digitalWrite(PIN_MOTORBRN, HIGH);
			digitalWrite(PIN_MOTORBLP, LOW);
			digitalWrite(PIN_MOTORBLN, HIGH);
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
		vTaskDelayUntil(&xLastWakeTime, 50);
	}
}

void tAudio(void *p) {
	TickType_t xLastWakeTime = xTaskGetTickCount();
	int babyShark[30] = {
		294, 330, 392, 392, 392, 392, 392, 392, 392,
		294, 330, 392, 392, 392, 392, 392, 392, 392,
		294, 330, 392, 392, 392, 392, 392, 392, 392,
		392, 392, 370};
	int babySharkDelay[30] = {
		294, 330, 392, 392, 392, 392, 392, 392, 392,
		294, 330, 392, 392, 392, 392, 392, 392, 392,
		294, 330, 392, 392, 392, 392, 392, 392, 392,
		392, 392, 370};

	while(1) {
		if (moveState == Connect) {
			tone(PIN_AUDIO, 2637);
			vTaskDelayUntil(&xLastWakeTime, 150);
			noTone(PIN_AUDIO);
			vTaskDelayUntil(&xLastWakeTime, 300);
			moveState = Idle;
		}
		else if (moveState == Disconnect)
			challengeRun = 0;
		else if (moveState == End) {
			for(int i=0; i<3; i++) {
				tone(PIN_AUDIO, 2637);
				vTaskDelayUntil(&xLastWakeTime, 150);
				noTone(PIN_AUDIO);
				vTaskDelayUntil(&xLastWakeTime, 350);
			}
			challengeRun = 0;
			moveState = Idle;
		}
		else if ((challengeRun == 1 || moveState == Start) && (moveState != Connect) && (moveState != End)) {
			challengeRun = 1;
			for(int i = 0; i < 30; i++) {
				if (moveState == End || moveState == Disconnect) {
					break;
				}
				tone(PIN_AUDIO, babyShark[i]);
				vTaskDelayUntil(&xLastWakeTime, babySharkDelay[i]);
				noTone(PIN_AUDIO);
				vTaskDelayUntil(&xLastWakeTime, 75);
			}
			vTaskDelayUntil(&xLastWakeTime, 350);
		}
		vTaskDelayUntil(&xLastWakeTime, 50);
	}
}

