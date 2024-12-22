// Remote IR Controller
// Based on https://www.makerguides.com/ir-receiver-remote-arduino-tutorial/
// Receives the number from the remote and turn's on the number associated with that LED, and enters the
// number into the digit_register and moves the current_digit to the next register
// Pressing the EQ resets the LED's and clears the digit_register
// Example:
// Keypress: EQ clears the digit_register and turns all LED's off
//                                          digit_register = - - - - - - - - - -
// Keypress 1: #0 Turns on the #0 LED       digit_register = 0 - - - - - - - - -
// Keypress 2: #0 The #0 LED is already on  digit_register = 0 0 - - - - - - - -
// Keypress 3: #2 Turns on the #2 LED       digit_register = 0 0 2 - - - - - - -
// Keypress 4: #4 Turns on the #4 LED       digit_register = 0 0 2 4 - - - - - -
// Keypress 4: #4 Turns on the #5 LED       digit_register = 0 0 2 4 5 - - - - -

#include <Arduino.h>
#include "IRremote.hpp"
#include "avr8-stub.h"
// #include "app_api.h"

#define IR_RECEIVE_PIN 5 // Data 5 pin 8
#define ZERO DD2         // data 2 pin 5
#define ONE DD3          // data 3 pin 6
#define TWO DD4          // data 4 pin 7
#define THREE 0          // data 4 pin 7
#define FOUR 0           // data 4 pin 7
#define FIVE 0           // data 4 pin 7
#define SIX 0            // data 4 pin 7
#define SEVEN 0
#define EIGHT 0
#define NINE 0

char digit_register[10]; // stores the digits in sequence received in the array
int pinout_register[10]; // stores the pin numbers in sequence received in the array
#define TOTAL_NUMBERS_ALLOWED sizeof(digit_register) / sizeof(char)
#define TOTAL_PINS_ALLOWED sizeof(pinout_register)

unsigned int current_digit; // current digit received

void print_registers()
{
  // Serial.print("Digit #: ");
  // Serial.print(current_digit);
  // Serial.println("  ");
  // Serial.print("Digit Register: ");
  for (unsigned int i = 0; i < TOTAL_NUMBERS_ALLOWED; i++)
  {
    // Serial.print("[");
    // Serial.print(digit_register[i]);
    // Serial.print("] ");
  }
  // Serial.println();
  // Serial.print("  Pin Register: ");
  for (unsigned int i = 0; i < TOTAL_NUMBERS_ALLOWED; i++)
  {
    // Serial.print("[");
    // Serial.print(pinout_register[i]);
    // Serial.print("] ");
  }
  // Serial.println();
}
/// @brief clears all register numbers to spaces
/// @param  digit_register
void reset_all(char *pdigit_register, int *ppinout_register)
{
  // Serial.println();
  // Serial.println();
  // Serial.println();
  for (unsigned int x = 0; x < TOTAL_NUMBERS_ALLOWED; x++)
  {
    digitalWrite(ppinout_register[x], LOW); // Turn off the LED
    pdigit_register[x] = '?';
    ppinout_register[x] = 0;
  }
  // print_registers();
  // Serial.println("Reset Completed!");
}

void setup()
{
  // put your setup code here, to run once:
  // Serial.begin(9600);
  debug_init();
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  pinMode(ZERO, OUTPUT);
  pinMode(ONE, OUTPUT);
  pinMode(TWO, OUTPUT);
  current_digit = 0;
  reset_all(digit_register, pinout_register);
  // Serial.println("Init Completed!");
}

void loop()
{
  if (IrReceiver.decode())
  {
    uint16_t command = IrReceiver.decodedIRData.command;
    // Serial.println(command);
    switch (command)
    {
    case 9:
      // Serial.println("EQ");
      current_digit = 0;
      reset_all(digit_register, pinout_register);
      break;
    case 7:
      // Serial.println("VOL-");
      break;
    case 8:
      // Serial.println("4");
      pinout_register[current_digit] = FOUR;
      digit_register[current_digit++] = '4';
      digitalWrite(FOUR, HIGH); // Turn on the #1 LED
      break;
    case 12:
      pinout_register[current_digit] = ONE;
      digit_register[current_digit++] = '1';
      digitalWrite(ONE, HIGH); // Turn on the #1 LED
      break;
    case 13:
      // Serial.println("200+");
      break;
    case 21:
      // Serial.println("VOL+");
      break;
    case 22: // received a ZERO
      pinout_register[current_digit] = ZERO;
      digit_register[current_digit++] = '0';
      digitalWrite(ZERO, HIGH); // Turn on the #0 LED
      break;
    case 24:
      pinout_register[current_digit] = TWO;
      digit_register[current_digit++] = '2';
      digitalWrite(TWO, HIGH); // Turn on the #2 LED
      break;
    case 25:
      // Serial.println("100+");
      break;
    case 28:
      // Serial.println("5");
      pinout_register[current_digit] = FIVE;
      digit_register[current_digit++] = '5';
      digitalWrite(FIVE, HIGH); // Turn on the #1 LED
      break;
    case 64:
      // Serial.println("NEXT");
      break;
    case 66:
      // Serial.println("7");
      pinout_register[current_digit] = SEVEN;
      digit_register[current_digit++] = '7';
      digitalWrite(SEVEN, HIGH); // Turn on the #2 LED
      break;
    case 67:
      // Serial.println("PLAY");
      break;
    case 68:
      // Serial.println("PREV");
      break;
    case 69:
      // Serial.println("CH-");
      break;
    case 70:
      // Serial.println("CH");
      break;
    case 71:
      // Serial.println("CH+");
      break;
    case 74:
      // Serial.println("9");
      pinout_register[current_digit] = NINE;
      digit_register[current_digit++] = '9';
      digitalWrite(NINE, HIGH); // Turn on the #1 LED
      break;
    case 82:
      // Serial.println("8");
      pinout_register[current_digit] = EIGHT;
      digit_register[current_digit++] = '8';
      digitalWrite(EIGHT, HIGH); // Turn on the #1 LED
      break;
    case 90:
      // Serial.println("6");
      pinout_register[current_digit] = SIX;
      digit_register[current_digit++] = '6';
      digitalWrite(SIX, HIGH); // Turn on the #1 LED
      break;
    case 94:
      // Serial.println("3");
      pinout_register[current_digit] = THREE;
      digit_register[current_digit++] = '3';
      digitalWrite(THREE, HIGH); // Turn on the #1 LED

      break;
    default:
      // Serial.println("UNDEFINED");
      break;
    }
    delay(300);
    // if you have exceed the numbers allowed reset the counter to 0
    if (current_digit > TOTAL_NUMBERS_ALLOWED)
    {
      // Serial.println("Digit Overflow ...!");
      for (int x = 0; x < 6; x++)
      {

        for (unsigned int y = 0; y < TOTAL_NUMBERS_ALLOWED; y++)
        {
          digitalWrite(pinout_register[y], HIGH); // Turn off the LED
        }
        delay(300);
        for (unsigned int y = 0; y < TOTAL_NUMBERS_ALLOWED; y++)
        {
          digitalWrite(pinout_register[y], LOW); // Turn off the LED
        }
        delay(300);
      }
      delay(1000);
      current_digit = 0;
      reset_all(digit_register, pinout_register);
    }
    print_registers();
    IrReceiver.resume();
  }
}
