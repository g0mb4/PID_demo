#include <Arduino.h>

#include "pid_controller.h"

static float I = 0;

static float AntiWindup(const ProgramState * state, float control_signal, float dI){
	/*
		Only run if anti-windup is enabled.
	*/
	if(!state->anti_windup){
		return control_signal;
	}
	
	/*
		Neglect integrator if output saturates.
	*/
	if(control_signal > OUT_MAX || control_signal < OUT_MIN){
	    I -= dI;
		control_signal -= dI;
	}
	
	return control_signal;
}

float UpdateController(const ProgramState * state, float delta_time) {
	float P = state->k_P * state->control_error;
	float dI = state->k_I  * state->control_error * delta_time;
	float D = state->k_D * (state->dcontrol_error / delta_time);
	
    I += dI;
    
	float control_signal = P + D + I;
	
	control_signal = AntiWindup(state, control_signal, dI);
	
	control_signal = constrain(control_signal, OUT_MIN, OUT_MAX);

	return control_signal;
}
