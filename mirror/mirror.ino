#include <Adafruit_NeoPixel.h>
#define PINNeoPixel 8
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 104
#define BRIGHTNESS 10

// COLORS
int colors [8] [3] = {
  //as many vals as dim1
  {BRIGHTNESS, 0, 0}, //R
  {0, BRIGHTNESS, 0}, //G
  {0, 0, BRIGHTNESS}, //B
  {0, BRIGHTNESS, BRIGHTNESS}, //C
  {BRIGHTNESS, 0, BRIGHTNESS}, //M
  {BRIGHTNESS, BRIGHTNESS, 0}, //J
  {BRIGHTNESS, BRIGHTNESS, BRIGHTNESS} // White
};

char classifier; // Classifier received from Processing

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PINNeoPixel, NEO_GRBW + NEO_KHZ800);

int color;
int lastClassifier;
boolean isAnimationFinished;

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
  Serial.begin(9600);

  // Initialize the first classifier to 0
  lastClassifier = 0;
  classifier = 1;
  isAnimationFinished = true;
}

void clearAll() {
  for (int i = 0; i < NUMPIXELS ; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  pixels.show();
}


void loop() {

  if (Serial.available()) {
    classifier = Serial.read();
  }

  // If there is no animation at the time
  if (isAnimationFinished || classifier != lastClassifier) {

    clearAll();
    if (classifier == '1') {
      sparkle(100, 100, 255);
    } else if (classifier == '2') {
      rainbow(1);
    } else if (classifier == '3') {
      sky(2);
    } else if (classifier = '9') { 
      // For lighting off the mirror
      clearAll();
    }
    lastClassifier = classifier;

  } else {
    clearAll();
  }

}


void sparkle(int red, int green, int blue) {

  int i, j;
  isAnimationFinished = false;

  for (j = 0; j < 10; j++) {
    clearAll();
    for (i = 0; i < 5; i++) {
      int id = int(random(NUMPIXELS));
      pixels.setPixelColor(id, random(red), random(green), random(blue));
    }
    pixels.show();
    delay(1);
  }

  isAnimationFinished = true;

}


void sky(uint8_t wait) {
  uint16_t i, j;
  isAnimationFinished = false;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < pixels.numPixels(); i++) {
      pixels.setPixelColor(i, SkyWheel((i + j) & -100));
    }
    pixels.show();
    delay(wait);
  }
  isAnimationFinished = true;
}

void sparklingSky(uint8_t wait) {

  uint16_t i, j;
  isAnimationFinished = false;

  clearAll();

  for (j = 0; j < 256; j++) {
    for (i = 0; i < 10; i++) {
      int randomPixel = int(random(pixels.numPixels()));
      pixels.setPixelColor(randomPixel, SkyWheel((i + j) & -100));
      //int newj = map(j, 0, 256, 128, 170);
      //Serial.println(j);
      //Serial.println(newj);
      // pixels.setPixelColor(i, j+i, j+i,255);
    }
    pixels.show();
    delay(wait);
  }
  isAnimationFinished = true;
}

void rainbow(uint8_t wait) {
  uint16_t i, j;
  isAnimationFinished = false;


  for (j = 0; j < 256; j++) {
    for (i = 0; i < pixels.numPixels(); i++) {
      pixels.setPixelColor(i, RainbowWheel((i + j) & 255));
    }
    pixels.show();
    delay(wait);
  }

  isAnimationFinished = true;

}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t SkyWheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  return pixels.Color(255 - WheelPos * 3, 240 - WheelPos * 3, 255);
}

uint32_t RainbowWheel(byte WheelPos) {
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
