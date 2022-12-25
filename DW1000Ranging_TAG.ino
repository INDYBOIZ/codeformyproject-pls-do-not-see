
\
#include <SPI.h>
#include "DW1000Ranging.h"
#include <Wire.h>
#include <MechaQMC5883.h>
#include <Keypad.h>

MechaQMC5883 qmc;

const byte ROWS = 1; 
const byte COLS = 3; 
char hexaKeys[ROWS][COLS] = {
  {'1','2','3'}
};
byte rowPins[ROWS] = {25}; 
byte colPins[COLS] = {13, 14, 15}; 

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

#define SPI_SCK 18
#define SPI_MISO 19
#define SPI_MOSI 23
#define DW_CS 4
#define PI 3.1415926535897932384626433832795

// connection pins
const uint8_t PIN_RST = 27; // reset pin
const uint8_t PIN_IRQ = 34; // irq pin
const uint8_t PIN_SS = 4;   // spi select pin

float Distant = 0;
float DISTANT = 0;
float DISTANT1 = 0;
float DISTANT2 = 0;
int Anchor = 0;

float a = 0;
float b = 0;
float c = 0;
float d = 0;
float e = 0;

float f = 0;
float g = 0;
float h = 0;
float i = 0;
float j = 0;

float X = 0; 
float Y = 0;

void setup()
{
    Wire.begin();
    Serial.begin(115200);
    delay(1000);
    qmc.init();
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
    DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ);
    DW1000Ranging.attachNewRange(newRange);
    DW1000Ranging.attachNewDevice(newDevice);
    DW1000Ranging.attachInactiveDevice(inactiveDevice);

    DW1000Ranging.startAsTag("7D:00:22:EA:82:60:3B:9C", DW1000.MODE_LONGDATA_RANGE_LOWPOWER);

}

void loop()
{
    DW1000Ranging.loop();
}

