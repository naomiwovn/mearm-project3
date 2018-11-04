
#include <Servo.h>
#include <math.h>

int r_min_th = 173; //extended
int l_max_p = 120;

int r_home_th = 79;
int l_home_p = 100; //center

int r_max_th = 1;
int l_min_p = 95; //retracted

int r = 16;
int z = 8;
int joy_1x = A0;
int joy_1y = A1;
int joy_1x_val;
int joy_1y_val;

int joy_2x = A2;
int joy_2y = A3;
int joy_2x_val;
int joy_2y_val;


float r_angle_p = 0;
float l_angle_th = 0;
int rotate;

int j = 0;
int i = 0;
Servo servo_l;
Servo servo_r;
Servo servo_c;
Servo servo_h;
Servo turn_servo;

void setup()
{
  servo_r.attach(10);
  servo_l.attach(9);
  servo_c.attach(8);
  servo_h.attach(7);
  // Initialize serial port

  Serial.begin(9600);
  pinMode(joy_1x, INPUT);
  pinMode(joy_1y, INPUT);

  pinMode(joy_2x, INPUT);
  pinMode(joy_2y, INPUT);


  servo_r.write(r_home_th);
  servo_l.write(l_home_p);
  delay(1000);
}

void loop()
{


  //**** Servos ****
  //r straight up = 40
  //l all back  = 120
  //max back = r5, L95
  //max forward = r173, L120
  //home = r80, L80

  //**** Joysticks ****

  joy_1y_val = analogRead(joy_1y);
  joy_2y_val = 2 + analogRead(joy_2y);
  rotate = map(joy_1x, 1, 1022, 1, 120);


  z = map(joy_1y_val, 0, 1022, 12, 0);
  r = map(joy_2y_val, 0, 1022, 0, 12);

  r=8;
  z=2;

  r_angle_p = (2 * atan(z / r) + acos(r / sqrt(pow(r, 2) + pow(z, 2)))) * (180 / 3.1416);
  l_angle_th =  160-(-1 * acos(r / sqrt(pow(r, 2) + pow(z, 2))) - atan(z / r)) * (180 / 3.1416);

  r = 6*cos(l_angle_th-160)+6*cos(r_angle_p);
  Serial.println(r);

  Serial.print("r:");
  Serial.print(r);
  Serial.print(" z:");
  Serial.print(z);
  Serial.print(" theta:");
  Serial.print(l_angle_th);
  Serial.print(" phi:");
  Serial.print(r_angle_p);
  Serial.print(" rotation:");
  Serial.print(rotate);
  Serial.println();

  if(r_angle_p < 125 && l_angle_th > 35){
    servo_r.write(r_angle_p);
    servo_l.write(l_angle_th);
  }

  delay(10);


  //    delay(1000);


}

//##############################

void move_to(int r, int z, int turnAngle) {

}

