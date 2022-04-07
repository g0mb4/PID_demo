#include "position_sensor.h"
#include <Arduino.h>

void InitSensor(void){
	pinMode(SENSOR_ANALOG_PIN, INPUT); 
}

float ReadSensor(void){
	uint32_t sum = 0;
	for(uint16_t i = 0; i < SENSOR_NO_MEASUREMENTS; ++i){
		sum += analogRead(SENSOR_ANALOG_PIN);
	}

	float adc = sum / SENSOR_NO_MEASUREMENTS;
	
	float distance = 259643 * pow(adc, -1.717);
	
	return distance;
}
