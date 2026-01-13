#include "fsm.h"

extern uint16_t ly;
extern uint16_t lx;

bool isQuadrant1(){
  if( (ly >= 0) && (lx >= 0) ) return true;
  else false;
}

bool isQuadrant2(){
  if( (ly >= 0) && (lx <= 0) ) return true;
  else false;
}

bool isQuadrant3(){
  if( (ly <= 0) && (lx <= 0) ) return true;
  else false;
}

bool isQuadrant4(){
  if( (ly <= 0) && (lx >= 0) ) return true;
  else false;
}

bool isIdle(){
  if(!(ly && lx)) return true;
  else false;
}
