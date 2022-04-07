#include "control_system.h"
#include "servo_motor.h"
#include "pid_controller.h"
#include "position_sensor.h"
#include "utils.h"

#include <Arduino.h>

static float prev_error = 0;
static uint32_t prev_run_time = 0;

void InitControlSystem(void){
	InitSensor();
	InitServoMotor();
}

void RunControlSystem(ProgramState * state){
	if (!state->is_running || millis() < prev_run_time + DELTA_TIME_MS) {
		return;
	}

	float process_value = ReadSensor();
	state->control_error = state->set_point - process_value;
	
	state->dcontrol_error = state->control_error - prev_error;

	float control_signal = UpdateController(state, DELTA_TIME_MS);
	
	float acting_signal = mapf(control_signal, OUT_MIN, OUT_MAX, SERVO_MIN_POS, SERVO_MAX_POS);
	WriteServoMotor(acting_signal);

	prev_run_time = millis();
	prev_error = state->control_error;
}
