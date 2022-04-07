#ifndef POSITION_SENSOR_H
#define POSITION_SENSOR_H

#define SENSOR_ANALOG_PIN 	A0

#define SENSOR_NO_MEASUREMENTS 50

void InitSensor(void);
float ReadSensor(void);

#endif
