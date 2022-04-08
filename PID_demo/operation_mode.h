#ifndef OPERATION_MODE_H
#define OPERATION_MODE_H

#include "program_state.h"

enum OperationMode {
    MANUAL = 0,             /* motor is controlled by the SP_MAN_AN potentiometer */
    PID,                    /* motor is controlled by the SP value via PID controller */
    PID_AW1,                /* PID with anti-windup #1 */
    PID_AW2,                /* PID with anti-windup #2 */
    PID_AW3,                /* PID_AW1 + PID_AW2 */
    OPERATION_MODE_COUNT
};

void StepOperationMode(ProgramState * state);

#endif
