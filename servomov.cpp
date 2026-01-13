#include "esp32-hal-timer.h"
#include "servomov.h"

extern bool r1;
extern bool l1;
extern bool r2;
extern bool l2;

volatile uint8_t count_r1;
volatile uint8_t count_l1;
uint8_t prev_r1 = 0;
uint8_t prev_l1 = 0;

Servo servo_gripper;
Servo servo_rotate;

static base_state_t r1_state = BUTTON_NOT_PRESSED;
static base_state_t l1_state = BUTTON_NOT_PRESSED;
static base_state_t r1_timer = DORMANT;
static base_state_t l1_timer = DORMANT;

extern hw_timer_t *handle_timer_r1;

void IRAM_ATTR timer_count_r1(void){
  count_r1++;
}

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
      if(r1 && !prev_r1) { r1_state = BUTTON_PRESSED ; Serial.println("r1 ditekan 1\n"); prev_r1 = 1; }
      if(r1 && prev_r1) { r1_state = BUTTON_PRESSED ; Serial.println("r1 ditekan 2\n"); prev_r1 = 0; }
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
      if(l1 && !prev_l1) { l1_state = BUTTON_PRESSED ; Serial.println("l1 ditekan 1\n"); prev_l1 = 1; }
      if(l1 && prev_l1) { l1_state = BUTTON_PRESSED ; Serial.println("l1 ditekan 2\n"); prev_l1 = 0; }
      break;
    case BUTTON_PRESSED:
      if(!l1) l1_state = BUTTON_NOT_PRESSED;
      break;
    default:
      l1_state = BUTTON_NOT_PRESSED;
  }
}

void fsm_timer_button(){
  switch(r1_timer){
    case DORMANT:
      if(r1_state == BUTTON_PRESSED) { r1_timer = TIMER_ON; timerStart(handle_timer_r1); Serial.println("timer aktif! tunggu 2 detik!\n"); }
      break;
    case TIMER_ON:
      if( !( count_r1 % 20) ) r1_timer = TIMER_OFF;
      break;
    case TIMER_OFF:
      timerReset(handle_timer_r1); timerWrite(handle_timer_r1, 0); Serial.println("timer 2 detik sudah selesai!\nFitur aktif!\n");
      r1_timer = DORMANT;
      break;
  }
}

void servoloop(){
  fsm_check_r1();
  fsm_check_l1();
  fsm_timer_button();
}
