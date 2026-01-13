#include <Ps3Controller.h>
#include <math.h>
#include "pindef.h"
#include "fsm.h"
#include "movement.h"

int16_t ly;
int16_t lx;
int16_t rx;

int32_t M1;
int32_t M2;
int32_t M3;
int32_t M4;

static fsm_state_quadrant_t current_state = IDLE;

void inisialisasi_motor(void){
  ledcAttachChannel(M1A, FREQ, RES, 15);
  ledcAttachChannel(M1B, FREQ, RES, 14);
  ledcAttachChannel(M2A, FREQ, RES, 13);
  ledcAttachChannel(M2B, FREQ, RES, 12);
  ledcAttachChannel(M3A, FREQ, RES, 11);
  ledcAttachChannel(M3B, FREQ, RES, 10);
  ledcAttachChannel(M4A, FREQ, RES, 9);
  ledcAttachChannel(M4B, FREQ, RES, 8);

  ledcWrite(M1A, 0);
  ledcWrite(M1B, 0);
  ledcWrite(M2A, 0);
  ledcWrite(M2B, 0);
  ledcWrite(M3A, 0);
  ledcWrite(M3B, 0);
  ledcWrite(M4A, 0);
  ledcWrite(M4B, 0);
}

void ps3_fetch(void){
  ly = Ps3.data.analog.stick.ly * -1;
  lx = Ps3.data.analog.stick.lx;
  rx = Ps3.data.analog.stick.rx * theta;

  if(abs(ly) <= deadzone) ly = 0; // Saat nilai ga sampe threshold maka diwrite 0, biar ga drift
  if(abs(lx) <= deadzone) lx = 0;
  if(abs(rx) <= deadzone) rx = 0;

  switch(current_state){
    case IDLE:
      if(isQuadrant1()) current_state = QUADRANT_1;
      else if(isQuadrant2()) current_state = QUADRANT_2;
      else if(isQuadrant3()) current_state = QUADRANT_3;
      else if(isQuadrant4()) current_state = QUADRANT_4;
      else current_state = IDLE;
      break;
  }
}

void kineval(void){
  ps3_fetch();

  switch(current_state){
    case QUADRANT_1:
      M1 = lambda * (  rx + sqrt( (ly + lx)^2 ) );
      M2 = lambda * ( rx + sqrt( ( ly + (-1*lx) )^2 ) );
      M3 = lambda * ( ( -1.0*rx ) + ly + ( -1*lx ) );
      M4 = lambda * ( ( -1.0*rx ) + ly + lx );
      current_state = IDLE;
      break;
    
    case QUADRANT_1:

      current_state = IDLE;
      break;
    
    case QUADRANT_1:

      current_state = IDLE;
      break;
    
    case QUADRANT_1:

      current_state = IDLE;
      break;
  }
  
  M1 = lambda * (  rx + ly + lx );
  M2 = lambda * ( rx + ly + (-1.0 * lx) );
  M3 = lambda * ( ( -1.0 * rx ) + ly + ( -1.0 * lx ) );
  M4 = lambda * ( ( -1.0 * rx ) + ly + lx );
  
  Serial.printf("M1 cooked : %d | M2 cooked : %d | M3 cooked : %d | M4 cooked : %d\n\
    lx : %d | ly : %d | rx : %d\n", M1, M2, M3, M4, lx, ly, rx);
}

void motormov(void){
  kineval();
// MOTOR 1
  if (M1 > 0) {
    ledcWrite(M1A, M1);
    ledcWrite(M1B, 0);
  } else if (M1 < 0) {
    ledcWrite(M1B, abs(M1));
    ledcWrite(M1A, 0);
  } else {
    ledcWrite(M1A, 0);
    ledcWrite(M1B, 0);
  }

// MOTOR 2
  if (M2 > 0) {
    ledcWrite(M2A, M2);
    ledcWrite(M2B, 0);
  } else if (M2 < 0) {
    ledcWrite(M2B, abs(M2));
    ledcWrite(M2A, 0);
  } else {
    ledcWrite(M2A, 0);
    ledcWrite(M2B, 0);
  }

// MOTOR 3
  if (M3 > 0) {
    ledcWrite(M3A, M3);
    ledcWrite(M3B, 0);
  } else if (M3 < 0) {
    ledcWrite(M3B, abs(M3));
    ledcWrite(M3A, 0);
  } else {
    ledcWrite(M3A, 0);
    ledcWrite(M3B, 0);
  }

// MOTOR 4
  if (M4 > 0) {
    ledcWrite(M4A, M4);
    ledcWrite(M4B, 0);
  } else if (M4 < 0) {
    ledcWrite(M4B, abs(M4));
    ledcWrite(M4A, 0);
  } else {
    ledcWrite(M4A, 0);
    ledcWrite(M4B, 0);
  }
}

void ps3_init(void){
  Serial.begin(115200);
  Ps3.begin(MACADDR);

}



