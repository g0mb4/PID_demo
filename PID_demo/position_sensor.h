
#ifndef POSITION_SENSOR_H
#define POSITION_SENSOR_H

#include "program_state.h"

#define SENSOR_AN   A0  /* analog pin of the sensor */

#define SENSOR_NO_MEASUREMENTS  50   /*  number of measurements in the low-pass filter */

void InitSensor(void);
float ReadSensor(const ProgramState * state);

#endif
