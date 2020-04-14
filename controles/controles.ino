#define X A0
#define Y A1
#define shot 2
#define jump 3
int s;
int j;
int Xvalue;
int Yvalue;
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
  if(Xvalue>=700 && 400<=Yvalue<=700){
    Serial.println("front");
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500);  
  }

  else if(Xvalue <= 400 &&  400<=Yvalue<=700){
    Serial.println("back");
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }

  else if(Yvalue>=700 && 400<=Xvalue<=700){
    Serial.println("up");
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }

  else if(Yvalue <= 400 && 400<=Xvalue<=700){
    Serial.println("couch");
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }
      else {
    Serial.println("standing"); 
    Xvalue=analogRead(X);
    Yvalue=analogRead(Y);
    delay(500); 
  }
}
