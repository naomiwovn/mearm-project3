
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
int l_max = 150;
int l_min = 40;
int r_max = 115;// forwards
int r_min = 10; // backwards
//////////////////////

///////Test Values////
int r_ext_p = 173; //extend
int l_ext_th = 120;

int r_home_p = 80; //center
int l_home_th = 80;

int r_ret_p = 30;  // retracted
int l_ret_th = 120;
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
////////////////////

void setup()
{
  servo_L.attach(servo_Lpin);    // Left-theta Pin-9
  servo_R.attach(servo_Rpin);   // Right-phi Pin-10
  turn_servo.attach(turn_servo_pin); // Turn Pin-6
  Serial.begin(9600);// Initialize serial port

}

void loop()
{
  j1y_pos = joy_to_pos(joy_1y_pin);

  if (j1y_pos < 90) {
    move_down(turn_servo, j1y_pos, joy_1y_pin);
  }
  else if (j1y_pos > 90) {
    move_up(turn_servo, j1y_pos, joy_1y_pin);
  }
  else {
    turn_servo.write(90);
  }

  delay(100);
}

void move_up(Servo servo, int pos, int joy_pin) {
  int i = 90;
  for (i = 90; i < pos; i++) {
    servo.write(i);
    delay(10);
  }
  while (pos > 90) {
    pos = joy_to_pos(joy_pin);
    servo.write(pos);
  }
}

void move_down(Servo servo, int pos, int joy_pin) {
  int i = 90;
  for (i = 90; i > pos; i--) {
    servo.write(i);
    delay(10);
  }

  while (pos < 90) {
    pos = joy_to_pos(joy_pin);
    servo.write(pos);
  }

}


int joy_to_pos(int joy_pin) {
  int potpin = 0;
  int val;
  val = analogRead(joy_pin);
  Serial.print("joy: ");
  Serial.println(val);
  val = map(val, 0, 1023, 0, 180);
  Serial.print("pos: ");
  Serial.println(val);
  //  move_to(turn_servo, val);
  return val;
}

void arm_move_home() {
  servo_R.write(r_home_p);
  servo_L.write(l_home_th);
  delay(1000);
}
