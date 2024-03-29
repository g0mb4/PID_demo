#include "utils.h"

/*
    Arduino's map() function extended to floating point numbers.
*/
float mapf(float x, float in_min, float in_max, float out_min, float out_max){
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/*
    abs() function for floats
*/
float absf(float x){
    if(x < 0.0f){
        return x * -1.0f;
    } else {
        return x;
    }
}
