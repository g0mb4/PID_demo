#include "servo_motor.h"

#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>

static Servo servo;

void InitServoMotor(void){
	servo.attach(SERVO_PIN);
	servo.write(SERVO_HORIZONTAL);
}

void WriteServoMotor(float value){
	servo.write(value);
}
