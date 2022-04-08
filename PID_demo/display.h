#ifndef DISPLAY_H
#define DISPLAY_H

#include "program_state.h"

#define PCF8574_I2C_ADDR    0x27    /* I2C address of the device */

/* 
    The resolution of the display is 16x2 in characters.
*/
enum Row {
	ROW_0 = 0,
	ROW_1,
	ROW_COUNT
};

#define COLUMN_COUNT	16

/*
    The possible display modes (screens).
*/
enum DisplayMode {
	DISPLAY_HOME = 0,
	DISPLAY_PID1,
	DISPLAY_PID2,
	DISPLAY_MODE_COUNT
};

void InitDisplay(void);
void UpdateDisplay(const ProgramState * state);

void StepDisplayMode(ProgramState * state);

#endif
