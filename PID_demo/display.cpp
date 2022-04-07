#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "display.h"

static LiquidCrystal_I2C lcd(PCF8574_I2C_ADDR, COLUMN_COUNT, ROW_COUNT);
static uint8_t mode = DISPLAY_HOME;

/*
    In order to prevent previous characters to remain on the screen
    a "backbuffer" is used to keep track the content of the display.
    If an update wolud result previous characters to remain on the screen
    the appropriate row is cleared.
    
    Too fequent clearing will result flickering, so it is not suitable to
    clear before every update.
*/

/*
    Backbuffer containing enought space for the 2 rows and the 16 columns
     + 1 extra character for termination of the string.
*/
static char buffer[ROW_COUNT][COLUMN_COUNT + 1];
static uint8_t buffer_count[ROW_COUNT];     // number of characters in the buffer
/*
    Number of characters currentiy on the display.
    This is used to decide if clearing is necessary.
*/
static uint8_t prev_buffer_count[ROW_COUNT] = { COLUMN_COUNT, COLUMN_COUNT };

static char empty_line[COLUMN_COUNT + 1] = "                ";

/*
    Buffer for float to string conversion.
    snprintf() is not working for floats.
*/
static char float_buffer[10];

static void ClearRow(int row){
	lcd.setCursor(0, row);
	lcd.print(empty_line);
}

/*
    The status of the controller is always present in the display
    and does not affect the clearing mechanism.
*/
static void UpdateStatus(const ProgramState * state){
	lcd.setCursor(14, ROW_0);
	lcd.print(state->is_running ? '*' : 'x');
	lcd.print(state->anti_windup ? 'A' : '-');
}

static void HomeScreen(const ProgramState * state){
	dtostrf(state->set_point, 2, 2, float_buffer);
	buffer_count[ROW_0] = snprintf(buffer[ROW_0], COLUMN_COUNT, "SP=%s", float_buffer);
	
	if(state->is_running){
	    dtostrf(state->control_error, 2, 2, float_buffer);
	    buffer_count[ROW_1] = snprintf(buffer[ROW_1], COLUMN_COUNT, "e=%s", float_buffer);
	} else {
	    buffer_count[ROW_1] = snprintf(buffer[ROW_1], COLUMN_COUNT, " ");
	}
}

static void PID1Screen(const ProgramState * state){
	dtostrf(state->k_P, 2, 2, float_buffer);
	buffer_count[ROW_0] = snprintf(buffer[ROW_0], COLUMN_COUNT, "k_P=%s", float_buffer);
	
	dtostrf(state->k_I, 1, 5, float_buffer);
	buffer_count[ROW_1] = snprintf(buffer[ROW_1], COLUMN_COUNT, "k_I=%s", float_buffer);
}

static void PID2Screen(const ProgramState * state){
	dtostrf(state->k_D, 3, 1, float_buffer);
	buffer_count[ROW_0] = snprintf(buffer[ROW_0], COLUMN_COUNT, "k_D=%s", float_buffer);
	
	buffer_count[ROW_1] = snprintf(buffer[ROW_1], COLUMN_COUNT, " ");
}

static void InternalErrorScreen(void){
	buffer_count[ROW_0] = snprintf(buffer[ROW_0], COLUMN_COUNT, "INTERNAL ERROR");
	buffer_count[ROW_1] = snprintf(buffer[ROW_1], COLUMN_COUNT, " ");
}

/*
    The task of ths function is to check if clearing in nessessary, clear if needed
    and update the contents of the display.
*/
static void DisplayBuffer(void){
    for(uint8_t i = 0; i < ROW_COUNT; ++i){
        /*
            If the backbuffer contains less characters than the currently displayed line,
            the update wolud cause junk characters on the screen, so it is nessessary
            to clear the line.
        */
        if(buffer_count[i] < prev_buffer_count[i]){
            ClearRow(i);
        }

        lcd.setCursor(0, i);
        lcd.print(buffer[i]);

        /* Update the number of currently displayed characters. */
        prev_buffer_count[i] = buffer_count[i];
    }
}

void InitDisplay(void) {
	lcd.init();
	lcd.backlight();
}

void UpdateDisplay(const ProgramState * state) {
	switch (mode) {
	case DISPLAY_HOME: HomeScreen(state); break;
	case DISPLAY_PID1: PID1Screen(state); break;
	case DISPLAY_PID2: PID2Screen(state); break;
	case DISPLAY_MODE_COUNT:
	default:
		InternalErrorScreen();
		break;
	}
	
	DisplayBuffer();
	UpdateStatus(state);
}

/*
    Change the currently displayed screen. 
    The screens will get around.
*/
void StepDisplayMode(void){
	mode = (++mode) % DISPLAY_MODE_COUNT;
}
