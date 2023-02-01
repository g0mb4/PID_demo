#include "program_state.h"
#include "operation_mode.h"

void DumpState(const ProgramState * state){
    switch(OM(state)){
        case MANUAL: Serial.println("MANUAL"); break;
        case PID_LP: Serial.println("LOW-PASS"); break;
        case PID_KAL: Serial.println("KAMLAN"); break;
        case PID_AW1: Serial.println("AW1"); break;
        case PID_AW2: Serial.println("AW2"); break;
        default: Serial.println("UNKNOWN"); break;
    }

    Serial.println(PV(state));
}
