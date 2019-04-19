/*
 * main.h
 *
 *  Created on: 3 Apr 2019
 *      Author: ChuaCY
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <Arduino.h>
#include <avr/io.h>
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#define STACK_SIZE 200
#define POS_PWM   32

// LEDs
#define PIN_RLED	A1
#define PIN_GLED1	A5
#define PIN_GLED2	A4
#define PIN_GLED3	A3
#define PIN_GLED4	A2
#define PIN_GLED5	A0
#define PIN_GLED6	2
#define PIN_GLED7	4
#define PIN_GLED8	11

// Motor
#define PIN_MOTORFRP	10	// PWM
#define PIN_MOTORFRN	12
#define PIN_MOTORFLP	5	// PWM
#define PIN_MOTORFLN	13
#define PIN_MOTORBRP	9	// PWM
#define PIN_MOTORBRN	8
#define PIN_MOTORBLP	6	// PWM
#define PIN_MOTORBLN	7

// Buzzer
#define PIN_AUDIO   3

// Serial
#define PIN_RX 		0

// Bluetooth
#define CMD_CONNECTED 'c'
#define CMD_DISCONNECTED 'd'
#define CMD_OFF 'f'
#define CMD_SONG 'b'
#define CMD_LEFT 'L'
#define CMD_RIGHT 'R'
#define CMD_FORWARD 'F'
#define CMD_REVERSE 'B'
#define CMD_STOP 'S'
#define CMD_LEFTFRONT 'H'
#define CMD_LEFTBACK 'I'
#define CMD_RIGHTFRONT 'J'
#define CMD_RIGHTBACK 'K'

// timings
#define PERIOD_LED_SLOW		250
#define PERIOD_LED_FAST		500
#define PERIOD_LED_RUNNING	100
#define PEIROD_SONG			50

enum state {Start, Connect, Idle, Forward, Reverse, Left, Right, LeftFront, RightFront, LeftBack, RightBack, Disconnect, End};
state moveState = Disconnect;

char bluetoothVal;
int challengeRun = 0;

void initPins(void);
void tRedLED(void *p);
void tGreenLED(void *p);
void tSerial(void *p);
void tMotorControl(void *p);
void tAudio(void *p);

#endif /* MAIN_H_ */
