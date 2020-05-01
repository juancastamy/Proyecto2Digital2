//***************************************************************************************************************************************
/* Librería para el uso de la pantalla ILI9341 en modo 8 bits
 * Basado en el código de martinayotte - https://www.stm32duino.com/viewtopic.php?t=637
 * Adaptación, migración y creación de nuevas funciones: Pablo Mazariegos y José Morales
 * Con ayuda de: José Guerra
 * IE3027: Electrónica Digital 2 - 2019
 * 
 * Adapatación de CONTRA
 * IE3027: Electrónica Digital 2 - 2020
 * Juan Diego Castillo Amaya
 * Carné 17074
 * Hector Alejandro Klée González 
 * Carné 17118
 */
//***************************************************************************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include <TM4C123GH6PM.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

#include "bitmaps.h"
#include "font.h"
#include "lcd_registers.h"

#define LCD_RST PD_0
#define LCD_CS PD_1
#define LCD_RS PD_2
#define LCD_WR PD_3
#define LCD_RD PE_1
#define X PE_4
#define Y PE_5
#define shot PA_7
#define jump PA_6
#define start PA_5
//se define los puertos para el segundo jugador
#define X2 PE_2
#define Y2 PE_3
#define shot2 PA_2
#define jump2 PA_3
#define start2 PA_4
int DPINS[] = {PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7};  
int BLINK;
int MENSAJE[] = {0,0,0,0,0,0,0,0,0,0};
//varianles de disparo y salto primer jugado
int s;
int j;
int Xvalue;
int Yvalue;
int MAPX;
int MAPY;
int START;

//varianles de disparo y salto segundo jugado
int s2;
int j2;
int Xvalue2;
int MAPX2;
int Yvalue2;
int MAPY2;
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
int SET=0;
int xl;
int BIT=0;
int x=0;
int Fl=0;
int Bl=0;
//***************************************************************************************************************************************
// Functions Prototypes
//***************************************************************************************************************************************
void LCD_Init(void);
void LCD_CMD(uint8_t cmd);
void LCD_DATA(uint8_t data);
void SetWindows(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void LCD_Clear(unsigned int c);
void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c);
void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c);
void Rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c);
void FillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c);
void LCD_Print(String text, int x, int y, int fontSize, int color, int background);

void LCD_Bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]);
void LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[],int columns, int index, char flip, char offset);
//Main Screen
extern uint8_t title_screen[];
extern uint8_t characters[];
//Enemies
extern uint8_t boss[];
extern uint8_t spider[];
extern uint8_t soldier[];
//Bullet
extern uint8_t bullet[];
//Bill Rizer
extern uint8_t bill_dying[];
extern uint8_t bill_jumping[];
extern uint8_t bill_running[];
extern uint8_t bill_shooting[];
extern uint8_t bill_shooting_running[];
extern uint8_t bill_shooting_down[];
extern uint8_t bill_upward_shooting[];
extern uint8_t bill_upward_shooting_with_angle[];
extern uint8_t bill_downward_shooting_with_angle[];
//Lance Bean
extern uint8_t lance_dying[];
extern uint8_t lance_jumping[];
extern uint8_t lance_running[];
extern uint8_t lance_shooting[];
extern uint8_t lance_shooting_running[];
extern uint8_t lance_shooting_down[];
extern uint8_t lance_upward_shooting[];
extern uint8_t lance_upward_shooting_with_angle[];
extern uint8_t lance_downward_shooting_with_angle[];
void MANDOS(void);
void INICIO(void);

