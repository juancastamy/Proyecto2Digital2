#include <SD.h>
#include <Wire.h>
#define SD_ChipSelectPin 10
#include <TMRpcm.h>
#include <SPI.h>
#include<pcmConfig.h>
void receiveEvent(int howMany);
TMRpcm tmrpcm;
int COM;
int INICIO;
int CONTRA;
int PAUSA;
int DEAD;
int CLEAR;
void setup() {
  INICIO=0;
  CONTRA=0;
  PAUSA=0;
  DEAD=0;
  CLEAR=0;
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  Serial.begin(9600);           // start serial for output
  tmrpcm.speakerPin = 9;
 
  
  if (!SD.begin(SD_ChipSelectPin)) {
  Serial.println("SD fail");
  return;
  }
  tmrpcm.setVolume(6); 
}
void loop() {
  Serial.print(INICIO);
  Serial.print("\t");
  Serial.print(CONTRA);
  Serial.print("\t");
  Serial.print(PAUSA);
  Serial.print("\t");
  Serial.print(DEAD);
  Serial.print("\t");
  Serial.println(CLEAR);
    if(digitalRead(3)==LOW && digitalRead(4)==LOW && digitalRead(5)==LOW && INICIO==0){
      INICIO++;
      tmrpcm.stopPlayback();
      tmrpcm.play("Title.wav");
    }
    if((digitalRead(3)!=LOW || digitalRead(4)!=LOW || digitalRead(5)!=LOW) && INICIO==1){
      INICIO=0;
    }
    if(digitalRead(3)==HIGH && digitalRead(4)==LOW && digitalRead(5)==LOW && CONTRA==0){
      CONTRA++;
      tmrpcm.stopPlayback();
      tmrpcm.play("CONTRA.wav");
    }
    if((digitalRead(3)!=HIGH || digitalRead(4)!=LOW || digitalRead(5)!=LOW) && CONTRA==1){
      CONTRA=0;
    }
    if(digitalRead(3)==LOW && digitalRead(4)==HIGH && digitalRead(5)==LOW && PAUSA==0){
      PAUSA++;
      tmrpcm.stopPlayback();
      tmrpcm.play("Pause.wav");
    }
    if((digitalRead(3)!=LOW || digitalRead(4)!=HIGH || digitalRead(5)!=LOW) && PAUSA==1){
      PAUSA=0;
    }
    if(digitalRead(3)==HIGH && digitalRead(4)==HIGH && digitalRead(5)==LOW && DEAD==0){
      DEAD++;
      tmrpcm.stopPlayback();
      tmrpcm.play("GameOver.wav");
    }
    if((digitalRead(3)!=HIGH || digitalRead(4)!=HIGH || digitalRead(5)!=LOW) && DEAD==1){
      DEAD=0;
    }
    if(digitalRead(3)==LOW && digitalRead(4)==LOW && digitalRead(5)==HIGH && CLEAR==0){
      CLEAR++;
      tmrpcm.stopPlayback();
      tmrpcm.play("CLEAR.wav");
    }
    if((digitalRead(3)!=LOW || digitalRead(4)!=LOW || digitalRead(5)!= HIGH) && CLEAR==1){
      CLEAR=0;
    }
}
void receiveEvent(int howMany) {
    while (4 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  COM = Wire.read();    // receive byte as an integer
  Serial.println(COM);         // print the integer
}
