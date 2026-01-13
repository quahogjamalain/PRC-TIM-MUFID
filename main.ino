#include "movement.h"
#include "servomov.h"

void setup() {
  init_servo();
  inisialisasi_motor();
  ps3_init();
}

void loop() {
  motormov();
  servoloop();
  delay(50);
}
