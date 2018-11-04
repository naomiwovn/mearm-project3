
#include <Servo.h>
#include <math.h>

float angle1 = 0;
float angle2 = 0;
int turnAngle = 0;
int pos_s1 = 0;
int pos_s2 = 0;

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
Servo turn_servo;

void setup()
{
  servo_1.attach(9);
  servo_2.attach(10);
  // Initialize serial port
  Serial.begin(9600);

  
}

void loop()
{
  //Equations to calculate servo position for a given r & z coordinate
  //r_angle_th = 180+(-acos(r / (sqrt(r ^ 2 + z ^ 2))) - atan(z / r))*180/3.1416;
  //l_angle_p = (2 * atan(z / r) + acos(r / sqrt(r ^ 2 + z ^ 2)))*180/3.1416;
  
  int r_min_th = 173;
  int l_max_p = 120;

  int r_home_th = 80;
  int l_home_p = 80;

  int r_max_th = 30;
  int l_min_th = 120;

  //move home
  servo_2.write(r_home_th);
  servo_1.write(l_home_p);
  delay(1000);
  
  //move to max extend
  servo_2.write(r_min_th);
  servo_1.write(l_max_p);
  delay(1000);

  //move to min extend
  servo_2.write(r_max_th);
  servo_1.write(l_min_th);
  delay(1000);

}

