// Arduino pin numbers
#include<Wire.h>
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t GyX,GyY;

const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output
int direction = 0;
int gyro; 
int incomingbyte;
int buzzerPin = 7;


void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);

  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
}

void loop() {
//  Serial.print("Switch:  ");
//  Serial.print(digitalRead(SW_pin));
//  Serial.print(direction);
//  Serial.print("\n");

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers


  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)

  if(GyY < -5000){ 
    gyro = 4; 
    Serial.print("up");
  }

  if(GyY > 5000){
    gyro = 3;
    Serial.print("down");
  }

  if(GyX < -5000){
    gyro = 2;
    Serial.print("right");
  }

  if(GyX > 5000){
    gyro = 1;
    Serial.print("left");
  }

  
  delay(1);

  if(Serial.available() > 0){
  incomingbyte = Serial.read();
  }

  if(incomingbyte == 'B'){
    Serial.print("B received");
    incomingbyte = 69;
    digitalWrite(buzzerPin, HIGH);
    delay(1000);
    digitalWrite(buzzerPin, LOW);
  }

  
  
//  Serial.print("X-axis: ");
  if( ((analogRead(X_pin)) > 412) && ((analogRead(X_pin)) < 572) && ((analogRead(Y_pin)) > 430) && ((analogRead(Y_pin)) < 590) ) {
//    Serial.print(analogRead(X_pin));
//    Serial.print("\n center");
      //direction = 0;
      //Serial.print(direction);
  }
  
  else if((analogRead(X_pin)) < 412){
//    Serial.print(analogRead(X_pin));
//    Serial.print("\n right");
      direction = 2; 
      Serial.print("right");
  }
  
  else if((analogRead(X_pin)) > 572){
//    Serial.print(analogRead(X_pin));
//    Serial.print("\n left");
      direction = 1;
      Serial.print("left");
  }  
  else if((analogRead(Y_pin)) > 590){
//    Serial.println(analogRead(Y_pin));
//    Serial.println(" up");
      direction = 4;
      Serial.print("up");
   }

   else if((analogRead(Y_pin)) < 430){
//    Serial.println(analogRead(Y_pin));
//    Serial.println(" down");
      direction = 3;
      Serial.print("down");
   }

  delay(200);
}
