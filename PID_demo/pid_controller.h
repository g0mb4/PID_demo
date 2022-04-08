#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include "program_state.h"

/* 
    Range of the control signal of the controller.
    The actuator is a servo motor with a 180 degree rotational range
    and the accuracity of 1 degree.
*/
#define OUT_MIN -90
#define OUT_MAX 90

#define AW2_TRESHOLD    0.1

float UpdateController(const ProgramState * state, float delta_time);

#endif
