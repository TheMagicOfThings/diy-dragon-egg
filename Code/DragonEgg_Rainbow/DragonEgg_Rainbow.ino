/////////////////ANIMATED RAINBOW LIGHT////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
//////////The following segment sets up all the technical stuff////////////
///You shouldn't change these lines unless you're a well trained wizard!///
///////////////////////////////////////////////////////////////////////////

#include <Adafruit_NeoPixel.h>

// Which pin are the LEDs getting data from?
#define PIN            7

// How many LEDs are attached to the Controller?
#define NUMPIXELS      3

// Setup the NeoPixel library with the number of pixels, pin and type of pixel
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int sensorPin = 8;         // Which pin is the sensor outputting data to?

int currentState = LOW;      // the current currentState of the output pin
int sensorReading;           // the current reading from the input pin
int previousState = HIGH;    // the previousSate reading from the input pin

// Variables used for debouncing
long time = 0;         // the last time the output pin was toggled
long debounce = 50;   // delay between readings

void setup()
{
  Serial.begin(9600);
  pinMode(sensorPin, INPUT_PULLUP);

  //Initialise the NeoPixel
  pixels.begin(); // This initializes the NeoPixel library.

}


//////////////////////////////////////////////////////////////////////////////////////
///////The following segment, once again, just deals with the technical aspects///////
//////////////////////////////////////////////////////////////////////////////////////

void loop()
{

  sensorReading = digitalRead(sensorPin); //Get a reading from the sensor

  // if the input changed from HIGH to LOW and we've waited long enough
  // for debouncing, toggle the output pin and record the current time
  if (sensorReading == LOW && previousState == HIGH && millis() - time > debounce) {
    if (currentState == HIGH)
      currentState = LOW;
    else
      currentState = HIGH;

    time = millis();
  }

  previousState = sensorReading;

  if (currentState == HIGH) {


    rainbow(20);

  }
  if (currentState == LOW) {

    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Turn pixels off.
      pixels.show(); // Show the selected colour on the pixel
    }
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;


  for (j = 0; j < 256; j++) {

    int check = digitalRead(sensorPin);


    for (i = 0; i < pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel((i + j) & 255));

      }

      pixels.show();
      delay(wait);

      if (check == LOW) {
        return;
    }


  }

}



// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
