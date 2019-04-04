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

#define STACK_SIZE 200

// LEDs
#define PIN_REDLED	A0
#define PIN_GREENLED1	A1
#define PIN_GREENLED2	A2
#define PIN_GREENLED3	A3
#define PIN_GREENLED4	A4
#define PIN_GREENLED5	A5
#define PIN_GREENLED6	2
#define PIN_GREENLED7	4
#define PIN_GREENLED8	7

// Motor
#define PIN_MOTORFR	11
#define PIN_MOTORFL	10
#define PIN_MOTORBR	9
#define PIN_MOTORBL	6

// Buzzer
#define PIN_AUDIO	3

// Serial
#define PIN_RX	0
#define PIN_TX	1

enum state {Forward, Reverse, Left, Right, Idle};
state moveState = Idle;

void TaskRedLED(void *p);
void TaskGreenLED(void *p);
void TaskSerial(void *p);
void TaskMotor(void *p);
void TaskAudio(void *p);

#endif /* MAIN_H_ */
