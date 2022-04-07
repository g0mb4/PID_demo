#ifndef POSITION_SENSOR_H
#define POSITION_SENSOR_H

#define SENSOR_ANALOG_PIN   A0  /* pin of the sensor */

#define SENSOR_NO_MEASUREMENTS  50   /*  number of measurements in the low-pass filter */

void InitSensor(void);
float ReadSensor(void);

#endif
