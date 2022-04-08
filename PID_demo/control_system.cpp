#include <Arduino.h>

#include "control_system.h"
#include "operation_mode.h"
#include "pid_controller.h"
#include "position_sensor.h"
#include "servo_motor.h"
#include "utils.h"

static float prev_error = 0;        // pevious error, used to determine derror
static uint32_t prev_run_time = 0;  // time of the previous control step

void InitControlSystem(void){
    InitSensor();
    InitServoMotor();
}

static void RunManual(ProgramState * state){
    state->sensor_value = ReadSensor();

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
	state->sensor_value = ReadSensor();
	
	state->control_error = state->set_point - state->sensor_value;
	state->dcontrol_error = state->control_error - prev_error;

	float control_signal = UpdateController(state, DELTA_TIME_MS);
	
	float acting_signal = mapf(control_signal, OUT_MIN, OUT_MAX, SERVO_MIN_POS, SERVO_MAX_POS);
	WriteServoMotor(acting_signal);

	prev_run_time = millis();
	prev_error = state->control_error;
}

void RunControlSystem(ProgramState * state){
    if(!state->is_running){
        return;
    }

    if(state->operation_mode == MANUAL){
        RunManual(state);
    } else if (state->operation_mode >= PID && state->operation_mode <= PID_AW2){
        RunPID(state);
    } else {
        Serial.print("ERROR: unknown state");
        Serial.println(state->operation_mode);
    }
}
