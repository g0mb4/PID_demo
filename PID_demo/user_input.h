#ifndef USER_INPUT
#define USER_INPUT

#include "program_state.h"

#define BTN_ANTI_WINDUP_PIN   10
#define BTN_DISPLAY_MODE_PIN  11
#define BTN_START_STOP_PIN    12

#define POT_SET_POINT A1
#define POT_P         A2
#define POT_I         A3
#define POT_D         A4

#define INPUT_NO_ANALOG_READS 20

#define P_MIN	0.0f
#define P_MAX	5.0f

#define I_MIN	0.0f
#define I_MAX	0.01f

#define D_MIN	0.0f
#define D_MAX	2000.0f

#define SP_MIN	4.0f
#define SP_MAX	18.0f

void InitUserInput(void);
void ReadUserInput(ProgramState * state);

#endif
