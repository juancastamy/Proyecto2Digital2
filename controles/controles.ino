#include <SD.h>
#define SD_ChipSelectPin 10
#include <TMRpcm.h>
#include <SPI.h>
#include<pcmConfig.h>

TMRpcm tmrpcm;

//se define los puertos para el primer jugador
#define X A0
#define Y A1
#define shot 2
#define jump 3
#define start 4
//se define los puertos para el segundo jugador
#define X2 A2
#define Y2 A3
#define shot2 5
#define jump2 6
#define start2 7
int PAUSESOUND;
int x;
//varianles de disparo y salto primer jugado
int s;
int j;
int Xvalue;
int Yvalue;
int START;

//varianles de disparo y salto segundo jugado
int s2;
int j2;
int Xvalue2;
int Yvalue2;
int START2;
//variable para anti rebote
int ju;
int ju2;
int sh;
int sh2;
int STOP;
int STOP2;
// variable para pausa
int PAUSE;
int PAUSE2;

unsigned char MENSAJE[] = {0,0,0,0,0,0,0,0,0,0};
void setup() {
  tmrpcm.speakerPin = 9;
  Serial.begin(9600);
  
  if (!SD.begin(SD_ChipSelectPin)) {
  Serial.println("SD fail");
  return;
  }
  tmrpcm.setVolume(6);
  tmrpcm.play("CONTRA.wav");
  //definicion de puertos primer jugador
  pinMode(shot,INPUT);
  pinMode(jump,INPUT);
  pinMode(start,INPUT);

  //definicion de puertos segundo jugador
  pinMode(shot2,INPUT);
  pinMode(jump2,INPUT);
  pinMode(start2,INPUT); 
  // put your setup code here, to run once:
  //variable para anti rebote
  ju=0;
  ju2=0;
  sh=0;
  sh2=0;
  STOP=0;
  STOP2=0;
  // variable para pausa
  PAUSE=0;
  PAUSE2=0;

}

void loop() {
  s=digitalRead(shot);
  j=digitalRead(jump);
  START=digitalRead(start);
  
  //se leen los botones del jugador 2
  s2=digitalRead(shot2);
  j2=digitalRead(jump2);
  START2=digitalRead(start2);

   //Lectura de puerto analogico primer jugador
  Xvalue=analogRead(X);
  Yvalue=analogRead(Y);

  //Lectura de puerto analogico segundo jugador
  Xvalue2=analogRead(X2);
  Yvalue2=analogRead(Y2);
  
  if(s==HIGH){
    ju = 1;
  }
  if (s==LOW && ju==1){
    MENSAJE[0] = 1;
    ju=0;
  }

  if(j==HIGH){
    sh=1;
  }
  if(j==LOW && sh==1){
    MENSAJE[1]=1;
    sh=0;
    }

  if(START==HIGH && PAUSE2==0){
    STOP=1;
  }
  if(START2==HIGH && PAUSE==0){
    STOP2=1;
  }
  if(START==LOW && STOP==1 && PAUSE2==0){
    PAUSE=~PAUSE;
    STOP=0;
  }
  if(START2==LOW && STOP2==1 && PAUSE==0){
    PAUSE2=~PAUSE2;
    STOP2=0;
  }
  if(PAUSE==-1){
    MENSAJE[2]=1;
    PAUSE2=0;
  }
   else{
    MENSAJE[2]=0;
  }
  if(PAUSE2==-1){
    MENSAJE[3]=1;
    PAUSE=0;
  }
  else{
    MENSAJE[3]=0;
  }
  
  if(Xvalue>=700){
    MENSAJE[4]=2;
  }
  if(Xvalue<=400){
    MENSAJE[4]=1;
  }
  if(Xvalue>400 && Xvalue<700){
    MENSAJE[4]=0;
  }
  if(Yvalue>=700){
    MENSAJE[5]=2;
  }
  if(Yvalue<=400){
    MENSAJE[5]=1;
  }
  if(Yvalue>400 && Yvalue<700){
    MENSAJE[5]=0;
  }

  if(s2==HIGH){
    ju2=1;
  }
  if (s2==LOW && ju2==1){
    MENSAJE[6]=1;
    ju2=0;
  }

  if(j2==HIGH){
    sh2=1;
  }
  if(j2==LOW && sh2==1){
    MENSAJE[7]=1;
    sh2=0;
  }
  
  if(Xvalue2>=700){
    MENSAJE[8]=2;
  }
  if(Xvalue2<=400){
    MENSAJE[8]=1;
  }
  if(Xvalue2>400 && Xvalue2<700){
    MENSAJE[8]=0;
  }
  if(Yvalue2>=700){
    MENSAJE[9]=2;
  }
  if(Yvalue2<=400){
    MENSAJE[9]=1;
  }
  if(Yvalue2>400 && Yvalue2<700){
    MENSAJE[9]=0;
  }
  Serial.write(3);
  x=0;
  for(x=0;x<=9;x++){
    Serial.write(MENSAJE[x]);
  }
  Serial.write(4);
  MENSAJE[0]=0;
  MENSAJE[1]=0;
  MENSAJE[6]=0;
  MENSAJE[7]=0;
}
