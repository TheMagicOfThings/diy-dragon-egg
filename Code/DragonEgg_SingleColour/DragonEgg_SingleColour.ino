/////////////////SINGLE COLOR LIGHT////////////////////////////////////////

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
int previousSate = HIGH;    // the previousSate reading from the input pin

// Variables used for debouncing
long time = 0;         // the last time the output pin was toggled
long debounce = 200;   // delay between readings

void setup()
{
  Serial.begin(9600);
  pinMode(sensorPin, INPUT_PULLUP);

  //Initialise the NeoPixel
  pixels.begin(); // This initializes the NeoPixel library.
  
}


//////////////////////////////////////////////////////////////////
///////OK, with that out of the way, let's see what's next.///////
//////////////////////////////////////////////////////////////////
///This following line lets you change the color of your light.///
//////////////////////////////////////////////////////////////////

//Set the pixel colour
int r = 180, g = 50, b = 12;

//

//////////////////////////////////////////////////////////////////////////////////////
///////The following segment, once again, just deals with the technical aspects///////
//////////////////////////////////////////////////////////////////////////////////////

void loop()
{

  sensorReading = digitalRead(sensorPin); //Get a reading from the sensor

  // if the input changed from HIGH to LOW and we've waited long enough
  // for debouncing, toggle the output pin and record the current time
  if (sensorReading == LOW && previousSate == HIGH && millis() - time > debounce) {
    if (currentState == HIGH)
      currentState = LOW;
    else
      currentState = HIGH;

    time = millis();    
  }

  previousSate = sensorReading;

if (currentState == HIGH) {
    
  //  Set the pixel colour
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i,r,g,b);
  }
  pixels.show(); 
  }
  if (currentState == LOW) {
   
    for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(0,0,0)); // Turn pixels off.
    pixels.show(); // Show the selected colour on the pixel
  }
  }
}
