#ifndef SERVO_MOTOR_H
#define SERVO_MOTOR_H

#define SERVO_PIN 9

#define SERVO_HORIZONTAL	90

#define SERVO_MIN_POS	0
#define SERVO_MAX_POS	180

void InitServoMotor(void);
void WriteServoMotor(float value);

#endif
