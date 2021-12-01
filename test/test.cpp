#include "pch.h"
#include "C:\my-data\Semester-7\EL4121 Perancangan Sistem Embedded\Tugas\Tugas 7\13218080-source-code-tugas7\fsm\fsm.h"
#include "C:\my-data\Semester-7\EL4121 Perancangan Sistem Embedded\Tugas\Tugas 7\13218080-source-code-tugas7\fsm\fsm.c"

TEST(FSM_Debounce, ButtonNotPressed) {
	int state = STATE_DEBOUNCE_LOW_STABLE;
	int output = 0;

	fsm_debounce_reaction(0, &state, &output);

	EXPECT_EQ(state, STATE_DEBOUNCE_LOW_STABLE);
	EXPECT_EQ(output, 0);
}

TEST(FSM_Debounce, ButtonPressed) {
	int state = STATE_DEBOUNCE_LOW_STABLE;
	int output = 0;

	fsm_debounce_reaction(1, &state, &output);

	EXPECT_EQ(state, STATE_DEBOUNCE_LOW_TO_HIGH);
	EXPECT_EQ(output, 1);
}


TEST(FSM_Debounce, ButtonDebouncingLowToHigh) {
	int state = STATE_DEBOUNCE_LOW_TO_HIGH;
	int output = 1;

	for (int i = 0; i < 50; i++) {
		fsm_debounce_reaction((rand() % 2), &state, &output);
		EXPECT_EQ(state, STATE_DEBOUNCE_LOW_TO_HIGH);
		EXPECT_EQ(output, 1);
	}

	fsm_debounce_reaction(1, &state, &output);
	EXPECT_EQ(state, STATE_DEBOUNCE_HIGH_STABLE);
	EXPECT_EQ(output, 1);
	
}

TEST(FSM_Debounce, ButtonHold) {
	int state = STATE_DEBOUNCE_HIGH_STABLE;
	int output = 1;

	fsm_debounce_reaction(1, &state, &output);
	EXPECT_EQ(state, STATE_DEBOUNCE_HIGH_STABLE);
	EXPECT_EQ(output, 1);
}

TEST(FSM_Debounce, ButtonReleased) {
	int state = STATE_DEBOUNCE_HIGH_STABLE;
	int output = 1;

	fsm_debounce_reaction(0, &state, &output);
	EXPECT_EQ(state, STATE_DEBOUNCE_HIGH_TO_LOW);
	EXPECT_EQ(output, 0);
}

TEST(FSM_Debounce, ButtonDebouncingHighToLow) {
	int state = STATE_DEBOUNCE_HIGH_TO_LOW;
	int output = 0;

	for (int i = 0; i < 50; i++) {
		fsm_debounce_reaction((rand() % 2), &state, &output);
		EXPECT_EQ(state, STATE_DEBOUNCE_HIGH_TO_LOW);
		EXPECT_EQ(output, 0);
	}

	fsm_debounce_reaction(1, &state, &output);
	EXPECT_EQ(state, STATE_DEBOUNCE_LOW_STABLE);
	EXPECT_EQ(output, 0);
}

TEST(FSM_Edge, EdgeLow) {
	int state = STATE_EDGE_LOW;
	int output = 0;

	fsm_edge_reaction(0, &state, &output);
	EXPECT_EQ(state, STATE_EDGE_LOW);
	EXPECT_EQ(output, 0);
}

TEST(FSM_Edge, EdgeLowToHigh) {
	int state = STATE_EDGE_LOW;
	int output = 0;

	fsm_edge_reaction(1, &state, &output);
	EXPECT_EQ(state, STATE_EDGE_HIGH);
	EXPECT_EQ(output, 1);
}

TEST(FSM_Edge, EdgeHigh) {
	int state = STATE_EDGE_HIGH;
	int output = 1;

	fsm_edge_reaction(1, &state, &output);
	EXPECT_EQ(state, STATE_EDGE_HIGH);
	EXPECT_EQ(output, 0);

}

