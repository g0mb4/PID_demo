#ifndef OPERATION_MODE_H
#define OPERATION_MODE_H

#include "program_state.h"

enum OperationMode {
    MANUAL = 0,
    PID,
    PID_AW1,
    PID_AW2,
    PID_AW3,
    OPERATION_MODE_COUNT
};

void StepOperationMode(ProgramState * state);

#endif
