#include "operation_mode.h"

void StepOperationMode(ProgramState * state){
    OM(state) = (++OM(state)) % OPERATION_MODE_COUNT;
}
