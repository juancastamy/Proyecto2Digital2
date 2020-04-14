//se define los puertos para el primer jugador
#define X A0
#define Y A1
#define shot 2
#define jump 3
//se define los puertos para el segundo jugador
#define X2 A2
#define Y2 A3
#define shot2 4
#define jump2 5

//varianles de disparo y salto primer jugado
int s;
int j;
int Xvalue;
int Yvalue;

//varianles de disparo y salto segundo jugado
int s2;
int j2;
int Xvalue2;
int Yvalue2;

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
  Serial.begin(9600);
  //definicion de puertos primer jugador
  pinMode(shot,INPUT);
  pinMode(jump,INPUT);

  //definicion de puertos segundo jugador
  pinMode(shot2,INPUT);
  pinMode(jump2,INPUT);
  
  //se limpian las variables de ambos jugadores 
  s=0;
  j=0;
  s2=0;
  j2=0;
}

void loop() {
  //se leen los botones del jugador 1
  s=digitalRead(shot);
  j=digitalRead(jump);
  
  //se leen los botones del jugador 2
  s2=digitalRead(shot2);
  j2=digitalRead(jump2);

   //Lectura de puerto analogico primer jugador
  Xvalue=analogRead(X);
  Yvalue=analogRead(Y);

  //Lectura de puerto analogico segundo jugador
  Xvalue2=analogRead(X2);
  Yvalue2=analogRead(Y2);
  
  //se llaman las funciones del primer jugador
  Serial.println("PLAYER ONE");
  FRONT();
  BACK();
  UP();
  CROUCH();
  STANDING();   
  CRUZE();
  NOMOVE();

  //se llaman las funciones del segundo jugador
  Serial.println("PLAYER TWO");
  FRONT2();
  BACK2();
  UP2();
  CROUCH2();
  STANDING2();   
  CRUZE2();
  NOMOVE2();
}
//funciones del primer jugador que permiten su movimiento y acciones
void FRONT(){
  if(Xvalue>=700 && Yvalue>400 && Yvalue<700 && s==LOW && j==LOW){
    Serial.println("front");
    delay(500);  
  }
  else if(Xvalue>=700 && Yvalue>400 && Yvalue<700 && s==LOW && j==HIGH){
    Serial.println("front and jump");
    delay(500);  
  }
  else if(Xvalue>=700 && Yvalue>400 && Yvalue<700 && s==HIGH && j==LOW){
    Serial.println("front and shot");
    delay(500);  
  }
  else if(Xvalue>=700 && Yvalue>400 && Yvalue<700 && s==HIGH && j==HIGH){
    Serial.println("front, jump and shoot");
    delay(500);  
  }
}
void BACK(){
  if(Xvalue <= 400 &&  Yvalue>400 && Yvalue<700 && s==LOW && j==LOW){
    Serial.println("back");
    delay(500); 
  }
  else if(Xvalue <= 400 &&  Yvalue>400 && Yvalue<700 && s==LOW && j==HIGH){
    Serial.println("back and jump");
    delay(500); 
  }
  else if(Xvalue <= 400 &&  Yvalue>400 && Yvalue<700 && s==HIGH && j==LOW){
    Serial.println("back and shot");
    delay(500); 
  }
  else if(Xvalue <= 400 &&  Yvalue>400 && Yvalue<700 && s==HIGH && j==HIGH){
    Serial.println("back, jump and shot");
    delay(500); 
  }
}
void UP(){
  if(Yvalue>=700 && Xvalue>400 && Xvalue<700 && s==LOW && j==LOW){
    Serial.println("up");
    delay(500); 
  }
  else if(Yvalue>=700 && Xvalue>400 && Xvalue<700 && s==LOW && j==HIGH){
    Serial.println("up and jump");
    delay(500); 
  }
  else if(Yvalue>=700 && Xvalue>400 && Xvalue<700 && s==HIGH && j==LOW){
    Serial.println("up and shot");
    delay(500); 
  }
  else if(Yvalue>=700 && Xvalue>400 && Xvalue<700&& s==HIGH && j==HIGH){
    Serial.println("up, jump and shot");
    delay(500); 
  }
}
void CROUCH(){
  if(Yvalue <= 400 && Xvalue>400 && Xvalue<700&& s==LOW && j==LOW){
    Serial.println("crouch");
    delay(500); 
  }
  else if(Yvalue <= 400 && Xvalue>400 && Xvalue<700 && s==LOW && j==HIGH){
    Serial.println("crouch and jump");
    delay(500); 
  }
  else if(Yvalue <= 400 && Xvalue>400 && Xvalue<700&& s==HIGH && j==LOW){
    Serial.println("crouch and shot");
    delay(500); 
  }
  if(Yvalue<=400 && Xvalue>400 && Xvalue<700 && s==HIGH && j==HIGH){
    Serial.println("crouch, jump and shot");
    delay(500); 
  }
}
void STANDING(){
    if (Xvalue>400 && Xvalue<700 && Yvalue>400 && Yvalue<700 && s==LOW && j==LOW){
    Serial.println("standing"); 
    delay(500); 
  }
  else if (Xvalue>400 && Xvalue<700 && Yvalue>400 && Yvalue<700 && s==LOW && j==HIGH){
    Serial.println("standing and jump"); 
    delay(500); 
  }
  else if (Xvalue>400 && Xvalue<700 && Yvalue>400 && Yvalue<700 && s==HIGH && j==LOW){
    Serial.println("standing and shot"); 
    delay(500); 
  }
  else if (Xvalue>400 && Xvalue<700 && Yvalue>400 && Yvalue<700 && s==HIGH&& j==HIGH){
    Serial.println("standing, jump and shot"); 
    delay(500); 
  }
}
void CRUZE(){
  if(Xvalue>=700 && Yvalue>=700 && s==LOW && j==LOW){
    Serial.println("right diagonal"); 
    delay(500); 
  }
  else if(Xvalue>=700 && Yvalue>=700 && s==LOW && j==HIGH){
    Serial.println("right diagonal and jump"); 
    delay(500); 
  }
  else if(Xvalue>=700 && Yvalue>=700 && s==HIGH && j==LOW){
    Serial.println("right diagonal and shot"); 
    delay(500); 
  }
  else if(Xvalue>=700 && Yvalue>=700 && s==HIGH && j==HIGH){
    Serial.println("right diagonal, jump and shot"); 
    delay(500); 
  }
  else if(Xvalue<=400 && Yvalue>=700 && s==LOW && j==LOW){
    Serial.println("left diagonal"); 
    delay(500); 
  }
  else if(Xvalue<=400 && Yvalue>=700 && s==LOW && j==HIGH){
    Serial.println("left diagonal and jump"); 
    delay(500); 
  }
  else if(Xvalue<=400 && Yvalue>=700 && s==HIGH && j==LOW){
    Serial.println("left diagonal and shot"); 
    delay(500); 
  }
  else if(Xvalue<=400 && Yvalue>=700 && s==HIGH && j==HIGH){
    Serial.println("left diagonal, jump and shot"); 
    delay(500); 
  }
}
void NOMOVE(){
  if(Xvalue>=700 && Yvalue<=400 && s==LOW && j==LOW){
    Serial.println("front");
    delay(500);  
  }
  else if(Xvalue>=700 && Yvalue<=400 && s==LOW && j==HIGH){
    Serial.println("front and jump");
    delay(500); 
  }
  else if(Xvalue>=700 && Yvalue<=400 && s==HIGH && j==LOW){
    Serial.println("front and shot");
    delay(500); 
  }
  else if(Xvalue>=700 && Yvalue<=400 && s==HIGH && j==HIGH){ 
    Serial.println("front, jump and shot");
    delay(500); 
  }
  else if(Xvalue<=400 && Yvalue<=400 && s==LOW && j==LOW){
    Serial.println("back");
    delay(500); 
  }
  else if(Xvalue<=400 && Yvalue<=400 && s==LOW && j==HIGH){
    Serial.println("back and jump");
    delay(500); 
  }
  else if(Xvalue<=400 && Yvalue<=400 && s==HIGH && j==LOW){
    Serial.println("back and shot");
    delay(500); 
  }
  else if(Xvalue<=400 && Yvalue<=400 && s==HIGH && j==HIGH){
    Serial.println("back, jump and shot");
    delay(500); 
  }
}

