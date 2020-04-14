#define X A0
#define Y A1
#define shot 2
#define jump 3
int s;
int j;
int Xvalue;
int Yvalue;
void FRONT();
void BACK();
void UP();
void CROUCH();
void STANDING();
void CRUZE();
void NOMOVE();
void setup() {
  Serial.begin(9600);
  pinMode(shot,INPUT);
  pinMode(jump,INPUT);
  Xvalue=analogRead(X);
  Yvalue=analogRead(Y);
  s=0;
  j=0;
  // put your setup code here, to run once:
}

void loop() {
  
  s=digitalRead(shot);
  j=digitalRead(jump);
  Serial.print(Xvalue);
  Serial.print("\t");
  Serial.println(Yvalue);
  //moviendose
  FRONT();
  BACK();
  UP();
  CROUCH();
  STANDING();   
  CRUZE();
  NOMOVE();
}

void FRONT(){
  if(Xvalue>=700 && Yvalue>400 && Yvalue<700 && s==LOW && j==LOW){
    Serial.println("front");
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500);  
  }
  else if(Xvalue>=700 && Yvalue>400 && Yvalue<700 && s==LOW && j==HIGH){
    Serial.println("front and jump");
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500);  
  }
  else if(Xvalue>=700 && Yvalue>400 && Yvalue<700 && s==HIGH && j==LOW){
    Serial.println("front and shot");
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500);  
  }
  else if(Xvalue>=700 && Yvalue>400 && Yvalue<700 && s==HIGH && j==HIGH){
    Serial.println("front, jump and shoot");
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500);  
  }
}
void BACK(){
  if(Xvalue <= 400 &&  Yvalue>400 && Yvalue<700 && s==LOW && j==LOW){
    Serial.println("back");
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }
  else if(Xvalue <= 400 &&  Yvalue>400 && Yvalue<700 && s==LOW && j==HIGH){
    Serial.println("back and jump");
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }
  else if(Xvalue <= 400 &&  Yvalue>400 && Yvalue<700 && s==HIGH && j==LOW){
    Serial.println("back and shot");
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }
  else if(Xvalue <= 400 &&  Yvalue>400 && Yvalue<700 && s==HIGH && j==HIGH){
    Serial.println("back, jump and shot");
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }
}
void UP(){
  if(Yvalue>=700 && Xvalue>400 && Xvalue<700 && s==LOW && j==LOW){
    Serial.println("up");
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }
  else if(Yvalue>=700 && Xvalue>400 && Xvalue<700 && s==LOW && j==HIGH){
    Serial.println("up and jump");
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }
  else if(Yvalue>=700 && Xvalue>400 && Xvalue<700 && s==HIGH && j==LOW){
    Serial.println("up and shot");
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }
  else if(Yvalue>=700 && Xvalue>400 && Xvalue<700&& s==HIGH && j==HIGH){
    Serial.println("up, jump and shot");
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }
}
void CROUCH(){
  if(Yvalue <= 400 && Xvalue>400 && Xvalue<700&& s==LOW && j==LOW){
    Serial.println("crouch");
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }
  else if(Yvalue <= 400 && Xvalue>400 && Xvalue<700 && s==LOW && j==HIGH){
    Serial.println("crouch and jump");
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }
  else if(Yvalue <= 400 && Xvalue>400 && Xvalue<700&& s==HIGH && j==LOW){
    Serial.println("crouch and shot");
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }
  if(Yvalue<=400 && Xvalue>400 && Xvalue<700 && s==HIGH && j==HIGH){
    Serial.println("crouch, jump and shot");
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }
}
void STANDING(){
    if (Xvalue>400 && Xvalue<700 && Yvalue>400 && Yvalue<700 && s==LOW && j==LOW){
    Serial.println("standing"); 
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }
  else if (Xvalue>400 && Xvalue<700 && Yvalue>400 && Yvalue<700 && s==LOW && j==HIGH){
    Serial.println("standing and jump"); 
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }
  else if (Xvalue>400 && Xvalue<700 && Yvalue>400 && Yvalue<700 && s==HIGH && j==LOW){
    Serial.println("standing and shot"); 
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }
  else if (Xvalue>400 && Xvalue<700 && Yvalue>400 && Yvalue<700 && s==HIGH&& j==HIGH){
    Serial.println("standing, jump and shot"); 
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }
}
void CRUZE(){
  if(Xvalue>=700 && Yvalue>=700 && s==LOW && j==LOW){
    Serial.println("right diagonal"); 
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }
  else if(Xvalue>=700 && Yvalue>=700 && s==LOW && j==HIGH){
    Serial.println("right diagonal and jump"); 
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }
  else if(Xvalue>=700 && Yvalue>=700 && s==HIGH && j==LOW){
    Serial.println("right diagonal and shot"); 
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }
  else if(Xvalue>=700 && Yvalue>=700 && s==HIGH && j==HIGH){
    Serial.println("right diagonal, jump and shot"); 
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }
  else if(Xvalue<=400 && Yvalue>=700 && s==LOW && j==LOW){
    Serial.println("left diagonal"); 
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }
  else if(Xvalue<=400 && Yvalue>=700 && s==LOW && j==HIGH){
    Serial.println("left diagonal and jump"); 
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }
  else if(Xvalue<=400 && Yvalue>=700 && s==HIGH && j==LOW){
    Serial.println("left diagonal and shot"); 
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }
  else if(Xvalue<=400 && Yvalue>=700 && s==HIGH && j==HIGH){
    Serial.println("left diagonal, jump and shot"); 
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }
}
void NOMOVE(){
  if(Xvalue>=700 && Yvalue<=400 && s==LOW && j==LOW){
    Serial.println("front");
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500);  
  }
  else if(Xvalue>=700 && Yvalue<=400 && s==LOW && j==HIGH){
    Serial.println("front and jump");
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }
  else if(Xvalue>=700 && Yvalue<=400 && s==HIGH && j==LOW){
    Serial.println("front and shot");
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }
  else if(Xvalue>=700 && Yvalue<=400 && s==HIGH && j==HIGH){ 
    Serial.println("front, jump and shot");
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }
  else if(Xvalue<=400 && Yvalue<=400 && s==LOW && j==LOW){
    Serial.println("back");
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }
  else if(Xvalue<=400 && Yvalue<=400 && s==LOW && j==HIGH){
    Serial.println("back and jump");
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }
  else if(Xvalue<=400 && Yvalue<=400 && s==HIGH && j==LOW){
    Serial.println("back and shot");
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }
  else if(Xvalue<=400 && Yvalue<=400 && s==HIGH && j==HIGH){
    Serial.println("back, jump and shot");
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }
}
