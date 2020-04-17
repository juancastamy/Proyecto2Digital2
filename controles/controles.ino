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
int STOP;
int STOP2;
// variable para pausa
int PAUSE;
int PAUSE2;
void PAUSA();
//funciones usadas para el primer jugador 
void FRONT();
void BACK();
void UP();
void CROUCH();
void STANDING();
void CRUZE();
void NOMOVE();

//funciones usadas para el segundo jugador 
void FRONT2();
void BACK2();
void UP2();
void CROUCH2();
void STANDING2();
void CRUZE2();
void NOMOVE2();

void setup() {
  tmrpcm.speakerPin = 9;
  Serial.begin(9600);
  
  if (!SD.begin(SD_ChipSelectPin)) {
  Serial.println("SD fail");
  return;
  }
  tmrpcm.setVolume(6);
  tmrpcm.play("CONTRA.wav");
  tmrpcm.play("CONTRA.wav");
  //definicion de puertos primer jugador
  pinMode(shot,INPUT);
  pinMode(jump,INPUT);
  pinMode(start,INPUT);

  //definicion de puertos segundo jugador
  pinMode(shot2,INPUT);
  pinMode(jump2,INPUT);
  pinMode(start2,INPUT); 
  //se limpian las variables de ambos jugadores 
  s=0;
  j=0;
  START=0;
  s2=0;
  j2=0;
  START2=0;
  STOP=0;
  STOP2=0;
  PAUSE=0;
  PAUSE2=0;
  PAUSESOUND=0;
  //MUSICA
  }



