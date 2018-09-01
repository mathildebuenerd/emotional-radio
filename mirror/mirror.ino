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

int counter;

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

void effaceTout() {
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

    effaceTout();
    if (classifier == '1') {
      sky(1);
    } else if (classifier == '2') {
      sparkle(100, 100, 255);
    } else if (classifier == '3') {
      // Effect by https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/
      Fire(55, 120, 15);
    } else if (classifier = '9') {
      effaceTout();
    }
    lastClassifier = classifier;

  } else {
    effaceTout();
  }

}


void sparkle(int red, int green, int blue) {

  int i, j;
  isAnimationFinished = false;


  for (j = 0; j < 10; j++) {
    effaceTout();
    for (i = 0; i < 5; i++) {
      int id = int(random(NUMPIXELS));
      //byte col[3];
      //chooseColor(col);
      pixels.setPixelColor(id, random(red), random(green), random(blue));
    }
    pixels.show();
    delay(1);
  }

  isAnimationFinished = true;

}


void chooseColor(byte pcol[]) {
  int r = int(random(BRIGHTNESS));
  int g = int(random(BRIGHTNESS));
  int b = int(random(BRIGHTNESS));
  pcol[0] = r;
  pcol[1] = g;
  pcol[2] = b;
}

int chooseRandomColor() {
  int dice = int(random(10));
  if (dice == 0) {
    return 0;
  } else if (dice == 1) {
    return 1;
  } else if (dice == 2) {
    return 3;
  } else if (dice == 3) {
    return 4;
  } else {
    return 2;
  }

}

void singleColor(String col) {
  effaceTout();
  for (int i = 0; i < NUMPIXELS; i++) {
    int ledId = i;
    if (col == "blue") {
      pixels.setPixelColor(ledId, pixels.Color(0, 0, BRIGHTNESS));
    } else if (col == "red") {
      pixels.setPixelColor(ledId, pixels.Color(20, 0, 0));
    } else if (col == "green") {
      pixels.setPixelColor(ledId, pixels.Color(0, 20, 0));
    }
  }
}

void hasard() {
  effaceTout();
  for (int i = 0; i < 50; i++) {
    int ledId = int(random(NUMPIXELS));
    color = chooseRandomColor();
    pixels.setPixelColor(ledId, pixels.Color(colors[color][0], colors[color][1], colors[color][2]));
  }
  pixels.show();
}

void sky(uint8_t wait) {
  uint16_t i, j;
  isAnimationFinished = false;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel((i + j) & -100));
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

void sparklingSky(uint8_t wait) {

  uint16_t i, j;
  isAnimationFinished = false;

  effaceTout();

  for (j = 0; j < 256; j++) {
    for (i = 0; i < 10; i++) {
      int randomPixel = int(random(pixels.numPixels()));
      pixels.setPixelColor(randomPixel, Wheel((i + j) & -100));
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
      pixels.setPixelColor(i, Wheel((i + j) & 255));
    }
    pixels.show();
    delay(wait);
  }

  isAnimationFinished = true;

}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  //if (WheelPos < 85) {
  return pixels.Color(255 - WheelPos * 3, 240 - WheelPos * 3, 255);
  //}
  //if (WheelPos < 170) {
  //WheelPos -= 85;
  //return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  //}
  //WheelPos -= 170;
  //return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void Fire(int Cooling, int Sparking, int SpeedDelay) {

  static byte heat[NUMPIXELS];
  int cooldown;
  isAnimationFinished = false;


  // Step 1.  Cool down every cell a little
  for ( int i = 0; i < NUMPIXELS; i++) {
    cooldown = random(0, ((Cooling * 10) / NUMPIXELS) + 2);

    if (cooldown > heat[i]) {
      heat[i] = 0;
    } else {
      heat[i] = heat[i] - cooldown;
    }
  }

  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for ( int k = NUMPIXELS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }

  // Step 3.  Randomly ignite new 'sparks' near the bottom
  if ( random(255) < Sparking ) {
    int y = random(7);
    heat[y] = heat[y] + random(160, 255);
    //heat[y] = random(160,255);
  }

  // Step 4.  Convert heat to LED colors
  for ( int j = 0; j < NUMPIXELS; j++) {
    setPixelHeatColor(j, heat[j] );
  }
  pixels.show();
  delay(SpeedDelay);
  isAnimationFinished = true;
}

void setPixelHeatColor (int Pixel, byte temperature) {

  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature / 255.0) * 191);

  // calculate ramp up from
  byte heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252

  // figure out which third of the spectrum we're in:
  if ( t192 > 0x80) {                    // hottest
    pixels.setPixelColor(Pixel, 255, 255, heatramp);
  } else if ( t192 > 0x40 ) {            // middle
    pixels.setPixelColor(Pixel, 255, heatramp, 0);
  } else {                               // coolest
    pixels.setPixelColor(Pixel, heatramp, 0, 0);
  }
}
