#include <HX711.h>
#include <DS3231.h>
#include <Servo.h>
#define DOUT 2
#define CLK 3
#define pinServoAtas 4
#define pinServoBawah 5
HX711 scale;
DS3231 rtc(SDA, SCL);
Servo servoAtas;
Servo servoBawah;
float calibration_factor = 380000;
float berat;
int posisi;
String mode = "waktu";
void setup(){
 Serial.begin(9600);
 scale.begin(DOUT, CLK);
 scale.set_scale(calibration_factor);
 scale.tare();
 rtc.begin();
servoAtas.attach(pinServoAtas);
servoBawah.attach(pinServoBawah);
servoAtas.write(30);
servoBawah.write(8); 
}
void loop(){
if(mode == "waktu"){
 String waktu = rtc.getTimeStr();
 Serial.println(waktu);
 if(waktu == "07:00:00" || waktu =="16:00:00"
 servoAtas.write(75);
 mode = "timbang";
 } else {
 delay(300);
 }
 } else
 if(mode == "timbang"){
 berat = scale.get_units(10);
 Serial.print(berat);
Serial.println(" kg");
 if(berat>=0.05){
 servoAtas.write(30);
 mode = "kutah";
}
} else
 if(mode == "kutah"){
 delay(1000);
for(posisi=10; posisi<144; posisi+=2){
 servoBawah.write(posisi);
 }
 delay(500);
 servoBawah.write(8);
 delay(500);
 mode = "waktu";
 }
} 