

#include "SPI.h"
#include "DMD.h"
#include "TimerOne.h"  
#include "Arial_black_16.h"
 
/*
 nOE(D9) |1     2| A(D6)
 Gnd     |3     4| B(D7)
 Gnd     |5     6| C
 Gnd     |6     8| CLK(D13)
 Gnd     |7    10| SCLK(D8)
 Gnd     |11   12| R(D11)
 Gnd     |13   14| G
 Gnd     |15   16| D
 ---------
 -----------------------------------------------------------------------*/

#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);
 
void ScanDMD()
{
  dmd.scanDisplayBySPI();
}
 
const byte PanelWidth = 32;
const byte MaxStringLength = 5;
char CharBuf[MaxStringLength + 1];
const byte interruptPin = 2;
const byte interruptPin1 = 3;
int val = 0;
int i=0;

 
void setup() {
  
  Timer1.initialize( 5000 );          
  Timer1.attachInterrupt( ScanDMD );  
  dmd.selectFont(Arial_Black_16);
   pinMode(interruptPin, INPUT_PULLUP);
   pinMode(interruptPin1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptPin1), blink1, RISING);
}
 
void loop() {
  
  String myString;
  val=i;
  myString= val;
  center_theDisplay(myString); delay(1000);

 
  
}
void blink() {
 if (i>=999){
    val != i;
  }
  else 
  { i++;
  }
 
}
void blink1() {

  if (i<=0){
    val != i;
  }
  else 
  { i--;
  }
}
 
void center_theDisplay(String input_Str) {
  byte charCount, total_charWidth, x_position;
  input_Str.toCharArray(CharBuf, MaxStringLength + 1); 
 
  charCount=  input_Str.length();
  if (charCount==0) exit;
 
  total_charWidth= 0;
  for (byte thisChar = 0; thisChar <charCount; thisChar++) {
    total_charWidth= total_charWidth + dmd.charWidth(CharBuf[thisChar]) +1; 
  }  
 
  total_charWidth= total_charWidth -1; 
  x_position= (PanelWidth - total_charWidth) /2; 
  dmd.clearScreen(true);
 
  for (byte thisChar = 0; thisChar <charCount; thisChar++) {
    //dmd.drawChar(x, y,‘@', GRAPHICS_NORMAL)
    dmd.drawChar( x_position,  1, CharBuf[thisChar], GRAPHICS_NORMAL );
    x_position= x_position + dmd.charWidth(CharBuf[thisChar]) + 1;
  }  
}
