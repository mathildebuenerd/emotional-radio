/***
 
 Emotional Radio 
 Music changes depending on the current facial expression
 
 ***/

import oscP5.*;
import netP5.*;
import processing.sound.*;

// For counting how many files in each folder
import java.io.*;
import java.lang.*; 

// For connection with Arduino
import processing.serial.*;

OscP5 osc;
File file;
Serial myPort;
String serialVal;

ArrayList emotions;

// Emotion list, corresonding to the wekinator classifiers outputs
String[] emotionsList = {
  "idle", // classifier = 1
  "smile", // classifier = 2
  "surprised" // classifier = 3
}; 

int currentClassifier;
int lastClassifier;

String mirrorStatus = "on";

ArrayList classfrValues;

void setup()
{
  size(200, 200); 


  emotions = new ArrayList();
  classfrValues = new ArrayList(); // on peut créer une liste pour stocker les dernières valeurs de b
  lastClassifier = 1;
  currentClassifier = 1; // default emotion
  osc = new OscP5(this, 12000); // we listen to port 12000

  String portName = Serial.list()[1]; // Set the port

  //println(Serial.list());
  myPort = new Serial(this, portName, 9600);

  // We add soundFiles to Emotion objects
  for (int i=0; i<emotionsList.length; i++) {
    String[] files = countFiles(emotionsList[i]);
    SoundFile[] soundFiles = loadSoundFiles(emotionsList[i], files);
    Emotion newEmotion = new Emotion(emotionsList[i], files.length, soundFiles);
    emotions.add(newEmotion);
  }

  // Starts with the default music
  Emotion emotion = (Emotion)emotions.get(currentClassifier-1); // we get the current emotion, as the arraylist starts at 0 and the classifiers at 1, we remove 1
  emotion.playRandomSound();
  emotion.lightLED(str(currentClassifier));

  drawStopButton();
}

void drawStopButton() {
  // Draw the stop button
  fill(255, 0, 0);
  rect(15, 15, 70, 70);
  textSize(27);
  fill(255);
  text("stop", 25, 50);
}

void draw() 
{
  if (mirrorStatus == "off") {
    lightOff();
  }
}

void mousePressed() {

  // Switch the mirror status
  if (mirrorStatus == "on") {
    mirrorStatus = "off";
  } else {
    mirrorStatus = "on";
  }
}

void lightOff() {
  myPort.write("9");
}


void oscEvent(OscMessage msg) {
  // executed everytime Processing detects a message on port 12000

  if (mirrorStatus == "on") {
    String address = msg.addrPattern();

    if (address.equals("/wek/outputs")) { // look if the message comes from wekinator
      currentClassifier = (int) msg.get(0).floatValue(); // a number like 1, 2, 3
      println(currentClassifier);

      if (currentClassifier != lastClassifier) { // if the classifier is different than the one before, we change the sound
        Emotion emotion = (Emotion)emotions.get(currentClassifier-1); // we get the current emotion, as the arraylist starts at 0 and the classifiers at 1, we remove 1
        clearSound(); // then we clear all sounds
        emotion.playRandomSound();
        emotion.lightLED(str(currentClassifier));
      }
      lastClassifier = currentClassifier;
    }
  } else {
    lightOff();
  }
}


// Return the names of all files in each folder
String[] countFiles(String emotion) {
  String folder = "sounds/" + emotion; // get the folder
  file = new File(dataPath(folder)); // find the whole path
  String[] listPath = file.list(); // list files in that folder
  return listPath;
}

// load all the sound files for each emotion
SoundFile[] loadSoundFiles(String path, String[] fileList) {
  SoundFile[] soundFiles = new SoundFile[fileList.length]; // initialize the array
  for (int i=0; i<fileList.length; i++) {
    soundFiles[i] = new SoundFile (this, "sounds/" + path + "/" + fileList[i]);
  }
  return soundFiles;
}

// stop all sounds
void clearSound() {
  for (int i=0; i<emotions.size(); i++) {
    Emotion emotion = (Emotion)emotions.get(i);
    emotion.stopSound();
  }
}
