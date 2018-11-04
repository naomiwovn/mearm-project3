
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

int time_val = 0;
////////////////////

void setup()
{
  servo_L.attach(9);    // Left-theta Pin-9
  servo_R.attach(10);   // Right-phi Pin-10
  turn_servo.attach(6); // Turn Pin-6
  Serial.begin(9600);// Initialize serial port
  arm_move_home();
}

void loop()
{
  //save last position and move the servo to joy position
  last_pos = joy_to_pos(joy_1y_pin,last_pos);//send servo last position to move from there
  delay(100);
  
}

void move_to(Servo servo, int cur_pos, int new_pos) {
  int i = cur_pos;
  for (i = cur_pos; i < new_pos; i += 1) {
    servo.write(i);
    delay(10);
  }

}

int joy_to_pos(int pin, int last_pos) {
  int potpin = 0;
  int val;
  val = analogRead(pin);
  Serial.print("joy: ");
  Serial.println(val);
  val = map(val, 0, 1023, 0, 180);
  Serial.print("pos: ");
  Serial.println(val);
  move_to(turn_servo,last_pos,val);
  return last_pos;
}

void arm_move_home() {
  servo_R.write(r_home_p);
  servo_L.write(l_home_th);
  delay(1000);
}



