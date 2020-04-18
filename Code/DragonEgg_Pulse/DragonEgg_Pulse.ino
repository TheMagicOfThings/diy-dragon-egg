/////////////////SINGLE COLOR PULSING//////////////////////////////////////

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
int PreviousState = HIGH;    // the PreviousState reading from the input pin

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

//////////////////////////////////////////////////////////////////////////////////////
////////The following segment, once again, just deals with the technical stuff////////
//////////////////////////////////////////////////////////////////////////////////////
uint32_t chosencolor = pixels.Color(r, g, b);



void loop()
{

  sensorReading = digitalRead(sensorPin); //Get a reading from the sensor

  // if the input changed from HIGH to LOW and we've waited long enough
  // for debouncing, toggle the output pin and record the current time
  if (sensorReading == LOW && PreviousState == HIGH && millis() - time > debounce) {
    if (currentState == HIGH)
      currentState = LOW;
    else
      currentState = HIGH;

    time = millis();
  }

  PreviousState = sensorReading;

  if (currentState == HIGH) {


    pulse();

  }

  if (currentState == LOW) {

    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Turn pixels off.
      pixels.show(); // Show the selected colour on the pixel
    }
  }
}

void pulse() {

  FadeInOut(r, g, b);


}


void setPixel(int Pixel, byte red, byte green, byte blue) {
  pixels.setPixelColor(Pixel, pixels.Color(red, green, blue));
}

void setAll(byte red, byte green, byte blue) {
  for (int i = 0; i < NUMPIXELS; i++ ) {
    setPixel(i, red, green, blue);
  }
  pixels.show();
}

void FadeInOut(byte red, byte green, byte blue) {
  float r, g, b;

  sensorReading = digitalRead(sensorPin);

  if (sensorReading == LOW && PreviousState == HIGH) {
    if (currentState == HIGH) {
      currentState = LOW;
    } else {
      currentState = HIGH;
    }
  }

  for (int k = 100; k < 256; k = k + 1) {
    r = (k / 256.0) * red;
    g = (k / 256.0) * green;
    b = (k / 256.0) * blue;
    setAll(r, g, b);
    pixels.show();

    int  check = digitalRead(sensorPin);

    delay(5);
    if (check == LOW) {
      //   currentState = !currentState;
      return;
    }
  }

  for (int k = 255; k >= 100; k = k - 1) {
    r = (k / 256.0) * red;
    g = (k / 256.0) * green;
    b = (k / 256.0) * blue;
    setAll(r, g, b);
    pixels.show();

    int check = digitalRead(sensorPin);

    delay(5);
    if (check == LOW) {
      //   currentState = !currentState;
      return;
    }
  }
}

