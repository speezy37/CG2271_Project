#include <Arduino.h>
#include <avr/io.h>
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <queue.h>

#define STACK_SIZE 200

#define PIN_LED6 6
#define PIN_BUZZER7 7

#define BT_CONNECTED 'c'
#define OFF 'f'
#define BABY_SHARK 'b'
#define EMPTY 'e'
#define LEFT 'L'
#define RIGHT 'R'
#define FORWARD 'F'
#define BACKWARD 'B'


char blueToothVal; //value sent over via BT
char lastValue;	//stores last state of value

void TaskLED(void *pvParameters){
	while (1){
		if (blueToothVal == BT_CONNECTED){	//BT connection established
			digitalWrite(PIN_LED6, HIGH);
			vTaskDelay(500);
			digitalWrite(PIN_LED6, LOW);
			vTaskDelay(500);
			digitalWrite(PIN_LED6, HIGH);
			vTaskDelay(500);
			digitalWrite(PIN_LED6, LOW);
			vTaskDelay(500);
			blueToothVal = EMPTY;
		}
	}
}

void TaskSerial(void *pvParameters){
	while(1) {
		if (Serial.available()){	//if there is data being received
			blueToothVal = Serial.read();
		}
	}
}

void TaskMotor(void *pvParameters){
	while(1) {

	}
}

void TaskAudio(void *pvParameters){
	int specialTuneBT[3] = {261, 294, 330};

	int specialTuneEnd[3] = {330, 294, 261};

	int babyShark[30] = {294, 330, 392, 392, 392, 392, 392, 392, 392,
		294, 330, 392, 392, 392, 392, 392, 392, 392,
		294, 330, 392, 392, 392, 392, 392, 392, 392,
		392, 392, 370};

	while(1) {
		if (blueToothVal == BT_CONNECTED){
			for(int i = 0; i < 3; i++){
				tone(PIN_BUZZER7, specialTuneBT[i]);
				vTaskDelay(300);
				noTone(PIN_BUZZER7);
				vTaskDelay(100);
				blueToothVal = EMPTY;
			}
		}
		else if (blueToothVal == BABY_SHARK){
			while (blueToothVal != OFF){
				for(int i = 0; i < 30; i++){
					tone(PIN_BUZZER7, babyShark[i]);
					vTaskDelay(300);
					noTone(PIN_BUZZER7);
					vTaskDelay(100);
				}
			}
			for(int i = 0; i < 3; i++){
				tone(PIN_BUZZER7, specialTuneEnd[i]);
				vTaskDelay(300);
				noTone(PIN_BUZZER7);
				vTaskDelay(100);
			}
		}
	}
}

void setup() {
	Serial.begin(9600);
	pinMode(PIN_LED6, OUTPUT);
	pinMode(PIN_BUZZER7, OUTPUT);
}

void loop() {
	xTaskCreate(TaskLED, "LED", STACK_SIZE, NULL, 2, NULL);
	xTaskCreate(TaskAudio, "Audio", STACK_SIZE, NULL, 2, NULL);
	xTaskCreate(TaskSerial, "Serial", STACK_SIZE, NULL, 2, NULL);
//	xTaskCreate(TaskMotor, "Motor", STACK_SIZE, NULL, 2, NULL);
	vTaskStartScheduler();
}
