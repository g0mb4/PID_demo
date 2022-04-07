/*
	Demonstration of a PID controller.
	Tested on Arduino Mega.
	
	Used libraries: 
		Button:	https://github.com/madleech/Button
		LiquidCrystal_I2C: https://github.com/johnrickman/LiquidCrystal_I2C
*/

#include "display.h"
#include "control_system.h"
#include "program_state.h"
#include "user_input.h"

static ProgramState state;

void setup() {
    Serial.begin(9600);

    InitUserInput();
    InitDisplay();
    InitControlSystem();

    Serial.println("started.");
}

void loop() {
    ReadUserInput(&state);
    UpdateDisplay(&state);
    RunControlSystem(&state);
}
