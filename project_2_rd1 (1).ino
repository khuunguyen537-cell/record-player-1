/* bryce barkdull
ME 208 - project 2
last updated 11/12/2025
I didnt use ai */

//Set up pins
int PWMA = 11;
int AIN1 = 12;
int AIN2 = 13;

int switchpin = 3;
int switchval;
int speaker = 2;
//Varible flag
int DELAY_FLAG = -1;

//Notes frequency
const int melodyNotes[] = {
    329, 293, 261, 293, 329, 329, 329, DELAY_FLAG, 
    293, 293, 293, DELAY_FLAG, 
    329, 392, 392, DELAY_FLAG, 
    329, 293, 261, 293, 329, 329, 329, 329, 
    293, 293, 329, 293, 261 
};
//Note duration 
const int noteDurations[] = {
    200, 200, 200, 200, 200, 200, 200, 0, 
    200, 200, 200, 0,
    200, 200, 200, 0,
    200, 200, 200, 200, 200, 200, 200, 200, 
    200, 200, 200, 200, 450 
};
  void setup()
{
  //setting the motor as outputs and swich as inputs
    pinMode(PWMA, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
  
    pinMode(switchpin, INPUT_PULLUP);
  
    Serial.begin(9600);

  }

void loop()
{
  switchval = digitalRead(switchpin);
//checks if switch is on
  if (switchval == LOW) {   
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    //has to be atleast this to overcome internal resistance
    analogWrite(PWMA, 255);  
    //Number of notes
  for (int i = 0; i < 28; i++) {
     switchval = digitalRead(switchpin);
    if (switchval == HIGH) {
              break; 
    } else {
      int note = melodyNotes[i];
      int duration = noteDurations[i];
      if (note != DELAY_FLAG) {
            //play the note for its duration
            playNote(note, duration);
        }

        //check if their needs to be a delay
        if (note == DELAY_FLAG) {
            delay(250); 
        }
    }
  }


  }
  //stop all of it if switch is of
  else{
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, 0);
    noTone(speaker);
  }
}

//note function
void playNote(int freq, int dur) {
  tone(speaker, freq, dur);
  delay(dur + 50);
}

