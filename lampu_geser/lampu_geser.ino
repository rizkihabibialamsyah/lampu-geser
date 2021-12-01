#include <TimerOne.h>
#include "fsm.h"

// Penentuan PIN yang digunakan
#define PIN_BUTTON_A 2
#define PIN_BUTTON_B 3
#define PIN_LED_1 4
#define PIN_LED_2 5
#define PIN_LED_3 6
#define PIN_LED_4 7

int input_a, input_b;
int state_debounce_a, state_debounce_b;
int state_edge_a, state_edge_b;
int state_shift;
int output_led_1, output_led_2, output_led_3, output_led_4;

void setup() {
  // Set mode PIN button menjadi INPUT
  pinMode(PIN_BUTTON_A, INPUT_PULLUP);
  pinMode(PIN_BUTTON_B, INPUT_PULLUP);
  
  // Set mode PIN LED menjadi OUTPUT
  pinMode(PIN_LED_1, OUTPUT);
  pinMode(PIN_LED_2, OUTPUT);
  pinMode(PIN_LED_3, OUTPUT);
  pinMode(PIN_LED_4, OUTPUT);
  
  fsm_init(&state_debounce_a, &state_debounce_b, &state_edge_a, &state_edge_b, &state_shift, &output_led_1, &output_led_2, &output_led_3, &output_led_4);
  
  Timer1.initialize(1000); 
  Timer1.attachInterrupt(ISR_Timer); 
}

void loop() {
}

void ISR_Timer(void) {
  input_a = !digitalRead(PIN_BUTTON_A);
  input_b = !digitalRead(PIN_BUTTON_B);
  fsm_reaction(input_a, input_b, &state_debounce_a, &state_debounce_b, &state_edge_a, &state_edge_b, &state_shift, &output_led_1, &output_led_2, &output_led_3, &output_led_4);
  if (output_led_1 == 1)
    digitalWrite(PIN_LED_1, HIGH);
  else
    digitalWrite(PIN_LED_1, LOW);
  if (output_led_2 == 1)
    digitalWrite(PIN_LED_2, HIGH);
  else
    digitalWrite(PIN_LED_2, LOW);
  if (output_led_3 == 1)
    digitalWrite(PIN_LED_3, HIGH);
  else
    digitalWrite(PIN_LED_3, LOW);
  if (output_led_4 == 1)
    digitalWrite(PIN_LED_4, HIGH);
  else
    digitalWrite(PIN_LED_4, LOW);
}
