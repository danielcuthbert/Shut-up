#include <Arduino.h>
#include <Keyboard.h>


// With mechanical switches, you get noise so you need to think about debounce time. this is basically an amount of time when the switch
// doesnt register another click. 


const char ctrlKey = KEY_LEFT_GUI;   // apple command key
const char shiftKey = KEY_LEFT_SHIFT;
const int buttonPin = 4; // using pin 4 on the pro micro 
int debounceDelay = 50;  // rough guess here of 50 milliseconds, ymmv 
int lastSteadyState = LOW; // read the previous state of pin 4
int lastFlickerableState = LOW; // 
int currentState; // current state of pin 4
unsigned long lastDebounceTime = 0; // setting the time to zero here, im sure there is a better way to do this. basicaly read this as the time of the last button press
int buttonState = 0; 
int previousButtonState = 0;



// we need pin 4 to be high all the time unless pressed so we use the internal pullup for this
void setup() 
{
  pinMode(buttonPin,INPUT_PULLUP); 
  digitalWrite(buttonPin, HIGH);  
  Keyboard.begin();
}


void loop() 
{
  // lets read the current state of the button attached to pin 4
  buttonState = digitalRead(buttonPin);
  
  // if the pin state is not HIGH (default) then that means the button was pressed. There is noise here too so we need to debounce  
  if (currentState != lastFlickerableState)
  {
   lastDebounceTime = millis();
   lastFlickerableState = currentState;
  }
  
  // here's where it got confusing. so if the state is there and is greater than the debounce time, then we know that's the actual state (i think)
  if (millis() - lastDebounceTime > debounceDelay)
  {
    if (buttonState = HIGH && currentState != HIGH)

  // this is where we send cmd + shift + m to mute teams   
  {
    Keyboard.press(ctrlKey);
    Keyboard.press(shiftKey);
    Keyboard.press('m');
    delay(100);
    Keyboard.releaseAll();
  }
// save this state for the next time around
    lastSteadyState = currentState;
    
  
    }
}