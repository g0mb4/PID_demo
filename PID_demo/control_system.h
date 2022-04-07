#ifndef CONTROL_SYSTEM
#define CONTROL_SYSTEM

#include "program_state.h"

/*
    This is a strictily digital control. 
*/
#define DELTA_TIME_MS   50  /* minimal time difference between control steps */

void InitControlSystem(void);
void RunControlSystem(ProgramState * state);

#endif
