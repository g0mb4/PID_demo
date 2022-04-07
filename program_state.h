#ifndef PROGRAM_STATE_H
#define PROGRAM_STATE_H

typedef struct {
	// pid_controller
	float k_P;
	float k_I;
	float k_D;
	bool anti_windup;
	
	// control_system
	float set_point;
	bool is_running;
	float control_error;
	float dcontrol_error;
} ProgramState;

#endif
