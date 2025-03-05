/*
  5 March 2025 - this was cloned from local Elke_One_1.2.ino

  First job is to create a struct rather than a load of ints. It's complicated because 
  the Elke has multiple input lines which feed into the Elke. My brain hurts already!
  
  Will be working through this: https://tigoe.github.io/SoundExamples/

  Next to do - look at BassPedals1 and see how to:
  (a) simplify code using arrays and structs
  (b) Add offset 
  (c) Add DEBOUNCE to remove stutter and take out delay loop
  (d) Look at speed between off and on and use this to determine velocity?
*/

#include "MIDIUSB.h"
#include "PitchToNote.h"

#define NUM_BUTTONS  7

int keyVelocity = 100;

int val = 0;

/* 
  Eleven wires go into the arduino and are triggered in pairs.

  Eight wires represent the notes, three wires represent the octaves. 
*/
int blackLine  = 0;      
int brownLine  = 0;
int redLine    = 0;
int orangeLine = 0;
int yellowLine = 0;
int greenLine  = 0;
int blueLine   = 0;
int purpleLine = 0;

int bottomLine = 0;
int middleLine = 0;
int topLine    = 0;

/* 
  So we can read the wires then calculate and send one of 18 notes. 

  We then store it for when the pedal is pressed continuously. 
*/

int noteG2  = 0;
int noteA2b = 0;
int noteA2  = 0;
int noteB2b = 0;
int noteB2  = 0;
int noteC3  = 0;
int noteD3b = 0;
int noteD3  = 0;
int noteE3b = 0;
int noteE3  = 0;
int noteF3  = 0;
int noteG3b = 0;
int noteG3  = 0;
int noteA3b = 0;
int noteA3  = 0;
int noteB3b = 0;
int noteB3 = 0;
int noteC4 = 0;

int lastNoteG2  = 0;
int lastNoteA2b = 0;
int lastNoteA2  = 0;
int lastNoteB2b = 0;
int lastNoteB2  = 0;
int lastNoteC3  = 0;
int lastNoteD3b = 0;
int lastNoteD3  = 0;
int lastNoteE3b = 0;
int lastNoteE3  = 0;
int lastNoteF3  = 0;
int lastNoteG3b = 0;
int lastNoteG3  = 0;
int lastNoteA3b = 0;
int lastNoteA3  = 0;
int lastNoteB3b = 0;
int lastNoteB3  = 0;
int lastNoteC4  = 0;

int note = 0;

void setup() {
  Serial.begin(9600);
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  
  pinMode(13, OUTPUT); digitalWrite(13, LOW);
  pinMode(14, OUTPUT); digitalWrite(14, LOW);
  pinMode(15, OUTPUT); digitalWrite(15, LOW);
  pinMode(16, OUTPUT); digitalWrite(16, LOW);
  pinMode(17, OUTPUT); digitalWrite(17, LOW);
  pinMode(18, OUTPUT); digitalWrite(18, LOW);
  
  pinMode(52, INPUT);
  pinMode(50, INPUT);
  pinMode(48, INPUT);
  pinMode(46, INPUT);
  pinMode(44, INPUT);
  pinMode(42, INPUT);
  pinMode(40, INPUT);
  pinMode(38, INPUT);
  
  pinMode(7, INPUT); //   pinMode(7, INPUT_PULLUP); // Try this without redoing pins ;)
}

// send a 3-byte midi message
void midiCommand(byte cmd, byte data1, byte data2) {
  // First parameter is the event type (top 4 bits of the command byte).
  // Second parameter is command byte combined with the channel.
  // Third parameter is the first data byte
  // Fourth parameter second data byte

  midiEventPacket_t midiMsg = {cmd >> 4, cmd, data1, data2};
  MidiUSB.sendMIDI(midiMsg);
}

