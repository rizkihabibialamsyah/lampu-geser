#ifndef _FSM_H
#define _FSM_H

#define STATE_DEBOUNCE_LOW_STABLE 0
#define STATE_DEBOUNCE_LOW_TO_HIGH 1
#define STATE_DEBOUNCE_HIGH_STABLE 2
#define STATE_DEBOUNCE_HIGH_TO_LOW 3

#define STATE_EDGE_LOW 0
#define STATE_EDGE_HIGH 1

#define STATE_SHIFT_ON_LED_1 0
#define STATE_SHIFT_ON_LED_2 1
#define STATE_SHIFT_ON_LED_3 2
#define STATE_SHIFT_ON_LED_4 3

#define BATAS_WAKTU 50

void fsm_init(int *state_debounce_a, int *state_debounce_b, int *state_edge_a, int *state_edge_b, int *state_shift, int *output_led_1, int *output_led_2, int *output_led_3, int *output_led_4);
void fsm_reaction(int input_a, int input_b, int *state_debounce_a, int *state_debounce_b, int *state_edge_a, int *state_edge_b, int *state_shift, int *output_led_1, int *output_led_2, int *output_led_3, int *output_led_4);

void fsm_debounce_reaction(int input, int *state, int *output);
void fsm_edge_reaction(int input, int *state, int *output);
void fsm_shift_reaction(int input_a, int input_b, int *state, int *output_1, int *output_2, int *output_3, int *output_4);

#endif