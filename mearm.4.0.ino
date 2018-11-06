

#include <Servo.h>
#include <math.h>

///////Joysticks///////
int joy_1x_pin = A0;
int joy_1y_pin = A1;
int joy_1x_val;
int joy_1y_val;

int joy_2x_pin = A2;
int joy_2y_pin = A3;
int joy_2x_val;
int joy_2y_val;
//////////////////////


///////Bounds//////////
//int l_max = 150;
//int l_min = 40;
//int r_max = 115;// forwards
//int r_min = 10; // backwards
//////////////////////

///////Test Values////
//int r_ext_p = 173; //extend
//int l_ext_th = 120;
//
int r_home_p = 80; //center
int l_home_th = 80;
//
//int r_ret_p = 30;  // retracted
//int l_ret_th = 120;
//////////////////////

//////Servos/////////
Servo servo_L;
Servo servo_R;
Servo turn_servo;
int servo_Lpin = 9;
int servo_Rpin = 10;
int turn_servo_pin = 6;

int last_pos = 0;
int j1y_pos = 0;
int j1x_pos = 0;

int r_angle_p;
int l_angle_th;
////////////////////

/////Absolute Distance////
int l = 80;
int zmin = -60;
int zmax = 78;

int rmin = 4;
int rmax = 156;

int r;
int z;

int z_atrmax = 0;
int r_atzmax = 78;
int z_atrmin = 0;
int r_atzmin = 78;
//////////////////////////

void setup()
{
  servo_L.attach(servo_Lpin);    // Left-theta Pin-9
  servo_R.attach(servo_Rpin);   // Right-phi Pin-10
  turn_servo.attach(turn_servo_pin); // Turn Pin-6
  Serial.begin(9600);// Initialize serial port

}

void loop()
{

  //turn_servo_move(joy_1x_pin);
  arm_move_home();

  r = 156;
  z = 0;
  
  move_arm(r,z);
  delay(1000);

  r=10;
  z=72;
  move_arm(r,z);

  
//////////////////////////


}
void move_arm(int r, int z){
  
//  if (r >= rmax) {
//    r = rmax;
//    z = z_atrmax;
//  }
//  else if (z >= zmax) {
//    z = zmax;
//    r = r_atzmax;
//  }
//  else if (r <= rmin) {
//    r = rmin;
//    z = z_atrmin;
//  }
//  else if (z <= zmin) {
//    z = zmin;
//    r = r_atzmin;
//  }

////////////////////////////

  //r_angle_p = 120-(2 * atan(z / r) + acos(r / sqrt(pow(r, 2) + pow(z, 2)))) * 180 / 3.1416;
  //l_angle_th = 180 - (-acos(r / (sqrt(pow(r, 2) + pow(z, 2)))) - atan(z / r)) * 180 / 3.1416;

  r_angle_p = 8*(2*(atan(z/r))+2*acos((pow(r,2)+pow(l,2))/(2*pow(l,2)))-1)* (180 / 3.1416);
  l_angle_th = 180-(acos(((pow(r,2)+pow(l,2))/(2*pow(l,2)))-1)-atan(z/r))* (180 / 3.1416);
  

  //r_angle_p = acos((pow(r,2)+pow(l,2)/(2*pow(l,2)))-1)-atan(z/r)* 180 / 3.1416;
  //l_angle_th = 180-2*atan(z/r)+2*acos((pow(r,2)+pow(l,2)/(2*pow(l,2)))-1)* 180 / 3.1416;
  
  // The left arm cannot go past the right arm. Theres a screw blocking a certain
  // distance so the left arm cannot go within 17 degrees of the right arm
  delay(15);

  
  if (l_angle_th > r_angle_p-15) {
    l_angle_th = 180-r_angle_p-15 ;
  }

  if (l_angle_th > 140){
    l_angle_th = 140;
  }


  Serial.print(r);
  Serial.print(",");
  Serial.print(z);
  Serial.print("--rphi: ");
  Serial.print(r_angle_p);

  Serial.print(" ltheta: ");
  Serial.print(l_angle_th);
  Serial.println();

  delay(1000);
  //move to min extend
  servo_R.write(r_angle_p);
  servo_L.write(l_angle_th);
  delay(1000);

}

void turn_servo_move(int joy_1x_pin) {

  j1x_pos = joy_to_pos(joy_1x_pin);
  delay(10);
  if (j1x_pos < 90) {
    move_right(turn_servo, j1x_pos, joy_1x_pin);
  }
  if (j1x_pos > 90) {
    move_left(turn_servo, j1x_pos, joy_1x_pin);
  }

}

void move_left(Servo servo, int pos, int joy_pin) {
  int i = 90;
  for (i = 90; i < pos; i += 2) {
    servo.write(i);
    delay(10);
  }

  pos = joy_to_pos(joy_pin);
  delay(100);
  while (pos > 91) {
    pos = joy_to_pos(joy_pin);
    servo.write(i);
    delay(15);
  }
}

void move_right(Servo servo, int pos, int joy_pin) {
  int i = 90;
  for (i = 90; i > pos; i -= 2) {
    servo.write(i);
    delay(10);
  }

  pos = joy_to_pos(joy_pin);
  delay(100);
  while (pos < 89) {
    pos = joy_to_pos(joy_pin);
    servo.write(i);
    delay(15);
  }

}

int joy_to_pos(int joy_pin) {
  int val;
  val = analogRead(joy_pin);
  Serial.print("joy: ");
  Serial.println(val);
  val = map(val, 0, 1023, 0, 180);
  Serial.print("pos: ");
  Serial.println(val);
  return val;
}

void arm_move_home() {
  servo_R.write(r_home_p);
  servo_L.write(l_home_th);
  delay(1000);
}
