#include <ESP32Servo.h>
#pragma once

#define minservos 1000
#define maxservos 2000

typedef enum {
  SERVO_GRIPPER,
  SERVO_ROTATE
} base_servo_t;

typedef enum {
  BUTTON_PRESSED,
  BUTTON_NOT_PRESSED,
  TIMER_ON,
  TIMER_OFF
} base_state_t;

void init_servo(void);
void movservo(base_servo_t, uint8_t);
void fsm_check_r1(void);
void fsm_check_l1(void);
void servoloop(void);