class Emotion {
  String name;
  int numberOfFiles;
  SoundFile[] soundFiles;

  Emotion(String _name, int _numberOfFiles, SoundFile[] _soundFiles) {
    this.name = _name;
    this.numberOfFiles = _numberOfFiles;
    this.soundFiles = _soundFiles;
  }

  void playRandomSound() {
    int randomFile = int(random(numberOfFiles));
    soundFiles[randomFile].play();
    soundFiles[randomFile].loop();
  }
  
  void stopSound() {
    for (int i=0; i<soundFiles.length; i++) {
      soundFiles[i].stop();
    }
  }
  
  void lightLED(String classifier) {
    myPort.write(classifier); // Send the current classifier to Arduino
  }
}
