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
int SET=0;
int xl;
int BIT=0;
int l=0;
int Fl=0;
int Bl=0;
int b=0;
int bl=0;
int BILL=0;
int LANCE=0;
//SOLDADOS IZQUIERDA-DERECHA
int animSOLD;
int SOLDADO=0;
int XSL=0;
//****//
int SOLDADO2=0;
int XSL2=0;
//SOLDADOS DERECHA-IZQUIERDA
int SOLDADO3=0;
int XSR=285;
int SOLDADO4=0;
int XSR2=285;

//ARAÑAS IZQUIERDA-DERECHA
int animARA;
int ARANA1=0;
int XAL1=0;
int ARANA3=0;
int XAL2=0;
//ARAÑAS DERECHA-IZQUIERDA
int ARANA2=0;
int XAR1=279;
int ARANA4=0;
int XAR2=279;
//BOSS IZQUIERDA-DERECHA
int animBOSS;
int BOSSL=0;
int XBL=131;
//BOSS DERECHA-IZQUIERDA
int BOSSR=0;
int XBR=131;

 int LIFEM=20;

//POSICION DE BILL
int XBILL=143;
int YBILL=56;
int YBLB=71;
//POSICION DE LANCE
int XLANCE=143;
int YLANCE=156;
int YBLL=171;
//BALA BILL DERECHA-AIRZUIERDA
int animBULLET;
int BALA=0;
int XBAL=143;
int N=0;

//BALA BILL IRQUIERDA-DERECHA
int BALA2=0;
int XBAL2=176;
int N2=0;

//BALA LANCE DERECHA-AIRZUIERDA
int BALA3=0;
int XBAB=143;
int N3=0;

//BALA LANCE IRQUIERDA-DERECHA
int BALA4=0;
int XBAB2=176;
int N4=0;

//CONTADOR DE ENEMIGOS
int EN1=random(0,3);
int EN2=random(0,3);
int EN3=random(0,1);
//VARIABLES MUERTE BILL
int animDEADB=0;
int XDB=143;
int DEADB=0;

//VARIABLES MUERTE LANCE
int DEADL = 0;
int XDL = 143;
//VIDA DE PERSONAGES
int LIFEB=3;
int LIFEL=3;
//CONTADOR DE MUERTES 
int KILL_BILL=19;
int KILL_LANCE=20;
//int anim;
//int anim2;
//int anim3;
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
extern uint8_t lives [];
void MANDOS(void);
void INICIO(void);
void MOVIMIENTOB(void);
void MOVIMIENTOL(void);
//SOLDADOS LEFT
void SOLDADOL(void);
void SOLDADOL2(void);
//SOLDADOS RIGHT
void SOLDADOR(void);
void SOLDADOR2(void);
//ARANAS LEFT
void ARANAL(void);
void ARANAL2(void);
//ARANAS RIGHT
void ARANAR(void);
void ARANAR2(void);
//BOSS LEFT
void BOSS_LEFT(void);
//BOSS RIGHT
void BOSS_RIGHT(void);
//BALA BILL
void BALAL(void);
void BALAR(void);
void BALALL(void);
void BALARL(void);
//VIDAS BILL
void VIDASB(void);
//VIDAS LANCE
void VIDASL(void);
//MUERTE BILL
void MUERTEB (void);
void MUERTEL(void);
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
    VIDASB();
    VIDASL();
    FillRect(0,100,320,30,0xC67B);
    FillRect(0,200,320,30,0xC67B);    