//***************************************************************************************************************************************
// Inicialización
//***************************************************************************************************************************************
void setup() {
  BLINK=0;
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
  SET=0;
  SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
  Serial.begin(9600);
  GPIOPadConfigSet(GPIO_PORTB_BASE, 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);
  Serial.println("Inicio");
  LCD_Init();
  LCD_Clear(0x00);
  
  //FillRect(0, 0, 194, 84, 0xff);
  LCD_Bitmap(108, 40, 105, 44, title_screen);//**ESTA LINEA DESCOMENTALA PARA PROBAR**
  LCD_Bitmap(131, 98, 59, 45, characters);//**ESTA LINEA DESCOMENTALA PARA PROBAR**
  
  
  //LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[],int columns, int index, char flip, char offset);
    
  //LCD_Bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]);
  
  /*
  for(int x = 0; x <319; x++){
    LCD_Bitmap(x, 52, 16, 16, tile2);
    LCD_Bitmap(x, 68, 16, 16, tile);
    
    LCD_Bitmap(x, 207, 16, 16, tile);
    LCD_Bitmap(x, 223, 16, 16, tile);
    x += 15;
 }*/
  
}
//***************************************************************************************************************************************
// Loop Infinito
//***************************************************************************************************************************************
void loop() {
  MANDOS();
  if (SET==0){
      INICIO();
  }
  if(SET==1){
      FillRect(0,100,320,30,0xC67B);
      FillRect(0,200,320,30,0xC67B);
      switch (MENSAJE[8]){
        case 0:
         LCD_Sprite(143,156,35,44,lance_shooting,2,0,Fl,0);
         break;
        case 1:
          Fl=1;
          LCD_Sprite(143,156,35,44,lance_shooting,2,0,Fl,0);
          break;
        case 2:
          Fl=0;
          LCD_Sprite(143,156,35,44,lance_shooting,2,0,Fl,0);
          break;
      }
      switch (MENSAJE[4]){
        case 0:
         LCD_Sprite(143,56,35,44,bill_shooting,2,0,Bl,0);
         break;
        case 1:
          Bl=1;
          LCD_Sprite(143,56,35,44,lance_shooting,2,0,Bl,0);
          break;
        case 2:
          Bl=0;
          LCD_Sprite(143,56,35,44,lance_shooting,2,0,Bl,0);
          break;
      }
  }
      /*if(MENSAJE[8]==2){
        if(x<320-35){
          x=x+1;
        delay(5);
        int xl=(x/10)%6;
        LCD_Sprite(x,156,35,44,lance_running,6,xl,0,0);
        V_line(x-1,156,44, 0x00);
        LCD_Sprite(0,156,35,44,bill_shooting,2,1,0,0);
      }
      }*/
      
  /*
  for(int x = 0; x <320-35; x++){
    delay(5);
    int anim = (x/10)%7;

    //LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[],int columns, int index, char flip, char offset);
    LCD_Sprite(x,100,35,44,soldier,7,anim,1,0);
    V_line( x -1, 100, 44, 0x00);  
  }*/
//******************************************************************************************************************************************  
  /*for(int x = 320-35; x >0; x--){
    delay(5);
    int anim2 = (x/10)%4;
    
    LCD_Sprite(x,100,41,44,spider,4,anim2,0,0);
    V_line( x + 41, 100, 44, 0x00); //16
  }*/

 MENSAJE[0]=0;
  MENSAJE[1]=0;
  MENSAJE[6]=0;
  MENSAJE[7]=0;
}
//***************************************************************************************************************************************
// Función para inicializar LCD
//***************************************************************************************************************************************
void LCD_Init(void) {
  pinMode(LCD_RST, OUTPUT);
  pinMode(LCD_CS, OUTPUT);
  pinMode(LCD_RS, OUTPUT);
  pinMode(LCD_WR, OUTPUT);
  pinMode(LCD_RD, OUTPUT);
  for (uint8_t i = 0; i < 8; i++){
    pinMode(DPINS[i], OUTPUT);
  }
  //****************************************
  // Secuencia de Inicialización
  //****************************************
  digitalWrite(LCD_CS, HIGH);
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_WR, HIGH);
  digitalWrite(LCD_RD, HIGH);
  digitalWrite(LCD_RST, HIGH);
  delay(5);
  digitalWrite(LCD_RST, LOW);
  delay(20);
  digitalWrite(LCD_RST, HIGH);
  delay(150);
  digitalWrite(LCD_CS, LOW);
  //****************************************
  LCD_CMD(0xE9);  // SETPANELRELATED
  LCD_DATA(0x20);
  //****************************************
  LCD_CMD(0x11); // Exit Sleep SLEEP OUT (SLPOUT)
  delay(100);
  //****************************************
  LCD_CMD(0xD1);    // (SETVCOM)
  LCD_DATA(0x00);
  LCD_DATA(0x71);
  LCD_DATA(0x19);
  //****************************************
  LCD_CMD(0xD0);   // (SETPOWER) 
  LCD_DATA(0x07);
  LCD_DATA(0x01);
  LCD_DATA(0x08);
  //****************************************
  LCD_CMD(0x36);  // (MEMORYACCESS)
  LCD_DATA(0x40|0x80|0x20|0x08); // LCD_DATA(0x19);
  //****************************************
  LCD_CMD(0x3A); // Set_pixel_format (PIXELFORMAT)
  LCD_DATA(0x05); // color setings, 05h - 16bit pixel, 11h - 3bit pixel
  //****************************************
  LCD_CMD(0xC1);    // (POWERCONTROL2)
  LCD_DATA(0x10);
  LCD_DATA(0x10);
  LCD_DATA(0x02);
  LCD_DATA(0x02);
  //****************************************
  LCD_CMD(0xC0); // Set Default Gamma (POWERCONTROL1)
  LCD_DATA(0x00);
  LCD_DATA(0x35);
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0x02);
  //****************************************
  LCD_CMD(0xC5); // Set Frame Rate (VCOMCONTROL1)
  LCD_DATA(0x04); // 72Hz
  //****************************************
  LCD_CMD(0xD2); // Power Settings  (SETPWRNORMAL)
  LCD_DATA(0x01);
  LCD_DATA(0x44);
  //****************************************
  LCD_CMD(0xC8); //Set Gamma  (GAMMASET)
  LCD_DATA(0x04);
  LCD_DATA(0x67);
  LCD_DATA(0x35);
  LCD_DATA(0x04);
  LCD_DATA(0x08);
  LCD_DATA(0x06);
  LCD_DATA(0x24);
  LCD_DATA(0x01);
  LCD_DATA(0x37);
  LCD_DATA(0x40);
  LCD_DATA(0x03);
  LCD_DATA(0x10);
  LCD_DATA(0x08);
  LCD_DATA(0x80);
  LCD_DATA(0x00);
  //****************************************
  LCD_CMD(0x2A); // Set_column_address 320px (CASET)
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0x3F);
  //****************************************
  LCD_CMD(0x2B); // Set_page_address 480px (PASET)
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0xE0);
//  LCD_DATA(0x8F);
  LCD_CMD(0x29); //display on 
  LCD_CMD(0x2C); //display on

  LCD_CMD(ILI9341_INVOFF); //Invert Off
  delay(120);
  LCD_CMD(ILI9341_SLPOUT);    //Exit Sleep
  delay(120);
  LCD_CMD(ILI9341_DISPON);    //Display on
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para enviar comandos a la LCD - parámetro (comando)
//***************************************************************************************************************************************
void LCD_CMD(uint8_t cmd) {
  digitalWrite(LCD_RS, LOW);
  digitalWrite(LCD_WR, LOW);
  GPIO_PORTB_DATA_R = cmd;
  digitalWrite(LCD_WR, HIGH);
}
//***************************************************************************************************************************************
// Función para enviar datos a la LCD - parámetro (dato)
//***************************************************************************************************************************************
void LCD_DATA(uint8_t data) {
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_WR, LOW);
  GPIO_PORTB_DATA_R = data;
  digitalWrite(LCD_WR, HIGH);
}
//***************************************************************************************************************************************
// Función para definir rango de direcciones de memoria con las cuales se trabajara (se define una ventana)
//***************************************************************************************************************************************
void SetWindows(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {
  LCD_CMD(0x2a); // Set_column_address 4 parameters
  LCD_DATA(x1 >> 8);
  LCD_DATA(x1);   
  LCD_DATA(x2 >> 8);
  LCD_DATA(x2);   
  LCD_CMD(0x2b); // Set_page_address 4 parameters
  LCD_DATA(y1 >> 8);
  LCD_DATA(y1);   
  LCD_DATA(y2 >> 8);
  LCD_DATA(y2);   
  LCD_CMD(0x2c); // Write_memory_start
}
//***************************************************************************************************************************************
// Función para borrar la pantalla - parámetros (color)
//***************************************************************************************************************************************
void LCD_Clear(unsigned int c){  
  unsigned int x, y;
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);   
  SetWindows(0, 0, 319, 239); // 479, 319);
  for (x = 0; x < 320; x++)
    for (y = 0; y < 240; y++) {
      LCD_DATA(c >> 8); 
      LCD_DATA(c); 
    }
  digitalWrite(LCD_CS, HIGH);
} 
//***************************************************************************************************************************************
// Función para dibujar una línea horizontal - parámetros ( coordenada x, cordenada y, longitud, color)
//*************************************************************************************************************************************** 
void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c) {  
  unsigned int i, j;
  LCD_CMD(0x02c); //write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);
  l = l + x;
  SetWindows(x, y, l, y);
  j = l;// * 2;
  for (i = 0; i < l; i++) {
      LCD_DATA(c >> 8); 
      LCD_DATA(c); 
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar una línea vertical - parámetros ( coordenada x, cordenada y, longitud, color)
//*************************************************************************************************************************************** 
void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c) {  
  unsigned int i,j;
  LCD_CMD(0x02c); //write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);
  l = l + y;
  SetWindows(x, y, x, l);
  j = l; //* 2;
  for (i = 1; i <= j; i++) {
    LCD_DATA(c >> 8); 
    LCD_DATA(c);
  }
  digitalWrite(LCD_CS, HIGH);  
}
//***************************************************************************************************************************************
// Función para dibujar un rectángulo - parámetros ( coordenada x, cordenada y, ancho, alto, color)
//***************************************************************************************************************************************
void Rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c) {
  H_line(x  , y  , w, c);
  H_line(x  , y+h, w, c);
  V_line(x  , y  , h, c);
  V_line(x+w, y  , h, c);
}
//***************************************************************************************************************************************
// Función para dibujar un rectángulo relleno - parámetros ( coordenada x, cordenada y, ancho, alto, color)
//***************************************************************************************************************************************
void FillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c) {
  unsigned int i;
  for (i = 0; i < h; i++) {
    H_line(x  , y  , w, c);
    H_line(x  , y+i, w, c);
  }
}
//***************************************************************************************************************************************
// Función para dibujar texto - parámetros ( texto, coordenada x, cordenada y, color, background) 
//***************************************************************************************************************************************
void LCD_Print(String text, int x, int y, int fontSize, int color, int background) {
  int fontXSize ;
  int fontYSize ;
  
  if(fontSize == 1){
    fontXSize = fontXSizeSmal ;
    fontYSize = fontYSizeSmal ;
  }
  if(fontSize == 2){
    fontXSize = fontXSizeBig ;
    fontYSize = fontYSizeBig ;
  }
  
  char charInput ;
  int cLength = text.length();
  //Serial.println(cLength,DEC);
  int charDec ;
  int c ;
  int charHex ;
  char char_array[cLength+1];
  text.toCharArray(char_array, cLength+1) ;
  for (int i = 0; i < cLength ; i++) {
    charInput = char_array[i];
    //Serial.println(char_array[i]);
    charDec = int(charInput);
    digitalWrite(LCD_CS, LOW);
    SetWindows(x + (i * fontXSize), y, x + (i * fontXSize) + fontXSize - 1, y + fontYSize );
    long charHex1 ;
    for ( int n = 0 ; n < fontYSize ; n++ ) {
      if (fontSize == 1){
        charHex1 = pgm_read_word_near(smallFont + ((charDec - 32) * fontYSize) + n);
      }
      if (fontSize == 2){
        charHex1 = pgm_read_word_near(bigFont + ((charDec - 32) * fontYSize) + n);
      }
      for (int t = 1; t < fontXSize + 1 ; t++) {
        if (( charHex1 & (1 << (fontXSize - t))) > 0 ) {
          c = color ;
        } else {
          c = background ;
        }
        LCD_DATA(c >> 8);
        LCD_DATA(c);
      }
    }
    digitalWrite(LCD_CS, HIGH);
  }
}
//***************************************************************************************************************************************
// Función para dibujar una imagen a partir de un arreglo de colores (Bitmap) Formato (Color 16bit R 5bits G 6bits B 5bits)
//***************************************************************************************************************************************
void LCD_Bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]){  
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW); 
  
  unsigned int x2, y2;
  x2 = x+width;
  y2 = y+height;
  SetWindows(x, y, x2-1, y2-1);
  unsigned int k = 0;
  unsigned int i, j;

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      LCD_DATA(bitmap[k]);
      LCD_DATA(bitmap[k+1]);
      //LCD_DATA(bitmap[k]);    
      k = k + 2;
     } 
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar una imagen sprite - los parámetros columns = número de imagenes en el sprite, index = cual desplegar, flip = darle vuelta
//***************************************************************************************************************************************
void LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[],int columns, int index, char flip, char offset){
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW); 

  unsigned int x2, y2;
  x2 =   x+width;
  y2=    y+height;
  SetWindows(x, y, x2-1, y2-1);
  int k = 0;
  int ancho = ((width*columns));
  if(flip){
  for (int j = 0; j < height; j++){
      k = (j*(ancho) + index*width -1 - offset)*2;
      k = k+width*2;
     for (int i = 0; i < width; i++){
      LCD_DATA(bitmap[k]);
      LCD_DATA(bitmap[k+1]);
      k = k - 2;
     } 
  }
  }else{
     for (int j = 0; j < height; j++){
      k = (j*(ancho) + index*width + 1 + offset)*2;
     for (int i = 0; i < width; i++){
      LCD_DATA(bitmap[k]);
      LCD_DATA(bitmap[k+1]);
      k = k + 2;
     } 
  }
    
    
    }
  digitalWrite(LCD_CS, HIGH);
}
void MANDOS(void){
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
    if(SET==0){
      LCD_Clear(0x00);
      SET++;
    }
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
  
  if(Xvalue>=3000){
    MENSAJE[4]=2;
    Serial.println(Xvalue);
  }
  if(Xvalue<=1500){
    MENSAJE[4]=1;
  }
  if(Xvalue>1500 && Xvalue<3000){
    MENSAJE[4]=0;
  }
  if(Yvalue>=1500){
    MENSAJE[5]=2;
  }
  if(Yvalue<=3000){
    MENSAJE[5]=1;
  }
  if(Yvalue>1500 && Yvalue<3000){
    MENSAJE[5]=0;
  }

  if(s2==HIGH){
    ju2=1;
  }
  if (s2==LOW && ju2==1){
    MENSAJE[6]=1;
    ju2=0;
    if(SET==0){
      LCD_Clear(0x00);
      SET++;
    }
  }

  if(j2==HIGH){
    sh2=1;
  }
  if(j2==LOW && sh2==1){
    MENSAJE[7]=1;
    sh2=0;
  }
  
  if(Xvalue2>=1500){
    MENSAJE[8]=2;
  }
  if(Xvalue2<=1500){
    MENSAJE[8]=1;
  }
  if(Xvalue2>1500 && Xvalue2<3000){
    MENSAJE[8]=0;
  }
  if(Yvalue2>=1500){
    MENSAJE[9]=2;
  }
  if(Yvalue2<=3000){
    MENSAJE[9]=1;
  }
  if(Yvalue2>1500 && Yvalue2<3000){
    MENSAJE[9]=0;
  }
  for(BIT=0;BIT<=9;BIT++){
    Serial.print(MENSAJE[BIT]);
  }
  Serial.println("");
}
void INICIO(void){
  if(MENSAJE[2]==0 && MENSAJE[3]==0 && SET==0){
    switch(BLINK){
      case 0:
        if(BLINK==0){
          String text1 = "Press A";
          LCD_Print(text1, 100, 150, 2, 0xffff, 0x00);
          delay(100);
          }
          BLINK++;
          break;
      case 1:
        if(BLINK==1){
          String text1 = "Press A";
          LCD_Print(text1, 100, 150, 2, 0x00, 0x00);
          delay(100);        
          }
          BLINK=0;
          break;
    }
  }
}
