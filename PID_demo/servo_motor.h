#ifndef SERVO_MOTOR_H
#define SERVO_MOTOR_H

#define SERVO_PIN   9   /* pin of the servo motor */ 

#define SERVO_HORIZONTAL	90  /* horizontal position in degree */

/* range of the servo motor in degrees */
#define SERVO_MIN_POS	0
#define SERVO_MAX_POS	180

void InitServoMotor(void);
void WriteServoMotor(float value);

#endif
