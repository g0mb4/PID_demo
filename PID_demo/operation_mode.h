#ifndef OPERATION_MODE_H
#define OPERATION_MODE_H

#include "program_state.h"

enum OperationMode {
    MANUAL = 0,             /* motor is controlled by the SP_MAN_AN potentiometer */
    PID_LP,                 /* motor is controlled by the SP value via PID controller using low-pass filter */
    PID_KAL,                /* motor is controlled by the SP value via PID controller using Kalman-filter */
    PID_AW1,                /* PID + Kalman with anti-windup #1 */
    PID_AW2,                /* PID + Kalman with anti-windup #2 */
    OPERATION_MODE_COUNT
};

void StepOperationMode(ProgramState * state);

#endif