void loop() {

  //se leen los botones del jugador 1
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
  PAUSA();
  if(PAUSE==0 && PAUSE2==0){
    //se llaman las funciones del primer jugador
    Serial.print("PLAYER ONE");
    Serial.print ('\t');
    Serial.println("PLAYER TWO");
    FRONT();
    BACK();
    UP();
    CROUCH();
    STANDING();   
    CRUZE();
    NOMOVE();

    
    //se llaman las funciones del segundo jugador
    
    FRONT2();
    BACK2();
    UP2();
    CROUCH2();
    STANDING2();   
    CRUZE2();
    NOMOVE2();  
    PAUSESOUND=0;  
  }
  else{
    PAUSESOUND++;
    Serial.println("PAUSE");    
  }
 if(PAUSESOUND==1){
    tmrpcm.stopPlayback();
    tmrpcm.play("Pause.wav");
    delay(500);
    tmrpcm.play("CONTRA.wav");
  }
}
//Funcion para poner pausa
void PAUSA(){
  if(START==HIGH && PAUSE2==0){
    STOP=1;
  }
  if(START2==HIGH && PAUSE==0){
    STOP2=1;
  }
  if(START==LOW && STOP==1 && PAUSE2==0){
    PAUSE= ~PAUSE;
    STOP=0;
  }
  if(START2==LOW && STOP2==1 && PAUSE==0){
    PAUSE2=~PAUSE2;
    STOP2=0;
  }
  if(PAUSE==1){
    PAUSE2=0;
  }
  if(PAUSE2==1){
    PAUSE=0;
  }
  return;
}
//funciones del primer jugador que permiten su movimiento y acciones
void FRONT(){
  if(Xvalue>=700 && Yvalue>400 && Yvalue<700 && s==LOW && j==LOW){
    Serial.print("front");
    Serial.print ('\t');
  }
  else if(Xvalue>=700 && Yvalue>400 && Yvalue<700 && s==LOW && j==HIGH){
    Serial.print("front and jump");
    Serial.print ('\t'); 
  }
  else if(Xvalue>=700 && Yvalue>400 && Yvalue<700 && s==HIGH && j==LOW){
    Serial.print("front and shot");
    Serial.print ('\t');
  }
  else if(Xvalue>=700 && Yvalue>400 && Yvalue<700 && s==HIGH && j==HIGH){
    Serial.print("front, jump and shoot");
    Serial.print ('\t');  
  }
}
void BACK(){
  if(Xvalue <= 400 &&  Yvalue>400 && Yvalue<700 && s==LOW && j==LOW){
    Serial.print("back");
    Serial.print ('\t');
     
  }
  else if(Xvalue <= 400 &&  Yvalue>400 && Yvalue<700 && s==LOW && j==HIGH){
    Serial.print("back and jump");
    Serial.print ('\t');
     
  }
  else if(Xvalue <= 400 &&  Yvalue>400 && Yvalue<700 && s==HIGH && j==LOW){
    Serial.print("back and shot");
    Serial.print ('\t');
     
  }
  else if(Xvalue <= 400 &&  Yvalue>400 && Yvalue<700 && s==HIGH && j==HIGH){
    Serial.print("back, jump and shot");
    Serial.print ('\t');
     
  }
}
void UP(){
  if(Yvalue>=700 && Xvalue>400 && Xvalue<700 && s==LOW && j==LOW){
    Serial.print("up");
    Serial.print ('\t');
     
  }
  else if(Yvalue>=700 && Xvalue>400 && Xvalue<700 && s==LOW && j==HIGH){
    Serial.print("up and jump");
    Serial.print ('\t');
     
  }
  else if(Yvalue>=700 && Xvalue>400 && Xvalue<700 && s==HIGH && j==LOW){
    Serial.print("up and shot");
    Serial.print ('\t');
     
  }
  else if(Yvalue>=700 && Xvalue>400 && Xvalue<700&& s==HIGH && j==HIGH){
    Serial.print("up, jump and shot");
    Serial.print ('\t');
     
  }
}
void CROUCH(){
  if(Yvalue <= 400 && Xvalue>400 && Xvalue<700&& s==LOW && j==LOW){
    Serial.print("crouch");
    Serial.print ('\t');
     
  }
  else if(Yvalue <= 400 && Xvalue>400 && Xvalue<700 && s==LOW && j==HIGH){
    Serial.print("crouch and jump");
    Serial.print ('\t');
     
  }
  else if(Yvalue <= 400 && Xvalue>400 && Xvalue<700&& s==HIGH && j==LOW){
    Serial.print("crouch and shot");
    Serial.print ('\t');
     
  }
  if(Yvalue<=400 && Xvalue>400 && Xvalue<700 && s==HIGH && j==HIGH){
    Serial.print("crouch, jump and shot");
    Serial.print ('\t');
     
  }
}
void STANDING(){
    if (Xvalue>400 && Xvalue<700 && Yvalue>400 && Yvalue<700 && s==LOW && j==LOW){
    Serial.print("standing"); 
    Serial.print ('\t');
     
  }
  else if (Xvalue>400 && Xvalue<700 && Yvalue>400 && Yvalue<700 && s==LOW && j==HIGH){
    Serial.print("standing and jump");
    Serial.print ('\t'); 
     
  }
  else if (Xvalue>400 && Xvalue<700 && Yvalue>400 && Yvalue<700 && s==HIGH && j==LOW){
    Serial.print("standing and shot"); 
    Serial.print ('\t');
     
  }
  else if (Xvalue>400 && Xvalue<700 && Yvalue>400 && Yvalue<700 && s==HIGH&& j==HIGH){
    Serial.print("standing, jump and shot"); 
    Serial.print ('\t');
     
  }
}
void CRUZE(){
  if(Xvalue>=700 && Yvalue>=700 && s==LOW && j==LOW){
    Serial.print("right diagonal"); 
    Serial.print ('\t');
     
  }
  else if(Xvalue>=700 && Yvalue>=700 && s==LOW && j==HIGH){
    Serial.print("right diagonal and jump"); 
    Serial.print ('\t');
     
  }
  else if(Xvalue>=700 && Yvalue>=700 && s==HIGH && j==LOW){
    Serial.print("right diagonal and shot"); 
    Serial.print ('\t');
     
  }
  else if(Xvalue>=700 && Yvalue>=700 && s==HIGH && j==HIGH){
    Serial.print("right diagonal, jump and shot");
    Serial.print ('\t'); 
     
  }
  else if(Xvalue<=400 && Yvalue>=700 && s==LOW && j==LOW){
    Serial.print("left diagonal"); 
    Serial.print ('\t');
     
  }
  else if(Xvalue<=400 && Yvalue>=700 && s==LOW && j==HIGH){
    Serial.print("left diagonal and jump"); 
    Serial.print ('\t');
     
  }
  else if(Xvalue<=400 && Yvalue>=700 && s==HIGH && j==LOW){
    Serial.print("left diagonal and shot"); 
    Serial.print ('\t');
     
  }
  else if(Xvalue<=400 && Yvalue>=700 && s==HIGH && j==HIGH){
    Serial.print("left diagonal, jump and shot"); 
    Serial.print ('\t');
     
  }
}
void NOMOVE(){
  if(Xvalue>=700 && Yvalue<=400 && s==LOW && j==LOW){
    Serial.print("front");
    Serial.print ('\t');
      
  }
  else if(Xvalue>=700 && Yvalue<=400 && s==LOW && j==HIGH){
    Serial.print("front and jump");
    Serial.print ('\t');
     
  }
  else if(Xvalue>=700 && Yvalue<=400 && s==HIGH && j==LOW){
    Serial.print("front and shot");
    Serial.print ('\t');
     
  }
  else if(Xvalue>=700 && Yvalue<=400 && s==HIGH && j==HIGH){ 
    Serial.print("front, jump and shot");
    Serial.print ('\t');
     
  }
  else if(Xvalue<=400 && Yvalue<=400 && s==LOW && j==LOW){
    Serial.print("back");
    Serial.print ('\t');
     
  }
  else if(Xvalue<=400 && Yvalue<=400 && s==LOW && j==HIGH){
    Serial.print("back and jump");
    Serial.print ('\t');
     
  }
  else if(Xvalue<=400 && Yvalue<=400 && s==HIGH && j==LOW){
    Serial.print("back and shot");
    Serial.print ('\t');
     
  }
  else if(Xvalue<=400 && Yvalue<=400 && s==HIGH && j==HIGH){
    Serial.print("back, jump and shot");
    Serial.print ('\t');
     
  }
}

