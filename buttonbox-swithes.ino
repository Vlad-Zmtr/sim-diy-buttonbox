#include <FastLED.h>
#include <Joystick.h>

// How many leds in your strip?
#define NUM_LEDS 32
#define DATA_PIN 8

// Define the array of leds
CRGB leds[NUM_LEDS];

// Create the Joystick
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,
  JOYSTICK_TYPE_JOYSTICK,
  20, //number of buttons
  0, //number of hat switches
  //Set as many axis to "true" as you have potentiometers for
  false, // y axis
  false, // x axis
  false, // z axis
  false, // rx axis
  false, // ry axis
  false, // rz axis
  false, // rudder
  false, // throttle
  false, // accelerator
  false, // brake
  false); // steering wheel

// Last state of the button
int lastButtonState[6] = {0,0,0,0,0,0};
int buttonDelay = 50;
bool ledStatus = false;
// Constant that maps the phyical pin to the joystick button.
const int pinToButtonMap = 2;

void setup() { 
    // Initialize LED
    FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is assumed

    // Initialize Button Pins
    pinMode(2, INPUT_PULLUP);
    pinMode(3, INPUT_PULLUP);
    pinMode(4, INPUT_PULLUP);
    pinMode(5, INPUT_PULLUP);
    pinMode(6, INPUT_PULLUP);
    pinMode(7, INPUT_PULLUP);

    // Initialize Joystick Library
    Joystick.begin();
}

void fill(CRGB color)
{
    for(int i = 0; i < NUM_LEDS; i++) {
        leds[i] = color;
    }
}

/// blink red and then off every half second.
void loop() {
    CheckAllButtons();
    if (!ledStatus)
    {
        EnableLED();
    }
}

  // LED
  // Turn the LED on, then pause
void EnableLED(void)
{
  fill(CRGB::Red);
  FastLED.show();
  ledStatus = true;
}

// BUTTONS
void CheckAllButtons(void)
{
  // Read pin values
  for (int index = 0; index < 6; index++)
  {
    int currentButtonState = !digitalRead(index + pinToButtonMap);
    if (currentButtonState != lastButtonState[index])
    {
        if (index != 1)  // 1 is normal button
        {
            Joystick.setButton(index, 1);
            lastButtonState[index] = currentButtonState;
            delay(buttonDelay);
            Joystick.setButton(index,0);
        }
        else
        {
            Joystick.setButton(index, currentButtonState);
            lastButtonState[index] = currentButtonState;
        }
    }    
  }
    delay(50);
}
