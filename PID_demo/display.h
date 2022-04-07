#ifndef DISPLAY_H
#define DISPLAY_H

#include "program_state.h"

#define PCF8574_I2C_ADDR 0x27
#define PCF8574_LCD_COLUMNS 16
#define PCF8574_LCD_ROWS    2

enum DisplayMode {
	DISPLAY_HOME = 0,
	DISPLAY_PID1,
	DISPLAY_PID2,
	DISPLAY_MODE_COUNT
};

void InitDisplay(void);
void UpdateDisplay(const ProgramState * state);

void StepDisplayMode(void);

#endif
