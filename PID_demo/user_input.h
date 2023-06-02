#ifndef USER_INPUT
#define USER_INPUT

#include "program_state.h"

/* pins of the buttons */
#define BTN_OP_MODE_PIN         10
#define BTN_DISPLAY_MODE_PIN    11
#define BTN_START_STOP_PIN      12

/* analog pins of the potentiometers */
#define SP_MAN_AN   A1  /* SP in control mode, manual in manual mode */
#define KP_AN       A2
#define KI_AN       A3
#define KD_AN       A4

#define INPUT_NO_ANALOG_READS   20 /* number of measurements in the low-pass filter */

/* ranges of the user inputs */
#define KP_MIN    0.0f
#define KP_MAX    5.0f

#define KI_MIN    0.0f
#define KI_MAX    0.01f

#define KD_MIN    0.0f
#define KD_MAX    2000.0f

#define SP_MIN    4.0f
#define SP_MAX    18.0f

void InitUserInput(void);
void ReadUserInput(ProgramState * state);

#endif
