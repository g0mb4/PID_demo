#include "display.h"

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

enum Row {
	ROW_0 = 0,
	ROW_1,
	ROW_COUNT
};

#define COLUMN_COUNT	16

static LiquidCrystal_I2C lcd(PCF8574_I2C_ADDR, PCF8574_LCD_COLUMNS, PCF8574_LCD_ROWS);
static uint8_t mode = DISPLAY_HOME;

static char buffer[ROW_COUNT][COLUMN_COUNT + 1];
static uint8_t buffer_count[ROW_COUNT];
static uint8_t prev_buffer_count[ROW_COUNT] = { COLUMN_COUNT, COLUMN_COUNT };
static char empty_line[COLUMN_COUNT + 1] = "                ";
static char float_buffer[10];

static void ClearRow(int row){
	lcd.setCursor(0, row);
	lcd.print(empty_line);
}

static void UpdateStatus(const ProgramState * state){
	lcd.setCursor(14, ROW_0);
	lcd.print(state->is_running ? '*' : 'x');
	lcd.print(state->anti_windup ? 'A' : '-');
}

static void HomeScreen(const ProgramState * state){
	dtostrf(state->set_point, 2, 2, float_buffer);
	buffer_count[ROW_0] = snprintf(buffer[ROW_0], COLUMN_COUNT, "SP=%s", float_buffer);
	
	dtostrf(state->control_error, 2, 2, float_buffer);
	buffer_count[ROW_1] = snprintf(buffer[ROW_1], COLUMN_COUNT, "e=%s", float_buffer);
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

static void DisplayBuffer(void){
	for(uint8_t i = 0; i < ROW_COUNT; ++i){
		if(buffer_count[i] < prev_buffer_count[i]){
			ClearRow(i);
		}
		
		lcd.setCursor(0, i);
		lcd.print(buffer[i]);
		
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

void StepDisplayMode(void){
	mode = (++mode) % DISPLAY_MODE_COUNT;
}
