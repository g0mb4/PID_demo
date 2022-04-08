#include <Arduino.h>

#include "position_sensor.h"

void InitSensor(void){
    pinMode(SENSOR_AN, INPUT);
}

/*
    Reads the sensor and gives the distance in cm-s.
*/
float ReadSensor(void){
	uint32_t sum = 0;
	
	/*
	    Using a low-pass filter to minimalize noise.
	*/
	for(uint8_t i = 0; i < SENSOR_NO_MEASUREMENTS; ++i){
		sum += analogRead(SENSOR_AN);
	}

	float adc = sum / SENSOR_NO_MEASUREMENTS;
	
	/*
	    This function converts the raw ADC value to a distance measured in cm-s.
	    The function is a result of curve fitting on measured data points.
	*/
	float distance = 259643 * pow(adc, -1.717);
	
	return distance;
}