//funciones del segundo jugador que permiten su movimiento y acciones
void FRONT2(){
  if(Xvalue2>=700 && Yvalue2>400 && Yvalue2<700 && s2==LOW && j2==LOW){
    Serial.println("front");
    delay(500);  
  }
  else if(Xvalue2>=700 && Yvalue2>400 && Yvalue2<700 && s2==LOW && j2==HIGH){
    Serial.println("front and jump");
    delay(500);  
  }
  else if(Xvalue2>=700 && Yvalue2>400 && Yvalue2<700 && s2==HIGH && j2==LOW){
    Serial.println("front and shot");
    delay(500);  
  }
  else if(Xvalue2>=700 && Yvalue2>400 && Yvalue2<700 && s2==HIGH && j2==HIGH){
    Serial.println("front, jump and shoot");
    delay(500);  
  }
}
void BACK2(){
  if(Xvalue2 <= 400 &&  Yvalue2>400 && Yvalue2<700 && s2==LOW && j2==LOW){
    Serial.println("back");
    delay(500); 
  }
  else if(Xvalue2 <= 400 &&  Yvalue2>400 && Yvalue2<700 && s2==LOW && j2==HIGH){
    Serial.println("back and jump");
    delay(500); 
  }
  else if(Xvalue2 <= 400 &&  Yvalue2>400 && Yvalue2<700 && s2==HIGH && j2==LOW){
    Serial.println("back and shot");
    delay(500); 
  }
  else if(Xvalue2 <= 400 &&  Yvalue2>400 && Yvalue2<700 && s2==HIGH && j2==HIGH){
    Serial.println("back, jump and shot");
    delay(500); 
  }
}
void UP2(){
  if(Yvalue2>=700 && Xvalue2>400 && Xvalue2<700 && s2==LOW && j2==LOW){
    Serial.println("up");
    delay(500); 
  }
  else if(Yvalue2>=700 && Xvalue2>400 && Xvalue2<700 && s2==LOW && j2==HIGH){
    Serial.println("up and jump");
    delay(500); 
  }
  else if(Yvalue2>=700 && Xvalue2>400 && Xvalue2<700 && s2==HIGH && j2==LOW){
    Serial.println("up and shot");
    delay(500); 
  }
  else if(Yvalue2>=700 && Xvalue2>400 && Xvalue2<700&& s2==HIGH && j2==HIGH){
    Serial.println("up, jump and shot");
    delay(500); 
  }
}
void CROUCH2(){
  if(Yvalue2 <= 400 && Xvalue2>400 && Xvalue2<700&& s2==LOW && j2==LOW){
    Serial.println("crouch");
    delay(500); 
  }
  else if(Yvalue2 <= 400 && Xvalue2>400 && Xvalue2<700 && s2==LOW && j2==HIGH){
    Serial.println("crouch and jump");
    delay(500); 
  }
  else if(Yvalue2 <= 400 && Xvalue2>400 && Xvalue2<700&& s2==HIGH && j2==LOW){
    Serial.println("crouch and shot");
    delay(500); 
  }
  if(Yvalue2<=400 && Xvalue2>400 && Xvalue2<700 && s2==HIGH && j2==HIGH){
    Serial.println("crouch, jump and shot");
    delay(500); 
  }
}
void STANDING2(){
    if (Xvalue2>400 && Xvalue2<700 && Yvalue2>400 && Yvalue2<700 && s2==LOW && j2==LOW){
    Serial.println("standing"); 
    delay(500); 
  }
  else if (Xvalue2>400 && Xvalue2<700 && Yvalue2>400 && Yvalue2<700 && s2==LOW && j2==HIGH){
    Serial.println("standing and jump"); 
    delay(500); 
  }
  else if (Xvalue2>400 && Xvalue2<700 && Yvalue2>400 && Yvalue2<700 && s2==HIGH && j2==LOW){
    Serial.println("standing and shot"); 
    delay(500); 
  }
  else if (Xvalue2>400 && Xvalue2<700 && Yvalue2>400 && Yvalue2<700 && s2==HIGH&& j2==HIGH){
    Serial.println("standing, jump and shot"); 
    delay(500); 
  }
}
void CRUZE2(){
  if(Xvalue2>=700 && Yvalue2>=700 && s2==LOW && j2==LOW){
    Serial.println("right diagonal"); 
    delay(500); 
  }
  else if(Xvalue2>=700 && Yvalue2>=700 && s2==LOW && j2==HIGH){
    Serial.println("right diagonal and jump");
    delay(500); 
  }
  else if(Xvalue2>=700 && Yvalue2>=700 && s2==HIGH && j2==LOW){
    Serial.println("right diagonal and shot"); 
    delay(500); 
  }
  else if(Xvalue2>=700 && Yvalue2>=700 && s2==HIGH && j2==HIGH){
    Serial.println("right diagonal, jump and shot"); 
    delay(500); 
  }
  else if(Xvalue2<=400 && Yvalue2>=700 && s2==LOW && j2==LOW){
    Serial.println("left diagonal"); 
    delay(500); 
  }
  else if(Xvalue2<=400 && Yvalue2>=700 && s2==LOW && j2==HIGH){
    Serial.println("left diagonal and jump"); 
    delay(500); 
  }
  else if(Xvalue2<=400 && Yvalue2>=700 && s2==HIGH && j2==LOW){
    Serial.println("left diagonal and shot"); 
    delay(500); 
  }
  else if(Xvalue2<=400 && Yvalue2>=700 && s2==HIGH && j2==HIGH){
    Serial.println("left diagonal, jump and shot"); 
    delay(500); 
  }
}
void NOMOVE2(){
  if(Xvalue2>=700 && Yvalue2<=400 && s2==LOW && j2==LOW){
    Serial.println("front");
    delay(500);  
  }
  else if(Xvalue2>=700 && Yvalue2<=400 && s2==LOW && j2==HIGH){
    Serial.println("front and jump");
    delay(500); 
  }
  else if(Xvalue2>=700 && Yvalue2<=400 && s2==HIGH && j2==LOW){
    Serial.println("front and shot");
    delay(500); 
  }
  else if(Xvalue2>=700 && Yvalue2<=400 && s2==HIGH && j2==HIGH){ 
    Serial.println("front, jump and shot");
    delay(500); 
  }
  else if(Xvalue2<=400 && Yvalue2<=400 && s2==LOW && j2==LOW){
    Serial.println("back");
    delay(500); 
  }
  else if(Xvalue2<=400 && Yvalue2<=400 && s2==LOW && j2==HIGH){
    Serial.println("back and jump");
    delay(500); 
  }
  else if(Xvalue2<=400 && Yvalue2<=400 && s2==HIGH && j2==LOW){
    Serial.println("back and shot");
    delay(500); 
  }
  else if(Xvalue2<=400 && Yvalue2<=400 && s2==HIGH && j2==HIGH){
    Serial.println("back, jump and shot");
    delay(500); 
  }
}
