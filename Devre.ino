#include <Arduino.h>
#include <TinyMPU6050.h>
#include <Servo.h>

float pos_offset = 10;
float neg_offset = -10;
long angle_x, angle_y, angle_z, offset_x, offset_y, offset_z;
MPU6050 mpu (Wire);
Servo myservo;
int var;

void setup() {

  // Kurulum
  mpu.Initialize();
	myservo.attach(9);
	var =10; //Maks. 180

  //Kalibrasyon
  Serial.begin(9600);
  Serial.println("=====================================");
  Serial.println("Kalibrasyon Basladi...");
  Serial.println("Kalibrasyon Tamamlandi!");
  Serial.println("Ofsetler:");
  Serial.print("AccX Ofseti = ");
  Serial.println(mpu.GetAccXOffset());
  Serial.print("AccY Ofseti = ");
  Serial.println(mpu.GetAccYOffset());
  Serial.print("AccZ Ofseti = ");
  Serial.println(mpu.GetAccZOffset());
  Serial.print("GyroX Ofseti = ");
  Serial.println(mpu.GetGyroXOffset());
  Serial.print("GyroY Ofseti = ");
  Serial.println(mpu.GetGyroYOffset());
  Serial.print("GyroZ Ofseti = ");
  Serial.println(mpu.GetGyroZOffset());
  pinMode(14,OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(14, LOW);
  digitalWrite(9, LOW);

  delay(1000);
  for(int i=0; i<200;i++){
   mpu.Execute();
  offset_x = mpu.GetAngX();
  offset_y = mpu.GetAngY();
  offset_z = mpu.GetAngZ();
  }
  Serial.print("offset_x = ");
  Serial.print(offset_x);
  Serial.print("  /  offsetY = ");
  Serial.print(offset_y);
  Serial.print("  /  offsetZ = ");
  Serial.println(offset_z);
  
}

void loop() {

 for(int i=0; i<5;i++){
  mpu.Execute();
  angle_x = mpu.GetAngX();
  angle_y = mpu.GetAngY();
  angle_z = mpu.GetAngZ();
 }

  Serial.print("AngX = ");
  Serial.print(angle_x - offset_x);
  Serial.print("  /  AngY = ");
  Serial.print(angle_y - offset_y);
  Serial.print("  /  AngZ = ");
  Serial.println(angle_z - offset_z);
  

 if ( pos_offset < angle_x - offset_x || neg_offset > angle_x - offset_x || pos_offset < angle_y - offset_y || neg_offset > angle_y - offset_y || pos_offset < angle_z - offset_z || neg_offset > angle_z - offset_z)//Bu k?sma yorum yok :){

  for(int i=0; i<50; i++){
	myservo.write(val);
  delay(50);
  }   
  delay(5000);  
  mpu.Execute();
  offset_x = mpu.GetAngX();
  offset_y = mpu.GetAngY();
  offset_z = mpu.GetAngZ();

 }  
}

