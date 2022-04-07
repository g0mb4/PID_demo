#include <Arduino.h>
#include <Button.h>

#include "display.h"
#include "user_input.h"
#include "utils.h"

static Button btn_display_mode(BTN_DISPLAY_MODE_PIN);
static Button btn_start_stop(BTN_START_STOP_PIN);
static Button btn_anti_windup(BTN_ANTI_WINDUP_PIN);

void InitUserInput(void){
    btn_display_mode.begin();
    btn_start_stop.begin();
    btn_anti_windup.begin();

    pinMode(POT_SET_POINT, INPUT);
    pinMode(POT_P, INPUT); 
    pinMode(POT_I, INPUT); 
    pinMode(POT_D, INPUT); 
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
        StepDisplayMode();
    }

    if(btn_anti_windup.released()){
        state->anti_windup = !state->anti_windup;
    }

    state->set_point = ReadAD(POT_SET_POINT, SP_MIN, SP_MAX);
    state->k_P = ReadAD(POT_P, P_MIN, P_MAX);
    state->k_I = ReadAD(POT_I, I_MIN, I_MAX);
    state->k_D = ReadAD(POT_D, D_MIN, D_MAX);
}
