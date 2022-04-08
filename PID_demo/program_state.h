#ifndef PROGRAM_STATE_H
#define PROGRAM_STATE_H

/*
	The program state is used to pass data between modules.
*/
typedef struct {
	/* pid_controller */
	float k_P;				/* coefficient of the P member */
	float k_I;				/* coefficient of the I member */
	float k_D;				/* coefficient of the D member */
	bool anti_windup;		/* is anti-windup active? */
	
	/* control_system */
	float set_point;		/* SP of the control system*/
	bool is_running;		/* is control system running? */
	float control_error;	/* error of the control */
	float dcontrol_error;	/* difference of error */
} ProgramState;

#endif
