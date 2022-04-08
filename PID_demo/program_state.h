#ifndef PROGRAM_STATE_H
#define PROGRAM_STATE_H

#include <Arduino.h>

/* short-hand macros */
#define OM(s)   (s)->operation_mode
#define DM(s)   (s)->display_mode

/* SP macro is used for Stack Pointer */
#undef SP

#define SP(s)   (s)->set_point
#define PV(s)   (s)->process_value

#define E(s)    (s)->control_error
#define DE(s)   (s)->control_error_difference

#define KP(s)   (s)->k_P
#define KI(s)   (s)->k_I
#define KD(s)   (s)->k_D

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
	float set_point;                /* set point of the control system */
	bool is_running;		        /* is control system running? */
	float control_error;	        /* error of the control */
	float control_error_difference;	/* difference of error */
	
	/* sensor */
	float process_value;     /* sensor data */
} ProgramState;

#endif
