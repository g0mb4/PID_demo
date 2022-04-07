#include "display.h"
#include "control_system.h"
#include "user_input.h"
#include "program_state.h"

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
