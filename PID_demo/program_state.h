#ifndef PROGRAM_STATE_H
#define PROGRAM_STATE_H

#include <Arduino.h>

/*
	The program state is used to pass data between modules.
*/
typedef struct {
    uint8_t operation_mode;	/* operation mode */
    uint8_t display_mode;   /* display mode */

    float manual;           /* output in manual mode (same pin as SP) */ 

	/* pid_controller */
	float k_P;				/* coefficient of the P member */
	float k_I;				/* coefficient of the I member */
	float k_D;				/* coefficient of the D member */
	
	/* control_system */
	float set_point;        /* SP of the control system */
	bool is_running;		/* is control system running? */
	float control_error;	/* error of the control */
	float dcontrol_error;	/* difference of error */
	
	/* sensor */
	float sensor_value;
} ProgramState;

#endif