//****************************************************BILL*************************************************************************        
    if(LIFEB!=0){
      MOVIMIENTOB();
      if(XSL==120 && LIFEB!=0){
        FillRect(0,56,143,44,0x00);
        LIFEB--;
        XSL=0;
        EN1=random(0,3);
      }
      if(XSL>=0 && XSL<=120 && EN1==0){
        SOLDADOL();
      }
      if((XSL+20)>=XBAL && N==1){
          FillRect(0,56,143,44,0x00);
          KILL_BILL++;
          EN1=random(0,3);
          N=0;
          XSL=0;
          XBAL=143;
        }
        if(N==1 && XBAL>=0 && XBAL<=143){
          BALAL();
        }
        else{
          N=0;
          XBAL=143;
        }
        //*****************************************DERECHA - IZQUIERDA**********************************************************
        if(XSR<=164 && LIFEB!=0){
          FillRect(178,56,143,44,0x00);
          EN1=random(0,3);
          LIFEB--;
          XSR=279;
        }
        if(XSR>=165 && XSR<=285 && EN1==1){
          SOLDADOR();
        }
        if(XSR<=XBAL2 && N2==1){
          FillRect(178,56,142,44,0x00);
          EN1=random(0,3);
          KILL_BILL++;
          N2=0;
          XSR=279;
          XBAL2=176;
        }
        if(N2==1 && XBAL2>=176 && XBAL2<=320){
          BALAR();
        }
        else{
          N2=0;
          XBAL2=176;
        }
      //*****************************************IZQUIERDA - DERECHA***********************************************************
      if(XAL1==110 && LIFEB!=0){
        FillRect(0,56,143,44,0x00);
        LIFEB--;
        XAL1=0;
        EN1=random(0,3);
      }
      if(XAL1>=0 && XAL1<=110 && EN1==2){
        ARANAL();
      }
      if((XAL1+30)>=XBAL && N==1){
          FillRect(0,56,143,44,0x00);
          EN1=random(0,3);
          KILL_BILL++;
          N=0;
          XAL1=0;
          XBAL=143;
        }
        if(N==1 && XBAL>=0 &&XBAL<=143){
          BALAL();
        }
        else{
          N=0;
          XBAL=143;
        }
        //*****************************************DERECHA - IZQUIERDA**********************************************************
        if(XAR1==164 && LIFEB!=0){
          FillRect(178,56,143,44,0x00);
          EN1=random(0,3);
          LIFEB--;
          XAR1=279;
        }
        if(XAR1>=164 && XAR1<=279 && EN1==3){
          ARANAR();
        }
        if(XAR1<=XBAL2 && N2==1){
          FillRect(178,56,142,44,0x00);
          EN1=random(0,3);
          KILL_BILL++;
          N2=0;
          XAR1=279;
          XBAL2=176;
        }
        if(N2==1 && XBAL2>=176 && XBAL2<=320){
          BALAR();
        }
        else{
          N2=0;
          XBAL2=176;
        }
    }
      
        //***************************************LANCE*******************************************************
    if(LIFEL!=0){
      MOVIMIENTOL();
      if(XSL2==120 && LIFEL!=0){
        FillRect(0,156,143,44,0x00);
        LIFEL--;
        XSL2=0;
        EN2=random(0,3);
      }
      if(XSL2>=0 && XSL2<=120 && EN2==0){
        SOLDADOL2();
      }
      if((XSL2+20)>=XBAB && N4==1){
          FillRect(0,156,143,44,0x00);
          KILL_LANCE++;
          EN2=random(0,3);
          N4=0;
          XSL2=0;
          XBAB=143;
        }
        if(N4==1 && XBAB>=0 && XBAB<=143){
          BALALL();
        }
        else{
          N4=0;
          XBAB=143;
        }
      //*****************************************DERECHA - IZQUIERDA**********************************************************
        if(XSR2<=164 && LIFEL!=0){
          FillRect(178,156,143,44,0x00);
          EN2=random(0,3);
          LIFEL--;
          XSR2=279;
        }
        if(XSR2>=165 && XSR2<=285 && EN2==1){
          SOLDADOR2();
        }
        if(XSR2<=XBAB2 && N3==1){
          FillRect(178,156,142,44,0x00);
          EN2=random(0,3);
          KILL_LANCE++;
          N3=0;
          XSR2=279;
          XBAB2=176;
        }
        if(N3==1 && XBAB2>=176 && XBAB2<=320){
          BALARL();
        }
        else{
          N3=0;
          XBAB2=176;
        }
         //*****************************************IZQUIERDA - DERECHA***********************************************************
      if(XAL2==110 && LIFEL!=0){
        FillRect(0,156,143,44,0x00);
        LIFEL--;
        XAL2=0;
        EN2=random(0,3);
      }
      if(XAL2>=0 && XAL2<=110 && EN2==2){
        ARANAL2();
      }
      if((XAL2+30)>=XBAB && N4==1){
          FillRect(0,156,143,44,0x00);
          EN2=random(0,3);
          KILL_LANCE++;
          N4=0;
          XAL2=0;
          XBAB=143;
        }
        if(N4==1 && XBAB>=0 &&XBAB<=143){
          BALALL();
        }
        else{
          N4=0;
          XBAB=143;
        }
        //*****************************************DERECHA - IZQUIERDA**********************************************************
        if(XAR2==164 && LIFEL!=0){
          FillRect(178,156,143,44,0x00);
          EN2=random(0,3);
          LIFEL--;
          XAR2=279;
        }
        if(XAR2>=164 && XAR2<=279 && EN2==3){
          ARANAR2();
        }
        if(XAR2<=XBAB2 && N3==1){
          FillRect(178,156,142,44,0x00);
          EN2=random(0,3);
          KILL_LANCE++;
          N3=0;
          XAR2=279;
          XBAB2=176;
        }
        if(N3==1 && XBAB2>=176 && XBAB2<=280){
          BALARL();
        }
        else{
          N3=0;
          XBAB2=176;
        }

        //ARANAR();
        //BOSS_LEFT();
        //BOSS_RIGHT();
    }
   if(KILL_BILL>=20 & KILL_LANCE>=20){
    SET++;
    LCD_Clear(0x00);
   }
  }
  //***************************************************2PANTALLA**********************************************************
  if(SET==2){
    FillRect(0,210,320,30,0xC67B);
    VIDASB();
    VIDASL();
    YBILL=166;
    YLANCE=166;
    XBILL=10;
    XLANCE=275;
    YBLB=181;
    YBLL=181;
    if(LIFEB!=0 && LIFEL!=0){
      MOVIMIENTOB();
      MOVIMIENTOL();
      if(XBR==35 && LIFEB!=0){
        FillRect(35,150,240,60,0X00);
        EN3=random(0,1);
        LIFEB--;
        XBR=131;
      }
      if(XBR>=35 && XBR<=131 && EN3==0){
        BOSS_RIGHT(); 
      }
      if(XBR<=XBAL2 && N2==1){
        FillRect(35,150,240,60,0X00);
        EN3=random(0,1);
        LIFEM--;
        N2=0;
        XBAL2=30;
        XBR=131;
      }
      if(N2==1 && XBAL2>=30 && XBAL2<=160){
          BALAR();
        }
        else{
          N2=0;
          XBAL2=30;
        }

     if((XBL+57)==278 && LIFEL!=0){
        FillRect(35,150,240,60,0X00);
        EN3=random(0,1);
        LIFEL--;
        XBL=131;
     }
     if(XBL>=XBAB && N4==1){
       FillRect(35,150,240,60,0X00);
        EN3=random(0,1);
        LIFEM--;
        N4=0;
        XBAB=280;
        XBL=131;
     }
     if(XBL>=133 && XBL<=278 && EN3==1){
        BOSS_LEFT(); 
      }
      if(N4==1 && XBAB>=160 &&XBAB<=280){
          BALALL();
        }
        else{
          N4=0;
          XBAB=280;
        }
      /*
       * if(XAR2==164 && LIFEL!=0){
          FillRect(178,156,143,44,0x00);
          EN2=random(0,3);
          LIFEL--;
          XAR2=279;
        }
        if(XAR2>=164 && XAR2<=279 && EN2==3){
          ARANAR2();
        }
        if(XAR2<=XBAB2 && N3==1){
          FillRect(178,156,142,44,0x00);
          EN2=random(0,3);
          KILL_LANCE++;
          N3=0;
          XAR2=279;
          XBAB2=176;
        }
        if(N3==1 && XBAB2>=176 && XBAB2<=280){
          BALARL();
        }
        else{
          N3=0;
          XBAB2=176;
        }
       */
    }
  }
  
 // Serial.println(LIFEB);
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
    sh = 1;
  }
  if (s==LOW && sh==1){
    MENSAJE[0] = 1;
    sh=0;
    }

  if(j==HIGH){
    ju=1;
  }
  if(j==LOW && ju==1){
    MENSAJE[1]=1;
    if(SET==0){
      LCD_Clear(0x00);
      SET++;
    }
    ju=0;
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
    //Serial.println(Xvalue);
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
    sh2=1;
  }
  if (s2==LOW && sh2==1){
    MENSAJE[6]=1;
    sh2=0;
  }

  if(j2==HIGH){
    ju2=1;
  }
  if(j2==LOW && ju2==1){
    MENSAJE[7]=1;
    if(SET==0){
      LCD_Clear(0x00);
      SET++;
    }
    ju2=0;
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
  /*for(BIT=0;BIT<=9;BIT++){
    Serial.print(MENSAJE[BIT]);
  }*/
  //Serial.println("");
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
void MOVIMIENTOB(void){
  switch (BILL){
        case 0:
          if(MENSAJE[4]==0 && MENSAJE[5]==0){
              LCD_Sprite(XBILL,YBILL,35,44,bill_shooting,2,0,Bl,0);
            BILL++;
          }
          break;
        case 1:
          if(MENSAJE[4]==0 && MENSAJE[5]==0){
          if(MENSAJE[0]==1){
              LCD_Sprite(XBILL,YBILL,35,44,bill_shooting,2,1,Bl,0);
              N2=1;
            }
            else{
              LCD_Sprite(XBILL,YBILL,35,44,bill_shooting,2,0,Bl,0);
            }
          }
          if(MENSAJE[4]==2 && MENSAJE[5]==1){
            LCD_Sprite(XBILL,YBILL,35,44,bill_downward_shooting_with_angle,3,0,Bl,0);
            }
          if(MENSAJE[4]==1 && MENSAJE[5]==1){
            Bl=1;
            LCD_Sprite(XBILL,YBILL,35,44,bill_shooting_down,1,0,Bl,0);
            BILL++;
            }
          if(MENSAJE[4]==0 && MENSAJE[5]==1){
            LCD_Sprite(XBILL,YBILL,35,44,bill_shooting_down,1,0,Bl,0);
            }
          if(MENSAJE[4]==0 && MENSAJE[5]==0){
            LCD_Sprite(XBILL,YBILL,35,44,bill_shooting,2,0,Bl,0);
            }
          if(MENSAJE[4]==1 && MENSAJE[5]==0){
            Bl=1;
            if(MENSAJE[0]==1){
              LCD_Sprite(XBILL,YBILL,35,44,bill_shooting,2,1,Bl,0);
            }
            else{
              LCD_Sprite(XBILL,YBILL,35,44,bill_shooting,2,0,Bl,0);
            }
            BILL++;
          }
          break;
        case 2:
          if(MENSAJE[4]==0 && MENSAJE[5]==0){
            if(MENSAJE[0]==1){
               LCD_Sprite(XBILL,YBILL,35,44,bill_shooting,2,1,Bl,0);
               N=1;
              }
            else{
              LCD_Sprite(XBILL,YBILL,35,44,bill_shooting,2,0,Bl,0);
            }
          }
          if(MENSAJE[4]==1 && MENSAJE[5]==1){
              LCD_Sprite(XBILL,YBILL,35,44,bill_downward_shooting_with_angle,3,0,Bl,0);
            }
            if(MENSAJE[4]==0 && MENSAJE[5]==1){
              LCD_Sprite(XBILL,YBILL,35,44,bill_shooting_down,1,0,Bl,0);
            }
            if(MENSAJE[4]==0 && MENSAJE[5]==0){
              LCD_Sprite(XBILL,YBILL,35,44,bill_shooting,2,0,Bl,0);
            }
          if(MENSAJE[4]==2 && MENSAJE[5]==1){
            Bl=0;
            LCD_Sprite(XBILL,YBILL,35,44,bill_downward_shooting_with_angle,3,0,Bl,0);
            BILL=0;
            }
          if(MENSAJE[4]==2 && MENSAJE[5]==0){
            Bl=0;
            if(MENSAJE[0]==1){
              LCD_Sprite(XBILL,YBILL,35,44,bill_shooting,2,1,Bl,0);
            }
            else{
              LCD_Sprite(XBILL,YBILL,35,44,bill_shooting,2,0,Bl,0);
            }
            BILL=0;
          }
          break;
      }
}
void MOVIMIENTOL(void){
      switch (LANCE){
        case 0:
          if(MENSAJE[8]==0){
            LCD_Sprite(XLANCE,YLANCE,35,44,lance_shooting,2,0,Fl,0);
            LANCE++;
          }
          break;
        case 1:
        if(MENSAJE[8]==0 && MENSAJE[9]==0){
            if(MENSAJE[6]==1){
               LCD_Sprite(XLANCE,YLANCE,35,44,lance_shooting,2,1,Fl,0);
               N3=1;
              }
            else{
              LCD_Sprite(XLANCE,YLANCE,35,44,lance_shooting,2,0,Fl,0);
            }
          }
          if(MENSAJE[8]==2 && MENSAJE[9]==2){
            LCD_Sprite(XLANCE,YLANCE,35,44,lance_upward_shooting_with_angle,3,0,Fl,0);
            }
          if(MENSAJE[8]==1 && MENSAJE[9]==2){
            Fl=1;
            LCD_Sprite(XLANCE,YLANCE,35,44,lance_upward_shooting_with_angle,3,0,Fl,0);
            LANCE++;
            }
          if(MENSAJE[8]==0 && MENSAJE[9]==2){
            LCD_Sprite(XLANCE,YLANCE,35,44,lance_upward_shooting,2,0,Fl,0);
            }
          if(MENSAJE[8]==2 && MENSAJE[9]==1){
            LCD_Sprite(XLANCE,YLANCE,35,44,lance_downward_shooting_with_angle,3,0,Fl,0);
            }
          if(MENSAJE[8]==1 && MENSAJE[9]==1){
            Fl=1;
            LCD_Sprite(XLANCE,YLANCE,35,44,lance_downward_shooting_with_angle,3,0,Fl,0);
            LANCE++;
            }
          if(MENSAJE[8]==0 && MENSAJE[9]==1){
            LCD_Sprite(XLANCE,YLANCE,35,44,lance_shooting_down,1,0,Fl,0);
            }
          if(MENSAJE[8]==0 && MENSAJE[9]==0){
            LCD_Sprite(XLANCE,YLANCE,35,44,lance_shooting,2,0,Fl,0);
            }
          if(MENSAJE[8]==1 && MENSAJE[9]==0){
            Fl=1;
            if(MENSAJE[6]==1){
               LCD_Sprite(XLANCE,YLANCE,35,44,lance_shooting,2,1,Fl,0);
              }
            else{
              LCD_Sprite(XLANCE,YLANCE,35,44,lance_shooting,2,0,Fl,0);
            }
            LANCE++;
            }
          break;
        case 2:
        if(MENSAJE[8]==0 && MENSAJE[9]==0){
            if(MENSAJE[6]==1){
              N4=1;
              LCD_Sprite(XLANCE,YLANCE,35,44,lance_shooting,2,1,Fl,0);
              }
            else{
              LCD_Sprite(XLANCE,YLANCE,35,44,lance_shooting,2,0,Fl,0);
            }
          }
          if(MENSAJE[8]==1 && MENSAJE[9]==1){
              LCD_Sprite(XLANCE,YLANCE,35,44,lance_downward_shooting_with_angle,3,0,Fl,0);
            }
            if(MENSAJE[8]==0 && MENSAJE[9]==1){
              LCD_Sprite(XLANCE,YLANCE,35,44,lance_shooting_down,1,0,Fl,0);
            }
          if(MENSAJE[8]==1 && MENSAJE[9]==2){
              LCD_Sprite(XLANCE,YLANCE,35,44,lance_upward_shooting_with_angle,3,0,Fl,0);
          }
           if(MENSAJE[8]==2 && MENSAJE[9]==2){
            Fl=0;
            LCD_Sprite(XLANCE,YLANCE,35,44,lance_upward_shooting_with_angle,3,0,Fl,0);
            LANCE=0;
            }
            if(MENSAJE[8]==0 && MENSAJE[9]==2){
              LCD_Sprite(XLANCE,YLANCE,35,44,lance_upward_shooting,2,0,Fl,0);
            }
            if(MENSAJE[8]==0 && MENSAJE[9]==0){
              LCD_Sprite(XLANCE,YLANCE,35,44,lance_shooting,2,0,Fl,0);
            }
          if(MENSAJE[8]==2 && MENSAJE[9]==1){
            Fl=0;
            LCD_Sprite(XLANCE,YLANCE,35,44,lance_downward_shooting_with_angle,3,0,Fl,0);
            LANCE=0;
          }
          if(MENSAJE[8]==2 && MENSAJE[9]==0){
            Fl=0;
            if(MENSAJE[6]==1){
               LCD_Sprite(XLANCE,YLANCE,35,44,lance_shooting,2,1,Fl,0);
              }
            else{
              LCD_Sprite(XLANCE,YLANCE,35,44,lance_shooting,2,0,Fl,0);
            }
            LANCE=0;
          }
          break;
      }
  return;
}
void MUERTEB (void){
  switch(DEADB){
    if(LIFEB==0){
      case 0:
        LCD_Sprite(143,56,35,44,bill_dying,8,0,0,0);
        DEADB++;
        break;
      case 1:
        LCD_Sprite(143,56,35,44,bill_dying,8,3,0,0);
        XDB=XDB+5;
        DEADB++;
        break;
      case 2:
        LCD_Sprite(143,56,35,44,bill_dying,8,4,0,0);
        XDB=XDB+5;
        DEADB++;
        break;
      case 3:
        LCD_Sprite(143,56,35,44,bill_dying,8,5,0,0);
        XDB=XDB+5;
        DEADB++;
        break;
      case 4:
        LCD_Sprite(143,56,35,44,bill_dying,8,6,0,0);
        XDB=XDB+5;
        DEADB++;
        break;
      case 5:
        LCD_Sprite(143,56,35,44,bill_dying,8,7,0,0);
        XDB=XDB+5;
        DEADB++;
        break;
    }
  }
}
void MUERTEL (void){
  switch(DEADL){
    if(LIFEL==0){
      case 0:
        LCD_Sprite(143,156,35,44,lance_dying,8,0,0,0);
        DEADL++;
        break;
      case 1:
        LCD_Sprite(143,156,35,44,lance_dying,8,3,0,0);
        XDL=XDL+5;
        DEADL++;
        break;
      case 2:
        LCD_Sprite(143,156,35,44,lance_dying,8,4,0,0);
        XDL=XDL+5;
        DEADL++;
        break;
      case 3:
        LCD_Sprite(143,156,35,44,lance_dying,8,5,0,0);
        XDL=XDL+5;
        DEADL++;
        break;
      case 4:
        LCD_Sprite(143,156,35,44,lance_dying,8,6,0,0);
        XDL=XDL+5;
        DEADL++;
        break;
      case 5:
        LCD_Sprite(143,156,35,44,lance_dying,8,7,0,0);
        XDL=XDL+5;
        DEADL++;
        break;
    }
  }
}
//********************************************************************SOLDADOS******************************************************************
void SOLDADOL(void){
  switch (SOLDADO){
    case 0:
      animSOLD = (XSL/5)%7;
      LCD_Sprite(XSL,56,35,44,soldier,7,animSOLD,1,0);
      V_line( XSL-1, 56, 44, 0x00);
      XSL=XSL+5;
      SOLDADO++;
      break;
    case 1:
      animSOLD = (XSL/5)%7;
      LCD_Sprite(XSL,56,35,44,soldier,7,animSOLD,1,0);
      V_line( XSL-1, 56, 44, 0x00);
      XSL=XSL+5;
      SOLDADO++;
      break;
    case 2:
      animSOLD = (XSL/5)%7;
      LCD_Sprite(XSL,56,35,44,soldier,7,animSOLD,1,0);
      V_line( XSL-1, 56, 44, 0x00);
      XSL=XSL+5;
      SOLDADO++;
      break;
    case 3:
      animSOLD = (XSL/5)%7;
      LCD_Sprite(XSL,56,35,44,soldier,7,animSOLD,1,0);
      V_line( XSL-1, 56, 44, 0x00);
      XSL=XSL+5;
      SOLDADO++;
      break;
    case 4:
      animSOLD = (XSL/5)%7;
      LCD_Sprite(XSL,56,35,44,soldier,7,animSOLD,1,0);
      V_line( XSL-1, 56, 44, 0x00);
      XSL=XSL+5;
      SOLDADO++;
      break;
    case 5:
      animSOLD = (XSL/5)%7;
      LCD_Sprite(XSL,56,35,44,soldier,7,animSOLD,1,0);
      V_line( XSL-1, 56, 44, 0x00);
      XSL=XSL+5;
      SOLDADO++;
      break;
    case 6:
      animSOLD = (XSL/5)%7;
      LCD_Sprite(XSL,56,35,44,soldier,7,animSOLD,1,0);
      V_line( XSL-1, 56, 44, 0x00);
      XSL=XSL+5;
      SOLDADO++;
      break;
    case 7:
      animSOLD = (XSL/5)%7;
      LCD_Sprite(XSL,56,35,44,soldier,7,animSOLD,1,0);
      V_line( XSL-1, 56, 44, 0x00);
      XSL=XSL+5;
      SOLDADO=0;
      break;
   }
}
void SOLDADOL2(void){
  switch (SOLDADO2){
    case 0:
      animSOLD = (XSL2/5)%7;
      LCD_Sprite(XSL2,156,35,44,soldier,7,animSOLD,1,0);
      V_line(XSL2-1, 156, 44, 0x00);
      XSL2=XSL2+5;
      SOLDADO2++;
      break;
    case 1:
      animSOLD = (XSL2/5)%7;
      LCD_Sprite(XSL2,156,35,44,soldier,7,animSOLD,1,0);
      V_line( XSL2-1, 156, 44, 0x00);
      XSL2=XSL2+5;
      SOLDADO2++;
      break;
    case 2:
      animSOLD = (XSL2/5)%7;
      LCD_Sprite(XSL2,156,35,44,soldier,7,animSOLD,1,0);
      V_line(XSL2-1, 156, 44, 0x00);
      XSL2=XSL2+5;
      SOLDADO2++;
      break;
    case 3:
      animSOLD = (XSL2/5)%7;
      LCD_Sprite(XSL2,156,35,44,soldier,7,animSOLD,1,0);
      V_line( XSL2-1, 156, 44, 0x00);
      XSL2=XSL2+5;
      SOLDADO2++;
      break;
    case 4:
      animSOLD = (XSL2/5)%7;
      LCD_Sprite(XSL2,156,35,44,soldier,7,animSOLD,1,0);
      V_line( XSL2-1, 156, 44, 0x00);
      XSL2=XSL2+5;
      SOLDADO2++;
      break;
    case 5:
      animSOLD = (XSL2/5)%7;
      LCD_Sprite(XSL2,156,35,44,soldier,7,animSOLD,1,0);
      V_line( XSL2-1, 156, 44, 0x00);
      XSL2=XSL2+5;
      SOLDADO2++;
      break;
    case 6:
      animSOLD = (XSL2/5)%7;
      LCD_Sprite(XSL2,156,35,44,soldier,7,animSOLD,1,0);
      V_line( XSL2-1, 156, 44, 0x00);
      XSL2=XSL2+5;
      SOLDADO2++;
      break;
    case 7:
      animSOLD = (XSL2/5)%7;
      LCD_Sprite(XSL2,156,35,44,soldier,7,animSOLD,1,0);
      V_line( XSL2-1, 156, 44, 0x00);
      XSL2=XSL2+5;
      SOLDADO2=0;
      break;
  }
}
//************************************************************************************SOLDADO*************************************************************
void SOLDADOR(void){
  switch (SOLDADO3){
    case 0:
      animSOLD = (XSR/5)%7;
      LCD_Sprite(XSR,56,35,44,soldier,7,animSOLD,0,0);
      V_line(XSR+35, 56, 44, 0x00);
      XSR=XSR-5;
      SOLDADO3++;
      break;
    case 1:
      animSOLD = (XSR/5)%7;
      LCD_Sprite(XSR,56,35,44,soldier,7,animSOLD,0,0);
      V_line(XSR+35, 56, 44, 0x00);
      XSR=XSR-5;
      SOLDADO3++;
      break;
    case 2:
      animSOLD = (XSR/5)%7;
      LCD_Sprite(XSR,56,35,44,soldier,7,animSOLD,0,0);
      V_line(XSR+35, 56, 44, 0x00);
      XSR=XSR-5;
      SOLDADO3++;
      break;
    case 3:
      animSOLD = (XSR/5)%7;
      LCD_Sprite(XSR,56,35,44,soldier,7,animSOLD,0,0);
      V_line(XSR+35, 56, 44, 0x00);
      XSR=XSR-5;
      SOLDADO3++;
      break;
    case 4:
      animSOLD = (XSR/5)%7;
      LCD_Sprite(XSR,56,35,44,soldier,7,animSOLD,0,0);
      V_line(XSR+35, 56, 44, 0x00);
      XSR=XSR-5;
      SOLDADO3++;
      break;
    case 5:
      animSOLD = (XSR/5)%7;
      LCD_Sprite(XSR,56,35,44,soldier,7,animSOLD,0,0);
      V_line( XSR+35, 56, 44, 0x00);
      XSR=XSR-5;
      SOLDADO3++;
      break;
    case 6:
      animSOLD = (XSR/5)%7;
      LCD_Sprite(XSR,56,35,44,soldier,7,animSOLD,0,0);
      V_line( XSL2+35, 56, 44, 0x00);
      XSR=XSR-5;
      SOLDADO3++;
      break;
    case 7:
      animSOLD = (XSR/5)%7;
      LCD_Sprite(XSR,56,35,44,soldier,7,animSOLD,0,0);
      V_line( XSR+35, 56, 44, 0x00);
      XSR=XSR-5;
      SOLDADO3=0;
      break;
  }
}
void SOLDADOR2(void){
  switch (SOLDADO4){
    case 0:
      animSOLD = (XSR2/5)%7;
      LCD_Sprite(XSR2,156,35,44,soldier,7,animSOLD,0,0);
      V_line(XSR2+35, 156, 44, 0x00);
      XSR2=XSR2-5;
      SOLDADO4++;
      break;
    case 1:
      animSOLD = (XSR2/5)%7;
      LCD_Sprite(XSR2,156,35,44,soldier,7,animSOLD,0,0);
      V_line(XSR2+35, 156, 44, 0x00);
      XSR2=XSR2-5;
      SOLDADO4++;
      break;
    case 2:
      animSOLD = (XSR2/5)%7;
      LCD_Sprite(XSR2,156,35,44,soldier,7,animSOLD,0,0);
      V_line(XSR2+35, 156, 44, 0x00);
      XSR2=XSR2-5;
      SOLDADO4++;
      break;
    case 3:
      animSOLD = (XSR2/5)%7;
      LCD_Sprite(XSR2,156,35,44,soldier,7,animSOLD,0,0);
      V_line(XSR2+35, 156, 44, 0x00);
      XSR2=XSR2-5;
      SOLDADO4++;
      break;
    case 4:
      animSOLD = (XSR2/5)%7;
      LCD_Sprite(XSR2,156,35,44,soldier,7,animSOLD,0,0);
      V_line(XSR2+35, 156, 44, 0x00);
      XSR2=XSR2-5;
      SOLDADO4++;
      break;
    case 5:
      animSOLD = (XSR2/5)%7;
      LCD_Sprite(XSR2,156,35,44,soldier,7,animSOLD,0,0);
      V_line( XSR2+35, 156, 44, 0x00);
      XSR2=XSR2-5;
      SOLDADO4++;
      break;
    case 6:
      animSOLD = (XSR2/5)%7;
      LCD_Sprite(XSR2,156,35,44,soldier,7,animSOLD,0,0);
      V_line( XSL2+35, 156, 44, 0x00);
      XSR2=XSR2-5;
      SOLDADO4++;
      break;
    case 7:
      animSOLD = (XSR2/5)%7;
      LCD_Sprite(XSR2,156,35,44,soldier,7,animSOLD,0,0);
      V_line( XSR2+35, 156, 44, 0x00);
      XSR2=XSR2-5;
      SOLDADO4=0;
      break;
  }
}

//********************************************************************ARAÑAS******************************************************************
void ARANAL(void){
  switch (ARANA1){
    case 0:
      animARA = (XAL1/5)%4;
      LCD_Sprite(XAL1,56,41,44,spider,4,animARA,1,0);
      V_line(XAL1-1, 56, 44, 0x00);
      V_line(XAL1-2, 56, 44, 0x00);
      V_line(XAL1-3, 56, 44, 0x00);
      V_line(XAL1-4, 56, 44, 0x00);
      XAL1=XAL1+5;
      ARANA1++;
      break;
    case 1:
      animARA = (XAL1/5)%4;
      LCD_Sprite(XAL1,56,41,44,spider,4,animARA,1,0);
      V_line(XAL1-1, 56, 44, 0x00);
      V_line(XAL1-2, 56, 44, 0x00);
      V_line(XAL1-3, 56, 44, 0x00);
      V_line(XAL1-4, 56, 44, 0x00);
      XAL1=XAL1+5;
      ARANA1++;
      break;
    case 2:
      animARA = (XAL1/5)%4;
      LCD_Sprite(XAL1,56,41,44,spider,4,animARA,1,0);
      V_line(XAL1-1, 56, 44, 0x00);
      V_line(XAL1-2, 56, 44, 0x00);
      V_line(XAL1-3, 56, 44, 0x00);
      V_line(XAL1-4, 56, 44, 0x00);
      XAL1=XAL1+5;
      ARANA1++;
      break;
    case 3:
      animARA = (XAL1/5)%4;
      LCD_Sprite(XAL1,56,41,44,spider,4,animARA,1,0);
      V_line(XAL1-1, 56, 44, 0x00);
      V_line(XAL1-2, 56, 44, 0x00);
      V_line(XAL1-3, 56, 44, 0x00);
      V_line(XAL1-4, 56, 44, 0x00);
      XAL1=XAL1+5;
      ARANA1++;
      break;
    case 4:
      animARA = (XAL1/5)%4;
      LCD_Sprite(XAL1,56,41,44,spider,4,animARA,1,0);
      V_line(XAL1-1, 56, 44, 0x00);
      V_line(XAL1-2, 56, 44, 0x00);
      V_line(XAL1-3, 56, 44, 0x00);
      V_line(XAL1-4, 56, 44, 0x00);
      XAL1=XAL1+5;
      ARANA1=0;
      break;
  }
}
void ARANAR(void){
  switch (ARANA2){
    case 0:
      animARA = (XAR1/5)%4;
      LCD_Sprite(XAR1,56,41,44,spider,4,animARA,0,0);
      V_line(XAR1+42, 56, 44, 0x00);
      V_line(XAR1+43, 56, 44, 0x00);
      V_line(XAR1+44, 56, 44, 0x00);
      V_line(XAR1+45, 56, 44, 0x00);
      V_line(XAR1+46, 56, 44, 0x00);
      XAR1=XAR1-5;
      ARANA2++;
      break;
    case 1:
      animARA = (XAR1/5)%4;
      LCD_Sprite(XAR1,56,41,44,spider,4,animARA,0,0);
      V_line(XAR1+42, 56, 44, 0x00);
      V_line(XAR1+43, 56, 44, 0x00);
      V_line(XAR1+44, 56, 44, 0x00);
      V_line(XAR1+45, 56, 44, 0x00);
      V_line(XAR1+46, 56, 44, 0x00);
      XAR1=XAR1-5;
      ARANA2++;
      break;
    case 2:
      animARA = (XAR1/5)%4;
      LCD_Sprite(XAR1,56,41,44,spider,4,animARA,0,0);
      V_line(XAR1+42, 56, 44, 0x00);
      V_line(XAR1+43, 56, 44, 0x00);
      V_line(XAR1+44, 56, 44, 0x00);
      V_line(XAR1+45, 56, 44, 0x00);
      V_line(XAR1+46, 56, 44, 0x00);
      XAR1=XAR1-5;
      ARANA2++;
      break;
    case 3:
      animARA = (XAR1/5)%4;
      LCD_Sprite(XAR1,56,41,44,spider,4,animARA,0,0);
      V_line(XAR1+42, 56, 44, 0x00);
      V_line(XAR1+43, 56, 44, 0x00);
      V_line(XAR1+44, 56, 44, 0x00);
      V_line(XAR1+45, 56, 44, 0x00);
      V_line(XAR1+46, 56, 44, 0x00);
      XAR1=XAR1-5;
      ARANA2++;
      break;
    case 4:
      animARA = (XAR1/5)%4;
      LCD_Sprite(XAR1,56,41,44,spider,4,animARA,0,0);
      V_line(XAR1+42, 56, 44, 0x00);
      V_line(XAR1+43, 56, 44, 0x00);
      V_line(XAR1+44, 56, 44, 0x00);
      V_line(XAR1+45, 56, 44, 0x00);
      V_line(XAR1+46, 56, 44, 0x00);
      XAR1=XAR1-5;
      ARANA2=0;
      break;
  }
}
void ARANAL2(void){
  switch (ARANA3){
    case 0:
      animARA = (XAL2/5)%4;
      LCD_Sprite(XAL2,156,41,44,spider,4,animARA,1,0);
      V_line(XAL2-1, 156, 44, 0x00);
      V_line(XAL2-2, 156, 44, 0x00);
      V_line(XAL2-3, 156, 44, 0x00);
      V_line(XAL2-4, 156, 44, 0x00);
      XAL2=XAL2+5;
      ARANA3++;
      break;
    case 1:
      animARA = (XAL2/5)%4;
      LCD_Sprite(XAL2,156,41,44,spider,4,animARA,1,0);
      V_line(XAL2-1, 156, 44, 0x00);
      V_line(XAL2-2, 156, 44, 0x00);
      V_line(XAL2-3, 156, 44, 0x00);
      V_line(XAL2-4, 156, 44, 0x00);
      XAL2=XAL2+5;
      ARANA3++;
      break;
    case 2:
      animARA = (XAL2/5)%4;
      LCD_Sprite(XAL2,156,41,44,spider,4,animARA,1,0);
      V_line(XAL2-1, 156, 44, 0x00);
      V_line(XAL2-2, 156, 44, 0x00);
      V_line(XAL2-3, 156, 44, 0x00);
      V_line(XAL2-4, 156, 44, 0x00);
      XAL2=XAL2+5;
      ARANA3++;
      break;
    case 3:
      animARA = (XAL2/5)%4;
      LCD_Sprite(XAL2,156,41,44,spider,4,animARA,1,0);
      V_line(XAL2-1, 156, 44, 0x00);
      V_line(XAL2-2, 156, 44, 0x00);
      V_line(XAL2-3, 156, 44, 0x00);
      V_line(XAL2-4, 156, 44, 0x00);
      XAL2=XAL2+5;
      ARANA3++;
      break;
    case 4:
      animARA = (XAL2/5)%4;
      LCD_Sprite(XAL2,156,41,44,spider,4,animARA,1,0);
      V_line(XAL2-1, 156, 44, 0x00);
      V_line(XAL2-2, 156, 44, 0x00);
      V_line(XAL2-3, 156, 44, 0x00);
      V_line(XAL2-4, 156, 44, 0x00);
      XAL2=XAL2+5;
      ARANA3=0;
      break;
  }
}
void ARANAR2(void){
  switch (ARANA4){
    case 0:
      animARA = (XAR2/5)%4;
      LCD_Sprite(XAR2,156,41,44,spider,4,animARA,0,0);
      V_line(XAR2+42, 156, 44, 0x00);
      V_line(XAR2+43, 156, 44, 0x00);
      V_line(XAR2+44, 156, 44, 0x00);
      V_line(XAR2+45, 156, 44, 0x00);
      V_line(XAR2+46, 156, 44, 0x00);
      XAR2=XAR2-5;
      ARANA4++;
      break;
    case 1:
      animARA = (XAR2/5)%4;
      LCD_Sprite(XAR2,156,41,44,spider,4,animARA,0,0);
      V_line(XAR2+42, 156, 44, 0x00);
      V_line(XAR2+43, 156, 44, 0x00);
      V_line(XAR2+44, 156, 44, 0x00);
      V_line(XAR2+45, 156, 44, 0x00);
      V_line(XAR2+46, 156, 44, 0x00);
      XAR2=XAR2-5;
      ARANA4++;
      break;
    case 2:
      animARA = (XAR2/5)%4;
      LCD_Sprite(XAR2,156,41,44,spider,4,animARA,0,0);
      V_line(XAR2+42, 156, 44, 0x00);
      V_line(XAR2+43, 156, 44, 0x00);
      V_line(XAR2+44, 156, 44, 0x00);
      V_line(XAR2+45, 156, 44, 0x00);
      V_line(XAR2+46, 156, 44, 0x00);
      XAR2=XAR2-5;
      ARANA4++;
      break;
    case 3:
      animARA = (XAR2/5)%4;
      LCD_Sprite(XAR2,156,41,44,spider,4,animARA,0,0);
      V_line(XAR2+42, 156, 44, 0x00);
      V_line(XAR2+43, 156, 44, 0x00);
      V_line(XAR2+44, 156, 44, 0x00);
      V_line(XAR2+45, 156, 44, 0x00);
      V_line(XAR2+46, 156, 44, 0x00);
      XAR2=XAR2-5;
      ARANA4++;
      break;
    case 4:
      animARA = (XAR2/5)%4;
      LCD_Sprite(XAR2,156,41,44,spider,4,animARA,0,0);
      V_line(XAR2+42, 156, 44, 0x00);
      V_line(XAR2+43, 156, 44, 0x00);
      V_line(XAR2+44, 156, 44, 0x00);
      V_line(XAR2+45, 156, 44, 0x00);
      V_line(XAR2+46, 156, 44, 0x00);
      XAR2=XAR2-5;
      ARANA4=0;
      break;
  }
}

//********************************************************************JEFE******************************************************************
void BOSS_LEFT(void){
  switch (BOSSL){
    case 0:
      animBOSS = (XBL/10)%2;
      LCD_Sprite(XBL,250,57,60,boss,2,animBOSS,0,0);
      V_line(XBL-1, 250, 60, 0x00);
      V_line(XBL-2, 250, 60, 0x00);
      V_line(XBL-3, 250, 60, 0x00);
      V_line(XBL-4, 250, 60, 0x00);
      V_line(XBL-5, 250, 60, 0x00);
      V_line(XBL-6, 250, 60, 0x00);
      XBL=XBL+5;
      BOSSL++;
      break;
    case 1:
      animBOSS = (XBL/10)%2;
      LCD_Sprite(XBL,250,57,60,boss,2,animBOSS,0,0);
      V_line(XBL-1, 250, 60, 0x00);
      V_line(XBL-2, 250, 60, 0x00);
      V_line(XBL-3, 250, 60, 0x00);
      V_line(XBL-4, 250, 60, 0x00);
      V_line(XBL-5, 250, 60, 0x00);
      V_line(XBL-6, 250, 60, 0x00);
      XBL=XBL+5;
      BOSSL++;
      break;
    case 2:
      animBOSS = (XBL/10)%2;
      LCD_Sprite(XBL,250,57,60,boss,2,animBOSS,0,0);
      V_line(XBL-1, 250, 60, 0x00);
      V_line(XBL-2, 250, 60, 0x00);
      V_line(XBL-3, 250, 60, 0x00);
      V_line(XBL-4, 250, 60, 0x00);
      V_line(XBL-5, 250, 60, 0x00);
      V_line(XBL-6, 250, 60, 0x00);
      XBL=XBL+5;
      BOSSL=0;
      break;
  }
}
void BOSS_RIGHT(void){
  switch (BOSSR){
    case 0:
      animBOSS = (XBR/10)%2;
      LCD_Sprite(XBR,250,57,60,boss,2,animBOSS,1,0);
      V_line(XBR+58, 250, 60, 0x00);
      V_line(XBR+59, 250, 60, 0x00);
      V_line(XBR+60, 250, 60, 0x00);
      V_line(XBR+61, 250, 60, 0x00);
      V_line(XBR+62, 250, 60, 0x00);
      V_line(XBR+63, 250, 60, 0x00);
      XBR=XBR-5;
      BOSSR++;
      break;
    case 1:
      animBOSS = (XBR/10)%2;
      LCD_Sprite(XBR,250,57,60,boss,2,animBOSS,1,0);
      V_line(XBR+58, 250, 60, 0x00);
      V_line(XBR+59, 250, 60, 0x00);
      V_line(XBR+60, 250, 60, 0x00);
      V_line(XBR+61, 250, 60, 0x00);
      V_line(XBR+62, 250, 60, 0x00);
      V_line(XBR+63, 250, 60, 0x00);
      XBR=XBR-5;
      BOSSR++;
      break;
    case 2:
      animBOSS = (XBR/10)%2;
      LCD_Sprite(XBR,250,57,60,boss,2,animBOSS,1,0);
      V_line(XBR+58, 250, 60, 0x00);
      V_line(XBR+59, 250, 60, 0x00);
      V_line(XBR+60, 250, 60, 0x00);
      V_line(XBR+61, 250, 60, 0x00);
      V_line(XBR+62, 250, 60, 0x00);
      V_line(XBR+63, 250, 60, 0x00);
      XBR=XBR-5;
      BOSSR=0;
      break;
  }
}
//****************************************************************FUNCION DISPARO************************************************************************************
void BALAL(void){
  switch (BALA){
    case 0:
    animBULLET =(XBAL/5)%1;
      LCD_Sprite(XBAL,YBLB,3,3,bullet,1,animBULLET,0,0);
       V_line(XBAL+4, YBLB, 3, 0x00);
       V_line(XBAL+5, YBLB, 3, 0x00);
       V_line(XBAL+6, YBLB, 3, 0x00);
       V_line(XBAL+7, YBLB, 3, 0x00);
       V_line(XBAL+8, YBLB, 3, 0x00);
      XBAL=XBAL-5;
      break;
  }
}
void BALAR (void){
  switch (BALA2){
    case 0:
      animBULLET =(XBAL2/5)%1;
      LCD_Sprite(XBAL2,YBLB,3,3,bullet,1,animBULLET,0,0);
       V_line(XBAL2-1, YBLB, 3, 0x00);
       V_line(XBAL2-2, YBLB, 3, 0x00);
       V_line(XBAL2-3, YBLB, 3, 0x00);
       V_line(XBAL2-4, YBLB, 3, 0x00);
       V_line(XBAL2-5, YBLB, 3, 0x00);
      XBAL2=XBAL2+5;
      break;
  }
}
//*******************************************************************FUNCION BALA LANCE******************************************************************************
void BALALL(void){
  switch (BALA3){
    case 0:
    animBULLET =(XBAB/5)%1;
      LCD_Sprite(XBAB,YBLL,3,3,bullet,1,animBULLET,0,0);
       V_line(XBAB+4, YBLL, 3, 0x00);
       V_line(XBAB+5, YBLL, 3, 0x00);
       V_line(XBAB+6, YBLL, 3, 0x00);
       V_line(XBAB+7, YBLL, 3, 0x00);
       V_line(XBAB+8, YBLL, 3, 0x00);
      XBAB=XBAB-5;
      break;
  }
}
void BALARL (void){
  switch (BALA4){
    case 0:
      animBULLET =(XBAB2/5)%1;
      LCD_Sprite(XBAB2,YBLL,3,3,bullet,1,animBULLET,0,0);
       V_line(XBAB2-1, YBLL, 3, 0x00);
       V_line(XBAB2-2, YBLL, 3, 0x00);
       V_line(XBAB2-3, YBLL, 3, 0x00);
       V_line(XBAB2-4, YBLL, 3, 0x00);
       V_line(XBAB2-5, YBLL, 3, 0x00);
      XBAB2=XBAB2+5;
      break;
  }
}

//*******************************************************************FUNCIONES PARA VIDA*****************************************************************************
void VIDASB(void){
  if(LIFEB==3){
    LCD_Sprite(2,2,8,16,lives,2,0,0,0);
    LCD_Sprite(12,2,8,16,lives,2,0,0,0);
    LCD_Sprite(22,2,8,16,lives,2,0,0,0);
  }
  if(LIFEB==2){
    LCD_Sprite(2,2,8,16,lives,2,0,0,0);
    LCD_Sprite(12,2,8,16,lives,2,0,0,0);
    FillRect(22,2,8,16,0x00);
  }
  if(LIFEB==1){
    LCD_Sprite(2,2,8,16,lives,2,0,0,0);
    FillRect(12,2,8,16,0x00);
  }
  if(LIFEB==0){
    FillRect(2,2,8,16,0x00);
    MUERTEB();
  }
}
void VIDASL(void){
  if(LIFEL==3){
    LCD_Sprite(310,2,8,16,lives,2,1,0,0);
    LCD_Sprite(300,2,8,16,lives,2,1,0,0);
    LCD_Sprite(290,2,8,16,lives,2,1,0,0);
  }
  if(LIFEL==2){
    LCD_Sprite(290,2,8,16,lives,2,1,0,0);
    LCD_Sprite(300,2,8,16,lives,2,1,0,0);
    FillRect(310,2,8,16,0x00);
  }
  if(LIFEL==1){
    LCD_Sprite(290,2,8,16,lives,2,1,0,0);
    FillRect(300,2,8,16,0x00);
  }
  if(LIFEL==0){
    FillRect(290,2,8,16,0x00);
    MUERTEL ();
  }
}
