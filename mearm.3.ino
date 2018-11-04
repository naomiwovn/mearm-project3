#include <Servo.h>
#include <math.h>

float angle1 = 0;
float angle2 = 0;
int turnAngle = 0;
int pos_s1 = 0;
int pos_s2 = 0;


int joy_1x = A0;
int joy_1y = A1;
int joy1_p = 7;

int joy_2x = A2;
int joy_2y = A3;
int joy2_p = 8;



/////////////////
int l_max = 150;
int l_min = 40;
int r_max = 115;// forwards
int r_min = 10; // backwards
////////////////

int r = 16;
int z = 8;
int r_angle_th = 153;
int l_angle_p = 53;
int j=0;
int i = 0;
Servo servo_1;
Servo servo_2;
Servo servo_3;
Servo turn_servo;

boolean stopped = false;
int pos2 = 80;

void setup()
{
  servo_1.attach(9);
  servo_2.attach(10);
  servo_3.attach(4);
  // Initialize serial port
  pinMode(joy_1x, INPUT);
  pinMode(joy_1y, INPUT);
  pinMode(joy1_p, INPUT);
  pinMode(joy_2x, INPUT);
  pinMode(joy_2y, INPUT);
  pinMode(joy2_p, INPUT);
  digitalWrite(joy1_p, HIGH);
  Serial.begin(9600);
  servo_2.write(pos2);
}


void loop()
{

  
if(digitalRead(joy1_p) == HIGH){
  servo_3.write(180);
}else{
  servo_3.write(120);
}

if(digitalRead(joy2_p) == HIGH && stopped == false){
  while(digitalRead(joy2_p) == HIGH){
  if(pos2 < 110) pos2++;
  servo_2.write(pos2);
  delay(5);
  }
  stopped = true;
}

if(digitalRead(joy2_p) == HIGH && stopped == true){
  servo_2.write(80);
  delay(5);
  stopped = false;
}


    delay(15);
}
//##############################

void move_to(int r, int z, int turnAngle) {

}
