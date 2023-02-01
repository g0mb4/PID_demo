#include <Arduino.h>

#include "position_sensor.h"
#include "kalman_filter.h"
#include "operation_mode.h"

void InitSensor(void){
    pinMode(SENSOR_AN, INPUT);
    InitKalmanFilter(0.5f, 10.0f, 0.5f);
}

static float ConvertADC(float adcValue){
    return 259643.0f * pow(adcValue, -1.717f);
}

/*
    Reads the sensor and gives the distance in cm-s.
*/
float ReadSensor(const ProgramState * state){
    if(OM(state) == PID_LP){
        uint32_t sum = 0;

        /*
            Using a low-pass filter to minimalize noise.
        */
        for(uint8_t i = 0; i < SENSOR_NO_MEASUREMENTS; ++i){
            sum += analogRead(SENSOR_AN);
        }

        float adc = sum / SENSOR_NO_MEASUREMENTS;
        return ConvertADC(adc);
    } else {
        float adc = analogRead(SENSOR_AN);
        float distance = ConvertADC(adc);
        return UpdateKalmanEstimate(distance);
    }
}
