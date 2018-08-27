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

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
  Serial.begin(9600);
  counter = 0;
  //effaceTout();


}

void effaceTout() {
  for (int i = 0; i < NUMPIXELS ; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  pixels.show();
}

void loop() {
 effaceTout();

  //  if (Serial.available()) {
  //    classifier = Serial.read();
  //  }

  //  if (classifier == '1') {
  //singleColor("blue");
  //  } else if (classifier == '2') {
  //    singleColor("red");
  //  } else if (classifier == '3') {
  //    singleColor("green");
  //  }

  //  if (counter % 100 == 0) {
  //    effaceTout();
  //    for (int i = 0; i < NUMPIXELS; i++) {
  //      byte col[3];
  //      chooseColor(col);
  //      pixels.setPixelColor(i, pixels.Color(col[0], col[1], col[2]));
  //    }
  //    counter = 0;
  //  }

  //hasard();
  //sparkle(10, 10, 50);
  //sky(1);
  //sparklingSky(1);
  //delay(10);
  //counter++;

}


void sparkle(int red, int green, int blue) {
  effaceTout();
  int i;

  for (i = 0; i < 5; i++) {
    int id = int(random(NUMPIXELS));
    //byte col[3];
    //chooseColor(col);
    pixels.setPixelColor(id, random(red), random(green), random(blue));
  }
  pixels.show();



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
}

void sparklingSky(uint8_t wait) {
  
  uint16_t i, j;

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
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel((i + j) & 255));
    }
    pixels.show();
    delay(wait);
  }
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



