#include <Adafruit_NeoPixel.h>
#define PINNeoPixel 8
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 15
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

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
  Serial.begin(9600);
  counter = 0;

}

void effaceTout() {
  for (int i = 0; i < NUMPIXELS ; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
}

void loop() {

  if (Serial.available()) {
    classifier = Serial.read();
  }

  if (classifier == '1') {
    singleColor("blue");
  } else if (classifier == '2') {
    singleColor("red");
  } else if (classifier == '3') {
    singleColor("green");
  }

  //  if (counter % 100 == 0) {
  //    effaceTout();
  //    for (int i = 0; i < NUMPIXELS; i++) {
  //      byte col[3];
  //      chooseColor(col);
  //      pixels.setPixelColor(i, pixels.Color(col[0], col[1], col[2]));
  //    }
  //    counter = 0;
  //  }

  pixels.show(); // This sends the updated pixel color to the hardware.

  counter++;

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
      pixels.setPixelColor(ledId, pixels.Color(0, 0, 20));
    } else if (col == "red") {
      pixels.setPixelColor(ledId, pixels.Color(20, 0, 0));
    } else if (col == "green") {
      pixels.setPixelColor(ledId, pixels.Color(0, 20, 0));
    }
  }
}

void hasard() {
  for (int i = 0; i < NUMPIXELS; i++) {
    int ledId = i;
    color = chooseRandomColor();
    pixels.setPixelColor(ledId, pixels.Color(colors[color][0], colors[color][1], colors[color][2]));
  }
}



