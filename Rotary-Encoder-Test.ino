#include <Arduino.h>

const int pinA = 2;
const int pinB = 3;
volatile byte aFlag = 0;
volatile byte bFlag = 0; 
volatile int encoderPos = 0;
volatile int oldEncPos = 0;
volatile byte reading = 0;


void setup() {
  Serial.begin(9600);
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);
  attachInterrupt(0,PinA,RISING);
  attachInterrupt(1,PinB,RISING);
}

void PinA(){
  cli();
  reading = PIND & 0xC;
  if(reading == B00001100 && aFlag) { 
    if (encoderPos==0) encoderPos=19;
    else encoderPos--;
    bFlag = 0;
    aFlag = 0;
  }
  else if (reading == B00000100) bFlag = 1;
  sei();
}

void PinB(){
  cli(); 
  reading = PIND & 0xC; 
  if (reading == B00001100 && bFlag) { 
    if(encoderPos==19) encoderPos=0;
    else encoderPos ++;
    bFlag = 0;
    aFlag = 0;
  }
  else if (reading == B00001000) aFlag = 1;
  sei();
}

void loop(){
  if(oldEncPos != encoderPos) {;
    Serial.println(encoderPos);
    oldEncPos = encoderPos;
  }
}
