#include "servomov.h"

extern bool r1;
extern bool l1;

Servo servo_gripper;
Servo servo_rotate;

static base_state_t r1_state = BUTTON_NOT_PRESSED;
static base_state_t l1_state = BUTTON_NOT_PRESSED;

void init_servo(){
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  servo_gripper.setPeriodHertz(50);
  servo_rotate.setPeriodHertz(50);
  servo_gripper.attach(5, minservos, maxservos);
  servo_rotate.attach(25), minservos, maxservos;
}

void movservo(base_servo_t servo_name, uint8_t angle){
  if ( (angle > 180) ) angle = 180;

  switch(servo_name){
    case SERVO_GRIPPER:
      servo_gripper.write(angle);
      break;
    case SERVO_ROTATE:
      servo_rotate.write(angle);
      break;
  }
}

void fsm_check_r1(){
  switch(r1_state){
    case BUTTON_NOT_PRESSED: // Aktif Naik buat aktifin servonya
      if(r1) { r1_state = BUTTON_PRESSED ; Serial.println("r1 ditekan\n"); };
      break;
    case BUTTON_PRESSED:
      if(!r1) r1_state = BUTTON_NOT_PRESSED;
      break;
    default:
      r1_state = BUTTON_NOT_PRESSED;
  }
}

void fsm_check_l1(){
  switch(l1_state){
    case BUTTON_NOT_PRESSED: // Aktif Naik buat aktifin servonya
      if(r1) { l1_state = BUTTON_PRESSED ; Serial.println("l1 ditekan\n"); };
      break;
    case BUTTON_PRESSED:
      if(!r1) l1_state = BUTTON_NOT_PRESSED;
      break;
    default:
      l1_state = BUTTON_NOT_PRESSED;
  }
}

void servoloop(){
  fsm_check_r1();
  fsm_check_l1();
}