void newRange()
{
    Distant = (DW1000Ranging.getDistantDevice()->getRange());
    DISTANT = (Distant-0.5083)/1.257;
    //Serial.print("from: ");
    //Serial.print(DW1000Ranging.getDistantDevice()->getShortAddress());
    Anchor = (DW1000Ranging.getDistantDevice()->getShortAddress());
    //Serial.print(" ");
    
    if (Anchor == 6018 ){
      DISTANT1 = DISTANT;
      }
    else if (Anchor == 6275 ){
      DISTANT2 = DISTANT;
      }
      
    Serial.print("NO.9: ");
    Serial.print(DISTANT1);
    Serial.print("  ");
    Serial.print("NO.8: ");
    Serial.print(DISTANT2);
    Serial.print("  ");

    a = DISTANT1;
    b = DISTANT2;
    c = 0.7;         //<-------scale of room

    d =(a*a+c*c-b*b)/(2*a*c);
    e =sqrt(1-(d*d));
    
    Y =e*DISTANT1;
    X =d*DISTANT1;
    Serial.print("  X ");
    Serial.print(X);
    Serial.print("  ");
    Serial.print("  Y ");
    Serial.print(Y);
    Serial.print("  ");
   
    int x, y, z;
    int azimuth;
    qmc.read(&x, &y, &z,&azimuth);
    Serial.print(" a: ");
    Serial.print(azimuth);
    Serial.println();

 char customKey = customKeypad.getKey();
 //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<insert command here<<<<<<<<<<<<<<<<<<<
    if (customKey == '1'){  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<insert command 1 here<<<<<<<<<<<<<<<<<<<
    Serial.println("1");
        if (azimuth >= 350 || azimuth <= 10 ){
        tone(2, 1000,500);
        delay(1000); 
        tone(2, 1000,500);
        delay(1000); 
        }
        if (azimuth < 350 && azimuth > 190 ){
        tone(2, 1000,100);
        delay(1000); 
        tone(2, 1000,500);
        delay(1000); 
        }
        if (azimuth > 10 && azimuth < 170 ){
        tone(2, 1000,500);
        delay(1000); 
        tone(2, 1000,100);
        delay(1000); 
        }
        if (azimuth <= 190 && azimuth >= 170 ){
        tone(2, 1000,100);
        delay(1000); 
        tone(2, 1000,100);
        delay(1000); 
        }
    }
    if (customKey == '2'){ //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<insert command 2 here<<<<<<<<<<<<<<<<<<<
    Serial.println("2");
    if (X <= 0.40 && X >= 0.3 && Y <= 0.40 && Y >= 0.30 ){
        tone(2, 1000,500);
        delay(1000); 
        tone(2, 1000,500);
        delay(1000); 
        tone(2, 1000,500);
        delay(1000);   
      }
    if (X <= 0.30 && Y <= 0.30){
      f=0.3-X;
      g=0.3-Y;
      h = atan(f/g);
      h = h*180/PI;
      Serial.println(h);
      i = h+10;
      j = h-10;
      if (azimuth >= j && azimuth <= i ){
        tone(2, 1000,500);
        delay(1000); 
        tone(2, 1000,500);
        delay(1000); 
        }
      if (azimuth < j){
        tone(2, 1000,500);
        delay(1000); 
        tone(2, 1000,100);
        delay(1000); 
        }
      if (azimuth > i){
        tone(2, 1000,100);
        delay(1000); 
        tone(2, 1000,500);
        delay(1000); 
        }
      }
     if (X <= 0.30 && Y >= 0.40){
        f=0.3-X;
        g=0.3-Y;
        h = atan(f/g);
        h = h*180/PI;
        h = 360-h;
        Serial.println(h);
        i = h+10;
        j = h-10;
       if (azimuth >= j && azimuth <= i ){
        tone(2, 1000,500);
        delay(1000); 
        tone(2, 1000,500);
        delay(1000); 
        }
      if (azimuth < j){
        tone(2, 1000,500);
        delay(1000); 
        tone(2, 1000,100);
        delay(1000); 
        }
      if (azimuth > i){
        tone(2, 1000,100);
        delay(1000); 
        tone(2, 1000,500);
        delay(1000); 
        }
      }
      if (X >= 0.40 && Y <= 0.30){
      f=0.3-X;
      g=0.3-Y;
      h = atan(f/g);
      h = h*180/PI;
      h = 180-h;
      Serial.println(h);
      i = h+10;
      j = h-10;
      if (azimuth >= j && azimuth <= i ){
        tone(2, 1000,500);
        delay(1000); 
        tone(2, 1000,500);
        delay(1000); 
        }
      if (azimuth < j){
        tone(2, 1000,500);
        delay(1000); 
        tone(2, 1000,100);
        delay(1000); 
        }
      if (azimuth > i){
        tone(2, 1000,100);
        delay(1000); 
        tone(2, 1000,500);
        delay(1000); 
        }
      }
      if (X >= 0.40 && Y >= 0.40){
      f=0.3-X;
      g=0.3-Y;
      h = atan(g/f);
      h = h*180/PI;
      h = 180+h;
      Serial.println(h);
      i = h+10;
      j = h-10;
      if (azimuth >= j && azimuth <= i ){
        tone(2, 1000,500);
        delay(1000); 
        tone(2, 1000,500);
        delay(1000); 
        }
      if (azimuth < j){
        tone(2, 1000,500);
        delay(1000); 
        tone(2, 1000,100);
        delay(1000); 
        }
      if (azimuth > i){
        tone(2, 1000,100);
        delay(1000);M 
        tone(2, 1000,500);
        delay(1000); 
        }
      }
    }
    if (customKey == '3'){ //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<insert command 3 here<<<<<<<<<<<<<<<<<<<
    Serial.println("3");
    if (X <= 1.60 && X >= 1.40 && Y <= 1.60 && Y >= 1.40 ){
        tone(2, 1000,500);
        delay(1000); 
        tone(2, 1000,500);
        delay(1000); 
        tone(2, 1000,500);
        delay(1000);   
      }
    if (X <= 1.40 && Y <= 1.40){
      X=f;
      Y=g;
      f=1.4-f;
      g=1.4-g;
      h = atan(f/g);
      Serial.println(h);
      h = h*180/PI;
      i = h+10;
      j = h-10;
      if (azimuth >= j && azimuth <= i ){
        tone(2, 1000,500);
        delay(1000); 
        tone(2, 1000,500);
        delay(1000); 
        }
      if (azimuth < j){
        tone(2, 1000,500);
        delay(1000); 
        tone(2, 1000,100);
        delay(1000); 
        }
      if (azimuth > i){
        tone(2, 1000,100);
        delay(1000); 
        tone(2, 1000,500);
        delay(1000); 
        }
      }
     if (X <= 1.40 && Y >= 1.60){
        X=f;
        Y=g;
        f=1.4-f;
        g=1.4-g;
        h = atan(f/g);
        Serial.println(h);
         h = h*180/PI;
         h = 360-h;
        i = h+10;
        j = h-10;
       if (azimuth >= j && azimuth <= i ){
        tone(2, 1000,500);
        delay(1000); 
        tone(2, 1000,500);
        delay(1000); 
        }
      if (azimuth < j){
        tone(2, 1000,500);
        delay(1000); 
        tone(2, 1000,100);
        delay(1000); 
        }
      if (azimuth > i){
        tone(2, 1000,100);
        delay(1000); 
        tone(2, 1000,500);
        delay(1000); 
        }
      }
      if (X >= 1.60 && Y <= 1.40){
      X=f;
      Y=g;
      f=1.4-f;
      g=1.4-g;
      h = atan(f/g);
      Serial.println(h);
      h = h*180/PI;
      h = 180-h;
      i = h+10;
      j = h-10;
      if (azimuth >= j && azimuth <= i ){
        tone(2, 1000,500);
        delay(1000); 
        tone(2, 1000,500);
        delay(1000); 
        }
      if (azimuth < j){
        tone(2, 1000,500);
        delay(1000); 
        tone(2, 1000,100);
        delay(1000); 
        }
      if (azimuth > i){
        tone(2, 1000,100);
        delay(1000); 
        tone(2, 1000,500);
        delay(1000); 
        }
      }
      if (X >= 1.60 && Y >= 1.60){
      X=f;
      Y=g;
      f=1.4-f;
      g=1.4-g;
      h = atan(g/f);
      Serial.println(h);
      h = h*180/PI;
      h = 180+h;
      i = h+10;
      j = h-10;
      if (azimuth >= j && azimuth <= i ){
        tone(2, 1000,500);
        delay(1000); 
        tone(2, 1000,500);
        delay(1000); 
        }
      if (azimuth < j){
        tone(2, 1000,500);
        delay(1000); 
        tone(2, 1000,100);
        delay(1000); 
        }
      if (azimuth > i){
        tone(2, 1000,100);
        delay(1000); 
        tone(2, 1000,500);
        delay(1000); 
        }
      }
  }
}

void newDevice(DW1000Device *device)
{
    Serial.print("ranging init; 1 device added ! -> ");
    Serial.print(" short:");
    Serial.println(device->getShortAddress(), HEX);
}

void inactiveDevice(DW1000Device *device)
{
    Serial.print("delete inactive device: ");
    Serial.println(device->getShortAddress(), HEX);
}
