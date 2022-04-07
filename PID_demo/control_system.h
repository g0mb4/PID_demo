#ifndef CONTROL_SYSTEM
#define CONTROL_SYSTEM

#include "program_state.h"

#define DELTA_TIME_MS 50

void InitControlSystem(void);
void RunControlSystem(ProgramState * state);

#endif
