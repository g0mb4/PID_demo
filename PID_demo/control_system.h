#ifndef CONTROL_SYSTEM
#define CONTROL_SYSTEM

#include "program_state.h"

/*
    Fixed minimal time step for stability reasons.
*/
#define DELTA_TIME_MS   50

void InitControlSystem(void);
void RunControlSystem(ProgramState * state);

#endif
