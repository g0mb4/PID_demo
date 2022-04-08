#include <Arduino.h>
#include <Button.h>

#include "display.h"
#include "user_input.h"
#include "servo_motor.h"
#include "operation_mode.h"
#include "utils.h"

static Button btn_display_mode(BTN_DISPLAY_MODE_PIN);
static Button btn_start_stop(BTN_START_STOP_PIN);
static Button btn_operation_mode(BTN_OP_MODE_PIN);

void InitUserInput(void){
    btn_display_mode.begin();
    btn_start_stop.begin();
    btn_operation_mode.begin();

    pinMode(SP_MAN_AN, INPUT);
    pinMode(KP_AN, INPUT);
    pinMode(KI_AN, INPUT);
    pinMode(KD_AN, INPUT);
}

/*
	Generic function to read the value of an ADC pin into a specified range
	using a simple techniques to prevent noise.
*/
static float ReadAD(int pin, float min, float max){
    uint32_t sum = 0;
    
    /*
    	Using a low-pass filter in order to minimalize noise.
    */
    for(uint8_t i = 0; i < INPUT_NO_ANALOG_READS; ++i){
        sum += analogRead(pin);
    }

    float adc_raw = sum / INPUT_NO_ANALOG_READS;
    
    /*
    	Arduino Mega uses a 10 bit ADC, but the bottom 2 bits are dropped
    	in order to minimalize noise. 
    */
    float adc = ((int)adc_raw) >> 2;
    
    /* Ensure zero state. */
    if(adc < 10){
        adc = 0;
    }
    
    /*
    	ADC value is 8 bit now (0-255).
    */
    return mapf(adc, 0, 255, min, max);
}

void ReadUserInput(ProgramState * state){
    if(btn_start_stop.released()){
        state->is_running = !state->is_running;
    }

    if(btn_display_mode.released()){
        StepDisplayMode(state);
    }

    if(btn_operation_mode.released()){
        StepOperationMode(state);
    }

    state->manual = ReadAD(SP_MAN_AN, SERVO_MIN_POS, SERVO_MAX_POS);
    state->set_point = ReadAD(SP_MAN_AN, SP_MIN, SP_MAX);

    state->k_P = ReadAD(KP_AN, KP_MIN, KP_MAX);
    state->k_I = ReadAD(KI_AN, KI_MIN, KI_MAX);
    state->k_D = ReadAD(KD_AN, KD_MIN, KD_MAX);
}