TEST(FSM_Edge, EdgeHighToLow) {
	int state = STATE_EDGE_HIGH;
	int output = 0;

	fsm_edge_reaction(0, &state, &output);
	EXPECT_EQ(state, STATE_EDGE_LOW);
	EXPECT_EQ(output, 0);
}

TEST(FSM_Shift, Shift1To2) {
	int state = STATE_SHIFT_ON_LED_1;
	int output_1 = 1;
	int output_2 = 0;
	int output_3 = 0;
	int output_4 = 0;

	fsm_shift_reaction(1, 0, &state, &output_1, &output_2, &output_3, &output_4);
	EXPECT_EQ(state, STATE_SHIFT_ON_LED_2);
	EXPECT_EQ(output_1, 0);
	EXPECT_EQ(output_2, 1);
	EXPECT_EQ(output_3, 0);
	EXPECT_EQ(output_4, 0);
}

TEST(FSM_Shift, Shift2To1) {
	int state = STATE_SHIFT_ON_LED_2;
	int output_1 = 0;
	int output_2 = 1;
	int output_3 = 0;
	int output_4 = 0;

	fsm_shift_reaction(0, 1, &state, &output_1, &output_2, &output_3, &output_4);
	EXPECT_EQ(state, STATE_SHIFT_ON_LED_1);
	EXPECT_EQ(output_1, 1);
	EXPECT_EQ(output_2, 0);
	EXPECT_EQ(output_3, 0);
	EXPECT_EQ(output_4, 0);
}

TEST(FSM_Shift, Shift2To3) {
	int state = STATE_SHIFT_ON_LED_2;
	int output_1 = 0;
	int output_2 = 1;
	int output_3 = 0;
	int output_4 = 0;

	fsm_shift_reaction(1, 0, &state, &output_1, &output_2, &output_3, &output_4);
	EXPECT_EQ(state, STATE_SHIFT_ON_LED_3);
	EXPECT_EQ(output_1, 0);
	EXPECT_EQ(output_2, 0);
	EXPECT_EQ(output_3, 1);
	EXPECT_EQ(output_4, 0);
}

TEST(FSM_Shift, Shift3To2) {
	int state = STATE_SHIFT_ON_LED_3;
	int output_1 = 0;
	int output_2 = 0;
	int output_3 = 1;
	int output_4 = 0;

	fsm_shift_reaction(0, 1, &state, &output_1, &output_2, &output_3, &output_4);
	EXPECT_EQ(state, STATE_SHIFT_ON_LED_2);
	EXPECT_EQ(output_1, 0);
	EXPECT_EQ(output_2, 1);
	EXPECT_EQ(output_3, 0);
	EXPECT_EQ(output_4, 0);
}

TEST(FSM_Shift, Shift3To4) {
	int state = STATE_SHIFT_ON_LED_3;
	int output_1 = 0;
	int output_2 = 0;
	int output_3 = 1;
	int output_4 = 0;

	fsm_shift_reaction(1, 0, &state, &output_1, &output_2, &output_3, &output_4);
	EXPECT_EQ(state, STATE_SHIFT_ON_LED_4);
	EXPECT_EQ(output_1, 0);
	EXPECT_EQ(output_2, 0);
	EXPECT_EQ(output_3, 0);
	EXPECT_EQ(output_4, 1);
}

TEST(FSM_Shift, Shift4To3) {
	int state = STATE_SHIFT_ON_LED_4;
	int output_1 = 0;
	int output_2 = 0;
	int output_3 = 0;
	int output_4 = 1;

	fsm_shift_reaction(0, 1, &state, &output_1, &output_2, &output_3, &output_4);
	EXPECT_EQ(state, STATE_SHIFT_ON_LED_3);
	EXPECT_EQ(output_1, 0);
	EXPECT_EQ(output_2, 0);
	EXPECT_EQ(output_3, 1);
	EXPECT_EQ(output_4, 0);
}

