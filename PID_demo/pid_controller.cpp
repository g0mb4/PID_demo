#include <Arduino.h>

#include "pid_controller.h"

static float P = 0, I = 0, D = 0;

static void AntiWindup(const ProgramState * state){
	/*
		Only run if anti-windup is enabled.
	*/
	if(!state->anti_windup){
		return;
	}
	
	/*
		Reset 'I' if it would cause saturation.
	*/
	if(I > OUT_MAX || I < OUT_MIN){
		I = 0;
	}
}

float UpdateController(const ProgramState * state, float delta_time) {
	P = state->k_P * state->control_error;
	I += state->k_I  * state->control_error * delta_time;
	D = state->k_D * (state->dcontrol_error / delta_time);

	AntiWindup(state);

	float control_signal = P + D + I;
	control_signal = constrain(control_signal, OUT_MIN, OUT_MAX);

	return control_signal;
}
