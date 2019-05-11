/*
bsed on
 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:

#include <LiquidCrystal.h>
#include <Wire.h>
#include <ClosedCube_HDC1080.h>
#include <Adafruit_CCS811.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);   // RS E DB4 DB5 DB6 DB7

///////
//HDC1080 Low Power High Accuracy Digital I2C Humidity and Temperature sensor
//Hardware connections for Arduino Uno:
//VDD to 3.3V DC
//SCL to A5
//SDA to A4
//GND to common ground
ClosedCube_HDC1080 hdc1080;

//CCS811 air quality sensor
//CCS811 - 0x5A
Adafruit_CCS811 ccs;
///////


void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("init ");
  
// Serial.begin(9600);
// Serial.println("HDC1080 and CCS811 test");
  
  // Default settings: 
  //  - Heater off
  //  - 14 bit Temperature and Humidity Measurement Resolutions
  //lcd.setCursor(0, 1);
  lcd.print("hdc1080 sensor");
  hdc1080.begin(0x40);
  delay(400);

//  Serial.print("Manufacturer ID=0x");
//  Serial.println(hdc1080.readManufacturerId(), HEX); // 0x5449 ID of Texas Instruments
//  Serial.print("Device ID=0x");
//  Serial.println(hdc1080.readDeviceId(), HEX); // 0x1050 ID of the device
	
  printSerialNumber();
  
  lcd.setCursor(0, 1);
  lcd.print("CCS811 sensor ");
  delay(200);

  
  if(!ccs.begin()){
//    Serial.println("Failed to start CCS811 sensor! Please check your wiring.");
    while(1);
  }
  
  //calibrate temperature sensor
  while(!ccs.available());
  float temp = ccs.calculateTemperature();
  ccs.setTempOffset(temp - 25.0);
  
  lcd.clear();
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 0);
  double T = hdc1080.readTemperature();
  double RH = hdc1080.readHumidity();
  lcd.print("");lcd.print(T,1);
  lcd.print("C RH=");lcd.print(RH,1);lcd.print("%");
  
//  Serial.print("T=");
//	Serial.print(T);
//	Serial.print("C, RH=");
//	Serial.print(RH);
//	Serial.println("%");
  delay(5000);
  
  float temp = 0.0;
  float CO2 = 0.0;
  float TVOC = 0.0;
  //общие летучие органические соединения; ОЛОС (total volatile organic compound;
  
  lcd.setCursor(0,1);
  
  if(ccs.available()){ 
    temp = ccs.calculateTemperature();
    if(!ccs.readData()){
      CO2 = ccs.geteCO2();
      TVOC = ccs.getTVOC();
      
      lcd.print("");lcd.print(temp,1);
      lcd.print("C CO2=");lcd.print(CO2,0);lcd.print("ppm");
      
      
//      Serial.print("CO2: ");
//      Serial.print(CO2);
//      Serial.print("ppm, TVOC: ");
//      Serial.print(TVOC);
//      Serial.print("ppb   Temp:");
//      Serial.println(temp);
    }
    else{
//      Serial.println("ERROR!");
      while(1);
    }
  }
  
  delay(5500);
}


void printSerialNumber() {
	Serial.print("Device Serial Number=");
	HDC1080_SerialNumber sernum = hdc1080.readSerialNumber();
	char format[12];
	sprintf(format, "%02X-%04X-%04X", sernum.serialFirst, sernum.serialMid, sernum.serialLast);
	Serial.println(format);
}