TEST(FSM_Shift, Shift4To1) {
	int state = STATE_SHIFT_ON_LED_4;
	int output_1 = 0;
	int output_2 = 0;
	int output_3 = 0;
	int output_4 = 1;

	fsm_shift_reaction(1, 0, &state, &output_1, &output_2, &output_3, &output_4);
	EXPECT_EQ(state, STATE_SHIFT_ON_LED_1);
	EXPECT_EQ(output_1, 1);
	EXPECT_EQ(output_2, 0);
	EXPECT_EQ(output_3, 0);
	EXPECT_EQ(output_4, 0);
}

TEST(FSM_Shift, Shift1To4) {
	int state = STATE_SHIFT_ON_LED_1;
	int output_1 = 1;
	int output_2 = 0;
	int output_3 = 0;
	int output_4 = 0;

	fsm_shift_reaction(0, 1, &state, &output_1, &output_2, &output_3, &output_4);
	EXPECT_EQ(state, STATE_SHIFT_ON_LED_4);
	EXPECT_EQ(output_1, 0);
	EXPECT_EQ(output_2, 0);
	EXPECT_EQ(output_3, 0);
	EXPECT_EQ(output_4, 1);
}

TEST(FSM_Cascade, FSM_Init) {
	int state_debounce_a, state_debounce_b;
	int state_edge_a, state_edge_b;
	int state_shift;
	int output_led_1, output_led_2, output_led_3, output_led_4;

	fsm_init(&state_debounce_a, &state_debounce_b, &state_edge_a, &state_edge_b, &state_shift, &output_led_1, &output_led_2, &output_led_3, &output_led_4);
	EXPECT_EQ(state_debounce_a, STATE_DEBOUNCE_LOW_STABLE);
	EXPECT_EQ(state_debounce_b, STATE_DEBOUNCE_LOW_STABLE);
	EXPECT_EQ(state_edge_a, STATE_EDGE_LOW);
	EXPECT_EQ(state_edge_b, STATE_EDGE_LOW);
	EXPECT_EQ(state_shift, STATE_SHIFT_ON_LED_1);
	EXPECT_EQ(output_led_1, 1);
	EXPECT_EQ(output_led_2, 0);
	EXPECT_EQ(output_led_3, 0);
	EXPECT_EQ(output_led_4, 0);
}

TEST(FSM_Cascade, FSM_Reaction) {
	int state_debounce_a = STATE_DEBOUNCE_LOW_STABLE;
	int state_debounce_b = STATE_DEBOUNCE_LOW_STABLE;
	int state_edge_a = STATE_EDGE_LOW;
	int state_edge_b = STATE_EDGE_LOW;
	int state_shift = STATE_SHIFT_ON_LED_1;
	int output_led_1 = 1;
	int output_led_3 = 0; 
	int output_led_4 = 0;
	int output_led_2 = 0; 

	fsm_reaction(1, 0, &state_debounce_a, &state_debounce_b, &state_edge_a, &state_edge_b, &state_shift, &output_led_1, &output_led_2, &output_led_3, &output_led_4);

	EXPECT_EQ(state_debounce_a, STATE_DEBOUNCE_LOW_TO_HIGH);
	EXPECT_EQ(state_debounce_b, STATE_DEBOUNCE_LOW_STABLE);
	EXPECT_EQ(state_edge_a, STATE_EDGE_HIGH);
	EXPECT_EQ(state_edge_b, STATE_EDGE_LOW);
	EXPECT_EQ(state_shift, STATE_SHIFT_ON_LED_2);
	EXPECT_EQ(output_led_1, 0);
	EXPECT_EQ(output_led_2, 1);
	EXPECT_EQ(output_led_3, 0);
	EXPECT_EQ(output_led_4, 0);
}