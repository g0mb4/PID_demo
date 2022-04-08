#include <Arduino.h>

#include "control_system.h"
#include "operation_mode.h"
#include "pid_controller.h"
#include "position_sensor.h"
#include "servo_motor.h"
#include "utils.h"

/* 
    Pevious error used to determine error difference.
*/
static float prev_error = 0;

/*
    Time of the previous control step 
    used to decide if control action can happen.
*/
static uint32_t prev_run_time = 0;

void InitControlSystem(void){
    InitSensor();
    InitServoMotor();
}

static void RunManual(ProgramState * state){
    PV(state) = ReadSensor();

    WriteServoMotor(state->manual);
}

static void RunPID(ProgramState * state){
    if(millis() < prev_run_time + DELTA_TIME_MS){
        return;
    }
    
    /*
        Typical control loop:
            + gathering data  <-+
            + decision making   |
            + acting          --+
    */
	PV(state) = ReadSensor();
	
	E(state) = SP(state) - PV(state);
	DE(state) = E(state) - prev_error;

	float control_signal = UpdateController(state, DELTA_TIME_MS);
	
	float acting_signal = mapf(control_signal, OUT_MIN, OUT_MAX, SERVO_MIN_POS, SERVO_MAX_POS);
	WriteServoMotor(acting_signal);

	prev_run_time = millis();
	prev_error = E(state);
}

void RunControlSystem(ProgramState * state){
    if(!state->is_running){
        return;
    }

    if(OM(state) == MANUAL){
        RunManual(state);
    } else if (OM(state) >= PID && OM(state) <= PID_AW3){
        RunPID(state);
    } else {
        Serial.print("ERROR: unknown state");
        Serial.println(OM(state));
    }
}
