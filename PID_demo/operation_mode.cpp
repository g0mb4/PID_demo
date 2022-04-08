#include "operation_mode.h"

void StepOperationMode(ProgramState * state){
    state->operation_mode = (++state->operation_mode) % OPERATION_MODE_COUNT;
}
