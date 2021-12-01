#include "fsm.h"

void fsm_init(int *state_debounce_a, int *state_debounce_b, int *state_edge_a, int *state_edge_b, int *state_shift, int *output_led_1, int *output_led_2, int *output_led_3, int *output_led_4) {
	*state_debounce_a = STATE_DEBOUNCE_LOW_STABLE;
	*state_debounce_b = STATE_DEBOUNCE_LOW_STABLE;
	
	*state_edge_a = STATE_EDGE_LOW;
	*state_edge_b = STATE_EDGE_LOW;
	
	*state_shift = STATE_SHIFT_ON_LED_1;
	
	*output_led_1 = 1;
	*output_led_2 = 0;
	*output_led_3 = 0;
	*output_led_4 = 0;
}

void fsm_reaction(int input_a, int input_b, int *state_debounce_a, int *state_debounce_b, int *state_edge_a, int *state_edge_b, int *state_shift, int *output_led_1, int *output_led_2, int *output_led_3, int *output_led_4) {
	static int output_debounce_a = 0, output_debounce_b = 0;
	static int output_edge_a = 0, output_edge_b = 0;
	
	fsm_debounce_reaction(input_a, state_debounce_a, &output_debounce_a);
	fsm_debounce_reaction(input_b, state_debounce_b, &output_debounce_b);
	
	fsm_edge_reaction(output_debounce_a, state_edge_a, &output_edge_a);
	fsm_edge_reaction(output_debounce_b, state_edge_b, &output_edge_b);
	
	fsm_shift_reaction(output_edge_a, output_edge_b, state_shift, output_led_1, output_led_2, output_led_3, output_led_4); 
}

void fsm_debounce_reaction(int input, int *state, int *output) {
	static int counter = 0;
	
	switch (*state) {
		case STATE_DEBOUNCE_LOW_STABLE:
		{
			if (input == 1) {
				*state = STATE_DEBOUNCE_LOW_TO_HIGH;
				*output = 1;
				counter = 0;
			}
			break;
		}
		case STATE_DEBOUNCE_LOW_TO_HIGH:
		{
			if (counter < BATAS_WAKTU) {
				counter++;
			}
			else {
				*state = STATE_DEBOUNCE_HIGH_STABLE;
			}
			break;
		}
		case STATE_DEBOUNCE_HIGH_STABLE:
		{
			if (input == 0) {
				*state = STATE_DEBOUNCE_HIGH_TO_LOW;
				*output = 0;
				counter = 0;
			}
			break;
		}
		case STATE_DEBOUNCE_HIGH_TO_LOW:
		{
			if (counter < BATAS_WAKTU) {
				counter++;
			}
			else {
				*state = STATE_DEBOUNCE_LOW_STABLE;
			}
			break;
		}
	}
}


void fsm_edge_reaction(int input, int *state, int *output) {
	switch (*state) {
		case STATE_EDGE_LOW:
		{
			if (input == 1) {
				*state = STATE_EDGE_HIGH;
				*output = 1;
			}
			break;
		}
		case STATE_EDGE_HIGH:
		{
			*output = 0;
			if (input == 0) {
				*state = STATE_EDGE_LOW;
			}
			break;
		}
	}
}


void fsm_shift_reaction(int input_a, int input_b, int *state, int *output_1, int *output_2, int *output_3, int *output_4) {
	switch (*state) {
		case STATE_SHIFT_ON_LED_1:
		{
			if (input_a == 1) {
				*state = STATE_SHIFT_ON_LED_2;
				*output_1 = 0;
				*output_2 = 1;
				*output_3 = 0;
				*output_4 = 0;
			}
			if (input_b == 1) {
				*state = STATE_SHIFT_ON_LED_4;
				*output_1 = 0;
				*output_2 = 0;
				*output_3 = 0;
				*output_4 = 1;
			}
			break;
		}
		case STATE_SHIFT_ON_LED_2:
		{
			if (input_a == 1) {
				*state = STATE_SHIFT_ON_LED_3;
				*output_1 = 0;
				*output_2 = 0;
				*output_3 = 1;
				*output_4 = 0;
			}
			if (input_b == 1) {
				*state = STATE_SHIFT_ON_LED_1;
				*output_1 = 1;
				*output_2 = 0;
				*output_3 = 0;
				*output_4 = 0;
			}
			break;
		}
		case STATE_SHIFT_ON_LED_3:
		{
			if (input_a == 1) {
				*state = STATE_SHIFT_ON_LED_4;
				*output_1 = 0;
				*output_2 = 0;
				*output_3 = 0;
				*output_4 = 1;
			}
			if (input_b == 1) {
				*state = STATE_SHIFT_ON_LED_2;
				*output_1 = 0;
				*output_2 = 1;
				*output_3 = 0;
				*output_4 = 0;
			}
			break;
		}
		case STATE_SHIFT_ON_LED_4:
		{
			if (input_a == 1) {
				*state = STATE_SHIFT_ON_LED_1;
				*output_1 = 1;
				*output_2 = 0;
				*output_3 = 0;
				*output_4 = 0;
			}
			if (input_b == 1) {
				*state = STATE_SHIFT_ON_LED_3;
				*output_1 = 0;
				*output_2 = 0;
				*output_3 = 1;
				*output_4 = 0;
			}
			break;
		}
	}
}