//funciones del segundo jugador que permiten su movimiento y acciones
void FRONT2(){
  if(Xvalue2>=700 && Yvalue2>400 && Yvalue2<700 && s2==LOW && j2==LOW){
    Serial.println("front");
      
  }
  else if(Xvalue2>=700 && Yvalue2>400 && Yvalue2<700 && s2==LOW && j2==HIGH){
    Serial.println("front and jump");
      
  }
  else if(Xvalue2>=700 && Yvalue2>400 && Yvalue2<700 && s2==HIGH && j2==LOW){
    Serial.println("front and shot");
      
  }
  else if(Xvalue2>=700 && Yvalue2>400 && Yvalue2<700 && s2==HIGH && j2==HIGH){
    Serial.println("front, jump and shoot");
      
  }
}
void BACK2(){
  if(Xvalue2 <= 400 &&  Yvalue2>400 && Yvalue2<700 && s2==LOW && j2==LOW){
    Serial.println("back");
     
  }
  else if(Xvalue2 <= 400 &&  Yvalue2>400 && Yvalue2<700 && s2==LOW && j2==HIGH){
    Serial.println("back and jump");
     
  }
  else if(Xvalue2 <= 400 &&  Yvalue2>400 && Yvalue2<700 && s2==HIGH && j2==LOW){
    Serial.println("back and shot");
     
  }
  else if(Xvalue2 <= 400 &&  Yvalue2>400 && Yvalue2<700 && s2==HIGH && j2==HIGH){
    Serial.println("back, jump and shot");
     
  }
}
void UP2(){
  if(Yvalue2>=700 && Xvalue2>400 && Xvalue2<700 && s2==LOW && j2==LOW){
    Serial.println("up");
     
  }
  else if(Yvalue2>=700 && Xvalue2>400 && Xvalue2<700 && s2==LOW && j2==HIGH){
    Serial.println("up and jump");
     
  }
  else if(Yvalue2>=700 && Xvalue2>400 && Xvalue2<700 && s2==HIGH && j2==LOW){
    Serial.println("up and shot");
     
  }
  else if(Yvalue2>=700 && Xvalue2>400 && Xvalue2<700&& s2==HIGH && j2==HIGH){
    Serial.println("up, jump and shot");
     
  }
}
void CROUCH2(){
  if(Yvalue2 <= 400 && Xvalue2>400 && Xvalue2<700&& s2==LOW && j2==LOW){
    Serial.println("crouch");
     
  }
  else if(Yvalue2 <= 400 && Xvalue2>400 && Xvalue2<700 && s2==LOW && j2==HIGH){
    Serial.println("crouch and jump");
     
  }
  else if(Yvalue2 <= 400 && Xvalue2>400 && Xvalue2<700&& s2==HIGH && j2==LOW){
    Serial.println("crouch and shot");
     
  }
  if(Yvalue2<=400 && Xvalue2>400 && Xvalue2<700 && s2==HIGH && j2==HIGH){
    Serial.println("crouch, jump and shot");
     
  }
}
void STANDING2(){
    if (Xvalue2>400 && Xvalue2<700 && Yvalue2>400 && Yvalue2<700 && s2==LOW && j2==LOW){
    Serial.println("standing"); 
     
  }
  else if (Xvalue2>400 && Xvalue2<700 && Yvalue2>400 && Yvalue2<700 && s2==LOW && j2==HIGH){
    Serial.println("standing and jump"); 
     
  }
  else if (Xvalue2>400 && Xvalue2<700 && Yvalue2>400 && Yvalue2<700 && s2==HIGH && j2==LOW){
    Serial.println("standing and shot"); 
     
  }
  else if (Xvalue2>400 && Xvalue2<700 && Yvalue2>400 && Yvalue2<700 && s2==HIGH&& j2==HIGH){
    Serial.println("standing, jump and shot"); 
     
  }
}
void CRUZE2(){
  if(Xvalue2>=700 && Yvalue2>=700 && s2==LOW && j2==LOW){
    Serial.println("right diagonal"); 
     
  }
  else if(Xvalue2>=700 && Yvalue2>=700 && s2==LOW && j2==HIGH){
    Serial.println("right diagonal and jump");
     
  }
  else if(Xvalue2>=700 && Yvalue2>=700 && s2==HIGH && j2==LOW){
    Serial.println("right diagonal and shot"); 
     
  }
  else if(Xvalue2>=700 && Yvalue2>=700 && s2==HIGH && j2==HIGH){
    Serial.println("right diagonal, jump and shot"); 
     
  }
  else if(Xvalue2<=400 && Yvalue2>=700 && s2==LOW && j2==LOW){
    Serial.println("left diagonal"); 
     
  }
  else if(Xvalue2<=400 && Yvalue2>=700 && s2==LOW && j2==HIGH){
    Serial.println("left diagonal and jump"); 
     
  }
  else if(Xvalue2<=400 && Yvalue2>=700 && s2==HIGH && j2==LOW){
    Serial.println("left diagonal and shot"); 
     
  }
  else if(Xvalue2<=400 && Yvalue2>=700 && s2==HIGH && j2==HIGH){
    Serial.println("left diagonal, jump and shot"); 
     
  }
}
void NOMOVE2(){
  if(Xvalue2>=700 && Yvalue2<=400 && s2==LOW && j2==LOW){
    Serial.println("front");
      
  }
  else if(Xvalue2>=700 && Yvalue2<=400 && s2==LOW && j2==HIGH){
    Serial.println("front and jump");
     
  }
  else if(Xvalue2>=700 && Yvalue2<=400 && s2==HIGH && j2==LOW){
    Serial.println("front and shot");
     
  }
  else if(Xvalue2>=700 && Yvalue2<=400 && s2==HIGH && j2==HIGH){ 
    Serial.println("front, jump and shot");
     
  }
  else if(Xvalue2<=400 && Yvalue2<=400 && s2==LOW && j2==LOW){
    Serial.println("back");
     
  }
  else if(Xvalue2<=400 && Yvalue2<=400 && s2==LOW && j2==HIGH){
    Serial.println("back and jump");
     
  }
  else if(Xvalue2<=400 && Yvalue2<=400 && s2==HIGH && j2==LOW){
    Serial.println("back and shot");
     
  }
  else if(Xvalue2<=400 && Yvalue2<=400 && s2==HIGH && j2==HIGH){
    Serial.println("back, jump and shot");
 
  }
}
