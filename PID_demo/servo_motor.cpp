#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>

#include "servo_motor.h"

static Servo servo;

void InitServoMotor(void){
	servo.attach(SERVO_PIN);
	
	/*
		Start in a known position.
	*/
	servo.write(SERVO_HORIZONTAL);
}

void WriteServoMotor(float value){
	servo.write(value);
}
