#include <Arduino.h>

#include "pid_controller.h"
#include "operation_mode.h"

static float I = 0;

static float AntiWindup1(float control_signal, float dI){
	/*
		Neglect the contribution of the integrator after output saturates.
	*/
	if(control_signal > OUT_MAX || control_signal < OUT_MIN){
	    I -= dI;
		control_signal -= dI;
	}
	
	return control_signal;
}

static void AntiWindup2(const ProgramState * state){
	/*
		Reset integrator.
	*/
	if(state->control_error < AW2_TRESHOLD && state->control_error > -AW2_TRESHOLD){
	    I = 0;
	}
}

float UpdateController(const ProgramState * state, float delta_time) {
	float P = KP(state) * E(state);
	float dI = KI(state) * E(state) * delta_time;
	float D = KD(state) * DE(state) / delta_time;
	
    I += dI;
    
	float control_signal = P + D + I;
	
	if(OM(state) == PID_AW1){
	    control_signal = AntiWindup1(control_signal, dI);
	}
	
	if(OM(state) == PID_AW2){
	    AntiWindup2(state);
	}
	
	control_signal = constrain(control_signal, OUT_MIN, OUT_MAX);

	return control_signal;
}