void loop() {

  bottomLine = HIGH; middleLine = LOW; topLine = LOW;
  digitalWrite(18, bottomLine); digitalWrite(16, middleLine); digitalWrite(14, topLine);
  
  blackLine  = digitalRead( 52 );      
  brownLine  = digitalRead( 50 );
  redLine    = digitalRead( 48 );
  orangeLine = digitalRead( 46 );
  yellowLine = digitalRead( 44 );
  greenLine  = digitalRead( 7 );
  blueLine   = digitalRead( 40 );
  purpleLine = digitalRead( 38 );

 
  noteG2 = blackLine;
  if (noteG2 != lastNoteG2) {               // Then check if note is toggling 
    if (blackLine == HIGH) {                // From Low to High
      Serial.println("G2 is pressed");
      midiCommand(0x90, pitchG2, keyVelocity);
      // Can set DEBOUNCE to high number, e.g. 1500 at this point 
      // Can then remove delay in loop
    } else if (blackLine == LOW) {          // From High to Low
      // Can decrement DEBOUNCE at this point and only switch off if it reaches zero
      Serial.println("G2 is released");
      midiCommand(0x80, pitchG2, keyVelocity);
    } 
  }
  lastNoteG2 = noteG2;

  noteA2b = brownLine;
  if (noteA2b != lastNoteA2b) {             // Then check if note is toggling 
    if (brownLine == HIGH) {                // From Low to High
      Serial.println("A2b is pressed");
      midiCommand(0x90, pitchA2b, keyVelocity);
    } else if (brownLine == LOW) {          // From High to Low
      Serial.println("A2b is released");
      midiCommand(0x80, pitchA2b, keyVelocity);
    } 
  }
  lastNoteA2b = noteA2b;

  noteA2 = redLine;
  if (noteA2 != lastNoteA2) {            // Then check if note is toggling 
    if (redLine == HIGH) {                // From Low to High
      Serial.println("A2 is pressed");
      midiCommand(0x90, pitchA2, keyVelocity);
    } else if (redLine == LOW) {          // From High to Low
      Serial.println("A2 is released");
      midiCommand(0x80, pitchA2, keyVelocity);
    } 
  }
  lastNoteA2 = noteA2;

  noteB2b = orangeLine;
  if (noteB2b != lastNoteB2b) {            // Then check if note is toggling 
    if (orangeLine == HIGH) {                // From Low to High
      Serial.println("B2b is pressed");
      midiCommand(0x90, pitchB2b, keyVelocity);
    } else if (orangeLine == LOW) {          // From High to Low
      Serial.println("B2b is released");
      midiCommand(0x80, pitchB2b, keyVelocity);
    } 
  }
  lastNoteB2b = noteB2b;

  noteB2 = yellowLine;
  if (noteB2 != lastNoteB2) {            // Then check if note is toggling 
    if (yellowLine == HIGH) {                // From Low to High
      Serial.println("B2 is pressed");
      midiCommand(0x90, pitchB2, keyVelocity);
    } else if (yellowLine == LOW) {          // From High to Low
      Serial.println("B2 is released");
      midiCommand(0x80, pitchB2, keyVelocity);
    } 
  }
  lastNoteB2 = noteB2;

  noteC3 = greenLine;
  if (noteC3 != lastNoteC3) {            // Then check if note is toggling 
    if (greenLine == HIGH) {                // From Low to High
      Serial.println("C3 is pressed");
      midiCommand(0x90, pitchC3, keyVelocity);
    } else if (greenLine == LOW) {          // From High to Low
      Serial.println("C3 is released");
      midiCommand(0x80, pitchC3, keyVelocity);
    } 
  }
  lastNoteC3 = noteC3;

  noteD3b = blueLine;
  if (noteD3b != lastNoteD3b) {            // Then check if note is toggling 
    if (blueLine == HIGH) {                // From Low to High
      Serial.println("D3b is pressed");
      midiCommand(0x90, pitchD3b, keyVelocity);
    } else if (blueLine == LOW) {          // From High to Low
      Serial.println("D3b is released");
      midiCommand(0x80, pitchD3b, keyVelocity);
    } 
  }
  lastNoteD3b = noteD3b;

  noteD3 = purpleLine;
  if (noteD3 != lastNoteD3) {            // Then check if note is toggling 
    if (purpleLine == HIGH) {                // From Low to High
      Serial.println("D3 is pressed");
      midiCommand(0x90, pitchD3, keyVelocity);
    } else if (purpleLine == LOW) {          // From High to Low
      Serial.println("D3 is released");
      midiCommand(0x80, pitchD3, keyVelocity);
    } 
  }
  lastNoteD3 = noteD3;

  bottomLine = LOW; middleLine = HIGH; topLine = LOW;
  digitalWrite(18, bottomLine); digitalWrite(16, middleLine); digitalWrite(14, topLine);
  
  blackLine  = digitalRead( 52 );      
  brownLine  = digitalRead( 50 );
  redLine    = digitalRead( 48 );
  orangeLine = digitalRead( 46 );
  yellowLine = digitalRead( 44 );
  greenLine  = digitalRead( 7 );
  blueLine   = digitalRead( 40 );
  purpleLine = digitalRead( 38 );

  noteE3b = blackLine;
  if (noteE3b != lastNoteE3b) {            // Then check if note is toggling 
    if (blackLine == HIGH) {                // From Low to High
      Serial.println("E3b is pressed");
      midiCommand(0x90, pitchE3b, keyVelocity);
    } else if (blackLine == LOW) {          // From High to Low
      Serial.println("E3b is released");
      midiCommand(0x80, pitchE3b, keyVelocity);
    } 
  }
  lastNoteE3b = noteE3b;

  noteE3 = brownLine;
  if (noteE3 != lastNoteE3) {            // Then check if note is toggling 
    if (brownLine == HIGH) {                // From Low to High
      Serial.println("E3 is pressed");
      midiCommand(0x90, pitchE3, keyVelocity);
    } else if (brownLine == LOW) {          // From High to Low
      Serial.println("E3 is released");
      midiCommand(0x80, pitchE3, keyVelocity);
    } 
  }
  lastNoteE3 = noteE3;

  noteF3 = redLine;
  if (noteF3 != lastNoteF3) {            // Then check if note is toggling 
    if (redLine == HIGH) {                // From Low to High
      Serial.println("F3 is pressed");
      midiCommand(0x90, pitchF3, keyVelocity);
    } else if (redLine == LOW) {          // From High to Low
      Serial.println("F3 is released");
      midiCommand(0x80, pitchF3, keyVelocity);
    } 
  }
  lastNoteF3 = noteF3;
  
  noteG3b = orangeLine;
  if (noteG3b != lastNoteG3b) {            // Then check if note is toggling 
    if (orangeLine == HIGH) {                // From Low to High
      Serial.println("G3b is pressed");
      midiCommand(0x90, pitchG3b, keyVelocity);
    } else if (orangeLine == LOW) {          // From High to Low
      Serial.println("G3b is released");
      midiCommand(0x80, pitchG3b, keyVelocity);
    } 
  }
  lastNoteG3b = noteG3b;

  noteG3 = yellowLine;
  if (noteG3 != lastNoteG3) {            // Then check if note is toggling 
    if (yellowLine == HIGH) {                // From Low to High
      Serial.println("G3 is pressed");
      midiCommand(0x90, pitchG3, keyVelocity);
    } else if (yellowLine == LOW) {          // From High to Low
      Serial.println("G3 is released");
      midiCommand(0x80, pitchG3, keyVelocity);
    } 
  }
  lastNoteG3 = noteG3;

  noteA3b = greenLine;
  if (noteA3b != lastNoteA3b) {            // Then check if note is toggling 
    if (greenLine == HIGH) {                // From Low to High
      Serial.println("A3b is pressed");
      midiCommand(0x90, pitchA3b, keyVelocity);
    } else if (greenLine == LOW) {          // From High to Low
      Serial.println("A3b is released");
      midiCommand(0x80, pitchA3b, keyVelocity);
    } 
  }
  lastNoteA3b = noteA3b;

  noteA3 = blueLine;
  if (noteA3 != lastNoteA3) {            // Then check if note is toggling 
    if (blueLine == HIGH) {                // From Low to High
      Serial.println("A3 is pressed");
      midiCommand(0x90, pitchA3, keyVelocity);
    } else if (blueLine == LOW) {          // From High to Low
      Serial.println("A3 is released");
      midiCommand(0x80, pitchA3, keyVelocity);
    } 
  }
  lastNoteA3 = noteA3;

  noteB3b = purpleLine;
  if (noteB3b != lastNoteB3b) {            // Then check if note is toggling 
    if (purpleLine == HIGH) {                // From Low to High
      Serial.println("B3b is pressed");
      midiCommand(0x90, pitchB3b, keyVelocity);
    } else if (purpleLine == LOW) {          // From High to Low
      Serial.println("B3b is released");
      midiCommand(0x80, pitchB3b, keyVelocity);
    } 
  }
  lastNoteB3b = noteB3b;

  bottomLine = LOW; middleLine = LOW; topLine = HIGH;
  digitalWrite(18, bottomLine); digitalWrite(16, middleLine); digitalWrite(14, topLine);
  
  blackLine  = digitalRead( 52 );      
  brownLine  = digitalRead( 50 );
  
  noteB3 = blackLine;
  if (noteB3 != lastNoteB3) {            // Then check if note is toggling 
    if (blackLine == HIGH) {                // From Low to High
      Serial.println("B3 is pressed");
      midiCommand(0x90, pitchB3, keyVelocity);
    } else if (blackLine == LOW) {          // From High to Low
      Serial.println("B3 is released");
      midiCommand(0x80, pitchB3, keyVelocity);
    } 
  }
  lastNoteB3 = noteB3;

  noteC4 = brownLine;
  if (noteC4 != lastNoteC4) {            // Then check if note is toggling 
    if (brownLine == HIGH) {                // From Low to High
      Serial.println("C4 is pressed");
      midiCommand(0x90, pitchC4, keyVelocity);
    } else if (brownLine == LOW) {          // From High to Low
      Serial.println("C4 is released");
      midiCommand(0x80, pitchC4, keyVelocity);
    } 
  }
  lastNoteC4 = noteC4;

 /*if ( blackLine || brownLine || redLine || orangeLine || yellowLine || greenLine || blueLine || purpleLine ){
    digitalWrite(LED_BUILTIN, HIGH);   // set the LED to val
    Serial.print( blackLine );
    Serial.print( brownLine );
    Serial.print( redLine );
    Serial.print( orangeLine );
    Serial.print( yellowLine );
    Serial.print( greenLine );
    Serial.print( blueLine );
    Serial.println( purpleLine );
  }*/
  MidiUSB.flush();
  delay(50);  
  digitalWrite(LED_BUILTIN, LOW);       
}
