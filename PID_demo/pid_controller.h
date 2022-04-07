#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include "program_state.h"

#define OUT_MIN		-90
#define OUT_MAX		90

float UpdateController(const ProgramState * state, float delta_time);

#endif
